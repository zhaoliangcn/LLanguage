/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpJsonObject.h"
#include "ScpFileObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpJsonObject::ScpJsonObject(void)
{
	objecttype = ObjJson;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_shutdown, InnerFunction_shutdown);
	BindObjectInnerFuction(scpcommand_en_shutdown, InnerFunction_shutdown);

	BindObjectInnerFuction(scpcommand_cn_open, InnerFunction_open);
	BindObjectInnerFuction(scpcommand_en_open, InnerFunction_open);

	BindObjectInnerFuction(scpcommand_cn_load, InnerFunction_load);
	BindObjectInnerFuction(scpcommand_en_load, InnerFunction_load);

	BindObjectInnerFuction(scpcommand_cn_save, InnerFunction_save);
	BindObjectInnerFuction(scpcommand_en_save, InnerFunction_save);

	BindObjectInnerFuction(scpcommand_cn_set, InnerFunction_set);
	BindObjectInnerFuction(scpcommand_en_set, InnerFunction_set);

}

ScpJsonObject::~ScpJsonObject(void)
{
}
void ScpJsonObject::Show(CScriptEngine * engine)
{
	engine->PrintError(ToString());	

}
ScpObject * ScpJsonObject::Clone(std::wstring strObjName)
{
	ScpJsonObject * obj = new ScpJsonObject;
	if (obj)
	{
		obj->jsonfileName = jsonfileName;
		return obj;
	}
	return NULL;
}	
std::wstring ScpJsonObject::ToString()
{
	std::wstring temp;
	temp=STDSTRINGEXT::AToW(ejson.ToString());
	return temp;
}
void ScpJsonObject::Release() 
{
	delete this;
}
bool ScpJsonObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpJsonObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
BOOL ScpJsonObject::Load(std::wstring jsonstring)
{
	return ejson.ParseString(STDSTRINGEXT::WToA(jsonstring).c_str());
}
BOOL ScpJsonObject::Save(std::wstring name)
{
	return FALSE;

}
BOOL ScpJsonObject::Open(std::wstring name)
{
	jsonfileName = name;
	if(ScpFileObject::FileExist(jsonfileName))
		return ejson.ParseFile(STDSTRINGEXT::WToA(jsonfileName).c_str());
	return FALSE;
}
BOOL ScpJsonObject::Close()
{
	jsonfileName=L"";
	return TRUE;
}
BOOL ScpJsonObject::GetValue(std::wstring tag,std::wstring& value)
{
	BOOL bRet=FALSE;
	char cvalue[256]={0};
	bRet= ejson.GetValue(STDSTRINGEXT::WToA(tag).c_str(),cvalue,256);
	value=STDSTRINGEXT::AToW(cvalue);
	return bRet;
}
BOOL ScpJsonObject::GetValue(std::wstring tag,int & value)
{
	BOOL bRet=FALSE;
	bRet= ejson.GetValue(STDSTRINGEXT::WToA(tag).c_str(),value);
	return bRet;
}
BOOL ScpJsonObject::SetValue(std::wstring tag,std::wstring value)
{
	BOOL bRet=FALSE;
	bRet= ejson.SetValue(STDSTRINGEXT::WToA(tag).c_str(),(char *)STDSTRINGEXT::WToA(value).c_str());
	return bRet;
}
BOOL ScpJsonObject::SetValue(std::wstring tag,int value)
{
	BOOL bRet=FALSE;
	bRet= ejson.SetValue(STDSTRINGEXT::WToA(tag).c_str(),value);
	return bRet;
}

ScpObject * ScpJsonObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;

}

