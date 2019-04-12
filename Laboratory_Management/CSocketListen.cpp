#include "stdafx.h"
#include "CSocketListen.h"
#include "CSocketClient.h"

CSocketListen::CSocketListen()
{
}


CSocketListen::~CSocketListen()
{
}

void CSocketListen::OnAccept(int nErrorCode) // ���ο� Ŭ���̾�Ʈ�� ������ ������ �ڵ� ȣ���.
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CSocketClient* pClient = new CSocketClient;
	if (Accept(*pClient))
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	}
	else
	{
		delete pClient;
		AfxMessageBox("Accept ����.");
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