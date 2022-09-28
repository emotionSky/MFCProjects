// DialogShow.cpp: 实现文件
//

#include "pch.h"
#include "DialogTest.h"
#include "afxdialogex.h"
#include "DialogShow.h"


// DialogShow 对话框

IMPLEMENT_DYNAMIC(DialogShow, CDialogEx)

DialogShow::DialogShow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW, pParent)
{

}

DialogShow::~DialogShow()
{
}

void DialogShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogShow, CDialogEx)
END_MESSAGE_MAP()


// DialogShow 消息处理程序
