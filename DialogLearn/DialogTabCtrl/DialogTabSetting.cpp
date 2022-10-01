// DialogTabSetting.cpp: 实现文件
//

#include "pch.h"
#include "DialogTabCtrl.h"
#include "afxdialogex.h"
#include "DialogTabSetting.h"


// DialogTabSetting 对话框

IMPLEMENT_DYNAMIC(DialogTabSetting, CDialogEx)

DialogTabSetting::DialogTabSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

DialogTabSetting::~DialogTabSetting()
{
}

void DialogTabSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTabSetting, CDialogEx)
END_MESSAGE_MAP()


// DialogTabSetting 消息处理程序
