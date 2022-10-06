#pragma once



// DialogAdd 窗体视图

class DialogAdd : public CFormView
{
	DECLARE_DYNCREATE(DialogAdd)

protected:
	DialogAdd();           // 动态创建所使用的受保护的构造函数
	virtual ~DialogAdd();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
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
	//继承的函数重写
	virtual void OnInitialUpdate();

	//事件的响应函数
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

private:
	CComboBox m_product;
	int m_price;
	int m_count;
	CString m_newCommodity;
	int m_newPrice;
	int m_newCount;
};


