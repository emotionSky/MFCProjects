// DialogAdd.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "component/DialogAdd.h"
#include "common/LocalParams.h"


// DialogAdd

IMPLEMENT_DYNCREATE(DialogAdd, CFormView)

DialogAdd::DialogAdd()
	: CFormView(IDD_DIALOG_ADD)
	, m_price(0)
	, m_count(0)
	, m_newCommodity(_T(""))
	, m_newPrice(0)
	, m_newCount(0)
{

}

DialogAdd::~DialogAdd()
{
}

void DialogAdd::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_product);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_count);
	DDX_Text(pDX, IDC_EDIT4, m_newCommodity);
	DDX_Text(pDX, IDC_EDIT5, m_newPrice);
	DDX_Text(pDX, IDC_EDIT6, m_newCount);
}

BEGIN_MESSAGE_MAP(DialogAdd, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DialogAdd::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &DialogAdd::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &DialogAdd::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &DialogAdd::OnBnClickedButton5)
END_MESSAGE_MAP()


// DialogAdd 诊断

#ifdef _DEBUG
void DialogAdd::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogAdd::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DialogAdd 消息处理程序


void DialogAdd::OnInitialUpdate()
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


void DialogAdd::OnCbnSelchangeCombo1()
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


void DialogAdd::OnBnClickedButton1()
{
	//添加已有的商品
	UpdateData(TRUE);

	if (m_count <= 0)
	{
		MessageBox(_T("添加的数量必须大于零"));
		return;
	}

	int index = m_product.GetCurSel();
	CString name;
	m_product.GetLBText(index, name);
	if (LocalParams::Instance()->AddCommodity(name, m_count))
	{
		const Commodity* p = LocalParams::Instance()->GetCommodityByName(name);
		if (p)
		{
			CString str;
			str.Format(_T("商品[%s]添加成功"), name);
			m_count = p->m_count;
			UpdateData(FALSE);
			MessageBox(str);
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
	//m_count = 0;
	//UpdateData(FALSE);
	return;
}


void DialogAdd::OnBnClickedButton3()
{
	//取消添加已有商品
	m_count = 0;
	UpdateData(FALSE);
}


void DialogAdd::OnBnClickedButton4()
{
	//添加新商品

	UpdateData(TRUE);
	if (m_newCommodity.IsEmpty() || m_newPrice <= 0 || m_newCount <= 0)
	{
		MessageBox(_T("新商品信息有误"));
		return;
	}

	if (LocalParams::Instance()->IsCommodityExist(m_newCommodity))
	{
		//正常思路下，这个应该可以添加，只不过是程序多做一个逻辑处理
		MessageBox(_T("该商品已存在"));
		return;
	}

	if (LocalParams::Instance()->AddNewCommodity(m_newCommodity, m_newPrice, m_newCount))
	{
		const Commodity* p = LocalParams::Instance()->GetCommodityByName(m_newCommodity);
		if (p)
		{
			CString str;
			str.Format(_T("商品[%s]添加成功"), m_newCommodity);
			MessageBox(str);
			m_product.InsertString(0, m_newCommodity);
			m_product.SetCurSel(0);
			OnCbnSelchangeCombo1();
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
	m_newCommodity.Empty();
	m_newPrice = 0;
	m_newCount = 0;
	UpdateData(FALSE);
}


void DialogAdd::OnBnClickedButton5()
{
	//取消添加新商品
	m_newCommodity.Empty();
	m_newPrice = 0;
	m_newCount = 0;
	UpdateData(FALSE);
}
