
// DialogTreeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DialogTree.h"
#include "DialogTreeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma warining(disable : 6387)


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDialogTreeDlg 对话框



CDialogTreeDlg::CDialogTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGTREE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CDialogTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDialogTreeDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CDialogTreeDlg 消息处理程序

BOOL CDialogTreeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//树控件使用
	//1. 设置图标
	
	//准备HICON图标
	HICON icons[4];
	icons[0] = AfxGetApp()->LoadIconW(IDI_ICON1);
	icons[1] = AfxGetApp()->LoadIconW(IDI_ICON2);
	icons[2] = AfxGetApp()->LoadIconW(IDI_ICON3);
	icons[3] = AfxGetApp()->LoadIconW(IDI_ICON4);

	//CImageList img_list; //不能在栈上实现list，否则tree中的图片显示不正常
	//创建图片集合
	m_imgList.Create(30, 30, ILC_COLOR32, 4, 4);
	//添加具体的图片
	for (auto & icon : icons)
	{
		m_imgList.Add(icon);
	}
	m_tree.SetImageList(&m_imgList, TVSIL_NORMAL);

	//2. 设置节点
	//参数：  节点名称、显示的图片、选中后显示的图片、父节点
	HTREEITEM root = m_tree.InsertItem(TEXT("根节点"), 0, 0, nullptr);
	HTREEITEM parent = m_tree.InsertItem(TEXT("父节点"), 1, 1, root);
	HTREEITEM son1 = m_tree.InsertItem(TEXT("子节点1"), 2, 2, parent);
	HTREEITEM son2 = m_tree.InsertItem(TEXT("子节点2"), 3, 3, parent);

	//3. 设置默认选项
	m_tree.SelectItem(son1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDialogTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDialogTreeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDialogTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//树控件选项变化的消息处理函数
void CDialogTreeDlg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;

	//获取当前项
	HTREEITEM item = m_tree.GetSelectedItem();
	CString name = m_tree.GetItemText(item);
	MessageBox(name);
}
