#include "MFCClass.h"

//保证对象是全局唯一的
static MyApp app;

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

BOOL MyApp::InitInstance()
{
	m_pMainWnd = new MyFrame();            //创建框架类对象
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL); //显示窗口
	m_pMainWnd->UpdateWindow();            //更新窗口
	return TRUE;
}

BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN() //鼠标左键按下
	ON_WM_CHAR() //键盘
	ON_WM_PAINT() //绘图宏
END_MESSAGE_MAP()

MyFrame::MyFrame()
{
	Create(nullptr, TEXT("测试窗口")); //创建窗口
}

MyFrame::~MyFrame()
{
}

void MyFrame::OnLeftButtonDown(UINT, CPoint point)
{
	//TCHAR buf[1024];
	//wsprintf(buf, TEXT("x = %d, y =%d"), point.x, point.y);
	//MessageBox(buf);


	//mfc中的字符串  CString
	CString str;
	str.Format(TEXT("x = %d ,,,, y = %d "), point.x, point.y);
	MessageBox(str);
}

void MyFrame::OnKeyboard(UINT key, UINT, UINT)
{
	CString str;
	str.Format(TEXT("按下了%c 键"), key);
	MessageBox(str);
}

void MyFrame::OnPaint()
{
	CPaintDC dc(this);  //CDC里找其他的能画的图形 

	dc.TextOutW(100, 100, TEXT("为了部落"));
	//画椭圆
	dc.Ellipse(10, 10, 100, 100);

	//多字节转为 宽字节 
	//TEXT是由自适应编码的转换
	// TCHER 自适应编码的转换
	//MessageBox(L"aaa");

	//统计字符串长度
	int num = 0;
	const char* p = "aaaa";
	num = strlen(p);

	//统计宽字节的字符串长度
	const wchar_t* p2 = L"bbbb";
	num = wcslen(p2);

	//char * 与 CString之间的转换   C++  string  .c_str();
	//char* -> CString
	const char* p3 = "ccc";
	CString str = CString(p3);
	//CString  -> char *
	CStringA tmp;
	tmp = str;
	char* pp = tmp.GetBuffer();
}
