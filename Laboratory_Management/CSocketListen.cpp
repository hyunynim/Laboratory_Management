#include "stdafx.h"
#include "CSocketListen.h"
#include "CSocketClient.h"

CSocketListen::CSocketListen()
{
}


CSocketListen::~CSocketListen()
{
}

void CSocketListen::OnAccept(int nErrorCode) // 새로운 클라이언트의 연결을 받을때 자동 호출됨.
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CSocketClient* pClient = new CSocketClient;
	if (Accept(*pClient))
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	}
	else
	{
		delete pClient;
		AfxMessageBox("Accept 실패.");
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CSocketListen::CloseClientSocket(CSocketListen* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);
	if (pos != NULL)
	{
		if (pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
		}
		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}

void CSocketListen::SendOrderResultDataAll(char* pszBuffer) 
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CSocketClient* pClient = NULL;
	while (pos != NULL)
	{
		pClient = (CSocketClient*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
			pClient->Send(pszBuffer, lstrlen(pszBuffer));
	}
}

void CSocketListen::SendOrderResultDataAll(const char* pszBuffer)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CSocketClient* pClient = NULL;
	while (pos != NULL)
	{
		pClient = (CSocketClient*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
			pClient->Send(pszBuffer, lstrlen(pszBuffer));
	}
}