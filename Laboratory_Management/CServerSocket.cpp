#include "stdafx.h"
#include "CServerSocket.h"


CServerSocket::CServerSocket()
{
}


CServerSocket::~CServerSocket()
{
}

void CServerSocket::SetWnd(HWND hWnd) {
	m_hWnd = hWnd;
}

void CServerSocket::OnAccept(int nErrorCode) {
	CClientSocket * pClient = new CClientSocket;
	if (Accept(*pClient))
		pClient->SetWnd(GetWnd());
	else {
		delete pClient;
		AfxMessageBox("Connected Error");
	}
	CSocket::OnAccept(nErrorCode);
}