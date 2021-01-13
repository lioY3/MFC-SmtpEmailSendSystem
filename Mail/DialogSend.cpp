// DialogSend.cpp: 实现文件
//

#include "pch.h"
#include "Mail.h"
#include "DialogSend.h"
#include "afxdialogex.h"


// DialogSend 对话框

IMPLEMENT_DYNAMIC(DialogSend, CDialogEx)

DialogSend::DialogSend(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGSend, pParent)
{

}

DialogSend::~DialogSend()
{
}

void DialogSend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogSend, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSend::OnBnClickedOk)
	ON_BN_CLICKED(IDAGAIN, &DialogSend::OnBnClickedAgain)
	ON_BN_CLICKED(IDC_BTN_VIEW, &DialogSend::OnBnClickedBtnView)
END_MESSAGE_MAP()


// DialogSend 消息处理程序


void DialogSend::OnBnClickedOk()
{
	// TODO: 响应点击发送按钮的事件
	MessageBox(TEXT("发送"));
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
