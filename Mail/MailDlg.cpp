
// MailDlg.cpp: 实现文件
//


#include "pch.h"
#include <mysql.h>
#include "framework.h"
#include "Mail.h"
#include "MailDlg.h"
#include "afxdialogex.h"
#include "DialogSend.h "
#include "MySQLConnector.h"
#include "RegisterDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMailDlg 对话框



CMailDlg::CMailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMailDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_RECEIVER, &CMailDlg::OnEnChangeEditReceiver)
	ON_BN_CLICKED(IDOK, &CMailDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_USER, &CMailDlg::OnEnChangeEditUser)
	ON_BN_CLICKED(IDC_TOREGISTER, &CMailDlg::OnBnClickedToregister)
END_MESSAGE_MAP()


// CMailDlg 消息处理程序

BOOL CMailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ConnectDatabase();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(255, 255, 255)); //设置为白色背景
		CDC dcImage, dcTrans;
		//加载位图
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP4); //IDB_BITMAP1是导入的位图ID

		//取得位图的详细信息
		BITMAP bm;
		bitmap.GetBitmap(&bm);
		int nWidth = bm.bmWidth-57;
		int nHeight = bm.bmHeight;
		//创建兼容DC
		dcImage.CreateCompatibleDC(&dc);
		CBitmap* pOldBitmapImage = dcImage.SelectObject(&bitmap);
		//强制设置位图背景色为白色
		dcImage.SetBkColor(RGB(255, 255, 255));
		//位图背景色与操作
		dc.BitBlt(rect.Width() - nWidth, 10, nWidth, nHeight, &dcImage, 0, 60, SRCAND);
		dcImage.SelectObject(pOldBitmapImage);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMailDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMailDlg::OnEnChangeEditReceiver()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CMailDlg::OnBnClickedOk()
{
	// TODO: 登录按钮的点击事件
	UpdateData(true);
	/*ConnectDatabase();*/
	CString uname;
	CString pwd;

	char password[20];
	GetDlgItem(IDC_EDIT_USER)->GetWindowText(uname);
	GetDlgItem(IDC_EDIT_PASS)->GetWindowText(pwd);
	memcpy(username, LPCTSTR(uname), uname.GetLength() * sizeof(TCHAR));
	memcpy(password, LPCTSTR(pwd), pwd.GetLength() * sizeof(TCHAR));

	username[uname.GetLength()] = 0;
	password[pwd.GetLength()] = 0;

	if (!user_login(username, password))	//登录
	{
		MessageBox(TEXT("用户名或密码错误！"));
		sprintf_s(username, "\0");
	}
	else
	{
		MessageBox(TEXT("登录成功！"));
		total_friend = get_all_friend();
		this->ShowWindow(SW_HIDE);
		DialogSend dlg;
		dlg.DoModal();
		this->ShowWindow(SW_SHOW);
	}
	
}


void CMailDlg::OnEnChangeEditUser()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMailDlg::OnBnClickedToregister()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	RegisterDLG dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}
