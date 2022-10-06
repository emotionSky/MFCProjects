// DialogLogin.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "component/DialogLogin.h"
#include "common/LocalParams.h"
#include "Resource.h"

// DialogLogin 对话框

IMPLEMENT_DYNAMIC(DialogLogin, CDialogEx)

DialogLogin::DialogLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

DialogLogin::~DialogLogin()
{
}

BOOL DialogLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//默认登录信息
	m_user = TEXT("管理员");
	UpdateData(FALSE); //将成员变量数据同步到界面上


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DialogLogin::OnOK()
{
	//CDialog::OnOK();
	//这里是避免直接回车之后退出的问题
	//一般情况下回车是登录
	OnBnClickedButtonLogin();
}

void DialogLogin::OnCancel()
{
	//CDialog::OnCancel();
	//exit(0);

	UnNormalExit();
}

void DialogLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_user);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
}


BEGIN_MESSAGE_MAP(DialogLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &DialogLogin::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &DialogLogin::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// DialogLogin 消息处理程序

void DialogLogin::OnBnClickedButtonLogin()
{
	UpdateData(TRUE); //将界面数据同步到成员变量上
	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("用户名和账号不可为空"));
		return;
	}

	CString name(LocalParams::Instance()->GetLoginName());
	CString pwd(LocalParams::Instance()->GetLoginPwd());

	if (name == m_user)
	{
		if (pwd == m_pwd)
			CDialog::OnOK(); //使用 OnOk() 或者 OnCancel() 退出当前对话框
		else
			MessageBox(TEXT("密码有误，请重新输入"));
	}
	else
	{
		MessageBox(TEXT("用户名有误"));
	}
}

//取消登录的消息处理
void DialogLogin::OnBnClickedButtonCancel()
{
	//exit(0);

	UnNormalExit();
}