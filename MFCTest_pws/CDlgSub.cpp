// CDlgSub.cpp: 구현 파일
//

#include "pch.h"
#include "MFCTest_pws.h"
#include "afxdialogex.h"
#include "CDlgSub.h"

#define nWidthDlg		1024
#define nHeightDlg		768


// CDlgSub 대화 상자

IMPLEMENT_DYNAMIC(CDlgSub, CDialogEx)

CDlgSub::CDlgSub(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgSub, pParent)
{

}

CDlgSub::~CDlgSub()
{
}

void CDlgSub::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSub, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgSub 메시지 처리기


BOOL CDlgSub::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, nWidthDlg, nHeightDlg);

	InitSub();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgSub::InitSub()
{
	int nBpp = 8;

	m_image.Create(nWidthDlg, -nHeightDlg, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidthDlg * nHeightDlg);
}


void CDlgSub::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
}

CImage& CDlgSub::GetImage()
{
	return m_image;
}
