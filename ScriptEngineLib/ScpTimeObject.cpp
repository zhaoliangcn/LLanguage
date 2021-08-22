/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpTimeObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "../Common/commonutil.hpp"
#include "../Common/stdstringext.hpp"
#include "ScriptEngine.h"
#include "ScpObjectNammes.h"
#include "commanddefine_uni.h"

ScpTimeObject::ScpTimeObject(void)
{
	objecttype= ObjTime;
	value = 0;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_transform, InnerFunction_transform);
	BindObjectInnerFuction(scpcommand_en_transform, InnerFunction_transform);

	BindObjectInnerFuction(scpcommand_cn_format, InnerFunction_format);
	BindObjectInnerFuction(scpcommand_en_format, InnerFunction_format);

	BindObjectInnerFuction(str_CN_year, InnerFunction_year);
	BindObjectInnerFuction(str_EN_year, InnerFunction_year);

	BindObjectInnerFuction(str_CN_month, InnerFunction_month);
	BindObjectInnerFuction(str_EN_month, InnerFunction_month);

	BindObjectInnerFuction(str_CN_day, InnerFunction_day);
	BindObjectInnerFuction(str_EN_day, InnerFunction_day);


	BindObjectInnerFuction(str_CN_hour, InnerFunction_hour);
	BindObjectInnerFuction(str_EN_hour, InnerFunction_hour);

	BindObjectInnerFuction(str_CN_minute, InnerFunction_minute);
	BindObjectInnerFuction(str_EN_minute, InnerFunction_minute);

	BindObjectInnerFuction(str_CN_second, InnerFunction_second);
	BindObjectInnerFuction(str_EN_second, InnerFunction_second);

}


ScpTimeObject::~ScpTimeObject(void)
{
}

void ScpTimeObject::Show(CScriptEngine * engine)
{
	if(name ==ScpObjectNames::GetSingleInsatnce()->strObjCurrentTime)
	{
		ShowNow(engine);
	}
	else
	{
	struct tm  timeinfo; 
#ifdef _WIN32
	localtime_s ( &timeinfo,&value );
#else 
	localtime_r ( &value ,&timeinfo);
#endif
	char strTime[100]={0};
#ifdef _WIN32
        asctime_s(strTime,sizeof(strTime),&timeinfo);
#else
        asctime_r(&timeinfo,strTime);
#endif
	engine->PrintError(STDSTRINGEXT::AToW(strTime));
	}
}
ScpObject * ScpTimeObject::Clone(std::wstring strObjName)
{
	ScpTimeObject * obj = new ScpTimeObject;
	if (obj)
	{
		obj->value = value;
		obj->name = name;
		return obj;
	}
	return NULL;
}	
std::wstring ScpTimeObject::ToString()
{
	std::wstring temp;
	temp = Now();
	return temp;
}
void ScpTimeObject::Release() 
{
	delete this;
}
bool ScpTimeObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpTimeObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
int ScpTimeObject::Compare(ScpTimeObject* time1,ScpTimeObject* time2)
{
	return (int)difftime(time1->value,time2->value);
}
ScpIntObject ScpTimeObject::LessThan(ScpTimeObject* time1,ScpTimeObject* time2)
{
	ScpIntObject ret;
	ret.value=Compare(time1,time2)<0?1:0;
	return ret;
}
ScpIntObject ScpTimeObject::BigThan(ScpTimeObject* time1,ScpTimeObject* time2)
{
	ScpIntObject ret;
	ret.value=Compare(time1,time2)>0?1:0;
	return ret;
}
ScpIntObject ScpTimeObject::BigorEqul(ScpTimeObject* time1,ScpTimeObject* time2)
{
	ScpIntObject ret;
	ret.value=Compare(time1,time2)>=0?1:0;
	return ret;
}
ScpIntObject ScpTimeObject::LessOrEqul(ScpTimeObject* time1,ScpTimeObject* time2)
{
	ScpIntObject ret;
	ret.value=Compare(time1,time2)<=0?1:0;
	return ret;
}
ScpIntObject ScpTimeObject::Equl(ScpTimeObject* time1,ScpTimeObject* time2)
{
	ScpIntObject ret;
	ret.value=Compare(time1,time2)==0?1:0;
	return ret;
}
void ScpTimeObject::ShowNow(CScriptEngine * engine)
{
	engine->PrintError(Now());
}
std::wstring ScpTimeObject::Now()
{
	time_t rawtime; 
	struct tm  timeinfo; 
	time ( &rawtime ); 
#ifdef _WIN32
	localtime_s ( &timeinfo,&rawtime );
#else 
	localtime_r ( &rawtime,&timeinfo );
#endif
	char strTime[100]={0};
#ifdef _WIN32
    asctime_s(strTime,sizeof(strTime),&timeinfo);
#else
    asctime_r(&timeinfo,strTime);
#endif
	return STDSTRINGEXT::AToW(strTime);
}
time_t ScpTimeObject::GetNow()
{
	time_t rawtime; 
	time ( &rawtime ); 
	return rawtime;
}
int ScpTimeObject::GetYear()
{
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &value);
#else
	localtime_r(&value, &timeinfo);
