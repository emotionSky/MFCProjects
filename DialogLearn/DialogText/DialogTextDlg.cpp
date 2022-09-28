
// DialogTextDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DialogText.h"
#include "DialogTextDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CDialogTextDlg 对话框



CDialogTextDlg::CDialogTextDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGTEXT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_staticText);
	DDX_Control(pDX, IDC_PICTURE, m_staticPic);
	DDX_Control(pDX, IDC_BUTTON_TEXT, m_btnText);
}

BEGIN_MESSAGE_MAP(CDialogTextDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogTextDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogTextDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_TEXT, &CDialogTextDlg::OnBnClickedButtonText)
END_MESSAGE_MAP()


// CDialogTextDlg 消息处理程序

BOOL CDialogTextDlg::OnInitDialog()
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

	//用static_text显示图片
	m_staticPic.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);

	//通过路径获取bitmap句柄
#define HBMP(filepath, width, height) \
(HBITMAP)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE | LR_CREATEDIBSECTION)

	//宽高设置应该按照控制大小取值
	CRect rect;
	m_staticPic.GetWindowRect(rect);

	//静态控制设置Bitmap
	m_staticPic.SetBitmap(HBMP(TEXT("./image/pic.bmp"), rect.Width(), rect.Height()));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDialogTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDialogTextDlg::OnPaint()
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
HCURSOR CDialogTextDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击设置按钮，设置文本内容
void CDialogTextDlg::OnBnClickedButton1()
{
	//设置文本内容
	m_staticText.SetWindowTextW(TEXT("这是设置后的静态文本"));
}

//点击获取按钮，获取文本内容
void CDialogTextDlg::OnBnClickedButton2()
{
	CString str;
	m_staticText.GetWindowTextW(str);
	MessageBox(str);
}

//双击之后修改内容
void CDialogTextDlg::OnBnClickedButtonText()
{
	//双击按钮，修改内容
	m_btnText.SetWindowTextW(TEXT("o_o"));

	//获取内容
	CString str;
	m_btnText.GetWindowTextW(str);
	MessageBox(str);

	//设置点击状态
	m_btnText.EnableWindow(FALSE);
}
