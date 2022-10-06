// DialogInfo.cpp: 实现文件
//

#include "pch.h"
#include "resource.h"
#include "component/DialogInfo.h"
#include "common/LocalParams.h"

#define GET_ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

// DialogInfo

IMPLEMENT_DYNCREATE(DialogInfo, CFormView)

DialogInfo::DialogInfo()
	: CFormView(IDD_DIALOG_INFO)
{

}

DialogInfo::~DialogInfo()
{
}

void DialogInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_listInfo);
}

BEGIN_MESSAGE_MAP(DialogInfo, CFormView)
END_MESSAGE_MAP()


// DialogInfo 诊断

#ifdef _DEBUG
void DialogInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DialogInfo 消息处理程序


void DialogInfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//初始化好list显示
	//设置扩展风格
	m_listInfo.SetExtendedStyle(m_listInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//初始化表格
	CString filed[] = { _T("商品ID"), _T("商品名称"), _T("商品价格"), _T("商品库存") };
	for (int index = 0; index < GET_ARRAY_SIZE(filed); ++index)
		m_listInfo.InsertColumn(index, filed[index], LVCFMT_CENTER, 90);

	const std::list<Commodity*>& cs = LocalParams::Instance()->GetAll();
	CString str;
	int col = 0, row = 0;
	for (const auto& cc : cs)
	{
		str.Format(_T("%d"), cc->m_id);
		m_listInfo.InsertItem(col, str);
		row = 1;
		m_listInfo.SetItemText(col, row++, cc->m_name);
		str.Format(_T("%d"), cc->m_price);
		m_listInfo.SetItemText(col, row++, str);
		str.Format(_T("%d"), cc->m_count);
		m_listInfo.SetItemText(col, row++, str);

		++col;
	}
}
