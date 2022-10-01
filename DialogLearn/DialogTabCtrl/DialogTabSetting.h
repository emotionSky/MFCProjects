#pragma once
#include "afxdialogex.h"


// DialogTabSetting 对话框

class DialogTabSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTabSetting)

public:
	DialogTabSetting(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogTabSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
