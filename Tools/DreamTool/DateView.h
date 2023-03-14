#pragma once

enum class LocalStyle
{
	NONE,
	STYLE_1,
	STYLE_2,
};

enum class AbStyle
{
	NONE,
	STYLE_1,
	STYLE_2,
	STYLE_3,
};

// CDateView 窗体视图

class CDateView : public CFormView
{
	DECLARE_DYNCREATE(CDateView)

protected:
	CDateView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDateView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATE };
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

public:
	afx_msg void OnCbnSelchangeComboLocal();
	afx_msg void OnCbnSelchangeComboAb();
	afx_msg void OnBnClickedButtonToAb();
	afx_msg void OnBnClickedButtonToLocal();

private:
	CComboBox  m_localCombo;
	CComboBox  m_abCombo;
	CString    m_localEdit;
	time_t     m_abEdit;

	LocalStyle m_localStyle;
	AbStyle    m_abStyle;
};


