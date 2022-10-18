// SelectView.cpp: 实现文件
//

#include "pch.h"
#include "DreamTool.h"
#include "SelectView.h"
#include "Common.h"


// SelectView

IMPLEMENT_DYNCREATE(SelectView, CTreeView)

SelectView::SelectView()
{

}

SelectView::~SelectView()
{
}

BEGIN_MESSAGE_MAP(SelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &SelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// SelectView 诊断

#ifdef _DEBUG
void SelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void SelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


void SelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	//初始化 树视图
	//获取树控件
	m_pTreeCtrl = &GetTreeCtrl();

	//准备图片集合
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_DATE);
	m_imgList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imgList.Add(icon);
	m_pTreeCtrl->SetImageList(&m_imgList, TVSIL_NORMAL);

	//添加节点
	m_pTreeCtrl->InsertItem(TEXT("时间变换"), 0, 0, nullptr);
}

void SelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前选中项
	HTREEITEM item = m_pTreeCtrl->GetSelectedItem();
	//通过选中的项来获取这个项中的内容
	CString str = m_pTreeCtrl->GetItemText(item);

	//MessageBox(str);

	//CWnd::PostMessage 是将一个消息放入窗口的消息队列，可以类比QT的发送信号
	//AfxGetMainWnd() 框架窗口对象的指针
	//AfxGetMainWnd()->GetSafeHwnd() 获取窗口的句柄
	//EMOTIONSKY_A 自定义的消息类型
	//(WPARAM)EMOTIONSKY_A 指定附加的消息信息
	//(LPARAM)0  指定附加的消息信息，此处这个参数没有意义，直接给0即可
	if (str == TEXT("时间变换"))
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EMOTIONSKY_A, (WPARAM)EMOTIONSKY_A, (LPARAM)0);
}

