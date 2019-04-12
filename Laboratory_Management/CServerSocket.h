#pragma once
#include <afxsock.h>
#include"CClientSocket.h"
class CServerSocket :
	public CSocket
{
private:
	HWND m_hWnd;
public:
	CServerSocket();
	~CServerSocket();
	void SetWnd(HWND hWnd);
	HWND GetWnd() { return m_hWnd; }
	virtual void OnAccept(int nErrorCode);
};

