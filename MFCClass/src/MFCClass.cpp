#include "MFCClass.h"

//��֤������ȫ��Ψһ��
static MyApp app;

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

BOOL MyApp::InitInstance()
{
	m_pMainWnd = new MyFrame();            //������������
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL); //��ʾ����
	m_pMainWnd->UpdateWindow();            //���´���
	return TRUE;
}

BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN() //����������
	ON_WM_CHAR() //����
	ON_WM_PAINT() //��ͼ��
END_MESSAGE_MAP()

MyFrame::MyFrame()
{
	Create(nullptr, TEXT("���Դ���")); //��������
}

MyFrame::~MyFrame()
{
}

void MyFrame::OnLeftButtonDown(UINT, CPoint point)
{
	//TCHAR buf[1024];
	//wsprintf(buf, TEXT("x = %d, y =%d"), point.x, point.y);
	//MessageBox(buf);


	//mfc�е��ַ���  CString
	CString str;
	str.Format(TEXT("x = %d ,,,, y = %d "), point.x, point.y);
	MessageBox(str);
}

void MyFrame::OnKeyboard(UINT key, UINT, UINT)
{
	CString str;
	str.Format(TEXT("������%c ��"), key);
	MessageBox(str);
}

void MyFrame::OnPaint()
{
	CPaintDC dc(this);  //CDC�����������ܻ���ͼ�� 

	dc.TextOutW(100, 100, TEXT("Ϊ�˲���"));
	//����Բ
	dc.Ellipse(10, 10, 100, 100);

	//���ֽ�תΪ ���ֽ� 
	//TEXT��������Ӧ�����ת��
	// TCHER ����Ӧ�����ת��
	//MessageBox(L"aaa");

	//ͳ���ַ�������
	int num = 0;
	const char* p = "aaaa";
	num = strlen(p);

	//ͳ�ƿ��ֽڵ��ַ�������
	const wchar_t* p2 = L"bbbb";
	num = wcslen(p2);

	//char * �� CString֮���ת��   C++  string  .c_str();
	//char* -> CString
	const char* p3 = "ccc";
	CString str = CString(p3);
	//CString  -> char *
	CStringA tmp;
	tmp = str;
	char* pp = tmp.GetBuffer();
}
