#include"stdafx.h"
#include"CConnectSocket.h"
#define BUFFER_SIZE 1024
using namespace std;

void CConnectSocket::reloadConnected() {
}

struct MESG {
	char user[1];
	char sbuf[1024];
};

CConnectSocket::CConnectSocket()
{
}


CConnectSocket::~CConnectSocket()
{
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//char szBuffer[BUFFER_SIZE];
	char szBuffer[BUFFER_SIZE];
	::ZeroMemory(szBuffer, BUFFER_SIZE);
	if (Receive(szBuffer, BUFFER_SIZE))
	{
		if (strlen(szBuffer) > BUFFER_SIZE);
		else {
			string str = szBuffer;
			//수신
			//m_Chat.AddString(str.c_str());
		}
	}

	CSocket::OnReceive(nErrorCode);
}

void CConnectSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();
	CSocket::OnClose(nErrorCode);
	AfxMessageBox("서버와 연결이 종료되었습니다.");
	::PostQuitMessage(0);
}