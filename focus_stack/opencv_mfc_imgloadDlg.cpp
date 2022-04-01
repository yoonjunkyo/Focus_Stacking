#include "pch.h"
#include "framework.h"
#include "opencv_mfc_imgload.h"
#include "opencv_mfc_imgloadDlg.h"
#include "afxdialogex.h"
#include "FocusStack.h"
#include "Gray2Color.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CopencvmfcimgloadDlg 대화 상자

CopencvmfcimgloadDlg::CopencvmfcimgloadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCV_MFC_IMGLOAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CopencvmfcimgloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PC_VIEW, m_picture);
	DDX_Control(pDX, IDC_PC_VIEW2, m_picture_2);
	DDX_Control(pDX, IDC_COMBO, m_combo);
}

BEGIN_MESSAGE_MAP(CopencvmfcimgloadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IAMGELOAD, &CopencvmfcimgloadDlg::OnBnClickedBtnIamgeload)
	ON_BN_CLICKED(IDC_BTN_COLOR, &CopencvmfcimgloadDlg::OnBnClickedBtnColor)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CopencvmfcimgloadDlg::OnBnClickedButtonColor)
	ON_BN_CLICKED(IDC_BTN_DNS, &CopencvmfcimgloadDlg::OnBnClickedBtnDns)
	ON_BN_CLICKED(IDC_BTN_SHARP, &CopencvmfcimgloadDlg::OnBnClickedBtnSharp)
END_MESSAGE_MAP()


// CopencvmfcimgloadDlg 메시지 처리기

BOOL CopencvmfcimgloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	SetWindowText(_T("Focused image of SEM"));

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_combo.InsertString(0,_T("AUTUMN"));
	m_combo.InsertString(1, _T("BONE"));
	m_combo.InsertString(2, _T("JET"));
	m_combo.InsertString(3, _T("WINTER"));
	m_combo.InsertString(4, _T("RAINBOW"));
	m_combo.InsertString(5, _T("OCEAN"));
	m_combo.InsertString(6, _T("SUMMER"));
	m_combo.InsertString(7, _T("SPRING"));
	m_combo.InsertString(8, _T("COOL")); 
	m_combo.InsertString(9, _T("HSV"));
	m_combo.InsertString(10, _T("PINK"));
	m_combo.InsertString(11, _T("HOT"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CopencvmfcimgloadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CopencvmfcimgloadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CopencvmfcimgloadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CopencvmfcimgloadDlg::CreateBitmapInfo(Mat mat_frame, HDC ah_dc)
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	int bpp = 8 * mat_frame.elemSize();
	//int bpp = 8 * mat_frame.channels();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
		padding = 4 - (mat_frame.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
	{
		border = 4 - (mat_frame.cols % 4);
	}

	Mat mat_temp;
	if (border > 0 || mat_frame.isContinuous() == false)
	{
		// Adding needed columns on the right (max 3 px)
		cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat_frame;
	}

	RECT r;
	m_picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	cimage_mfc.Create(winSize.width, winSize.height, 24);

	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;

	//그레이스케일 인경우 팔레트가 필요
	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}

	int destx = 0, desty = 0;
	int destw = winSize.width;
	int desth = winSize.height;

	// rectangle defined on source bitmap
	// using imgWidth instead of mat_temp.cols will ignore the padding border
	int imgx = 0, imgy = 0;
	int imgWidth = mat_temp.cols - border;
	int imgHeight = mat_temp.rows;

	HDC h_dc = cimage_mfc.GetDC();
	SetStretchBltMode(h_dc,COLORONCOLOR);
	StretchDIBits(h_dc,
		destx, desty, destw, (destw* imgHeight)/ imgWidth,
		imgx, imgy, imgWidth, imgHeight,
		mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);

	cimage_mfc.BitBlt(ah_dc, 0, 0);
	::ReleaseDC(m_picture.m_hWnd, ah_dc);
	::ReleaseDC(m_picture_2.m_hWnd, ah_dc);
	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();
}

/*Image Load*/

void CopencvmfcimgloadDlg::OnBnClickedBtnIamgeload()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();

		CT2CA pszString(path);
		string strPath(pszString);

		m_matImage = imread(strPath, IMREAD_UNCHANGED);

		FocusStack focus;
		focus.focusstack(m_matImage, m_stack_img, m_stack_cpy);

		HDC dc = ::GetDC(m_picture.m_hWnd);
		HDC dc_stack = ::GetDC(m_picture_2.m_hWnd);
		CreateBitmapInfo(m_stack_cpy,dc);
		CreateBitmapInfo(m_stack_img,dc_stack);
		
		MessageBox(L"완료", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
	}
}


/*Colorization*/

void CopencvmfcimgloadDlg::OnBnClickedBtnColor()
{
	m_gray2color_img = m_stack_img.clone();
	Mat m_color;
	
	int g = GetDlgItemInt(IDC_EDIT_GREEN, NULL);
	int b = GetDlgItemInt(IDC_EDIT_BLUE, NULL);			
	int r = GetDlgItemInt(IDC_EDIT_RED, NULL);

	Gray2Color graytocolor;
	Mat result = graytocolor.gray2color(m_gray2color_img, m_color);
	
	HDC dc_color = ::GetDC(m_picture_2.m_hWnd);
	CreateBitmapInfo(result, dc_color);
	MessageBox(L"완료", L"알림", MB_OKCANCEL | MB_ICONINFORMATION);
}

void CopencvmfcimgloadDlg::OnBnClickedButtonColor()
{
	int idx = m_combo.GetCurSel();
	if (CB_ERR != idx) {
		m_gray2color_img = m_stack_img.clone();

		CString sSel;
		m_combo.GetLBText(idx, sSel);
		MessageBox(sSel);
		Mat im_color;
		applyColorMap(m_gray2color_img, im_color, idx+1);

		HDC dc_color = ::GetDC(m_picture_2.m_hWnd);
		CreateBitmapInfo(im_color, dc_color);
	}
}

/*Denoise*/

void CopencvmfcimgloadDlg::OnBnClickedBtnDns()
{
	medianBlur(m_stack_img, m_stack_img, 3);
	HDC dc_color = ::GetDC(m_picture_2.m_hWnd);
	CreateBitmapInfo(m_stack_img, dc_color);
}


void CopencvmfcimgloadDlg::OnBnClickedBtnSharp()
{
	float weights[9] = { -1,-1, -1, -1, 9 ,-1, -1, -1, -1 };
	Mat mask = Mat(3, 3, CV_32F, weights);
	filter2D(m_stack_img, m_stack_img, -1, mask, Point(-1, -1), 0, BORDER_DEFAULT);
	HDC dc_color = ::GetDC(m_picture_2.m_hWnd);
	CreateBitmapInfo(m_stack_img, dc_color);
}