#endif

	return timeinfo.tm_year+1900;
}
int ScpTimeObject::GetMonth()
{
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &value);
#else
	localtime_r(&value, &timeinfo);
#endif

	return timeinfo.tm_mon + 1;
}
int ScpTimeObject::GetDay()
{
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &value);
#else
	localtime_r(&value, &timeinfo);
#endif

	return timeinfo.tm_mday;
}
	int ScpTimeObject::GetHour()
	{
        struct tm  timeinfo;
#ifdef _WIN32
		localtime_s(&timeinfo, &value);
#else
	localtime_r ( &value,&timeinfo );
#endif
        
        return timeinfo.tm_hour;
	}
	int ScpTimeObject::GetMinute()
	{
        struct tm  timeinfo;
#ifdef _WIN32
		localtime_s(&timeinfo, &value);
#else
		localtime_r ( &value,&timeinfo );
#endif        
		return timeinfo.tm_min;

	}
	int ScpTimeObject::GetSecond()
	{
        struct tm  timeinfo;
#ifdef _WIN32
		localtime_s(&timeinfo, &value);
#else
		localtime_r ( &value,&timeinfo );
#endif      
		return timeinfo.tm_sec;

	}

	ScpObject * ScpTimeObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		thisObject->Show(engine);
		return thisObject;
	}

	ScpObject * ScpTimeObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		if (parameters->size() == 1)
		{
			std::wstring param0 = parameters->at(0);
			StringStripQuote(param0);
			ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
			if (objparam0 && objparam0->GetType() == ObjString)
			{
				if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
					((ScpStringObject *)objparam0)->content == str_CN_ObjType)
				{
					ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
					tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
					tname->istemp = true;
					return tname;
				}
			}
			if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
			{
				ScpStringObject * tname = new ScpStringObject;
				tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_transform(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		if (parameters->size() == 1)
		{
			std::wstring formattype = parameters->at(0);
			StringStripQuote(formattype);
			ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(formattype);
			if (objparam0 && objparam0->GetType() == ObjString)
			{
				formattype = ((ScpStringObject *)objparam0)->content;
			}
			if (formattype == L"GMT")
			{
				time_t rawTime =((ScpTimeObject*) thisObject)->value;
				struct tm* timeInfo;
				char szTemp[64] = { 0 };
				time(&rawTime);
				timeInfo = gmtime(&rawTime);
				strftime(szTemp, sizeof(szTemp), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
				ScpStringObject * tname = new ScpStringObject;
				tname->content = STDSTRINGEXT::AToW(szTemp);
				tname->istemp = true;
				return tname;
			}

		}
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_format(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_year(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		ScpIntObject * year = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (year)
		{
			year->value = ((ScpTimeObject*)thisObject)->GetYear();
			year->istemp = true;
			return year;
		}

		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_month(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		ScpIntObject * month = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (month)
		{
			month->value = ((ScpTimeObject*)thisObject)->GetMonth();
			month->istemp = true;
			return month;
		}
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_day(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		ScpIntObject * day = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (day)
		{
			day->value = ((ScpTimeObject*)thisObject)->GetDay();
			day->istemp = true;
			return day;
		}
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_hour(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		ScpIntObject * hour = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (hour)
		{
			hour->value = ((ScpTimeObject*)thisObject)->GetHour();
			hour->istemp = true;
			return hour;
		}
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_minute(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		ScpIntObject * minute = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (minute)
		{
			minute->value = ((ScpTimeObject*)thisObject)->GetMinute();
			minute->istemp = true;
			return minute;
		}
		return nullptr;
	}

	ScpObject * ScpTimeObject::InnerFunction_second(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		ScpIntObject * second = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (second)
		{
			second->value = ((ScpTimeObject*)thisObject)->GetSecond();
			second->istemp = true;
			return second;
		}
		return nullptr;
	}

	ScpObject * __stdcall ScpTimeObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
	{
		return new ScpTimeObject;
	}
