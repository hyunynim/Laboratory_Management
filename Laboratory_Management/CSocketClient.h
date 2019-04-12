#pragma once
#include"stdafx.h"
#define BUFFER_SIZE 4096
class CSocketClient : public CSocket
{
public:
	CSocketClient();
	~CSocketClient();
	void SetListenSocket(CAsyncSocket* pSocket);
	void OnClose(int nErrorCode);
	CAsyncSocket* m_pListenSocket;
	void OnReceive(int nErrorCode);
};