ScpObject * ScpJsonObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
			ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			if (tname)
			{
				tname->content = ScpGlobalObject::GetInstance()->GetTypeName(((ScpJsonObject*)thisObject)->GetType());
				tname->istemp = true;
				return tname;
			}

		}
	}
	else if (parameters->size() == 2)
	{
		std::wstring objname2 = parameters->at(0);
		std::wstring objname3 = parameters->at(1);
		StringStripQuote(objname2);
		StringStripQuote(objname3);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(objname2);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			objname2 = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(objname3);
		if (objparam1 && objparam1->GetType() == ObjString)
		{
			objname3 = ((ScpStringObject *)objparam1)->content;
		}
		std::wstring content;
		int value;
		if (objname2 == str_CN_ObjValue ||
			objname2 == str_EN_ObjValue)
		{
			StringStripQuote(objname3);
			ScpObject * obj3 = engine->GetCurrentObjectSpace()->FindObject(objname3);
			if (obj3 && obj3->GetType() == ObjString)
			{
				objname3 = ((ScpStringObject*)obj3)->content;
			}
			if (((ScpJsonObject*)thisObject)->GetValue(objname3, content))
			{
				ScpStringObject * obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				if (obj)
				{
					obj->content = content;
					obj->istemp = true;
					return obj;
				}
			}
			else if (((ScpJsonObject*)thisObject)->GetValue(objname3, value))
			{
				ScpIntObject * obj = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
				if (obj)
				{
					obj->value = value;
					obj->istemp = true;
					return obj;
				}
			}
		}
	}
	return nullptr;
}

ScpObject * ScpJsonObject::InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpJsonObject*)thisObject)->Close();
	return nullptr;
}

ScpObject * ScpJsonObject::InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring userobjname = parameters->at(0);
		StringStripQuote(userobjname);
		ScpObject * userobj = engine->GetCurrentObjectSpace()->FindObject(userobjname);
		if (userobj)
		{
			if (userobj->GetType() == ObjString)
			{
				userobjname = ((ScpStringObject*)userobj)->content;
			}
		}
		StringStripQuote(userobjname);
		((ScpJsonObject*)thisObject)->Open(userobjname);
	}
	return nullptr;
}

ScpObject * ScpJsonObject::InnerFunction_load(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring userobjname = parameters->at(0);
		StringStripQuote(userobjname);
		ScpObject * userobj = engine->GetCurrentObjectSpace()->FindObject(userobjname);
		if (userobj)
		{
			if (userobj->GetType() == ObjString)
			{
				userobjname = ((ScpStringObject*)userobj)->content;
			}
		}
		StringStripQuote(userobjname);
		((ScpJsonObject*)thisObject)->Load(userobjname);
	}
	return nullptr;
}

ScpObject * ScpJsonObject::InnerFunction_save(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring userobjname = parameters->at(0);
		StringStripQuote(userobjname);
		ScpObject * userobj = engine->GetCurrentObjectSpace()->FindObject(userobjname);
		if (userobj)
		{
			if (userobj->GetType() == ObjString)
			{
				userobjname = ((ScpStringObject*)userobj)->content;
			}
		}
		StringStripQuote(userobjname);
		((ScpJsonObject*)thisObject)->Save(userobjname);
	}
	else if (parameters->size() == 0)
	{
		((ScpJsonObject*)thisObject)->Save();
	}
	return nullptr;
}

ScpObject * ScpJsonObject::InnerFunction_set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 3)
	{
		std::wstring objname2 = parameters->at(0);
		std::wstring objname3 = parameters->at(1);
		std::wstring content = parameters->at(2);
		StringStripQuote(objname2);
		StringStripQuote(objname3);
		StringStripQuote(content);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(objname2);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			objname2 = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(objname3);
		if (objparam1 && objparam1->GetType() == ObjString)
		{
			objname3 = ((ScpStringObject *)objparam1)->content;
		}
		ScpObject * objparam2 = engine->GetCurrentObjectSpace()->FindObject(content);
		if (objparam2 && objparam2->GetType() == ObjString)
		{
			content = ((ScpStringObject *)objparam2)->content;
		}
		int value;
		if (objname2 == str_CN_ObjValue ||
			objname2 == str_EN_ObjValue)
		{
			StringStripQuote(objname3);
			ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(content);
			if (obj)
			{
				if (obj->GetType() == ObjInt)
				{
					int value = ((ScpIntObject*)obj)->value;
					((ScpJsonObject*)thisObject)->SetValue(objname3, value);
				}
				else if (obj->GetType() == ObjString)
				{
					content = ((ScpStringObject*)obj)->content;
					((ScpJsonObject*)thisObject)->SetValue(objname3, content);
				}
				else
				{
					((ScpJsonObject*)thisObject)->SetValue(objname3, content);
				}
			}
		}
	}
	return nullptr;
}

ScpObject * __stdcall ScpJsonObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpJsonObject;
}
