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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//char szBuffer[BUFFER_SIZE];
	char szBuffer[BUFFER_SIZE];
	::ZeroMemory(szBuffer, BUFFER_SIZE);
	if (Receive(szBuffer, BUFFER_SIZE))
	{
		if (strlen(szBuffer) > BUFFER_SIZE);
		else {
			string str = szBuffer;
			//����
			//m_Chat.AddString(str.c_str());
		}
	}

	CSocket::OnReceive(nErrorCode);
}

void CConnectSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ShutDown();
	Close();
	CSocket::OnClose(nErrorCode);
	AfxMessageBox("������ ������ ����Ǿ����ϴ�.");
	::PostQuitMessage(0);
}