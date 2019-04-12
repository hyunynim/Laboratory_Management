#pragma once
#include <afxsock.h>
class CClientSocket :
	public CSocket
{
private:
	HWND m_hWnd;
public:
	CClientSocket();
	~CClientSocket();
	void SetWnd(HWND hWnd) { m_hWnd = hWnd; }
	HWND GetWnd() { return m_hWnd; }
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

