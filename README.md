# YUV422 display

This program shows frames of YUV movie (read from stdin), in which each line is multiplexed 4:2:2 component video (Cb Y Cr Y...) format. The program has two versions, in C++ and Python, and uses [OpenCV](https://opencv.org) library (tested on 2.4.10).

Usage:
```
yuv422_display WIDTH HEIGHT [NUM-IGNORE-LAST-BYTES] [DISPLAY-SCALE]
           WIDTH  - width of a frame
           HEIGHT - height of a frame
           NUM-IGNORE-LAST-BYTES  - optional; number of bytes to in a movie stream (in case of 
                                    concatenated video and audio raw, see bmdcapture); 
                                    default: 0
           DISPLAY-SCALE          - optional; scaling factor for displayed image; 
                                    default: 1.0
```
Example: `cat movie.yuv | yuv422_display 720 576`
