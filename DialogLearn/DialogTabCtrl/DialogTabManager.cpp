// DialogTabManager.cpp: 实现文件
//

#include "pch.h"
#include "DialogTabCtrl.h"
#include "afxdialogex.h"
#include "DialogTabManager.h"


// DialogTabManager 对话框

IMPLEMENT_DYNAMIC(DialogTabManager, CDialogEx)

DialogTabManager::DialogTabManager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

DialogTabManager::~DialogTabManager()
{
}

void DialogTabManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTabManager, CDialogEx)
END_MESSAGE_MAP()


// DialogTabManager 消息处理程序
