/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpMapObject.h"
#include "ScpStringObject.h"
#include "ScpTableObject.h"
#include "ScpGlobalObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"

ScpMapObject::ScpMapObject()
{
	objecttype = ObjMap;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_add, InnerFunction_add);
	BindObjectInnerFuction(scpcommand_en_add, InnerFunction_add);

	BindObjectInnerFuction(scpcommand_cn_clear, InnerFunction_clear);
	BindObjectInnerFuction(scpcommand_en_clear, InnerFunction_clear);

	BindObjectInnerFuction(scpcommand_cn_enum, InnerFunction_enum);
	BindObjectInnerFuction(scpcommand_en_enum, InnerFunction_enum);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);

	BindObjectInnerFuction(scpcommand_cn_erase, InnerFunction_erase);
	BindObjectInnerFuction(scpcommand_en_erase, InnerFunction_erase);


}
ScpMapObject::~ScpMapObject()
{
}
ScpObject * ScpMapObject::Clone(std::string strObjName)
{
	ScpMapObject * obj = (ScpMapObject *)new ScpMapObject;
	if (obj)
	{
		ITUSEROBJMAP it = scpobjectmap.begin();
		while (it != scpobjectmap.end())
		{
			ScpObject *objvalue = it->second->Clone("");
			if (objvalue)
			{
				objvalue->AddRef();
				obj->scpobjectmap[it->first] = objvalue;
			}
			it++;			
		}
	}
	return obj;
}	
std::string ScpMapObject::ToString()
{
	std::string temp;
	return temp;
}
void ScpMapObject::Release() 
{
	delete this;
}

void ScpMapObject::Show(CScriptEngine * engine)
{
}
bool ScpMapObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpMapObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
BOOL ScpMapObject::MapObject(std::string& key,std::string& value, CScriptEngine * engine)
{
	ScpObject * objkey = engine->GetCurrentObjectSpace()->FindObject(key);
	ScpObject * objvalue= engine->GetCurrentObjectSpace()->FindObject(value);
	std::string wskeystr = key;
	std::string wsvaluestr = value;
	if (objkey && objkey->GetType()==ObjString)
	{
		wskeystr = ((ScpStringObject *)objkey)->content;
	}
	if (!objvalue)
	{
		objvalue = new ScpStringObject;
		((ScpStringObject*)objvalue)->content = wsvaluestr;
	}
	else
	{
		if (objvalue->istemp)
		{
			objvalue->istemp = false;			
		}
	}
	objvalue->AddRef();
	ITUSEROBJMAP it =scpobjectmap.find(key);
	if(it==scpobjectmap.end())
	{
		scpobjectmap[wskeystr]= objvalue;
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMapObject::UnMapObject(std::string& key)
{
	ITUSEROBJMAP it =scpobjectmap.find(key);
	if(it!=scpobjectmap.end())
	{
		ScpObject * obj = it->second;
		scpobjectmap.erase(it);
		obj->DelRef();
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMapObject::UnMapObject(int index)
{
	if (index >= 0 && index < scpobjectmap.size())
	{
		ITUSEROBJMAP it = scpobjectmap.begin();
		while(index>0)
		{
			it++;
			index--;
		}
		ScpObject * obj = it->second;
		scpobjectmap.erase(it);
		obj->DelRef();
		return TRUE;
	}
	return FALSE;
}
ScpObject* ScpMapObject::GetKeyObject(std::string& key,ScpObjectSpace * objectSpace)
{
	ITUSEROBJMAP it =scpobjectmap.find(key);
	if(it!=scpobjectmap.end())
	{
		return objectSpace->FindObject(key);
	}
	return NULL;
}
ScpObject* ScpMapObject::GetValueObject(std::string& key,ScpObjectSpace * objectSpace)
{
	ScpObject * objkey = objectSpace->FindObject(key);
	std::string wskeystr = key;
	if (objkey && objkey->GetType() == ObjString)
	{
		wskeystr = ((ScpStringObject *)objkey)->content;
	}
	ITUSEROBJMAP it =scpobjectmap.find(wskeystr);
	if(it!=scpobjectmap.end())
	{
		return it->second;
	}
	return NULL;
}

ScpObject * ScpMapObject::GetValueObject(int index)
{
	if (index >= 0 && index < scpobjectmap.size())
	{
		ITUSEROBJMAP it = scpobjectmap.begin();
		while (index > 0)
		{
			it++;
			index--;
		}
		ScpObject * obj = it->second;
		return obj;
	}
	return NULL;
}

ScpObject * ScpMapObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpMapObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
			ScpStringObject * tname = new ScpStringObject;
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	else if (parameters->size() == 2)
	{
		std::string wsType, wsName;
		wsType = parameters->at(0);
		wsName = parameters->at(1);
		StringStripQuote(wsType);
		StringStripQuote(wsName);

		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(wsType);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			wsType = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(wsName);
		if (objparam1 && objparam1->GetType() == ObjString)
		{
			wsName = ((ScpStringObject *)objparam1)->content;
		}
		if (wsType == str_CN_ObjValue || 
			wsType == str_EN_ObjValue)
		{
			return ((ScpMapObject*)thisObject)->GetValueObject(wsName, engine->GetCurrentObjectSpace());
		}
		else if (IsStaticNumber(wsName))
		{
			return  ((ScpMapObject*)thisObject)->GetValueObject(StringToInt(wsName));
		}
	}
	return nullptr;
}

ScpObject * ScpMapObject::InnerFunction_add(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		std::string wsKey, wsValue;
		wsKey = parameters->at(0);
		wsValue = parameters->at(1);
		StringStripQuote(wsKey);
		StringStripQuote(wsValue);
		ScpIntObject * ret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		ret->value = 0;
		if (((ScpMapObject*)thisObject)->MapObject(wsKey, wsValue, engine))
		{
			ret->value = 1;
		}
		return ret;
	}
	return nullptr;
}

ScpObject * ScpMapObject::InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ITUSEROBJMAP it = ((ScpMapObject*)thisObject)->scpobjectmap.begin();
	if (it != ((ScpMapObject*)thisObject)->scpobjectmap.end())
	{
		ScpObject * obj = it->second;
		it = ((ScpMapObject*)thisObject)->scpobjectmap.erase(it);
		obj->DelRef();
	}
	return thisObject;
}

ScpObject * ScpMapObject::InnerFunction_enum(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpTableObject * tableobj = (ScpTableObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjTable);
	ITUSEROBJMAP it = ((ScpMapObject*)thisObject)->scpobjectmap.begin();
	if (it != ((ScpMapObject*)thisObject)->scpobjectmap.end())
	{
		ScpStringObject * strobj = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
		strobj->content = it->first;
		tableobj->AddElement(strobj->content, strobj);
	}
	return tableobj;
}

ScpObject * ScpMapObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * ret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	ret->value = ((ScpMapObject*)thisObject)->scpobjectmap.size();
	return ret;
}

ScpObject * ScpMapObject::InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string param0 = parameters->at(0);
		StringStripQuote(param0);
		if (IsStaticNumber(param0))
		{
			int index = StringToInt(param0);
			((ScpMapObject*)thisObject)->UnMapObject(index);
			return thisObject;
		}
	}
	return nullptr;
}

ScpObject * __stdcall ScpMapObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpMapObject;
}
