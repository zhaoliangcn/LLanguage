/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpRandomNumberObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "commanddefine_uni.h"
#include "ScriptEngine.h"
#include <random>
#include "../Common/commonutil.hpp"
ScpRandomNumberObject::ScpRandomNumberObject(void)
{
	objecttype = ObjRandomNumber;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_refresh, InnerFunction_refresh);
	BindObjectInnerFuction(scpcommand_en_refresh, InnerFunction_refresh);
}

ScpRandomNumberObject::~ScpRandomNumberObject(void)
{

}
ScpIntObject ScpRandomNumberObject::GetRandom()
{
	
	ScpIntObject ret ;
#ifdef _WIN32
	std::tr1::mt19937 eng;
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	eng.seed((ULONG)li.QuadPart); 
	//eng.seed(GetTickCount()); 
	std::tr1::uniform_int<int> unif(1, 2147483647);
	ret.value=unif(eng);
#else
	std::mt19937 eng;
	eng.seed((ULONG)time(0));
	std::uniform_int_distribution<> unif(1, 2147483647);
	ret.value = unif(eng);
#endif
	return ret;
}
ScpIntObject ScpRandomNumberObject::Refresh(ScpIntObject &currentvalue)
{
	ScpIntObject ret ;
	do
	{		
		ret=GetRandom(); 					
	}while(currentvalue.value==ret.value);
	return ret;
}
void ScpRandomNumberObject::SetValue(const ScpIntObject &v)
{
	value = v;
}
ScpIntObject ScpRandomNumberObject::GetValue()
{
	return value;
}

ScpObject * ScpRandomNumberObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpRandomNumberObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpRandomNumberObject::InnerFunction_refresh(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpRandomNumberObject*)thisObject)->SetValue(((ScpRandomNumberObject*)thisObject)->Refresh(((ScpRandomNumberObject*)thisObject)->value));
	return thisObject;

}

void ScpRandomNumberObject::Show(CScriptEngine * engine)
{
	value.Show(engine);
}
ScpObject * ScpRandomNumberObject::Clone(std::wstring strObjName)
{
	ScpRandomNumberObject * obj = new ScpRandomNumberObject;
	if (obj)
	{
		obj->value = value;
		return obj;
	}
	return NULL;
}	
std::wstring ScpRandomNumberObject::ToString()
{
	std::wstring temp;
	return temp;
}
void ScpRandomNumberObject::Release() 
{
	delete this;
}
bool ScpRandomNumberObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpRandomNumberObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;

}

ScpObject * __stdcall ScpRandomNumberObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() == 2)
	{
		std::wstring &strobj = paramters->at(0);
		std::wstring &userobjname = paramters->at(1);
		
		ScpRandomNumberObject *obj = new ScpRandomNumberObject;
		if (obj)
		{			
			return obj;
		}
	}
	return NULL;
}
