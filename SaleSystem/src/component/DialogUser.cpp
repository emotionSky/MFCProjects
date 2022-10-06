// DialogUser.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "component/DialogUser.h"
#include "common/LocalParams.h"


// DialogUser

IMPLEMENT_DYNCREATE(DialogUser, CFormView)

DialogUser::DialogUser()
	: CFormView(IDD_DIALOG_USER)
	, m_identify(_T(""))
	, m_user(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

DialogUser::~DialogUser()
{
}

void DialogUser::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();

	//初始化
	m_identify = TEXT("销售员");
	m_user = CString(LocalParams::Instance()->GetLoginName());
	UpdateData(FALSE);
}

void DialogUser::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
	DDX_Text(pDX, IDC_EDIT1, m_identify);
}

BEGIN_MESSAGE_MAP(DialogUser, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &DialogUser::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogUser::OnBnClickedButton1)
END_MESSAGE_MAP()


#ifdef _DEBUG
void DialogUser::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogUser::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void DialogUser::OnBnClickedButton3()
{
	//修改密码
	UpdateData(TRUE);

	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入的密码不可为空！"));
		return;
	}

	//新密码必须和确认密码一致
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码和确认密码必须一致！"));
		return;
	}

	//新密码和旧密码不能一致
	if (m_newPwd == CString(LocalParams::Instance()->GetLoginPwd()))
	{
		MessageBox(TEXT("新密码和当前密码不可一致！"));
		return;
	}

	//保存密码
	LocalParams::Instance()->SetLoginPwd(m_newPwd);
	LocalParams::Instance()->SaveLogin();
	MessageBox(TEXT("密码修改成功"));

	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}

void DialogUser::OnBnClickedButton1()
{
	//清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
