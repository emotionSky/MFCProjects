#pragma once
#include "afxdialogex.h"


// DialogSell 对话框

class DialogSell : public CFormView
{
	DECLARE_DYNCREATE(DialogSell)

protected:
	DialogSell();   // 标准构造函数
	virtual ~DialogSell();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELL
	};
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

private:
	CComboBox m_product;
	int       m_price;
	int       m_left;
	int       m_count;
	CString   m_sellInfo;	
};
