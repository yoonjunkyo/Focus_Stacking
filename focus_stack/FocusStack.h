#pragma once
class FocusStack
{
public:
	Mat m_dst, m_dst_lap, m_grad, m_res;
	void focusstack(Mat& a_src, Mat& a_stack_img, Mat& a_stack_cpy);
};
