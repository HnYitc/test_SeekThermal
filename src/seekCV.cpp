#include <thread>
#include <seek.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace LibSeek;
using namespace cv;

int main() {

	Imager iface;
	iface.init();

	Frame frame;

	iface.frame_init(frame);

	iface.frame_acquire(frame);

        int h = frame.height();
        int w = frame.width();
	Mat rawImg(Size(w, h), CV_8UC1, cv::Scalar(0,0,255));

        VideoCapture capture(0);
	Mat curr;
	Mat temp;

	while (waitKey(1) == -1){
		
		iface.frame_acquire(frame);
		h = frame.height();
		w = frame.width();
		vector<uint16_t> img(w*h);

		capture >> temp;
		resize(temp,curr,Size(),0.3,0.3,0);

		{
			int _max = 0x8250;
			int _min = 0x7e50;
			for (int y = 0; y < h; y++) {
				for (int x = 0; x < w; x++) {
					float v = float(frame.data()[y*w+x] - _min) / (_max - _min);
					
					if (v < 0.0) { v = 0; }
					if (v > 1.0) { v = 1; }
					
					rawImg.at<uchar>(y, x) = (uchar)(v*255.0);
				}
			}
			medianBlur(rawImg, rawImg, 3);
			cv::imshow("input", rawImg);
			cv::imshow("camera", curr);
		}


	}

	iface.frame_exit(frame);

	iface.exit();
}

