#include "pch.h"
#include "FocusStack.h"

void FocusStack::focusstack(Mat& a_src, Mat& a_stack_img, Mat& a_stack_cpy) {
	Mat m_matImage_gray;
	cvtColor(a_src, m_matImage_gray, COLOR_BGR2GRAY); //m_matImage = im1

	Mat mat_aligned;
	if (!a_stack_cpy.empty()) {
		// Define the motion model
		const int warp_mode = MOTION_AFFINE;

		// Set a 2x3 or 3x3 warp matrix depending on the motion model.
		Mat warp_matrix;
		// Initialize the matrix to identity
		warp_matrix.create(2, 3, CV_32F);
		warp_matrix = 0;
		warp_matrix.at<float>(0, 0) = 1.0f;
		warp_matrix.at<float>(1, 1) = 1.0f;
		// Specify the number of iterations.
		int number_of_iterations = 5000;

		findTransformECC(a_stack_img, m_matImage_gray, warp_matrix, cv::MOTION_AFFINE,
			TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 50, 0.001));

		// Storage for warped image.
		if (warp_mode != MOTION_HOMOGRAPHY)
			// Use warpAffine for Translation, Euclidean and Affine
			warpAffine(m_matImage_gray, mat_aligned, warp_matrix, a_stack_img.size(), INTER_LINEAR + WARP_INVERSE_MAP);
		else
			// Use warpPerspective for Homography
			warpPerspective(m_matImage_gray, mat_aligned, warp_matrix, a_stack_img.size(), INTER_LINEAR + WARP_INVERSE_MAP);
	}
	if (!mat_aligned.empty()) {
		GaussianBlur(mat_aligned, m_dst, Size(5, 5), 0, 0);
		Laplacian(m_dst, m_dst_lap, CV_16S, 3, 1, 0, BORDER_DEFAULT);
		convertScaleAbs(m_dst_lap, m_grad);
	}
	else {
		GaussianBlur(m_matImage_gray, m_dst, Size(5, 5), 0, 0);
		Laplacian(m_dst, m_dst_lap, CV_16S, 3, 1, 0, BORDER_DEFAULT);
		convertScaleAbs(m_dst_lap, m_grad);
	}

	//여기서비교
	if (!a_stack_cpy.empty()) {
		for (int r = 0; r < m_grad.rows; r++) {
			for (int c = 0; c < m_grad.cols; c++) {
				if (m_grad.at<uchar>(r, c) > a_stack_cpy.at<uchar>(r, c) && m_grad.at<uchar>(r, c) > 10) {
					a_stack_img.at<uchar>(r, c) = mat_aligned.at<uchar>(r, c);
				}
			}
		}
	}
	a_stack_cpy = m_grad.clone();

	if (a_stack_img.empty()) {
		a_stack_img = m_matImage_gray.clone();
	}
}