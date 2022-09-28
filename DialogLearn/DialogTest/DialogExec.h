#pragma once
#include "afxdialogex.h"


// DialogExec 对话框

class DialogExec : public CDialogEx
{
	DECLARE_DYNAMIC(DialogExec)

public:
	DialogExec(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogExec();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXEC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
