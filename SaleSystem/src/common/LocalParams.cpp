#include "pch.h" //这玩意必须放在第一行，否则编译不通过。微软的东西做的比QT差太远了

#include "common/LocalParams.h"
#include <cstdio>
#include <cstdlib>

constexpr auto _F_LOGIN = "login.ini";
constexpr auto _F_COMMDITY = "commdity.csv";

LocalParams::LocalParams()
{
	m_loginName = _T("");
	m_loginPwd = _T("");
}

static LocalParams* g_lp;
LocalParams* LocalParams::Instance()
{
	if (!g_lp)
		g_lp = new LocalParams();
	return g_lp;
}

void LocalParams::DestroyInstance()
{
	if (g_lp)
	{
		delete g_lp;
		g_lp = nullptr;
	}
}

LocalParams::~LocalParams()
{
	if (m_commodities.size())
	{
		for (auto& cc : m_commodities)
			delete cc;

		m_commodities.clear();
	}
}

bool LocalParams::Init()
{
	return ReadLogin() && ReadCommodities();
}

bool LocalParams::SaveLogin()
{
	FILE* fp = fopen(_F_LOGIN, "w");
	if (!fp)
		return false;

	CStringA tmp;
	tmp = m_loginName;
	fprintf(fp, "name=%s\n", tmp.GetBuffer());

	tmp = m_loginPwd;
	fprintf(fp, "password=%s\n", tmp.GetBuffer());
	fclose(fp);

	return true;
}

bool LocalParams::IsCommodityExist(const CString& name)
{
	for (const auto& cc : m_commodities)
	{
		if (cc->m_name == name)
			return true;
	}
	return false;
}

void LocalParams::GetCommodityName(std::vector<CString>& cs)
{
	for (const auto& cc : m_commodities)
		cs.push_back(cc->m_name);
}

const Commodity* LocalParams::GetCommodityByName(const CString& name)
{
	for (const auto& cc : m_commodities)
	{
		if (cc->m_name == name)
			return cc;
	}
	return nullptr;
}

bool LocalParams::AddNewCommodity(const CString& name, int price, int count)
{
	//这里可以进行判断，商品是否存在

	Commodity* cc = new Commodity();
	
	cc->m_id = (int)m_commodities.size() + 1;
	cc->m_name = name;
	cc->m_price = price;
	cc->m_count = count;

	m_commodities.emplace_back(cc);
	return SaveCommodities();
}

bool LocalParams::SellCommodity(const CString& name, int num)
{
	bool ret = false;
	for (auto& cc : m_commodities)
	{
		if (cc->m_name == name)
		{
			if (cc->m_count < num)
				return false;

			cc->m_count -= num;
			ret = true;
		}
	}

	//这里实际上还应该考虑如果保存失败，如何复原数据等等……
	//只不过一般情况下，只要文件没有被占用，写入都是没有问题的……
	return ret && SaveCommodities();
}

bool LocalParams::AddCommodity(const CString& name, int num)
{
	if (num <= 0)
		return false;

	for (auto& cc : m_commodities)
	{
		if (cc->m_name == name)
		{
			cc->m_count += num;
		}
	}

	//这里实际上还应该考虑如果保存失败，如何复原数据等等……
	//只不过一般情况下，只要文件没有被占用，写入都是没有问题的……
	return SaveCommodities();
}

bool LocalParams::ReadLogin()
{
	FILE* fp = fopen(_F_LOGIN, "r");
	if (!fp)
		return false;

	int ret = 0;
	char line[100];
	char key[20] = { 0 }, value[80] = { 0 };
	while (fgets(line, 100, fp))
	{
		ret = sscanf(line, "%[^=]=%s", key, value);

		if (ret != 2)
			return false;

		if (!strcmp(key, "name"))
			m_loginName = CString(value);
		else if (!strcmp(key, "password"))
			m_loginPwd = CString(value);
	}
	fclose(fp);

	if (m_loginName.IsEmpty())
		return false;

	return true;
}

bool LocalParams::ReadCommodities()
{
	FILE* fp = fopen(_F_COMMDITY, "r");
	if (!fp)
		return false;

	int ret = 0;
	bool bFirstLine = true;
	char line[100], name[40] = { 0 };

	while (fgets(line, 100, fp))
	{
		if (bFirstLine)
		{
			bFirstLine = false;
			continue;
		}

		Commodity* cc = new Commodity;
		ret = sscanf(line, "%d, %[^,], %d, %d", &cc->m_id, name, &cc->m_price, &cc->m_count);
		if (ret != 4)
			return false;

		cc->m_name = CString(name);
		m_commodities.emplace_back(cc);
	}

	fclose(fp);
	return true;
}

bool LocalParams::SaveCommodities()
{
	FILE* fp = fopen(_F_COMMDITY, "w");
	if (!fp)
		return false;

	fprintf(fp, "商品ID, 商品名称, 商品价格, 商品库存\n");

	CStringA tmp;
	for (const auto& cc : m_commodities)
	{
		tmp = cc->m_name;
		fprintf(fp, "%d, %s, %d, %d\n", cc->m_id, tmp.GetBuffer(), cc->m_price, cc->m_count);
	}

	fclose(fp);
	return true;
}

void UnNormalExit()
{
	LocalParams::DestroyInstance();
	exit(0);
}