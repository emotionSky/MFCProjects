
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

//自定义的消息ID，这个将在处理消息时作为一个标识
#define NM_A (WM_USER + 100)
#define NM_B (WM_USER + 101)
#define NM_C (WM_USER + 102)
#define NM_D (WM_USER + 103)
#define NM_E (WM_USER + 104)


class CMainFrame : public CFrameWnd
{	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	//自定义消息的实现函数
	afx_msg LRESULT OnSelectChanged(WPARAM wParam, LPARAM lParam);

public:
	//标题栏的一些控件的响应函数
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32776();

private:
	CSplitterWnd m_spliter; //拆分窗口类对象
};


