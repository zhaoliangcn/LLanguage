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


const static char  *str_CN_year = "年";
const static char  *str_CN_month = "月";
const static char  *str_CN_day = "日";
const static char  *str_CN_hour= "时";
const static char  *str_CN_minute = "分";
const static char  *str_CN_second = "秒";

const static char  * str_EN_year = "year";
const static char  *str_EN_month = "month";
const static char  *str_EN_day = "day";
const static char  *str_EN_hour = "hour";
const static char  *str_EN_minute = "minute";
const static char  *str_EN_second = "second";

class ScpTimeObject :public ScpObject
{
public:
	ScpTimeObject(void);
	~ScpTimeObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters,CScriptEngine * engine);
	static int Compare(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject LessThan(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject BigThan(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject BigorEqul(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject LessOrEqul(ScpTimeObject* time1,ScpTimeObject* time2);
	static ScpIntObject Equl(ScpTimeObject* time1,ScpTimeObject* time2);
	static void ShowNow(CScriptEngine * engine);
	static std::string Now();
	static time_t GetNow();
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();
	int GetSecond();
	time_t value;
	std::string name;

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