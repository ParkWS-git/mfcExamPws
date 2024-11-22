#pragma once
#include "afxdialogex.h"


// CDlgSub 대화 상자

class CDlgSub : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSub)

public:
	CDlgSub(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgSub();

	CImage m_image;
	CImage& GetImage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgSub };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitSub();
	afx_msg void OnPaint();
};
