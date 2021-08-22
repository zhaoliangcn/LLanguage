/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpQueueObject.h"
#include "ScriptEngine.h"
#include "ScpStringObject.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"

ScpQueueObject::ScpQueueObject()
{
	objecttype = ObjQueue;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_add, InnerFunction_add);
	BindObjectInnerFuction(scpcommand_en_add, InnerFunction_add);

	BindObjectInnerFuction(scpcommand_cn_pop, InnerFunction_pop);
	BindObjectInnerFuction(scpcommand_cn_pop, InnerFunction_pop);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);

}


ScpQueueObject::~ScpQueueObject()
{
}



void ScpQueueObject::Show(CScriptEngine * engine)
{
	if (scpqueue.size() > 0)
	{
		ScpQueue::iterator it = scpqueue.begin();
		while (it != scpqueue.end())
		{
			(*it)->Show(engine);
			it++;
		}
	}
}

ScpObject * ScpQueueObject::Clone(std::wstring strObjName)
{
	ScpQueueObject * tmpobj = new ScpQueueObject;
	tmpobj->scpqueue = scpqueue;
	return tmpobj;
}

std::wstring ScpQueueObject::ToString()
{
	return std::wstring();
}

void ScpQueueObject::Release()
{
	delete this;
}

bool ScpQueueObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}

ScpObject * ScpQueueObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpQueueObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpQueueObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpQueueObject::InnerFunction_add(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters && parameters->size() == 1)
	{
		std::wstring objname = parameters->at(0);
		StringStripQuote(objname);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindLocalObject(objname);
		if (obj)
		{
			((ScpQueueObject*)thisObject)->scpqueue.push_back(obj);
			return thisObject;
		}
	}
	return nullptr;
}

ScpObject * ScpQueueObject::InnerFunction_pop(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (((ScpQueueObject*)thisObject)->scpqueue.size() > 0)
	{
		ScpObject * obj = ((ScpQueueObject*)thisObject)->scpqueue.front();
		((ScpQueueObject*)thisObject)->scpqueue.pop_front();
		return obj;
	}
	return nullptr;
}

ScpObject * ScpQueueObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * ret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (ret)
	{
		ret->value = ((ScpQueueObject*)thisObject)->scpqueue.size();
		return ret;
	}
	return nullptr;
}

ScpObject * __stdcall ScpQueueObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpQueueObject;
}
