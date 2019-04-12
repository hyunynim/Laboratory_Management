#include "stdafx.h"
#include "CClientSocket.h"

#define bufSz (1<<10)

CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode) {
	CString strTmp = "", strIPAddr = "";
	UINT uPort = 0;
	TCHAR strBuf[bufSz];
	ZeroMemory(strBuf, sizeof(strBuf));

	GetPeerName(strIPAddr, uPort);
	if (Receive(strBuf, sizeof(strBuf)) > 0) {
		strTmp.Format("[%s : %d]: %s"), strIPAddr, uPort, strBuf);
	}
	CSocket::OnReceive(nErrorCode);
}
void CClientSocket::OnClose(int nErrorCode) {
	CSocket::OnClose(nErrorCode);
}
