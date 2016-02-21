#ifndef YUV422_loader_H
#define YUV422_loader_H

#include <opencv2/core/core.hpp>

class YUV422_Loader
{
public:
    YUV422_Loader(int width, int height);

    cv::Mat* grab_uyvy_frame(char* frame_raw);

private:
    int width;
    int height;
};

#endif