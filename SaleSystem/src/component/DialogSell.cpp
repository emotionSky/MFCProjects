// DialogSell.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "component/DialogSell.h"
#include "common/LocalParams.h"
#include "Resource.h"


// DialogSell 对话框

IMPLEMENT_DYNCREATE(DialogSell, CFormView)

DialogSell::DialogSell()
	: CFormView(IDD_DIALOG_SELL)
	, m_price(0)
	, m_left(0)
	, m_count(0)
	, m_sellInfo(_T(""))
{

}

DialogSell::~DialogSell()
{
}

void DialogSell::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_product);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT5, m_left);
	DDX_Text(pDX, IDC_EDIT6, m_count);
	DDX_Text(pDX, IDC_EDIT3, m_sellInfo);
}


BEGIN_MESSAGE_MAP(DialogSell, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DialogSell::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogSell::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &DialogSell::OnBnClickedButton3)
END_MESSAGE_MAP()


#ifdef _DEBUG
void DialogSell::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogSell::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void DialogSell::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//初始化销售订单窗口
	//初始化下拉框
	std::vector<CString> cs;
	LocalParams::Instance()->GetCommodityName(cs);
	for (const auto& cc : cs)
		m_product.AddString(cc);

	//默认选中第一个
	m_product.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void DialogSell::OnCbnSelchangeCombo1()
{
	//切换商品触发的事件
	int index = m_product.GetCurSel();
	CString name;
	m_product.GetLBText(index, name);

	const Commodity* p = LocalParams::Instance()->GetCommodityByName(name);
	if (p)
	{
		m_price = p->m_price;
		m_left = p->m_count;
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("并没有找到该商品的信息。"));
	}
}


void DialogSell::OnBnClickedButton1()
{
	//购买的事件
	UpdateData(TRUE);

	if (m_count <= 0)
	{
		MessageBox(_T("购买内容数量必须大于零"));
		return;
	}
	else if (m_count > m_left)
	{
		MessageBox(_T("商品库存不足"));
		return;
	}

	int index = m_product.GetCurSel();
	CString name;
	m_product.GetLBText(index, name);
	if (LocalParams::Instance()->SellCommodity(name, m_count))
	{
		const Commodity* p = LocalParams::Instance()->GetCommodityByName(name);
		if (p)
		{
			//这里使用\r\n是因为Windows……
			m_sellInfo.Format(_T("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name/*.GetBuffer()*/, m_price, m_count, m_count * m_price);
			m_left = p->m_count;
			UpdateData(FALSE);
			MessageBox(_T("购买成功"));
			goto label_back;
		}
		else
		{
			MessageBox(_T("系统内部错误"));
			goto label_back;
		}
	}
	else
	{
		MessageBox(_T("系统内部错误"));
		goto label_back;
	}

label_back:
	m_count = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}


void DialogSell::OnBnClickedButton3()
{
	//取消按钮的事件响应
	m_count = 0;
	m_sellInfo.Empty();

	m_product.SetCurSel(0);
	OnCbnSelchangeCombo1();
}
