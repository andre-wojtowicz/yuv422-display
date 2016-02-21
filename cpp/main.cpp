#include "yuv422_loader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <string>

#if defined(_WIN32)
#include <io.h>
#include <fcntl.h>
#endif

int main(int argc, char** argv)
{
#if defined(_WIN32)
    int result_in = _setmode(_fileno(stdin), _O_BINARY),
        result_out = _setmode(_fileno(stdout), _O_BINARY);
#if defined(_DEBUG)
    if (result_in == -1)
    {
        std::cerr << "Cannot set 'stdin' mode to binary." << std::endl;
        return -1;
    }
    else
        std::cerr << "'stdin' successfully changed to binary mode." << std::endl;

    if (result_out == -1)
    {
        std::cerr << "Cannot set 'stdout' mode to binary." << std::endl;
        return -2;
    }
    else
        std::cerr << "'stdout' successfully changed to binary mode." << std::endl;
#endif
#endif

    if (argc >= 3)
    {
        int width  = atoi(argv[1]);
        int height = atoi(argv[2]);
        int bytes_to_ign = (argc >= 4 ? atoi(argv[3]) : 0);
        float scaling_fact = (argc == 5 ? (float)atof(argv[4]) : 1.0f);

        YUV422_Loader loader(width, height);

        char* frame_raw = new char[(width * 2) * height];

        int i = 0;
        while (true)
        {
            // read next frame

            std::cin.read(frame_raw, (width * 2) * height);

            if (std::cin.eof() || std::cin.fail())
                break;

            cv::Mat* mat_frame_uyvy = loader.grab_uyvy_frame(frame_raw);

            cv::Mat mat_frame_bgr;
            cv::cvtColor(*mat_frame_uyvy, mat_frame_bgr, cv::COLOR_YUV2BGR_UYVY);

            if (scaling_fact != 1)
                cv::resize(mat_frame_bgr, mat_frame_bgr, cv::Size(), scaling_fact, scaling_fact);
            
            cv::imshow("", mat_frame_bgr);
            cv::waitKey(1);

            delete mat_frame_uyvy;
            std::cerr << ++i << std::endl;

            std::cin.read(frame_raw, bytes_to_ign);

            if (std::cin.eof() || std::cin.fail())
                break;
        }

        delete[] frame_raw;
    }
    else
    {
        std::cout << "This program shows frames of YUV movie (read from stdin), in which each line is multiplexed 4:2:2 component video (Cb Y Cr Y...) format." << std::endl << std::endl;
        std::cout << "Usage:   " << argv[0] << " WIDTH HEIGHT [NUM-IGNORE-LAST-BYTES] [DISPLAY-SCALE]" << std::endl;
        std::cout << "           WIDTH  - width of a frame" << std::endl;
        std::cout << "           HEIGHT - height of a frame" << std::endl;
        std::cout << "           NUM-IGNORE-LAST-BYTES  - optional; number of bytes to in a movie stream (in case of concatenated video and audio raw, see bmdcapture); default: 0" << std::endl;
        std::cout << "           DISPLAY-SCALE          - optional; scaling factor for displayed image; default: 1.0" << std::endl << std::endl;
        std::cout << "Example: cat movie.yuv | " << argv[0] << " 720 576" << std::endl;
    }

    return 0;
}
