﻿#pragma once


// RegisterDLG 对话框

class RegisterDLG : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDLG)

public:
	RegisterDLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RegisterDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGRIGI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_reg_username;
	CString m_reg_email;
	CString m_reg_pwd1;
	CString m_reg_pwd2;
	afx_msg void OnBnClickedOk();
};
