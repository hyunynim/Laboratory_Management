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
	m_pListenSocket = pSocket; // 소켓 리스트에 접근하기 위해서 Listen 소켓의 주소를 저장해둔다.
}

void CSocketClient::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	CSocketListen* pServerSocket = (CSocketListen*)m_pListenSocket;
	pServerSocket->CloseClientSocket((CSocketListen*)this);
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
	if (Receive(&szBuffer, BUFFER_SIZE) > 0)
	{
		CSocketListen* pServerSocket = (CSocketListen*)m_pListenSocket;
		pServerSocket->SendOrderResultDataAll((char *)&szBuffer); // 한 클라이언트로 부터 받은 메시지를 모든 클라이언트에게 전송한다.
	}

	CSocket::OnReceive(nErrorCode);
}