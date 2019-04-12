#include "stdafx.h"
#include "CSocketClient.h"
#include"CSocketListen.h"

using namespace std;

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

void CSocketClient::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString tmp = "", strIPAddress = "";
	UINT uPortNumber = 0;
	//char szBuffer[BUFFER_SIZE];
	struct MESG szBuffer;
	::ZeroMemory(&szBuffer, sizeof(szBuffer));
	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(&szBuffer, BUFFER_SIZE) > 0)
	{
		CSocketListen* pServerSocket = (CSocketListen*)m_pListenSocket;
		pServerSocket->SendOrderResultDataAll((char *)&szBuffer); // �� Ŭ���̾�Ʈ�� ���� ���� �޽����� ��� Ŭ���̾�Ʈ���� �����Ѵ�.
	}

	CSocket::OnReceive(nErrorCode);
}