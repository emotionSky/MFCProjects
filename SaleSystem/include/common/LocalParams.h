#pragma once

#include <list>
#include <vector>
#include <cstring>
#include "pch.h"

class Commodity
{
public:
	int     m_id;        //商品id
	int     m_price;     //商品价格
	int     m_count;     //商品数量
	CString m_name;      //商品名称
};

class LocalParams
{
private:
	LocalParams();

public:
	static LocalParams* Instance();
	static void DestroyInstance();
	~LocalParams();
	bool Init();

	CString GetLoginName() const { return m_loginName; }
	CString GetLoginPwd() const { return m_loginPwd; }

	void SetLoginName(const CString& name) { m_loginName = name; }
	void SetLoginPwd(const CString& pwd) { m_loginPwd = pwd; }
	bool SaveLogin();

	bool IsCommodityExist(const CString& name);
	const std::list<Commodity*>& GetAll() const { return m_commodities; }
	void GetCommodityName(std::vector<CString>& cs);
	const Commodity* GetCommodityByName(const CString& name);

	bool AddNewCommodity(const CString& name, int price, int count);
	bool SellCommodity(const CString& name, int num);
	bool AddCommodity(const CString& name, int num);
	
private:
	bool ReadLogin();
	bool ReadCommodities();
	bool SaveCommodities();

private:
#if 0
	class Commodity
	{
	public:
		int     m_id;        //商品id
		int     m_price;     //商品价格
		int     m_count;     //商品数量
		CString m_name;      //商品名称
	};
#endif

private:
	CString               m_loginName;   //登录账号
	CString               m_loginPwd;    //登录密码
	//如果是多线程操作，这里还是需要用上锁
	//实际上这里使用map/unordered_map更合适
	std::list<Commodity*> m_commodities; //商品信息
};

//全局函数，非正常退出函数
void UnNormalExit();