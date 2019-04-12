﻿
// Laboratory_ManagementDlg.h: 헤더 파일
//

#pragma once
#include"CSocketListen.h"
#include"CSocketClient.h"
// CLaboratoryManagementDlg 대화 상자
class CLaboratoryManagementDlg : public CDialogEx
{
// 생성입니다.
public:
	CLaboratoryManagementDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABORATORY_MANAGEMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LRESULT OnTaryNotifyAction(WPARAM wParam, LPARAM lParam);
public:
	bool initSocket();
	struct IPLIST {
		std::string ip;
		bool connected;
	};
	int ipCnt;
	int startIp[4];
	std::vector<int> getSelected();
	std::vector<IPLIST> ipList;
	bool getSettings();
	char msg[1010];
	std::set<int> selected;
	CListCtrl m_ComputerList;
	afx_msg void OnBnClickedDebug();
	afx_msg void OnClickComputerList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkComputerList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedHide();
	afx_msg void OnExit();
	CIPAddressCtrl m_ipControl;
private:
	CSocketListen * m_pListenSocket;
};
