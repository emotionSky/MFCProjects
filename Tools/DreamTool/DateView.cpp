// DateView.cpp: 实现文件
//

#include "pch.h"
#include "DreamTool.h"
#include "DateView.h"


// CDateView

IMPLEMENT_DYNCREATE(CDateView, CFormView)

CDateView::CDateView()
	: CFormView(IDD_DIALOG_DATE)
	, m_localEdit(_T(""))
	, m_abEdit(0)
	, m_localStyle(LocalStyle::NONE)
	, m_abStyle(AbStyle::NONE)
{

}

CDateView::~CDateView()
{
}

void CDateView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LOCAL, m_localCombo);
	DDX_Control(pDX, IDC_COMBO_AB, m_abCombo);
	DDX_Text(pDX, IDC_EDIT_LOCAL, m_localEdit);
	DDX_Text(pDX, IDC_EDIT_AB, m_abEdit);
}

BEGIN_MESSAGE_MAP(CDateView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCAL, &CDateView::OnCbnSelchangeComboLocal)
	ON_CBN_SELCHANGE(IDC_COMBO_AB, &CDateView::OnCbnSelchangeComboAb)
	ON_BN_CLICKED(IDC_BUTTON_TO_AB, &CDateView::OnBnClickedButtonToAb)
	ON_BN_CLICKED(IDC_BUTTON_TO_LOCAL, &CDateView::OnBnClickedButtonToLocal)
END_MESSAGE_MAP()


// CDateView 诊断

#ifdef _DEBUG
void CDateView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDateView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CDateView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_localCombo.AddString(_T("YYYY-MM-DD HH:MM:SS"));
	m_localCombo.AddString(_T("YYYY-MM-DDTHH:MM:SS"));

	m_abCombo.AddString(_T("绝对秒数"));

	m_localCombo.SetCurSel(0);
	OnCbnSelchangeComboLocal();
	m_abCombo.SetCurSel(0);
	OnCbnSelchangeComboAb();
}


void CDateView::OnCbnSelchangeComboLocal()
{
	int index = m_localCombo.GetCurSel();
	CString str;
	m_localCombo.GetLBText(index, str);

	if (str == _T("YYYY-MM-DD HH:MM:SS"))
		m_localStyle = LocalStyle::STYLE_1;
	else if (str == _T("YYYY-MM-DDTHH:MM:SS"))
		m_localStyle = LocalStyle::STYLE_2;
}


void CDateView::OnCbnSelchangeComboAb()
{
	int index = m_abCombo.GetCurSel();
	CString str;
	m_abCombo.GetLBText(index, str);

	if (str == _T("绝对秒数"))
		m_abStyle = AbStyle::STYLE_1;
}


void CDateView::OnBnClickedButtonToAb()
{
	UpdateData(TRUE);

	int year = 0, mon = 0, day = 0;
	int hour = 0, minu = 0, sec = 0;

	CStringA tmp;
	tmp = m_localEdit;

	switch (m_localStyle)
	{
	case LocalStyle::STYLE_1:
		sscanf(tmp.GetBuffer(), "%04d-%02d-%02d %02d:%02d:%02d", &year, &mon, &day, &hour, &minu, &sec);
		break;
	case LocalStyle::STYLE_2:
		sscanf(tmp.GetBuffer(), "%04d-%02d-%02dT%02d:%02d:%02d", &year, &mon, &day, &hour, &minu, &sec);
		break;
	default:
		break;
	}

	switch (m_abStyle)
	{
	case AbStyle::STYLE_1:
	{
		struct tm tm;
		memset(&tm, 0, sizeof(tm));

		tm.tm_year = year - 1900;
		tm.tm_mon = mon - 1;
		tm.tm_mday = day;
		tm.tm_hour = hour;
		tm.tm_min = minu;
		tm.tm_sec = sec;

		m_abEdit = mktime(&tm);
		break;
	}
		
	default:
		m_abEdit = 0;
		break;
	}

	UpdateData(FALSE);
}


void CDateView::OnBnClickedButtonToLocal()
{
	UpdateData(TRUE);

	int year = 0, mon = 0, day = 0;
	int hour = 0, minu = 0, sec = 0;

	switch (m_abStyle)
	{
	case AbStyle::STYLE_1:
	{
		struct tm tm;
		memset(&tm, 0, sizeof(tm));
		time_t t = m_abEdit;
		localtime_s(&tm, &t);

		year = tm.tm_year + 1900;
		mon = tm.tm_mon + 1;
		day = tm.tm_mday;
		hour = tm.tm_hour;
		minu = tm.tm_min;
		sec = tm.tm_sec;
		break;
	}

	default:
		break;
	}

	switch (m_localStyle)
	{
	case LocalStyle::STYLE_1:
		m_localEdit.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), year, mon, day, hour, minu, sec);
		break;
	case LocalStyle::STYLE_2:
		m_localEdit.Format(_T("%04d-%02d-%02dT%02d:%02d:%02d"), year, mon, day, hour, minu, sec);
		break;
	default:
		break;
	}

	UpdateData(FALSE);
}
