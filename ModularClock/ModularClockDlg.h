
// ModularClockDlg.h : header file
//

#pragma once

#include "Algorithm.h"

// CModularClockDlg dialog
class CModularClockDlg : public CDialogEx
{
// Construction
public:
	CModularClockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MODULARCLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit4();


	Algorithm *algo;
	int		selectedAlgo;
	bool	isSync;
	afx_msg void OnBnClickedCheck1();
};
