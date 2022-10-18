
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "DreamTool.h"
#include "Common.h"

#include "MainFrm.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "DateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE相应的是自定义消息类型
	//这里是产生 EMOTIONSKY_* 消息，然后调用对应的函数进行处理
	ON_MESSAGE(EMOTIONSKY_A, OnSelectChanged)
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

#if 0
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
#endif

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

#if 0
	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#endif

	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)AfxGetApp()->LoadIconW(IDI_ICON_TOOL));

	//设置标题，右侧标题
	SetTitle(TEXT("emotionsky"));

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



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	//拆成一行两列
	m_spliter.CreateStatic(this, 1, 2);

	//左侧和右侧具体的显示内容，注意这里的窗口位置，这里的窗口大小
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(SelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(DisplayView), CSize(600, 500), pContext);

	return TRUE; //自己进行窗口拆分
}

LRESULT CMainFrame::OnSelectChanged(WPARAM wParam, LPARAM lParam)
{
	//通过这个上下文变量进行界面挂载的配置
	CCreateContext ctx;

	switch (wParam)
	{
	case EMOTIONSKY_A:
	{
		ctx.m_pNewViewClass = RUNTIME_CLASS(CDateView);                              //新的子窗口类名
		ctx.m_pCurrentFrame = this;                                                  //当前窗口的指针
		ctx.m_pLastView = dynamic_cast<CFormView*>(m_spliter.GetPane(0, 1));         //获取现在的子窗口对象
		m_spliter.DeleteView(0, 1);                                                  //删除现在显示的那个子窗口，后面要换新
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDateView), CSize(600, 500), &ctx); //创建新的子窗口对象
		CDateView* pNewView = dynamic_cast<CDateView*>(m_spliter.GetPane(0, 1));     //获取新的子窗口指针
		m_spliter.RecalcLayout();                                                    //设置新的子窗口布局
		pNewView->OnInitialUpdate();                                                 //手动调用新的子窗口的初始化
		m_spliter.SetActivePane(0, 1);                                               //设置活动窗口
		break;
	}
	default:
		break;
	}

	return 0;
}
