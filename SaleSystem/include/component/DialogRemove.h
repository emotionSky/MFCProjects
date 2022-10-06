#pragma once



// DialogRemove 窗体视图

class DialogRemove : public CFormView
{
	DECLARE_DYNCREATE(DialogRemove)

protected:
	DialogRemove();           // 动态创建所使用的受保护的构造函数
	virtual ~DialogRemove();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REMOVE };
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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();

private:
	CComboBox m_product;
	int       m_price;
	int       m_count;
};


