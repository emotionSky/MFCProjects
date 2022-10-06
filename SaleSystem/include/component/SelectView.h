#pragma once

#include "afxcview.h"

// CSelectView 视图

class CSelectView : public CTreeView
{
	DECLARE_DYNCREATE(CSelectView)

protected:
	CSelectView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	//继承的函数重写
	virtual void OnInitialUpdate();

	//事件的处理函数
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);

private:
	CTreeCtrl* m_pTreeCtrl; //树控件
	CImageList m_imgList;  //图标列表
};


