
// MFCTest_pwsDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTest_pws.h"
#include "MFCTest_pwsDlg.h"
#include "afxdialogex.h"

#include "iostream"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

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


// CMFCTestpwsDlg 대화 상자



CMFCTestpwsDlg::CMFCTestpwsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_PWS_DIALOG, pParent)
	, m_nXStart(0)
	, m_nYStart(0)
	, m_nXEnd(0)
	, m_nYEnd(0)
	, m_nCountCircle(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestpwsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X_START, m_nXStart);
	DDV_MinMaxInt(pDX, m_nXStart, 0, 1023);
	DDX_Text(pDX, IDC_Y_START, m_nYStart);
	DDV_MinMaxInt(pDX, m_nYStart, 0, 767);
	DDX_Text(pDX, IDC_X_END, m_nXEnd);
	DDV_MinMaxInt(pDX, m_nXEnd, 0, 1023);
	DDX_Text(pDX, IDC_Y_END, m_nYEnd);
	DDV_MinMaxInt(pDX, m_nYEnd, 0, 767);
	DDX_Text(pDX, IDC_Count, m_nCountCircle);
}

BEGIN_MESSAGE_MAP(CMFCTestpwsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCTestpwsDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCTestpwsDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCTestpwsDlg::OnBnClickedBtnOpen)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCTestpwsDlg 메시지 처리기

BOOL CMFCTestpwsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	int nWidth = 1400;
	int nHeight = 768;
	MoveWindow(0, 0, nWidth, nHeight);

	m_pDlgImage = new CDlgSub;
	m_pDlgImage->Create(IDD_CDlgSub, this);
	m_pDlgImage->ShowWindow(SW_SHOW);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTestpwsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTestpwsDlg::OnPaint()
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
HCURSOR CMFCTestpwsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestpwsDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	int nRadius = rand() % 100;

	DrawCircle(m_nXStart, m_nYStart, nRadius);
	
	UpdateData(false);
}


void CMFCTestpwsDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	int nRadius = rand() % 100;
	int nCenterX = m_nXStart;
	int nCenterY = m_nYStart;
	int nCount = m_nCountCircle;
	int nXtemp = (m_nXEnd - m_nXStart) / nCount;
	int nYtemp = (m_nYEnd - m_nYStart) / nCount;

	for (int n = 0; n < nCount; n++) {
		DrawCircle(nCenterX, nCenterY, nRadius);
		nCenterX += nXtemp;
		nCenterY += nYtemp;
		Sleep(200);
		ImageSave();
	}
	UpdateData(false);
}

void CMFCTestpwsDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ImageLoad();

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 100;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double nCenterX = (double)nSumX / nCount;
	double nCenterY = (double)nSumY / nCount;
	
	std::cout << nCenterX << "," << nCenterY << std::endl;

	int nSize = 10;
	
	for (int j = (int)nCenterY - nSize; j < (int)nCenterY + nSize; j++) {
		for (int i = (int)nCenterX - nSize; i < (int)nCenterX + nSize; i++) {
			if (j == i) {
				fm[j * nPitch + i] = 0;
			}
		}
	}

	//CString strCoord;
	//strCoord.Format(_T("Center: (%.2f, %.2f)"), nCenterX, nCenterY);

	//CDC* pDC = m_pDlgImage->GetDC();
	//pDC->TextOut(static_cast<int>(nCenterX), static_cast<int>(nCenterY) - 20, strCoord);

	m_pDlgImage->Invalidate();
	m_pDlgImage->UpdateWindow();
}


void CMFCTestpwsDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pDlgImage)			delete m_pDlgImage;
}

void CMFCTestpwsDlg::DrawCircle(int nCenterX, int nCenterY, int radius)
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	int nRadius = radius;
	int nColor = 0xff;

	memset(fm, 0, nWidth * nHeight);

	int x = nCenterX;
	int y = nCenterY;
	fm[y * nPitch + x] = 0;
	for (int j = y - nRadius; j < y + nRadius; j++) {
		for (int i = x - nRadius; i < x + nRadius; i++) {
			if (isInCircle(i, j, x, y, nRadius)) {
				if (validImgPos(i, j))
					fm[j * nPitch + i] = nColor;
			}
		}
	}
	m_pDlgImage->Invalidate();
	m_pDlgImage->UpdateWindow();

}

bool CMFCTestpwsDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;
	double dX = i - nCenterX;
	double dY = j - nCenterY;

	if (((dX * dX) + (dY * dY)) <= (nRadius * nRadius)) {
		bRet = true;
	}

	return bRet;
}

BOOL CMFCTestpwsDlg::validImgPos(int x, int y)
{
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}


void CMFCTestpwsDlg::ImageSave()
{
	CImage& ImgSave = m_pDlgImage->GetImage();
	static int n = 0;

	CString strImageFolder = FindFilepath();
	CString filePath;

	filePath.Format(_T("%s\\ImageNo_%d.bmp"), strImageFolder, n);

	ImgSave.Save(filePath);
	n++;
}

void CMFCTestpwsDlg::ImageLoad()
{
	CString strImageFolder = FindFilepath();

	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg||"));

	dlg.m_ofn.lpstrInitialDir = strImageFolder;
	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();

		m_pDlgImage->GetImage().Destroy();
		m_pDlgImage->GetImage().Load(strFilePath);
		m_pDlgImage->Invalidate();
		m_pDlgImage->UpdateWindow();
	}
}

CString CMFCTestpwsDlg::FindFilepath()
{
	TCHAR szFilePath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString strPath = szFilePath;

	int nPos = strPath.ReverseFind(_T('\\'));
	if (nPos != -1) {
		strPath = strPath.Left(nPos);
	}

	CString strImageFolder = strPath + _T("\\image");

	if (!PathFileExists(strImageFolder)) {
		CreateDirectory(strImageFolder, NULL);
	}

	return strImageFolder;
}
