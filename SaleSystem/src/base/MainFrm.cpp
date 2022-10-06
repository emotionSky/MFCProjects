
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "base/SaleSystem.h"
#include "common/LocalParams.h"
#include "component/SelectView.h"
#include "component/DisplayView.h"
#include "component/DialogUser.h"
#include "component/DialogSell.h"
#include "component/DialogInfo.h"
#include "component/DialogAdd.h"
#include "component/DialogRemove.h"

#include "base/MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE相应的是自定义消息类型
	//这里是产生 NM_* 消息，然后调用对应的函数进行处理
	ON_MESSAGE(NM_A, OnSelectChanged)
	ON_MESSAGE(NM_B, OnSelectChanged)
	ON_MESSAGE(NM_C, OnSelectChanged)
	ON_MESSAGE(NM_D, OnSelectChanged)
	ON_MESSAGE(NM_E, OnSelectChanged)

	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32775, &CMainFrame::On32775)
	ON_COMMAND(ID_32776, &CMainFrame::On32776)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标  64位使用：GCLP_HICON  32位使用：GCL_HICON
#ifdef _WIN64
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)AfxGetApp()->LoadIconW(IDI_ICON_WIN));
#else
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));
#endif

	//设置标题，右侧标题
	SetTitle(TEXT("2022/10/02"));

	//设置窗口大小
	MoveWindow(0, 0, 800, 500);

	//设置居中显示
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	//拆成一行两列
	m_spliter.CreateStatic(this, 1, 2);

	//左侧和右侧具体的显示内容，注意这里的窗口位置，这里的窗口大小
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE; //自己进行窗口拆分
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

LRESULT CMainFrame::OnSelectChanged(WPARAM wParam, LPARAM lParam)
{
	//通过这个上下文变量进行界面挂载的配置
	CCreateContext ctx;

	switch (wParam)
	{
	case NM_A:
	{
		ctx.m_pNewViewClass = RUNTIME_CLASS(DialogUser);                             //新的子窗口类名
		ctx.m_pCurrentFrame = this;                                                  //当前窗口的指针
		ctx.m_pLastView = dynamic_cast<CFormView*>(m_spliter.GetPane(0, 1));         //获取现在的子窗口对象
		m_spliter.DeleteView(0, 1);                                                  //删除现在显示的那个子窗口，后面要换新
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(DialogUser), CSize(600, 500), &ctx);//创建新的子窗口对象
		DialogUser* pNewView = dynamic_cast<DialogUser*>(m_spliter.GetPane(0, 1));   //获取新的子窗口指针
		m_spliter.RecalcLayout();                                                    //设置新的子窗口布局
		pNewView->OnInitialUpdate();                                                 //手动调用新的子窗口的初始化
		m_spliter.SetActivePane(0, 1);                                               //设置活动窗口
		break;
	}

	case NM_B:
	{
		ctx.m_pNewViewClass = RUNTIME_CLASS(DialogSell);                             //新的子窗口类名
		ctx.m_pCurrentFrame = this;                                                  //当前窗口的指针
		ctx.m_pLastView = dynamic_cast<CFormView*>(m_spliter.GetPane(0, 1));         //获取现在的子窗口对象
		m_spliter.DeleteView(0, 1);                                                  //删除现在显示的那个子窗口，后面要换新
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(DialogSell), CSize(600, 500), &ctx);//创建新的子窗口对象
		DialogSell* pNewView = dynamic_cast<DialogSell*>(m_spliter.GetPane(0, 1));   //获取新的子窗口指针
		m_spliter.RecalcLayout();                                                    //设置新的子窗口布局
		pNewView->OnInitialUpdate();                                                 //手动调用新的子窗口的初始化
		m_spliter.SetActivePane(0, 1);                                               //设置活动窗口
		break;
	}

	case NM_C:
	{
		ctx.m_pNewViewClass = RUNTIME_CLASS(DialogInfo);                             //新的子窗口类名
		ctx.m_pCurrentFrame = this;                                                  //当前窗口的指针
		ctx.m_pLastView = dynamic_cast<CFormView*>(m_spliter.GetPane(0, 1));         //获取现在的子窗口对象
		m_spliter.DeleteView(0, 1);                                                  //删除现在显示的那个子窗口，后面要换新
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(DialogInfo), CSize(600, 500), &ctx);//创建新的子窗口对象
		DialogInfo* pNewView = dynamic_cast<DialogInfo*>(m_spliter.GetPane(0, 1));   //获取新的子窗口指针
		m_spliter.RecalcLayout();                                                    //设置新的子窗口布局
		pNewView->OnInitialUpdate();                                                 //手动调用新的子窗口的初始化
		m_spliter.SetActivePane(0, 1);                                               //设置活动窗口
		break;
	}

	case NM_D:
	{
		ctx.m_pNewViewClass = RUNTIME_CLASS(DialogAdd);                              //新的子窗口类名
		ctx.m_pCurrentFrame = this;                                                  //当前窗口的指针
		ctx.m_pLastView = dynamic_cast<CFormView*>(m_spliter.GetPane(0, 1));         //获取现在的子窗口对象
		m_spliter.DeleteView(0, 1);                                                  //删除现在显示的那个子窗口，后面要换新
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(DialogAdd), CSize(600, 500), &ctx); //创建新的子窗口对象
		DialogAdd* pNewView = dynamic_cast<DialogAdd*>(m_spliter.GetPane(0, 1));     //获取新的子窗口指针
		m_spliter.RecalcLayout();                                                    //设置新的子窗口布局
		pNewView->OnInitialUpdate();                                                 //手动调用新的子窗口的初始化
		m_spliter.SetActivePane(0, 1);                                               //设置活动窗口
		break;
	}

	case NM_E:
	{
		ctx.m_pNewViewClass = RUNTIME_CLASS(DialogRemove);                              //新的子窗口类名
		ctx.m_pCurrentFrame = this;                                                     //当前窗口的指针
		ctx.m_pLastView = dynamic_cast<CFormView*>(m_spliter.GetPane(0, 1));            //获取现在的子窗口对象
		m_spliter.DeleteView(0, 1);                                                     //删除现在显示的那个子窗口，后面要换新
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(DialogRemove), CSize(600, 500), &ctx); //创建新的子窗口对象
		DialogRemove* pNewView = dynamic_cast<DialogRemove*>(m_spliter.GetPane(0, 1));  //获取新的子窗口指针
		m_spliter.RecalcLayout();                                                       //设置新的子窗口布局
		pNewView->OnInitialUpdate();                                                    //手动调用新的子窗口的初始化
		m_spliter.SetActivePane(0, 1);                                                  //设置活动窗口
		break;
	}

	default:
		break;
	}

	return 0;
}

void CMainFrame::On32771()
{
	//退出
	//类似这些退出的函数，实际上应该写一个全局函数，处理一些内存释放，然后退出，这里直接粗暴退出，让系统进行资源释放.
	//exit(0);

	UnNormalExit();
}

void CMainFrame::On32772()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}

void CMainFrame::On32773()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}

void CMainFrame::On32774()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
}

void CMainFrame::On32775()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
}

void CMainFrame::On32776()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
}