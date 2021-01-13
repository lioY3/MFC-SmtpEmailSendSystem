// DialogSend.cpp: 实现文件
//

#include "pch.h"
#include "Mail.h"
#include "DialogSend.h"
#include "afxdialogex.h"
#include "Smtp.h"
#include "MySQLConnector.h"
#include "DialogAdd.h"

// DialogSend 对话框

IMPLEMENT_DYNAMIC(DialogSend, CDialogEx)

DialogSend::DialogSend(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGSend, pParent)
{
	m_Name = _T("");
	m_Addr = _T(email);
	m_Server = _T("");
	m_Port = _T(25);
	m_User = _T("");
	m_Pass = _T("");
	m_Receiver = _T("");
	m_Title = _T("");
	m_CC = _T("");
	m_BCC = _T("");
	m_Attach = _T("");
	m_Letter = _T("");
	m_Info = _T("");
	
}

DialogSend::~DialogSend()
{
	mysql_close(mysql);
}

void DialogSend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_Addr);
	DDX_Text(pDX, IDC_EDIT_PASS, m_Pass);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_Server);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_Receiver);
	DDX_Text(pDX, IDC_EDIT_CC, m_CC);
	DDX_Text(pDX, IDC_EDIT_BCC, m_BCC);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Title);
	DDX_Text(pDX, IDC_EDIT_ATTACH, m_Attach);
	DDX_Text(pDX, IDC_EDIT_LETTER, m_Letter);
	DDX_Control(pDX, IDC_LIST1, m_Friend);
	char friend_info[50];
	//sprintf_s(friend_info, " %-8s %-20s", "用户名", "好友邮箱");
	//m_Friend.AddString(friend_info);
	for (int i = 0;i < total_friend;i++)
	{
		sprintf_s(friend_info, " %-8s %-10s", friend_list[i][1], friend_list[i][2]);
		m_Friend.AddString(friend_info);
	}
}


BEGIN_MESSAGE_MAP(DialogSend, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSend::OnBnClickedOk)
	ON_BN_CLICKED(IDAGAIN, &DialogSend::OnBnClickedAgain)
	ON_BN_CLICKED(IDC_BTN_VIEW, &DialogSend::OnBnClickedBtnView)
	ON_EN_CHANGE(IDC_EDIT_NAME, &DialogSend::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_MFCBUTTONADD, &DialogSend::OnBnClickedMfcbuttonadd)
	ON_BN_CLICKED(IDC_MFCBUTTONDECREASE, &DialogSend::OnBnClickedMfcbuttondecrease)
	ON_BN_CLICKED(IDC_BTN_DELET, &DialogSend::OnBnClickedBtnDelet)
END_MESSAGE_MAP()


// DialogSend 消息处理程序


void DialogSend::OnBnClickedOk()
{
	// TODO: 响应点击发送按钮的事件
	UpdateData(true);
	
	int port = (int)m_Port;
	CSmtp smtp(
		port,
		m_Server.GetBuffer(0),
		m_Addr.GetBuffer(0),
		m_Pass.GetBuffer(0),
		m_Receiver.GetBuffer(0),
		m_Title.GetBuffer(0),
		m_Letter.GetBuffer(0)
	);

	int err;
	if ((err = smtp.SendEmail_Ex()) != 0)
	{
		if (err == 1)
			MessageBox(TEXT("错误1: 由于网络不畅通，发送失败!"));
		if (err == 2)
			MessageBox(TEXT("错误2: 用户名错误,请核对!"));
		if (err == 3)
			MessageBox(TEXT("错误3: 用户密码错误，请核对!"));
		if (err == 4)
			MessageBox(TEXT("错误4: 请检查附件目录是否正确，以及文件是否存在!"));
	}
	else
	{
		MessageBox(TEXT("发送成功！"));
	}
}


void DialogSend::OnBnClickedAgain()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	DialogSend dlg;//你添加的对话框的头文件要加到原对话框的.cpp文件中 否则编译不通过
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void DialogSend::OnBnClickedBtnView()
{
	// TODO:响应附件按钮
}


void DialogSend::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void DialogSend::OnBnClickedMfcbuttonadd()
{
	// TODO:响应添加好友按钮
	DialogAdd dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void DialogSend::OnBnClickedMfcbuttondecrease()
{
	// TODO:响应删除好友按钮
}


void DialogSend::OnBnClickedBtnDelet()
{
	// TODO: 响应删除附件按钮
}
