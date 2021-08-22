/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//时间对象
*/
#ifndef _H_SCPTIMEOBJECT
#define _H_SCPTIMEOBJECT
#include <time.h>
#include "ScpObject.h"
#include "ScpIntObject.h"


const static wchar_t *str_CN_year = L"年";
const static wchar_t *str_CN_month = L"月";
const static wchar_t *str_CN_day = L"日";
const static wchar_t *str_CN_hour= L"时";
const static wchar_t *str_CN_minute = L"分";
const static wchar_t *str_CN_second = L"秒";

const static wchar_t * str_EN_year = L"year";
const static wchar_t *str_EN_month = L"month";
const static wchar_t *str_EN_day = L"day";
const static wchar_t *str_EN_hour = L"hour";
const static wchar_t *str_EN_minute = L"minute";
const static wchar_t *str_EN_second = L"second";

class ScpTimeObject :public ScpObject
{
public:
	ScpTimeObject(void);
	~ScpTimeObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters,CScriptEngine * engine);
	static int Compare(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject LessThan(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject BigThan(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject BigorEqul(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject LessOrEqul(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject Equl(ScpTimeObject* time1,ScpTimeObject* time2);
	static void ShowNow(CScriptEngine * engine);
	static std::wstring Now();
	static time_t GetNow();
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();
	int GetSecond();
	time_t value;
	std::wstring name;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_transform(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_format(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_year(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_month(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_day(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_hour(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_minute(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_second(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};


ScpObject * __stdcall ScpTimeObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPTIMEOBJECT