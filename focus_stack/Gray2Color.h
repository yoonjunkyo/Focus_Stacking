#pragma once
class Gray2Color
{
public:
	void gray2color_func(Mat a_src, Mat a_dst, int a_blue = 210, int a_green = 255, int a_red = 220); //�Ű����� default ��
	Mat gray2color(Mat& a_src, Mat& a_dst);
};

