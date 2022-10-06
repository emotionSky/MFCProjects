#pragma once



// DialogInfo 窗体视图

class DialogInfo : public CFormView
{
	DECLARE_DYNCREATE(DialogInfo)

protected:
	DialogInfo();           // 动态创建所使用的受保护的构造函数
	virtual ~DialogInfo();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO };
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

private:
	CListCtrl m_listInfo;
};


