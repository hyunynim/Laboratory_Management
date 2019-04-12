
// Laboratory_ManagementDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Laboratory_Management.h"
#include "Laboratory_ManagementDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_TRAY_NOTIFYICATION WM_APP+10
#define TRAY_BALLOON 1

const int maxConnectTry = 1;
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

void CLaboratoryManagementDlg::OnBnClickedDebug()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int cnt = m_ComputerList.GetSelectedCount();
	std::vector<int> selected = getSelected();

	sprintf(msg, "Item 선택 개수: %d\n선택 item: ", cnt, m_ComputerList.GetSelectedColumn());
	for (auto i : selected) {
		std::string str = m_ComputerList.GetItemText(i, 1);
		IPLIST ipTmp;
		ipTmp.ip = str;
		connectTo(ipTmp.ip, ipTmp.ipToPort());
	}
	MessageBox(msg);
	;
}
bool CLaboratoryManagementDlg::getSettings() {
	FILE * fp = fopen("setting.txt", "r");
	if (fp == NULL)
		return 0;
	std::string str;
	char msg[1234];
	while (~fscanf(fp, "%s", msg)) {
		str = msg;
		if (str == "StartIP") {
			fscanf(fp, "%s", msg);
			sscanf(msg, "%d.%d.%d.%d", &startIp[0], &startIp[1], &startIp[2], &startIp[3]);
		}
		if (str == "IpCount")
			fscanf(fp, "%d", &ipCnt);
	}
	return 1;
}
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLaboratoryManagementDlg 대화 상자



CLaboratoryManagementDlg::CLaboratoryManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABORATORY_MANAGEMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLaboratoryManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPUTER_LIST, m_ComputerList);
	DDX_Control(pDX, IDC_IPADDRESS, m_ipControl);
}

BEGIN_MESSAGE_MAP(CLaboratoryManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DEBUG, &CLaboratoryManagementDlg::OnBnClickedDebug)
	ON_NOTIFY(NM_CLICK, IDC_COMPUTER_LIST, &CLaboratoryManagementDlg::OnClickComputerList)
	ON_NOTIFY(NM_DBLCLK, IDC_COMPUTER_LIST, &CLaboratoryManagementDlg::OnDblclkComputerList)
	ON_BN_CLICKED(IDC_HIDE, &CLaboratoryManagementDlg::OnBnClickedHide)
	ON_MESSAGE(WM_TRAY_NOTIFYICATION, OnTaryNotifyAction)
	ON_COMMAND(ID_EXIT, &CLaboratoryManagementDlg::OnExit)
END_MESSAGE_MAP()


// CLaboratoryManagementDlg 메시지 처리기

BOOL CLaboratoryManagementDlg::OnInitDialog()
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
	//Socket Init
	IN_ADDR addr = GetDefaultMyIP();
	CString tmp;
	GetIpAddress(tmp);
	myIP.ip = tmp;
	sprintf(msg, "%s", inet_ntoa(addr));
//	if (initSocket(myIP.ipToPort()));
//	else
		MessageBox("Socket init Fail!");
	sprintf(msg, "IP: %s(port: %d) Socket Opened", myIP.ip.c_str(), myIP.ipToPort());
	MessageBox(msg);
	CRect rt;
	m_ComputerList.GetWindowRect(&rt);
	m_ComputerList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ComputerList.InsertColumn(0, "번호", LVCFMT_LEFT, rt.Width() * 0.15);
	m_ComputerList.InsertColumn(1, "IP", LVCFMT_LEFT, rt.Width() * 0.55);
	m_ComputerList.InsertColumn(2, "연결상태", LVCFMT_LEFT, rt.Width() * 0.3);
	if (!getSettings()) {
		MessageBox("Setting.txt 파일이 없습니다");
		exit(0);
	}
	for (int i = 0; i < ipCnt; ++i) {
		sprintf(msg, "%d", i + 1);
		m_ComputerList.InsertItem(i, msg);
		sprintf(msg, "%d.%d.%d.%d", startIp[0], startIp[1], startIp[2], startIp[3]);
		++startIp[3];
		int carry = 0;
		for (int i = 3; i >= 0; --i) {
			startIp[i] += carry;
			carry = startIp[i] / 256;
			startIp[i] %= 256;
		}
		ipList.push_back({ msg, 0 });
		m_ComputerList.SetItem(i, 1, LVIF_TEXT, msg, 0, 0, 0, 0);
		m_ComputerList.SetItem(i, 2, LVIF_TEXT, "연결대기", 0, 0, 0, 0);
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLaboratoryManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLaboratoryManagementDlg::OnPaint()
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
HCURSOR CLaboratoryManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//현재 선택한 item의 index를 받아옴
std::vector<int> CLaboratoryManagementDlg::getSelected() {
	POSITION pos = m_ComputerList.GetFirstSelectedItemPosition();
	std::vector<int> selected;
	while (pos)
		selected.push_back(m_ComputerList.GetNextSelectedItem(pos));
	return selected;
}

//list Item 클릭 시
void CLaboratoryManagementDlg::OnClickComputerList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* comList = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
}

