
// opencv_mfc_imgload.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "opencv_mfc_imgload.h"
#include "opencv_mfc_imgloadDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;

// CopencvmfcimgloadApp

BEGIN_MESSAGE_MAP(CopencvmfcimgloadApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CopencvmfcimgloadApp 생성

CopencvmfcimgloadApp::CopencvmfcimgloadApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CopencvmfcimgloadApp 개체입니다.

CopencvmfcimgloadApp theApp;


// CopencvmfcimgloadApp 초기화

BOOL CopencvmfcimgloadApp::InitInstance()
{
	CWinApp::InitInstance();
	CopencvmfcimgloadDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

