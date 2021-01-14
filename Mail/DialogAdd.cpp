// DialogAdd.cpp: 实现文件
//

#include "pch.h"
#include "Mail.h"
#include "DialogAdd.h"
#include "DialogSend.h"
#include "afxdialogex.h"
#include "MySQLConnector.h"

// DialogAdd 对话框

IMPLEMENT_DYNAMIC(DialogAdd, CDialogEx)

DialogAdd::DialogAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADD, pParent)
	, m_add_username(_T(""))
{

}

DialogAdd::~DialogAdd()
{

}

void DialogAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_add_username);
}


BEGIN_MESSAGE_MAP(DialogAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogAdd::OnBnClickedOk)
	ON_BN_CLICKED(IDRESET, &DialogAdd::OnBnClickedReset)
END_MESSAGE_MAP()


// DialogAdd 消息处理程序


void DialogAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	if (m_add_username == "")
	{
		MessageBox(TEXT("请输入添加好友的用户名！"));
	}
	else
	{
		char friend_username[20];
		memcpy(friend_username, LPCTSTR(m_add_username), m_add_username.GetLength() * sizeof(TCHAR));
		friend_username[m_add_username.GetLength()] = 0;
		if (add_friend(friend_username) == 0)	//登录
		{
			MessageBox(TEXT("该用户名不存在！"));
		}
		else
		{
			MessageBox(TEXT("添加好友成功！"));
			total_friend = get_all_friend();
			this->ShowWindow(SW_HIDE);
			DialogSend dlg;
			dlg.DoModal();
			this->ShowWindow(SW_SHOW);
		}
	}
	
}


void DialogAdd::OnBnClickedReset()
{
	// TODO: 响应重置按钮
	m_add_username=_T("");
	UpdateData(FALSE);
}
