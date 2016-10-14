
// ModularClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModularClock.h"
#include "ModularClockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CModularClockDlg dialog



CModularClockDlg::CModularClockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModularClockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModularClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CModularClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CModularClockDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CModularClockDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDCANCEL, &CModularClockDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT4, &CModularClockDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_CHECK1, &CModularClockDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CModularClockDlg message handlers

BOOL CModularClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	algo = new Algorithm();
	selectedAlgo = -1;

	CEdit* delayEditBox = (CEdit*)GetDlgItem(IDC_EDIT5);
	delayEditBox->EnableWindow(FALSE);
	isSync = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CModularClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CModularClockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CModularClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModularClockDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();




	CEdit* userOneTextBox = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* userTwoTextBox = (CEdit*)GetDlgItem(IDC_EDIT3);

	/////////////////// Get User Input /////////

	// = selectedAlgo

	//
	CEdit* channelEditBox = (CEdit*)GetDlgItem(IDC_EDIT4);
	CString channelInput = _T("");
	channelEditBox->GetWindowTextW(channelInput);

	//
	CEdit* delayEditBox = (CEdit*)GetDlgItem(IDC_EDIT5);
	CString delayInput = _T("");
	delayEditBox->GetWindowTextW(delayInput);

	///////////////////// run algo ////////
	int m = _wtoi(channelInput);
	int d = isSync ? 0 : (_wtoi(delayInput));

	int *topArray = (int *)malloc(sizeof(int)* 100000);
	int *bottomArray = (int *)malloc(sizeof(int)* 100000);
	int bufferIndex = 0;
	int matchPos = -1;

	if (!isSync)
	{
		for (int i = 0; i < d; i++)
		{
			bottomArray[i] = -1;
		}
	}


	bool rendezvous = false;
	while (!rendezvous) {

		if (selectedAlgo == 0) {
			algo->setNumberOfChannels(m);
			algo->jumpStayAlgorithm(m);
			algo->generateUser(1);
			algo->jumpStayAlgorithm(m);
			algo->generateUser(2);
		}
		else if (selectedAlgo == 1) 
		{
			algo->setNumberOfChannels(m);
			algo->modularClockAlgorithm(m);
			algo->generateUser(1);
			algo->modularClockAlgorithm(m);
			algo->generateUser(2);
		}
		else if (selectedAlgo == 2)
		{
			algo->setNumberOfChannels(m);
			algo->randomAlgoritm(m);
			algo->generateUser(1);
			algo->randomAlgoritm(m);
			algo->generateUser(2);
		}

		rendezvous = algo->match();

		// copy 256 to big array
		if (isSync)
		{
			if (rendezvous)
			{
				matchPos = bufferIndex + algo->getMatchIndex();
			}

			for (int i = 0; i < 256; i++)
			{
				if (algo->userOne[i] < 0 || algo->userOne[i] < 0) {
					break;
				}

				topArray[bufferIndex] = algo->userOne[i];
				bottomArray[bufferIndex] = algo->userTwo[i];
				bufferIndex++;
			}
		}
		else 
		{
			for (int i = 0; i < 256; i++)
			{
				if (algo->userOne[i] < 0 || algo->userOne[i] < 0) {
					break;
				}

				topArray[bufferIndex] = algo->userOne[i];
				bottomArray[d + bufferIndex] = algo->userTwo[i];
				bufferIndex++;
			}

			for (int i = d; i < bufferIndex; i++)
			{
				if (topArray[i] == bottomArray[i]) 
				{
					rendezvous = true;
					matchPos = i;
					break;
				}
			}
		}
		
	}

	/////////////////////////////////////


	// fill the big array to CString

	CString userOneStr = _T("| ");
	CString userTwoStr = _T("| ");

	for (int i = 0; i < bufferIndex; i++)
	{
		CString str;

		if (i == matchPos)
		{
			str.Format(_T("=%d="), topArray[i]);
		}
		else
		{
			str.Format(_T("%d"), topArray[i]);
		}

		userOneStr = userOneStr + str + _T(" | ");
	}

	if (isSync) {
		for (int i = 0; i < bufferIndex; i++)
		{
			CString str2;
			if (i == matchPos)
			{
				str2.Format(_T("=%d="), bottomArray[i]);
			}
			else
			{
				str2.Format(_T("%d"), bottomArray[i]);
			}

			userTwoStr = userTwoStr + str2 + _T(" | ");
		}
	}
	else 
	{
		for (int i = 0; i < d; i++)
		{
			CString str2 = _T(" ");
			userTwoStr = userTwoStr + str2 + _T(" | ");
		}


		for (int i = d; i < (bufferIndex + d); i++)
		{
			CString str2;
			if (i == matchPos)
			{
				str2.Format(_T("=%d="), bottomArray[i]);
			}
			else
			{
				str2.Format(_T("%d"), bottomArray[i]);
			}

			userTwoStr = userTwoStr + str2 + _T(" | ");
		}
	}



	userOneTextBox->SetWindowText(userOneStr);
	userTwoTextBox->SetWindowText(userTwoStr);
	
	CEdit* matchEditBox = (CEdit*)GetDlgItem(IDC_EDIT7);
	CString matchStr;
	matchStr.Format(_T("%d"), (matchPos + 1 - d));
	matchEditBox->SetWindowTextW(matchStr);
}


void CModularClockDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	CEdit* textBox = (CEdit*)GetDlgItem(IDC_EDIT1);

	CComboBox* comboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int sel = comboBox->GetCurSel();
	selectedAlgo = sel;

	if (sel == 0) {
		textBox->SetWindowText(TEXT("Jump-Stay Rendezvous Algorithm. It is designed for multiple synchronous users with guaranteed rendezvous. Here we automatic simulate two-user symmetric case of this algorithm. For asymmetric case, Please enter how many time slots you want to delay."));
	
	}
	else if (sel == 1) {
		textBox->SetWindowText(TEXT("Modular Clock Algorithm. It is designed for minimizing the time required by two secondary users to make rendezvous. This algorithm do not guarantees rendezvous in one round in the symmetric case. For asymmetric case, Please enter how many time slots you want to delay."));
	}
	else if (sel == 2) {
		textBox->SetWindowText(TEXT("Random Rendezvous Algorithm. The random channel algorithm visits all channles in a random order. For each time sime slot, a channel is selected with uniform probability. And rendezvous is not guaranteed. For asymmetric case, Please enter how many time slots you want to delay."));
	}


}


void CModularClockDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CModularClockDlg::OnEnChangeEdit4()
{

}


void CModularClockDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	CEdit* delayEditBox = (CEdit*)GetDlgItem(IDC_EDIT5);

	isSync = !isSync;
	delayEditBox->EnableWindow(!isSync);
}
