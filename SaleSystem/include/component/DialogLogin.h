#pragma once
#include "afxdialogex.h"


// DialogLogin 对话框

class DialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DialogLogin)

public:
	DialogLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogLogin();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();
	virtual void OnCancel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonCancel();

private:
	CString m_user; //登录的账号控件
	CString m_pwd;  // 登录的密码控件
};
