#include "ScpAddressObject.h"
#include "../ScriptEngineLib/NumberHelp.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../Common/commonutil.hpp"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
ScpObject * __stdcall ScpAddressObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	ScpAddressObject * objaddr = new ScpAddressObject;
	if (paramters->size() == 4)
	{
		
		objaddr->addressname = paramters->at(1);
		objaddr->ip = paramters->at(2);
		objaddr->port = paramters->at(3);
		StringStripQuote(objaddr->ip);
		StringStripQuote(objaddr->port);
	}
	return objaddr;
}
BOOL WINAPI AddressObject_Set_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	BOOL ret = FALSE;
	if (vtparameters->size() == 3)
	{
		std::wstring objname1 = vtparameters->at(0);
		std::wstring objname2 = vtparameters->at(1);
		std::wstring objname3 = vtparameters->at(2);
		
		ScpObject * obj = (ScpObject *)currentObjectSpace->FindObject(objname1);
		if (obj && obj->GetType() == ObjAddress)
		{
			if (objname2 == str_CN_ScpAddressParameterIp || objname2 == str_EN_ScpAddressParameterIp)
			{
				((ScpAddressObject *)obj)->ip = objname3;
			}
			else(objname2 == str_CN_ScpAddressParameterPort || objname2 == str_EN_ScpAddressParameterPort);
			{
				((ScpAddressObject *)obj)->port = objname3;
			}
			return TRUE;
		}
	}
	return FALSE;
}
ScpAddressObject::ScpAddressObject(void)
{
	objecttype = ObjAddress;
	addressname = L"";
	ip=L"";
	port=L"";
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_set, InnerFunction_Set);
	BindObjectInnerFuction(scpcommand_en_set, InnerFunction_Set);
}

ScpAddressObject::~ScpAddressObject(void)
{
	
}


void ScpAddressObject::Show(CScriptEngine * engine) 
{
	std::wstring text;
	text=STDSTRINGEXT::Format(L"%s %s %s",addressname.c_str(),ip.c_str(),port.c_str());
	engine->PrintError(text);
}
std::wstring ScpAddressObject::ToString()
{
	std::wstring temp;
	temp=STDSTRINGEXT::Format(L"%s %s %s",addressname.c_str(),ip.c_str(),port.c_str());
	return temp;
}
void ScpAddressObject::Release() 
{
	delete this;
}
bool ScpAddressObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpAddressObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this,parameters, engine);
	}
	return NULL;
}
ScpObject * ScpAddressObject::Clone(std::wstring strObjName)
{
	ScpAddressObject *obj = new ScpAddressObject;
	if (obj)
	{
		obj->addressname = addressname;
		obj->ip = ip;
		obj->port = port;
		return obj;
	}
	return NULL;
}	

void ScpAddressObject::SetIp(std::wstring strip)
{
	ip = strip;
}
void ScpAddressObject::SetPort(std::wstring strport)
{
	port = strport;
}
std::wstring ScpAddressObject::GetIp()
{
	return ip;
}
int ScpAddressObject::GetPort()
{
	return StringToInt(port.c_str());
}
ScpObject * ScpAddressObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpAddressObject::InnerFunction_Get(ScpObject * thisObject,  VTPARAMETERS * parameters, CScriptEngine * engine)
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
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
			else if (((ScpStringObject *)objparam0)->content == str_CN_ScpAddressParameterIp || 
				((ScpStringObject *)objparam0)->content == str_EN_ScpAddressParameterIp)
			{
				ScpStringObject * tname = new ScpStringObject;
				tname->content = ((ScpAddressObject*)thisObject)->GetIp();
				tname->istemp = true;
				return tname;
			}
			else if (((ScpStringObject *)objparam0)->content == str_CN_ScpAddressParameterPort ||
				((ScpStringObject *)objparam0)->content == str_EN_ScpAddressParameterPort)
			{
				ScpStringObject * tname = new ScpStringObject;
				tname->content = ((ScpAddressObject*)thisObject)->GetPortStr();
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
		else if (parameters->at(0) == str_CN_ScpAddressParameterIp || parameters->at(0) == str_EN_ScpAddressParameterIp)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = ((ScpAddressObject*)thisObject)->GetIp();
			tname->istemp = true;
			return tname;
		}
		else if (parameters->at(0) == str_CN_ScpAddressParameterPort || parameters->at(0) == str_EN_ScpAddressParameterPort)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = ((ScpAddressObject*)thisObject)->GetPortStr();
			tname->istemp = true;
			return tname;
		}
	}
	return NULL;
}
ScpObject * ScpAddressObject::InnerFunction_Set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
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
			if (((ScpStringObject *)objparam0)->content == str_CN_ScpAddressParameterIp ||
				((ScpStringObject *)objparam0)->content == str_EN_ScpAddressParameterIp)
			{
				std::wstring ip = parameters->at(1);
				StringStripQuote(ip);
				ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(ip);
				if (obj && obj->GetType() == ObjString)
				{
					ip = ((ScpStringObject*)obj)->content;
					StringStripQuote(ip);
				}
				
				((ScpAddressObject*)thisObject)->SetIp(ip);
			}
			else if (((ScpStringObject *)objparam0)->content == str_CN_ScpAddressParameterPort || 
				((ScpStringObject *)objparam0)->content == str_EN_ScpAddressParameterPort)
			{
				std::wstring port = parameters->at(1);
				StringStripQuote(port);
				ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(port);
				if (obj && obj->GetType() == ObjString)
				{
					port = ((ScpStringObject*)obj)->content;
					StringStripQuote(port);
				}
				
				((ScpAddressObject*)thisObject)->SetPort(port);
			}
		}
		if (parameters->at(0) == str_CN_ScpAddressParameterIp || parameters->at(0) == str_EN_ScpAddressParameterIp)
		{
			std::wstring ip = parameters->at(1);
			ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(ip);
			if (obj && obj->GetType() == ObjString)
			{
				ip = ((ScpStringObject*)obj)->content;
			}
			StringStripQuote(ip);
			((ScpAddressObject*)thisObject)->SetIp(ip);
		}
		else if (parameters->at(0) == str_CN_ScpAddressParameterPort || parameters->at(0) == str_EN_ScpAddressParameterPort)
		{
			std::wstring port = parameters->at(1);
			ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(port);
			if (obj && obj->GetType() == ObjString)
			{
				port = ((ScpStringObject*)obj)->content;
			}
			StringStripQuote(port);
			((ScpAddressObject*)thisObject)->SetPort(port);
		}
	}
	return nullptr;
}
std::wstring ScpAddressObject::GetPortStr()
{
	return port;
}
