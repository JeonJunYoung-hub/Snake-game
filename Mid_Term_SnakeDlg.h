
// Mid_Term_SnakeDlg.h: 헤더 파일
//

#pragma once


// CMidTermSnakeDlg 대화 상자
class CMidTermSnakeDlg : public CDialogEx
{
private:
	CImage m_draw_image;  //메모리 dc로 쓸 객체 라고함(기초 메모리 step 1에 있다.)
	CDC m_draw_dc;
	CBitmap m_bmpFood; // 사탕 이미지 비트맵 사용할거


	COLORREF m_table[60][80] = { 0 }; // 데이터 저장 가로80 세로60 + 색상변경까지
	int m_count_map[60][80] = { 0 };    // 뱀이 있었던 자리를 카운트로 값을 받아온다.
	POINT m_pos = { 40,30 }; // 좌표가 40,30에서 뱀의 시작위치
	int m_direction = 0; // 0이면 left , 1이면 up, 2이면, right, 3이면 down
	int m_eat_count = 0;
	int m_playTime = 0;

	
// 생성입니다.
public:
	CMidTermSnakeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	void MAP();
	void DrawFood();
	void StopGame();
	void ClearGame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MID_TERM_SNAKE_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEatCountEdit();
	afx_msg void OnEnChangeEatCountEdit2();
	afx_msg void OnEnChangeplaytime();
};
