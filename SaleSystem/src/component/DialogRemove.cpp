// DialogRemove.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "component/DialogRemove.h"
#include "common/LocalParams.h"


// DialogRemove

IMPLEMENT_DYNCREATE(DialogRemove, CFormView)

DialogRemove::DialogRemove()
	: CFormView(IDD_DIALOG_REMOVE)
	, m_price(0)
	, m_count(0)
{

}

DialogRemove::~DialogRemove()
{
}

void DialogRemove::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_product);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_count);
}

BEGIN_MESSAGE_MAP(DialogRemove, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DialogRemove::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &DialogRemove::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogRemove::OnBnClickedButton1)
END_MESSAGE_MAP()


// DialogRemove 诊断

#ifdef _DEBUG
void DialogRemove::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogRemove::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DialogRemove 消息处理程序


void DialogRemove::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//初始化下拉框
	std::vector<CString> cs;
	LocalParams::Instance()->GetCommodityName(cs);
	for (const auto& cc : cs)
		m_product.AddString(cc);

	//默认选中第一个
	m_product.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void DialogRemove::OnCbnSelchangeCombo1()
{
	//切换商品触发的事件
	int index = m_product.GetCurSel();
	CString name;
	m_product.GetLBText(index, name);

	const Commodity* p = LocalParams::Instance()->GetCommodityByName(name);
	if (p)
	{
		m_price = p->m_price;
		m_count = p->m_count;
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("并没有找到该商品的信息。"));
	}
}


void DialogRemove::OnBnClickedButton3()
{
	UpdateData(TRUE);

	if (m_count <= 0)
	{
		MessageBox(_T("删除的数量必须大于零"));
		return;
	}

	int index = m_product.GetCurSel();
	CString name;
	m_product.GetLBText(index, name);

	//删除和售出行为上相同
	if (LocalParams::Instance()->SellCommodity(name, m_count))
	{
		const Commodity* p = LocalParams::Instance()->GetCommodityByName(name);
		if (p)
		{
			m_count = p->m_count;
			UpdateData(FALSE);
			MessageBox(_T("删除成功"));
		}
		else
		{
			MessageBox(_T("系统内部错误"));
		}
	}
	else
	{
		MessageBox(_T("系统内部错误"));
	}
}


void DialogRemove::OnBnClickedButton1()
{
	m_product.SetCurSel(0);
	OnCbnSelchangeCombo1();
}
