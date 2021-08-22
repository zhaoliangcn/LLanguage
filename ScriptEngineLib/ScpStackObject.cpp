/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpStackObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "ScpStringObject.h"
#include "../Common/commonutil.hpp"

ScpStackObject::ScpStackObject()
{
	objecttype = ObjStack;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_push, InnerFunction_push);
	BindObjectInnerFuction(scpcommand_en_push, InnerFunction_push);

	BindObjectInnerFuction(scpcommand_cn_pop, InnerFunction_pop);
	BindObjectInnerFuction(scpcommand_cn_pop, InnerFunction_pop);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);
}


ScpStackObject::~ScpStackObject()
{
}



void ScpStackObject::Show(CScriptEngine * engine)
{
	if (scpstack.size() > 0)
	{
		ScpStack::iterator it = scpstack.begin();
		while (it != scpstack.end())
		{
			(*it)->Show(engine);
			it++;
		}
		
	}
}

ScpObject * ScpStackObject::Clone(std::wstring strObjName)
{
	ScpStackObject * tmpobj = new ScpStackObject;
	tmpobj->scpstack = scpstack;
	return tmpobj;
}

std::wstring ScpStackObject::ToString()
{
	return std::wstring();
}

void ScpStackObject::Release()
{
	delete this;
}

bool ScpStackObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}

ScpObject * ScpStackObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpStackObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpStackObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpStackObject::InnerFunction_push(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters && parameters->size() == 1)
	{
		std::wstring objname = parameters->at(0);
		StringStripQuote(objname);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindLocalObject(objname);
		if (obj)
		{
			((ScpStackObject*)thisObject)->scpstack.push_front(obj);
			return thisObject;
		}
	}
	return nullptr;
}

ScpObject * ScpStackObject::InnerFunction_pop(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (((ScpStackObject*)thisObject)->scpstack.size() > 0)
	{
		ScpObject * obj = ((ScpStackObject*)thisObject)->scpstack.front();
		((ScpStackObject*)thisObject)->scpstack.pop_front();
		return obj;
	}
	return nullptr;
}

ScpObject * ScpStackObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * ret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (ret)
	{
		ret->value = ((ScpStackObject*)thisObject)->scpstack.size();
		return ret;
	}
	return nullptr;
}

ScpObject * __stdcall ScpStackObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpStackObject;
}
