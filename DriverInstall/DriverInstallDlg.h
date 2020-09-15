
// DriverInstallDlg.h : header file
//

#pragma once


// CDriverInstallDlg dialog
class CDriverInstallDlg : public CDialogEx
{
// Construction
public:
	CDriverInstallDlg(CWnd* pParent = nullptr);	// standard constructor
	BOOL ServiceManger(int status);
	BOOL DriverS=FALSE;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRIVERINSTALL_DIALOG };
#endif

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
	afx_msg void OnBnClickedButton1();
	CEdit DriverFilePath;
	afx_msg void OnEnChangeDriverFilePath();
	afx_msg void OnBnClickedButton4();
	CEdit ServerName;
	afx_msg void OnBnClickedButton2();
	CButton Title;
	CStatic Status;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
};
