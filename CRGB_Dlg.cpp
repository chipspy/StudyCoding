// CRGB_Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "spyChat.h"
#include "CRGB_Dlg.h"
#include "afxdialogex.h"
#include "spyChatDlg.h"


// CRGB_Dlg 대화 상자

IMPLEMENT_DYNAMIC(CRGB_Dlg, CDialogEx)

CRGB_Dlg::CRGB_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RGB_DIALOG, pParent)
{

}

CRGB_Dlg::~CRGB_Dlg()
{
}

void CRGB_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UTIL_R, m_r_s);
	DDX_Control(pDX, IDC_UTIL_G, m_g_s);
	DDX_Control(pDX, IDC_UTIL_B, m_b_s);
}


BEGIN_MESSAGE_MAP(CRGB_Dlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CRGB_Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRGB_Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRGB_Dlg 메시지 처리기


BOOL CRGB_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_r_s.SetRange(0, 255);
	m_g_s.SetRange(0, 255);
	m_b_s.SetRange(0, 255);
	    // 초기값은 0
	m_r_s.SetPos(192);
	m_g_s.SetPos(192);
	m_b_s.SetPos(192);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRGB_Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CspyChatDlg *pParent = (CspyChatDlg*)pParentWnd; /// 형변환부터

	m_rc = m_r_s.GetPos();
	m_gc = m_g_s.GetPos();
	m_bc = m_b_s.GetPos();

	pParent->ChangeParentWnodowColor(m_rc, m_gc, m_bc);
}

void CRGB_Dlg::OnBnClickedOk()
{
	CspyChatDlg* pParent = (CspyChatDlg*)pParentWnd; /// 형변환부터

	pParent->m_r_color = m_rc;
	pParent->m_g_color = m_gc;
	pParent->m_b_color = m_bc;

	CDialogEx::OnOK();	
}


void CRGB_Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CspyChatDlg* pParent = (CspyChatDlg*)pParentWnd; //부모 객체
	pParent->ChangeParentWnodowColor(pParent->m_r_color, pParent->m_g_color, pParent->m_b_color); // 부모 원래바탕ㅇ,로 되돌림

	CDialogEx::OnCancel();
}
