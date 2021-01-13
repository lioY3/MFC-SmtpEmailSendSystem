// RegisterDLG.cpp: 实现文件
//

#include "pch.h"
#include "Mail.h"
#include "MailDlg.h"
#include "RegisterDLG.h"
#include "afxdialogex.h"
#include "MySQLConnector.h"


// RegisterDLG 对话框

IMPLEMENT_DYNAMIC(RegisterDLG, CDialogEx)

RegisterDLG::RegisterDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGRIGI, pParent)
	, m_reg_username(_T(""))
	, m_reg_email(_T(""))
	, m_reg_pwd1(_T(""))
	, m_reg_pwd2(_T(""))
{

}

RegisterDLG::~RegisterDLG()
{
}

void RegisterDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_reg_username);
	DDX_Text(pDX, IDC_EDIT2, m_reg_email);
	DDX_Text(pDX, IDC_EDIT_PASS3, m_reg_pwd1);
	DDX_Text(pDX, IDC_EDIT_PASS2, m_reg_pwd2);
}


BEGIN_MESSAGE_MAP(RegisterDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &RegisterDLG::OnBnClickedOk)
END_MESSAGE_MAP()


// RegisterDLG 消息处理程序


void RegisterDLG::OnBnClickedOk()
{
	// TODO: 在此添加注册逻辑代码
	UpdateData(true);
	if(m_reg_username == "")
	{
		MessageBox(TEXT("请输入用户名！"));
	}
	else if (m_reg_email == "")
	{
		MessageBox(TEXT("请输入您的邮箱！"));
	}
	else if (m_reg_pwd1 == ""||m_reg_pwd2=="")
	{
		MessageBox(TEXT("请输入合法密码！"));
	}
	else if (m_reg_pwd1 != m_reg_pwd2)
	{
		MessageBox(TEXT("两次密码输入不一致！"));
	}
	else
	{
		char reg_username[20], reg_pwd[20], reg_email[30];
		memcpy(reg_username, LPCTSTR(m_reg_username), m_reg_username.GetLength() * sizeof(TCHAR));
		memcpy(reg_pwd, LPCTSTR(m_reg_pwd1), m_reg_pwd1.GetLength() * sizeof(TCHAR));
		memcpy(reg_email, LPCTSTR(m_reg_email), m_reg_email.GetLength() * sizeof(TCHAR));
		reg_username[m_reg_username.GetLength()] = 0;
		reg_pwd[m_reg_pwd1.GetLength()] = 0;
		reg_email[m_reg_email.GetLength()] = 0;
		if (user_register(reg_username, reg_pwd, reg_email) == 0)	//注册
		{
			MessageBox(TEXT("用户名已存在！"));
		}
		else
		{
			MessageBox(TEXT("注册成功！"));
			this->ShowWindow(SW_HIDE);
			CMailDlg dlg;
			dlg.DoModal();
			this->ShowWindow(SW_SHOW);
		}
	}

}
