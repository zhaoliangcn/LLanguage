/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpRegExpObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "ScriptEngine.h"
#include "ScpTableObject.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpRegExpObject::ScpRegExpObject()
{
	objecttype = ObjRegExp;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_match, InnerFunction_match);
	BindObjectInnerFuction(scpcommand_en_match, InnerFunction_match);

	BindObjectInnerFuction(scpcommand_cn_find, InnerFunction_find);
	BindObjectInnerFuction(scpcommand_en_find, InnerFunction_find);

	BindObjectInnerFuction(scpcommand_cn_replace, InnerFunction_replace);
	BindObjectInnerFuction(scpcommand_en_replace, InnerFunction_replace);

}
ScpRegExpObject::~ScpRegExpObject()
{

}
ScpObject * ScpRegExpObject::Clone(std::string strObjName)
{
	ScpRegExpObject *obj = new ScpRegExpObject;
	if (obj)
	{
		obj->wstrregexp = wstrregexp;
		return obj;
	}

	return NULL;
}	
std::string ScpRegExpObject::ToString()
{
	std::string temp;
	temp+=wstrregexp;
	return temp;
}
void ScpRegExpObject::Release() 
{
	delete this;
}
bool ScpRegExpObject::Compile(std::string regexp)
{
	bool ret = true;
#ifdef _WIN32
	wstrregexp=regexp;
	try
	{
		rgx = regexp;
	}
	catch(...)
	{
		ret = false;
	}
#endif
	return ret;
}
bool  ScpRegExpObject::Find(std::string Text)
{
	bool ret = false;
#ifdef _WIN32
	try
	{
		ret = regex_search(Text,rgx);
	}
	catch(...)
	{
		ret = false;
	}
#endif
	return ret;
}
bool ScpRegExpObject::Match(std::string Text)
{
	return false;
}
bool ScpRegExpObject::Replace(std::string Text,std::string Text2)
{
	return false;
}
ScpObject * ScpRegExpObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpRegExpObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
				tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}
ScpObject * ScpRegExpObject::InnerFunction_match(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string text = parameters->at(0);
		StringStripQuote(text);
		ScpIntObject* intobj = (ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		ScpStringObject *obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjString)
				text = obj->content;
		}
		if (((ScpRegExpObject*)thisObject)->Find(text))
		{
			intobj->value = 1;
		}
		else
		{
			intobj->value = 0;
		}
		return intobj;
	}
	return nullptr;
}
ScpObject * ScpRegExpObject::InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		bool bfind = false;
		int count = 0;
		std::string text = parameters->at(0);
		StringStripQuote(text);
		ScpTableObject* tableobj = (ScpTableObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjTable);
		ScpStringObject *obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjString)
				text = obj->content;
		}
		rgxiter first(text.begin(), text.end(), ((ScpRegExpObject*)thisObject)->rgx);
		rgxiter last;
		while (first != last)
		{
			bfind = true;
			count++;
			ScpStringObject *obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			obj->content = first->str();
			tableobj->AddElement(first->str() + IntToString(count), obj);
			first++;
		}
		if (bfind)
			return tableobj;
		else
			tableobj->DelRef();
		return NULL;
	}
	return nullptr;
}
ScpObject * ScpRegExpObject::InnerFunction_replace(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		bool bfind = false;
		int count = 0;
		std::string text = parameters->at(0);
		std::string reptext = parameters->at(1);
		StringStripQuote(reptext);
		StringStripQuote(text);
		ScpStringObject *obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjString)
				text = obj->content;
		}
		ScpStringObject *obj1 = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(reptext);
		if (obj1)
		{
			if (obj1->GetType() == ObjString)
				reptext = obj1->content;
		}
		ScpStringObject *objret = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
		objret->content = std::regex_replace(text, ((ScpRegExpObject*)thisObject)->rgx, reptext);
		return objret;
	}
	return nullptr;
}
void ScpRegExpObject::Show(CScriptEngine * engine)
{
	engine->PrintError(wstrregexp);
}
bool ScpRegExpObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpRegExpObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;	
}

ScpObject * __stdcall ScpRegExpObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() >= 2)
	{
		std::string &strobj = paramters->at(0);
		std::string &userobjname = paramters->at(1);
		std::string content;
		if (paramters->size() == 3)
			content = paramters->at(2);
		ScpRegExpObject * regexpobj = new ScpRegExpObject;
		if (regexpobj)
		{
			ScpStringObject * obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(content);
			if (obj)
			{
				if (obj->GetType() == ObjString)
				{
					content = obj->content;
				}
			}
			StringStripQuote(content);
			regexpobj->wstrregexp = content;
			regexpobj->Compile(content);
			return regexpobj;
		}
	}
	return NULL;
}
