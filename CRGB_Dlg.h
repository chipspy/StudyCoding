#pragma once


// CRGB_Dlg 대화 상자

class CRGB_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRGB_Dlg)

public:
	CRGB_Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRGB_Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RGB_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CWnd* pParentWnd;
	int m_rc;  //red
	int m_gc;  //green
	int m_bc;  //blue
	virtual BOOL OnInitDialog();
	CSliderCtrl m_r_s;
	CSliderCtrl m_g_s;
	CSliderCtrl m_b_s;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
