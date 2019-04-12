#pragma once
#include"stdafx.h"
class CSocketListen : public CAsyncSocket
{
public:
	CSocketListen();
	~CSocketListen();
	CPtrList m_ptrClientSocketList; 
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocketListen* pClient);// 모든 클라이언트 소켓 닫고 메모리 해제 및 네트워크 연결 종료
	void SendOrderResultDataAll(char* pszBuffer); // 한 클라이언트에서 받은 메시지를 연결된 모든 클라이언트에게 전송한다.
	void SendOrderResultDataAll(const char* pszBuffer);
};

