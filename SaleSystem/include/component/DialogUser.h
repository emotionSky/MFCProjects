#pragma once



// DialogUser 窗体视图

class DialogUser : public CFormView
{
	DECLARE_DYNCREATE(DialogUser)

protected:
	DialogUser();           // 动态创建所使用的受保护的构造函数
	virtual ~DialogUser();

public:
	virtual void OnInitialUpdate();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();

private:
	CString m_identify;
	CString m_user;
	CString m_newPwd;
	CString m_surePwd;
};


