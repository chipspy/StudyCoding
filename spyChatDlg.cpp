
// spyChatDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "spyChat.h"
#include "spyChatDlg.h"
#include "afxdialogex.h"

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


// CspyChatDlg 대화 상자



CspyChatDlg::CspyChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPYCHAT_DIALOG, pParent)
	, m_add_data(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CspyChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_chat_list);
	DDX_Text(pDX, IDC_EDIT1, m_add_data);
	DDX_Control(pDX, IDC_GET_TEXT, m_static_text);
	DDX_Control(pDX, IDC_SLIDER1, m_RedSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_GreenSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_BlueSlider);
}

BEGIN_MESSAGE_MAP(CspyChatDlg, CDialogEx)
//	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CspyChatDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST3, &CspyChatDlg::OnLbnSelchangeList3)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CspyChatDlg::OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CspyChatDlg::OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CspyChatDlg::OnCustomdrawSlider3)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CspyChatDlg::OnBnClickedButton2)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CspyChatDlg 메시지 처리기

BOOL CspyChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//// Test Code
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
	// 크기 설정
	int width= ::GetSystemMetrics(SM_CXSCREEN);
	int Height= ::GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(-10, -10, width+10, Height+10);
	// 색상 Slider 설정
	   // 범위
	//m_RedSlider.SetRange(0, 255);
	//m_GreenSlider.SetRange(0, 255);
	//m_BlueSlider.SetRange(0, 255);
	//    // 초기값은 0
	//m_RedSlider.SetPos(192);
	//m_GreenSlider.SetPos(192);
	//m_BlueSlider.SetPos(192);
	// 색깔 설정
	m_r_color = m_g_color = m_b_color = 192;
	SetBackgroundColor(RGB(m_r_color,
		m_g_color,
		m_b_color));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CspyChatDlg::OnPaint()
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
HCURSOR CspyChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CspyChatDlg::OnBnClickedButton1()
{
	UpdateData();
	int ix = m_chat_list.AddString(m_add_data);
	m_chat_list.SetCurSel(ix);
	m_add_data = L"";
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT1)->SetFocus();

}


void CspyChatDlg::OnLbnSelchangeList3()
{
	CString tmpStr;
	int ix;

	ix = m_chat_list.GetCurSel();
	m_chat_list.GetText(ix, tmpStr);
	m_static_text.SetWindowTextW(tmpStr);

}


HBRUSH CspyChatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG) return m_bk_brush;
	return hbr;
}


void CspyChatDlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}


void CspyChatDlg::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CspyChatDlg::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CspyChatDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CspyChatDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CspyChatDlg::OnBnClickedButton2()
{
	m_setting_color.m_rc = m_r_color;
	m_setting_color.m_gc = m_g_color;
	m_setting_color.m_bc = m_b_color;
	m_setting_color.pParentWnd = this;
	m_setting_color.DoModal();

	/*CRGB_Dlg* pDlg = new CRGB_Dlg;
	pDlg->Create(IDD_RGB_DIALOG);
	pDlg->m_gc = m_g_color;
	pDlg->m_gc = m_g_color;
	pDlg->m_bc = m_b_color;
	pDlg->ShowWindow(SW_SHOW);*/
}

BOOL CspyChatDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CspyChatDlg::ChangeParentWnodowColor(int r, int g, int b)
{
	// 위의 함수명이 이상하다 
	CDC* pDC = GetDC();
	
	SetBackgroundColor(RGB(r, g, b));
	return;
	
}
//
//
//   기록관리
