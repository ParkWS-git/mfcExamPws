
// MFCTest_pwsDlg.h: 헤더 파일
//
#include "CDlgSub.h"
#pragma once

// CMFCTestpwsDlg 대화 상자
class CMFCTestpwsDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCTestpwsDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgSub* m_pDlgImage;	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_PWS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_nXStart;
	int m_nYStart;
	int m_nXEnd;
	int m_nYEnd;
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnDestroy();
	void DrawCircle(int x, int y, int radius);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	BOOL validImgPos(int x, int y);
	void ImageSave();
	void ImageLoad();
	CString FindFilepath();
	int m_nCountCircle;
};
