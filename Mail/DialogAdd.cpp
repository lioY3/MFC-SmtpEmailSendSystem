// DialogAdd.cpp: 实现文件
//

#include "pch.h"
#include "Mail.h"
#include "DialogAdd.h"
#include "afxdialogex.h"


// DialogAdd 对话框

IMPLEMENT_DYNAMIC(DialogAdd, CDialogEx)

DialogAdd::DialogAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGADD, pParent)
{

}

DialogAdd::~DialogAdd()
{
}

void DialogAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogAdd, CDialogEx)
END_MESSAGE_MAP()


// DialogAdd 消息处理程序
