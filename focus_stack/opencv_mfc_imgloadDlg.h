#pragma once

// CopencvmfcimgloadDlg 대화 상자
class CopencvmfcimgloadDlg : public CDialogEx
{
// 생성입니다.
public:
	CopencvmfcimgloadDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	BITMAPINFO* m_pBitmapInfo; // Bitmap 정보를 담고 있는 구조체.
	void CreateBitmapInfo(Mat mat_frame, HDC ah_dc); // Bitmap 정보를 생성하는 함수.
	CImage cimage_mfc;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCV_MFC_IMGLOAD_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnIamgeload();
	CStatic m_picture;
	CStatic m_picture_2;
	afx_msg void OnBnClickedBtnColor();
	afx_msg void OnBnClickedButtonColor();

	CComboBox m_combo;
	Mat m_matImage; // 이미지 정보를 담고 있는 객체.
	Mat m_stack_img;
	Mat m_stack_cpy;

	Mat m_gray2color_img;
	afx_msg void OnBnClickedBtnDns();
	afx_msg void OnBnClickedBtnSharp();
};