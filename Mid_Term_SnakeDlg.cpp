
// Mid_Term_SnakeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Mid_Term_Snake.h"
#include "Mid_Term_SnakeDlg.h"
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


// CMidTermSnakeDlg 대화 상자



CMidTermSnakeDlg::CMidTermSnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MID_TERM_SNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMidTermSnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMidTermSnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMidTermSnakeDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EAT_COUNT_EDIT, &CMidTermSnakeDlg::OnEnChangeEatCountEdit)
	ON_EN_CHANGE(IDC_playTime, &CMidTermSnakeDlg::OnEnChangeEatCountEdit2)
	ON_EN_CHANGE(IDC_playTime, &CMidTermSnakeDlg::OnEnChangeplaytime)
END_MESSAGE_MAP()


void CMidTermSnakeDlg::MAP()
{
	m_draw_dc.SelectStockObject(DC_BRUSH);
	m_draw_dc.SelectStockObject(DC_PEN);
	m_draw_dc.SetDCPenColor(RGB(102, 0, 88)); // 격자색 설정

	for (int y = 0; y < 60; y++)  // 화면 크기에 따른 격자 생성
	{
		for (int x = 0; x < 80; x++)
		{
			if (m_count_map[y][x] > 0) // 뱀이 먹이를 먹으면 1 이상으로 간다.
			{
				m_count_map[y][x]--; // 그려지면서 1씩 감소하면서 뱀의 잔상을 구현한다. 0이되면 그위치에 다시 검은색으로 되게

				if (m_count_map[y][x] == 0) m_table[y][x] = 0; // 카운트를 지우다가 0이되면 검은색이
			}

			m_draw_dc.SetDCBrushColor(m_table[y][x]); 
			m_draw_dc.Rectangle(x * 15, y * 15, x * 15 + 16, y * 15 + 16); // 격자 크기 조정
		}
	}

	DrawFood(); // 먹이 그리는 함수 호출하여 화면에 먹이 출력
}

// 랜덤 함수로 먹이 만드는 함수 구현

void CMidTermSnakeDlg::DrawFood()
{
	// 메모리 DC 생성
	CDC memDC;
	memDC.CreateCompatibleDC(&m_draw_dc);

	// 비트맵 이미지 선택
	CBitmap* pOldBitmap = memDC.SelectObject(&m_bmpFood);
	BITMAP bmpInfo;
	m_bmpFood.GetBitmap(&bmpInfo);

	//  격자 크기 안에서 먹이(파란색)을 생성하고 이 위치에 비트맵 이미지로 먹이 그리기
	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			if (m_table[y][x] == RGB(255, 255, 255)) // 테이블에서 흰색(먹이)인 경우 설정
			{
				
				m_draw_dc.TransparentBlt(x * 15, y * 15, 15, 15, &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255)); // 이미지를 불러온다.
			}
		}
	}
	
	memDC.SelectObject(pOldBitmap);
}


void CMidTermSnakeDlg::StopGame()
{
	KillTimer(1);
	KillTimer(2);
	MessageBox(_T("GAME OVER"));
}

void CMidTermSnakeDlg::ClearGame()
{
	KillTimer(1);
	KillTimer(2);
	MessageBox(_T("Congratuation Game Clear !!"));
}









// CMidTermSnakeDlg 메시지 처리기

BOOL CMidTermSnakeDlg::OnInitDialog()
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

	m_draw_image.Create(801, 601, 32); // 32색상을 쓰는 대화상자 비트맵 800*600의 크기
	m_draw_dc.Attach(m_draw_image.GetDC()); // 메모리 dc 사용 물어보기


	srand((unsigned int)time(NULL));   //랜덤 함수로 먹이 구현
	int x, y;
	for (int i = 0; i < 150; i++)
	{
		x = rand() % 53;  //격자 칸수  (800 / 15 = 53.33, 소수점을 버린 값)
		y = rand() % 40;   
		if (m_table[y][x] == 0 ) m_table[y][x] = RGB( 255,255,255); // 중복된 값 처리
		else i--;
	}
	
	// 비트맵 이미지 로드
	m_bmpFood.LoadBitmap(IDB_BITMAP1);
	

	MAP();
	
	SetTimer(1, 200, NULL); // 0.2초마다 타이머 발생

	// 플레이 타임 나타내기 TImer 분산
	SetTimer(2, 1000, NULL); // 1초마다 타이머 이벤트 발생

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMidTermSnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMidTermSnakeDlg::OnPaint()
{
	CPaintDC dc(this);

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
		m_draw_image.Draw(dc, 0, 0); // 만들어진 이미지 출력
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMidTermSnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMidTermSnakeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_draw_dc.Detach();
	m_draw_image.ReleaseDC(); // dc 해제하는코드

	KillTimer(1); //게임이 끝나고 타이머도 같이 꺼진다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMidTermSnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) 
	{
		if (m_direction == 0)      m_pos.x--; // left  뱀의 위치를 구현 
		else if (m_direction == 1) m_pos.y--; // up
		else if (m_direction == 2) m_pos.x++; // right
		else if (m_direction == 3) m_pos.y++; // down


		if (m_pos.x >= 0 && m_pos.x <= 79 && m_pos.y >= 0 && m_pos.y <= 59)  // 울타리 범위 제한
		{
			if (m_table[m_pos.y][m_pos.x] == RGB(255, 255, 255)) //뱀이  먹이를 먹은 상황 
			{
				m_eat_count++; // 먹은것으로 간주
				SetDlgItemInt(IDC_EAT_COUNT_EDIT, m_eat_count);


				if (m_eat_count == 15) // 먹이 15개를 먹었을 때 게임 클리어
				{
					ClearGame();
					return;
				}

			}
			else if (m_table[m_pos.y][m_pos.x] != 0) // 경우 자신의 꼬리에 닿고 게임 오바
			{
				
				StopGame();
				return;
			}
			if (m_pos.x < 0 || m_pos.x >= 53 || m_pos.y < 1 || m_pos.y >= 40) // 뱀이 경기장 울타리에 부딪혔을때 게임오버
			{
				StopGame();
				return;
			}

			m_table[m_pos.y][m_pos.x] = RGB(71, 200, 62); // 이동한 위치에서 뱀(초록색) 을 다시 나타냄
			m_count_map[m_pos.y][m_pos.x] = m_eat_count + 2;

			MAP(); 
			
			CClientDC dc(this);
			m_draw_image.Draw(dc, 0, 0);
		}
		else 
		{
			KillTimer(1); //타이머 멈춤
			MessageBox(_T("GAME OVER"));
		}
	}
      else if (nIDEvent == 2) // 뱀 구현과 따로 해줌
	{
		// 플레이 타임 업데이트 
		m_playTime++;
		CString strPlayTime;
		strPlayTime.Format(_T(" %d 초"), m_playTime);
		SetDlgItemText(IDC_playTime, strPlayTime);

	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMidTermSnakeDlg::PreTranslateMessage(MSG* pMsg) // 대화상자에 키값을 사용하지않고 뱀게임에만 사용가능하게 하기위해서 
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam >= VK_LEFT && pMsg->wParam <= VK_DOWN)//0~3 까지 범위
		{
			m_direction = pMsg->wParam - VK_LEFT; //0123 밖에 안나온다.
			return TRUE; // 대화상자 확인 취소에 키보드 값이 안들어가게
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMidTermSnakeDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CMidTermSnakeDlg::OnEnChangeEatCountEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMidTermSnakeDlg::OnEnChangeEatCountEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMidTermSnakeDlg::OnEnChangeplaytime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
