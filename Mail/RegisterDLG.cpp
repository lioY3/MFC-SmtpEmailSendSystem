// RegisterDLG.cpp: 实现文件
//

#include "pch.h"
#include "Mail.h"
#include "RegisterDLG.h"
#include "afxdialogex.h"


// RegisterDLG 对话框

IMPLEMENT_DYNAMIC(RegisterDLG, CDialogEx)

RegisterDLG::RegisterDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGRIGI, pParent)
{

}

RegisterDLG::~RegisterDLG()
{
}

void RegisterDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegisterDLG, CDialogEx)
END_MESSAGE_MAP()


// RegisterDLG 消息处理程序
