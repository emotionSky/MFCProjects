#ifndef __MFC_CLASS_H__
#define __MFC_CLASS_H__

#include <afxwin.h>

class MyApp : public CWinApp
{
public:
	MyApp();
	~MyApp();

	//��������
	virtual BOOL InitInstance();
};

class MyFrame : public CFrameWnd
{
public:
	MyFrame();
	virtual ~MyFrame();

	//�����꣬�ṩ��Ϣӳ�����
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLeftButtonDown(UINT, CPoint);
	afx_msg void OnKeyboard(UINT, UINT, UINT);
	afx_msg void OnPaint();
};

#endif //!__MFC_CLASS_H__
