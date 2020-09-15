
// DriverInstallDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DriverInstall.h"
#include "DriverInstallDlg.h"
#include "afxdialogex.h"
#include <winsvc.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDriverInstallDlg dialog



CDriverInstallDlg::CDriverInstallDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRIVERINSTALL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_DRIVER_FILE_PATH, DriverFilePath);
	DDX_Control(pDX, ID_ServiceNameEdit, ServerName);
	//DDX_Control(pDX, IDC_BUTTON1, Title);
	DDX_Control(pDX, ID_TITLE, Status);
}

BEGIN_MESSAGE_MAP(CDriverInstallDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDriverInstallDlg::OnBnClickedButton1)
	ON_EN_CHANGE(ID_DRIVER_FILE_PATH, &CDriverInstallDlg::OnEnChangeDriverFilePath)
	ON_BN_CLICKED(IDC_BUTTON4, &CDriverInstallDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CDriverInstallDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDriverInstallDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CDriverInstallDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDriverInstallDlg message handlers

BOOL CDriverInstallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CDriverInstallDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDriverInstallDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDriverInstallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CDriverInstallDlg::OnBnClickedButton1()
{
	CString ReadFilePath;
	CFileDialog fileDlg(true, _T("sys"), _T("*.sys"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Driver Files (*.sys)|*.sys|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)   
	{
		ReadFilePath = fileDlg.GetPathName();
		GetDlgItem(ID_DRIVER_FILE_PATH)->SetWindowText(ReadFilePath);
		CString filename = fileDlg.GetFileName();
		ServerName.SetWindowTextW(fileDlg.GetFileTitle());
		DriverS = TRUE;
	}

	// TODO: Add your control notification handler code here
}


void CDriverInstallDlg::OnEnChangeDriverFilePath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CDriverInstallDlg::OnBnClickedButton4()
{

	if (DriverS != TRUE) {
		Status.SetWindowTextW(_T("Please select the driver file"));
		return;
	}
	ServiceManger(3);
	// TODO: Add you
	// TODO: Add your control notification handler code here
}

BOOL CDriverInstallDlg::ServiceManger(int status) {
	CString Message;
	CString ServiceName;
	ServerName.GetWindowTextW(ServiceName);
	CString Path;
	DriverFilePath.GetWindowTextW(Path);
	
	SC_HANDLE ScmObject = NULL;
	SC_HANDLE SerObject = NULL;
	ScmObject = OpenSCManagerW(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (ScmObject ==NULL) {
		Message.Format(_T("OpenSCManagerW ERROR CODE:%d"), GetLastError());
		Status.SetWindowTextW(Message);
		return FALSE;
	}

	switch (status)
	{
	case 1: //Create Service
		SerObject =CreateServiceW(ScmObject,
			ServiceName.GetBuffer(),
			ServiceName.GetBuffer(), 
			SERVICE_ALL_ACCESS, 
			SERVICE_KERNEL_DRIVER, 
			SERVICE_DEMAND_START, 
			SERVICE_ERROR_IGNORE, 
			Path.GetBuffer(),
			NULL, NULL, NULL, NULL, NULL);
		if (SerObject == NULL) {
			DWORD ErrorCode=GetLastError();
			if (ErrorCode == ERROR_SERVICE_EXISTS) {
				Status.SetWindowTextW(_T("Service Already exists"));
			}
			else {
				Message.Format(_T("CreateServiceW ERROR CODE:%d"), ErrorCode);
				Status.SetWindowTextW(Message);
			}

		}
		Status.SetWindowTextW(_T("Install Successfuly"));
		break;
	case 2://UnInstall
		SerObject = OpenServiceW(ScmObject, ServiceName.GetBuffer(), SERVICE_ALL_ACCESS);
		if (SerObject == NULL) {
			DWORD ErrorCode=GetLastError();
			Message.Format(_T("OpenServiceW ERROR CODE:%d"), ErrorCode);
			Status.SetWindowTextW(Message);
			break;
		}
		DeleteService(SerObject);
		Status.SetWindowTextW(_T("Uninstall Service"));
		break;
	case 3://Start
		SerObject = OpenServiceW(
			ScmObject,
			ServiceName.GetBuffer(), 
			SERVICE_ALL_ACCESS);

		if (SerObject == NULL) {
			DWORD ErrorCode = GetLastError();
			Message.Format(_T("OpenServiceW ERROR CODE:%d"), ErrorCode);
			Status.SetWindowTextW(Message);
			break;
		}
		if (StartService(SerObject, NULL, NULL)) {
			Status.SetWindowTextW(_T("Start Service"));
		}
		else {
			Status.SetWindowTextW(_T("Start Service faild"));
		}
		break;
	case 4://Stop
		SerObject = OpenServiceW(
			ScmObject,
			ServiceName.GetBuffer(),
			SERVICE_ALL_ACCESS);

		if (SerObject == NULL) {
			DWORD ErrorCode = GetLastError();
			Message.Format(_T("OpenServiceW ERROR CODE:%d"), ErrorCode);
			Status.SetWindowTextW(Message);
			break;
		}
		SERVICE_STATUS SerStatus = { 0 };
		if (ControlService(SerObject, 
			SERVICE_CONTROL_STOP, 
			&SerStatus)) {
			Status.SetWindowTextW(_T("Stop Service"));
			break;
		}
		
	}
	if (ScmObject != NULL) {
		CloseServiceHandle(ScmObject);

	}
	if (SerObject != NULL) {
		CloseServiceHandle(SerObject);
	}
	return TRUE;
}

void CDriverInstallDlg::OnBnClickedButton2()
{
	if (DriverS != TRUE) {
		Status.SetWindowTextW(_T("Please select the driver file"));
		return;
	}
	ServiceManger(1);
	
	// TODO: Add your control notification handler code here
}


void CDriverInstallDlg::OnBnClickedButton3()
{
	if (DriverS != TRUE) {
		Status.SetWindowTextW(_T("Please select the driver file"));
		return;
	}
	ServiceManger(2);
	// TODO: Add your control notification handler code here
}


void CDriverInstallDlg::OnBnClickedButton5()
{

	if (DriverS != TRUE) {
		Status.SetWindowTextW(_T("Please select the driver file"));
		return;
	}
	ServiceManger(4);
	// TODO: Add you
	// TODO: Add your control notification handler code here
}
