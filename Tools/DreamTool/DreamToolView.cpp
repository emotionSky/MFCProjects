﻿
// DreamToolView.cpp: CDreamToolView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DreamTool.h"
#endif

#include "DreamToolDoc.h"
#include "DreamToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDreamToolView

IMPLEMENT_DYNCREATE(CDreamToolView, CView)

BEGIN_MESSAGE_MAP(CDreamToolView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDreamToolView 构造/析构

CDreamToolView::CDreamToolView() noexcept
{
	// TODO: 在此处添加构造代码

}

CDreamToolView::~CDreamToolView()
{
}

BOOL CDreamToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDreamToolView 绘图

void CDreamToolView::OnDraw(CDC* /*pDC*/)
{
	CDreamToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDreamToolView 打印

BOOL CDreamToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDreamToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDreamToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDreamToolView 诊断

#ifdef _DEBUG
void CDreamToolView::AssertValid() const
{
	CView::AssertValid();
}

void CDreamToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDreamToolDoc* CDreamToolView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDreamToolDoc)));
	return (CDreamToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CDreamToolView 消息处理程序
