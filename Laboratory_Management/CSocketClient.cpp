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
	m_pListenSocket = pSocket; // ���� ����Ʈ�� �����ϱ� ���ؼ� Listen ������ �ּҸ� �����صд�.
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
	fprintf(fp, "netsh -c int ip set address name=\"�̴���\" source=static address=%s mask=255.255.252.0 gateway=10.10.55.254\n", ip.c_str());
	fprintf(fp, "netsh -c interface ip set dnsservers \"�̴���\" static 203.246.80.1\n");
	fclose(fp);
	ShellExecute(NULL, NULL, filePath, 0, 0, SW_HIDE);
	return 1;
}
void CSocketClient::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString tmp = "", strIPAddress = "";
	UINT uPortNumber = 0;
	//char szBuffer[BUFFER_SIZE];
	struct MESG szBuffer;
	::ZeroMemory(&szBuffer, sizeof(szBuffer));
	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(&szBuffer, BUFFER_SIZE) > 0) {
		CSocketListen* pServerSocket = (CSocketListen*)m_pListenSocket;
		//�޼��� ���ź�
		std::string msg = (char *)&szBuffer;
		if (msg == "PowerOFF")
			system("shutdown -s -t 1");
		else if (msg.find("IPConfig") != std::string::npos) {
			SetCustomIP(msg.substr(8));
		}
//		pServerSocket->SendOrderResultDataAll((char *)&szBuffer); // �� Ŭ���̾�Ʈ�� ���� ���� �޽����� ��� Ŭ���̾�Ʈ���� �����Ѵ�.
	}

	CSocket::OnReceive(nErrorCode);
}