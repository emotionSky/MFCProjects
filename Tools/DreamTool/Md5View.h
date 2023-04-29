#pragma once



// Md5View 窗体视图

class Md5View : public CFormView
{
	DECLARE_DYNCREATE(Md5View)

protected:
	Md5View();           // 动态创建所使用的受保护的构造函数
	virtual ~Md5View();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MD5 };
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
private:
	CString m_number;
	CString m_pwd;
	CString m_realme;
	CString m_nonce;
	CString m_uri;
	CString m_response;
public:
	afx_msg void OnBnClickedButton1();
};


