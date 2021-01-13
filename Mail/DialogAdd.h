#pragma once


// DialogAdd 对话框

class DialogAdd : public CDialogEx
{
	DECLARE_DYNAMIC(DialogAdd)

public:
	DialogAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_add_username;
	afx_msg void OnBnClickedOk();
};
