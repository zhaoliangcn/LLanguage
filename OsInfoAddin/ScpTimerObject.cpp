#include "ScpTimerObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpObject * __stdcall ScpTimerObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpTimerObject();
}
ScpTimerObject::ScpTimerObject(void)
{
	objecttype =ObjTimer;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);
}

ScpTimerObject::~ScpTimerObject(void)
{
}
void ScpTimerObject::Set(std::string timername,ScpFunctionObject * func,ULONG val)
{
	name = timername;
	timerfunc= func;
	interval = val;

}
#ifdef _WIN32
void   __stdcall   ScpTimerObject::TimerProc(HWND   hwnd,unsigned int   uMsg,UINT_PTR   idEvent,DWORD   dwTime)
{

}
#endif
void ScpTimerObject::Start()
{
#ifdef _WIN32
	SetTimer(NULL,eventid,interval,TimerProc);
#endif
}
void ScpTimerObject::Stop()
{
#ifdef _WIN32
	KillTimer(NULL,eventid);
#endif
}

void ScpTimerObject::Show(CScriptEngine * engine)
{

}
ScpObject * ScpTimerObject::Clone(std::string strObjName)
{
	ScpTimerObject * obj = new ScpTimerObject;
	if (obj)
	{
		obj->timerfunc = timerfunc;
		obj-> name = name;
		obj->interval = interval;
		obj->eventid = eventid;
	}
	return NULL;
}	
std::string ScpTimerObject::ToString()
{
	std::string temp;
	return temp;
}
void ScpTimerObject::Release() 
{
	delete this;
}
bool ScpTimerObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpTimerObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpTimerObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpTimerObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}
