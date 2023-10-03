
// spyChatDlg.h: 헤더 파일
//

#pragma once
#include "CRGB_Dlg.h"


// CspyChatDlg 대화 상자
class CspyChatDlg : public CDialogEx
{
// 생성입니다.
public:
	CspyChatDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPYCHAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_r_color, m_g_color, m_b_color;
	CListBox m_chat_list;
	CString m_add_data;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeList3();
	CStatic m_static_text;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_RedSlider;
	CSliderCtrl m_GreenSlider;
	CSliderCtrl m_BlueSlider;
	CBrush	m_bk_brush;
	CRGB_Dlg m_setting_color;
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton2();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void ChangeParentWnodowColor(int r, int g, int b);
};