//list Item 더블 클릭 시
void CLaboratoryManagementDlg::OnDblclkComputerList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = getSelected()[0];
	std::string ip = m_ComputerList.GetItemText(sel, 1);
	sprintf(msg, "선택한 item index: %d(ip: %s)", sel, ip.c_str());
	MessageBox(msg);
	*pResult = 0;
}


void CLaboratoryManagementDlg::OnBnClickedHide()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hWnd = m_hWnd;
	nid.hIcon = AfxGetApp()->LoadIconA(IDR_MAINFRAME);

	nid.uCallbackMessage = WM_TRAY_NOTIFYICATION;
	lstrcpy(nid.szTip, "Laboratory Management");

	::Shell_NotifyIcon(NIM_ADD, &nid);
	SetTimer(TRAY_BALLOON, 1000 * 60, 0);
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
}

LRESULT CLaboratoryManagementDlg::OnTaryNotifyAction(WPARAM wParam, LPARAM lParam) {
	switch (lParam) {
	case WM_RBUTTONDOWN:{
		CPoint pos;
		::GetCursorPos(&pos);
		CMenu menu;
		menu.LoadMenuA(IDR_MENU1);
		CMenu *pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, AfxGetMainWnd());
	}
		break;
	case WM_LBUTTONDBLCLK: {
		NOTIFYICONDATA nid;
		ZeroMemory(&nid, sizeof(nid));
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.uID = 0;
		nid.hWnd = GetSafeHwnd();

		BOOL ret = ::Shell_NotifyIcon(NIM_DELETE, &nid);
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
		KillTimer(TRAY_BALLOON);
	}
		break;
	}
	return 1;
}

void CLaboratoryManagementDlg::OnExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	exit(0);
}

bool CLaboratoryManagementDlg::initSocket(int port) {
	m_pListenSocket = new CSocketListen;
	if (m_pListenSocket->Create(port, SOCK_STREAM)) // 포트번호, TCP
	{
		if (!m_pListenSocket->Listen()) // 포트 충돌인지 검사
		{
			CString tmp;
			tmp.Format("Socket을 Listen하는데에 실패했습니다\r\n다른 프로그램에서 [포트번호 : %d] 를 사용 중인지 확인해주세요.", port);
			AfxMessageBox(tmp);
			return 0;
		}
	}
	else {
		AfxMessageBox("소켓 생성 실패");
		return 0;
	}
	return 1;
}

bool CLaboratoryManagementDlg::connectTo(std::string ip, int port) {
	CConnectSocket * pSocket = new CConnectSocket;
	pSocket->Create();
	int cnt = 0;
	while (pSocket->Connect(ip.c_str(), port) == FALSE)
		if (cnt++ == maxConnectTry)
			return 0;// 서버 연결 실패하면 프로그램 종료한다.
	connected.push_back(pSocket);
	return 1;
}

IN_ADDR CLaboratoryManagementDlg::GetDefaultMyIP() {
	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };

	if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)//호스트 이름 얻어오기
	{
		return addr;
	}
	HOSTENT *ptr = gethostbyname(localhostname);//호스트 엔트리 얻어오기
	while (ptr && ptr->h_name)
	{
		if (ptr->h_addrtype == PF_INET)//IPv4 주소 타입일 때
		{
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);//메모리 복사
			break;//반복문 탈출
		}
		ptr++;
	}
	return addr;
}
int CLaboratoryManagementDlg::GetIpAddress(CString & strIP)
{
	WSADATA WsaData;

	if (WSAStartup(0x202, &WsaData) == SOCKET_ERROR) //소켓초기화
		return false;

	char myaddr[256];
	PHOSTENT pHostInfo;
	struct sockaddr_in addr;

	//궁극적으로 ip정보가 저장될 곳
	CArray<sockaddr_in, sockaddr_in&> myIPArray;
	CString msgIP("");

	//로컬pc의 호스트이름을 표준양식으로받아옴(MSDN)
	gethostname(myaddr, sizeof(myaddr));

	//호스트이름에 대응되는Databas를 PHOSTENT구조체로 리턴
	pHostInfo = gethostbyname(myaddr);

	if (pHostInfo)//호스트데이터베이스에서ip만카피
	{
		for (int i = 0; pHostInfo->h_addr_list[i] != NULL; i++)
		{
			memcpy(&addr.sin_addr, pHostInfo->h_addr_list[i],
				pHostInfo->h_length);
			myIPArray.Add(addr);
		}
	}

	for (int i = 0; i < myIPArray.GetSize(); i++)//단순히 배열작업
	{
		msgIP = inet_ntoa(myIPArray.GetAt(i).sin_addr);
		if (msgIP.Find("10.10.") != -1) {
			strIP = msgIP;
			return 1;
		}
	}

	AfxMessageBox(msgIP);
	return 0;
}