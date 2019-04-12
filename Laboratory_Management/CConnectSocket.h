#pragma once
class CConnectSocket : public CSocket
{
public:
	CConnectSocket();
	virtual ~CConnectSocket();
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
	void reloadConnected();
};

