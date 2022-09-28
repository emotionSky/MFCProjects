// DialogExec.cpp: 实现文件
//

#include "pch.h"
#include "DialogTest.h"
#include "afxdialogex.h"
#include "DialogExec.h"


// DialogExec 对话框

IMPLEMENT_DYNAMIC(DialogExec, CDialogEx)

DialogExec::DialogExec(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXEC, pParent)
{

}

DialogExec::~DialogExec()
{
}

void DialogExec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogExec, CDialogEx)
END_MESSAGE_MAP()


// DialogExec 消息处理程序
