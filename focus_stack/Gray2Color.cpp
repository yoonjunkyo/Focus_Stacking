#include "pch.h"
#include "Gray2Color.h"

void Gray2Color::gray2color_func(Mat a_src, Mat a_dst, int a_blue, int a_green, int a_red) {
	for (int r = 0; r < a_src.rows; r++) {
		for (int c = 0; c < a_src.cols; c++) {
			a_dst.at<Vec3b>(r, c)[0] = a_src.at<uchar>(r, c) * a_blue / 255;
			a_dst.at<Vec3b>(r, c)[1] = a_src.at<uchar>(r, c) * a_green / 255;
			a_dst.at<Vec3b>(r, c)[2] = a_src.at<uchar>(r, c) * a_red / 255;
		}
	}
}
Mat Gray2Color::gray2color(Mat& a_src, Mat& a_dst) {

	Mat result;
	cvtColor(a_src, a_dst, COLOR_GRAY2BGR);
	gray2color_func(a_src, a_dst);
	a_dst.convertTo(result, -1, 1.0, 0);

	return result;
}