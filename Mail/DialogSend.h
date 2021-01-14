#pragma once


// DialogSend 对话框

class DialogSend : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSend)

public:
	DialogSend(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogSend();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSend };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Addr;
	CString m_Server;
	UINT m_Port;
	CString m_User;
	CString m_Pass;
	CString m_Receiver;
	CString m_Title;
	CString m_CC;
	CString m_BCC;
	CString m_Attach;
	CString m_Letter;
	CString m_Info;
	CListBox m_Friend;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAgain();
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnBnClickedMfcbuttonadd();
	afx_msg void OnBnClickedMfcbuttondecrease();
	afx_msg void OnBnClickedBtnDelet();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
