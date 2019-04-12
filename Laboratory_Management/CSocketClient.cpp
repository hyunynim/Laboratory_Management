#include "stdafx.h"
#include "CSocketClient.h"
#include"CSocketListen.h"
#include"Laboratory_ManagementDlg.h"
using namespace std;
const char * filePath = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\ipconfig.bat";
struct MESG {
	char user[1];
	char sbuf[1024];
};


CSocketClient::CSocketClient()
{
}


CSocketClient::~CSocketClient()
{
}

void CSocketClient::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket; // 소켓 리스트에 접근하기 위해서 Listen 소켓의 주소를 저장해둔다.
}

void CSocketClient::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	CSocketListen* pServerSocket = (CSocketListen*)m_pListenSocket;
	pServerSocket->CloseClientSocket((CSocketListen*)this);
}
bool SetCustomIP(std::string ip) {
	FILE * fp = fopen(filePath, "w");
	if (fp == NULL) return 0;
	fprintf(fp, "netsh -c int ip set address name=\"이더넷\" source=static address=%s mask=255.255.252.0 gateway=10.10.55.254\n", ip.c_str());
	fprintf(fp, "netsh -c interface ip set dnsservers \"이더넷\" static 203.246.80.1\n");
	fclose(fp);
	ShellExecute(NULL, NULL, filePath, 0, 0, SW_HIDE);
	return 1;
}
void CSocketClient::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString tmp = "", strIPAddress = "";
	UINT uPortNumber = 0;
	//char szBuffer[BUFFER_SIZE];
	struct MESG szBuffer;
	::ZeroMemory(&szBuffer, sizeof(szBuffer));
	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(&szBuffer, BUFFER_SIZE) > 0) {
		CSocketListen* pServerSocket = (CSocketListen*)m_pListenSocket;
		//메세지 수신부
		std::string msg = (char *)&szBuffer;
		if (msg == "PowerOFF")
			system("shutdown -s -t 1");
		else if (msg.find("IPConfig") != std::string::npos) {
			SetCustomIP(msg.substr(8));
		}
//		pServerSocket->SendOrderResultDataAll((char *)&szBuffer); // 한 클라이언트로 부터 받은 메시지를 모든 클라이언트에게 전송한다.
	}

	CSocket::OnReceive(nErrorCode);
}