CC=g++
CFLAGS=
LDFLAGS=-lopencv_core -lopencv_imgproc -lopencv_highgui

yuv422_loader: main.cpp yuv422_loader.cpp
	$(CC) -o yuv422_display main.cpp yuv422_loader.cpp $(CFLAGS) $(LDFLAGS)

clean:
	rm -f yuv422_display
