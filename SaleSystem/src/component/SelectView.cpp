// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "Resource.h"
#include "base/MainFrm.h"
#include "component/SelectView.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序

void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	//初始化 树视图
	//获取树控件
	m_pTreeCtrl = &GetTreeCtrl();

	//准备图片集合
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_RE);
	m_imgList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imgList.Add(icon);
	m_pTreeCtrl->SetImageList(&m_imgList, TVSIL_NORMAL);

	//添加节点
	m_pTreeCtrl->InsertItem(TEXT("个人信息"), 0, 0, nullptr);
	m_pTreeCtrl->InsertItem(TEXT("销售管理"), 0, 0, nullptr);
	m_pTreeCtrl->InsertItem(TEXT("库存信息"), 0, 0, nullptr);
	m_pTreeCtrl->InsertItem(TEXT("库存添加"), 0, 0, nullptr);
	m_pTreeCtrl->InsertItem(TEXT("库存删除"), 0, 0, nullptr);
}

void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
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
	//NM_A 自定义的消息类型
	//(WPARAM)NM_A 指定附加的消息信息
	//(LPARAM)0  指定附加的消息信息，此处这个参数没有意义，直接给0即可
	if (str == TEXT("个人信息"))
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	else if (str == TEXT("销售管理"))
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	else if (str == TEXT("库存信息"))
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	else if (str == TEXT("库存添加"))
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	else if (str == TEXT("库存删除"))
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
}
