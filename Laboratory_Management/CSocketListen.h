#pragma once
#include"stdafx.h"
class CSocketListen : public CAsyncSocket
{
public:
	CSocketListen();
	~CSocketListen();
	CPtrList m_ptrClientSocketList; 
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocketListen* pClient);// ��� Ŭ���̾�Ʈ ���� �ݰ� �޸� ���� �� ��Ʈ��ũ ���� ����
	void SendOrderResultDataAll(char* pszBuffer); // �� Ŭ���̾�Ʈ���� ���� �޽����� ����� ��� Ŭ���̾�Ʈ���� �����Ѵ�.
	void SendOrderResultDataAll(const char* pszBuffer);
};

