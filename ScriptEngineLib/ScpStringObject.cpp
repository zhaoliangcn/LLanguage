/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "ScriptEngine.h"
#include "ScpIntObject.h"
#include "ScpDoubleObject.h"
#include "ScpTableObject.h"
#include "ScpObjectNammes.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"




ScpStringObject::ScpStringObject()
{
	StringCodeType = scpStringCodeTypeUNICODE;
	objecttype = ObjString;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_transform, InnerFunction_transform);
	BindObjectInnerFuction(scpcommand_en_transform, InnerFunction_transform);


	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);

	BindObjectInnerFuction(scpcommand_cn_clear, InnerFunction_clear);
	BindObjectInnerFuction(scpcommand_en_clear, InnerFunction_clear);

	BindObjectInnerFuction(scpcommand_cn_getsubstring, InnerFunction_getsubstring);
	BindObjectInnerFuction(scpcommand_en_getsubstring, InnerFunction_getsubstring);

	BindObjectInnerFuction(scpcommand_cn_hash, InnerFunction_hash);
	BindObjectInnerFuction(scpcommand_en_hash, InnerFunction_hash);

	BindObjectInnerFuction(scpcommand_cn_format, InnerFunction_format);
	BindObjectInnerFuction(scpcommand_en_format, InnerFunction_format);

	BindObjectInnerFuction(scpcommand_cn_replace, InnerFunction_replace);
	BindObjectInnerFuction(scpcommand_en_replace, InnerFunction_replace);

	BindObjectInnerFuction(scpcommand_cn_find, InnerFunction_find);
	BindObjectInnerFuction(scpcommand_en_find, InnerFunction_find);

	BindObjectInnerFuction(scpcommand_cn_insert, InnerFunction_insert);
	BindObjectInnerFuction(scpcommand_en_insert, InnerFunction_insert);

	//BindObjectInnerFuction(scpcommand_cn_encode, InnerFunction_encode);
	//BindObjectInnerFuction(scpcommand_en_encode, InnerFunction_encode);

	//BindObjectInnerFuction(scpcommand_cn_decode, InnerFunction_decode);
	//BindObjectInnerFuction(scpcommand_en_decode, InnerFunction_decode);

	BindObjectInnerFuction(scpcommand_cn_split, InnerFunction_split);
	BindObjectInnerFuction(scpcommand_en_split, InnerFunction_split);


	//BindObjectInnerFuction(scpcommand_cn_encrypt, InnerFunction_encrypt);
	//BindObjectInnerFuction(scpcommand_en_encrypt, InnerFunction_encrypt);

	//BindObjectInnerFuction(scpcommand_cn_decrypt, InnerFunction_decrypt);
	//BindObjectInnerFuction(scpcommand_en_decrypt, InnerFunction_decrypt);

	BindObjectInnerFuction(scpcommand_cn_compare, InnerFunction_compare);
	BindObjectInnerFuction(scpcommand_en_compare, InnerFunction_compare);

	BindObjectInnerFuction(scpcommand_cn_connect, InnerFunction_connect);
	BindObjectInnerFuction(scpcommand_en_connect, InnerFunction_connect);

	BindObjectInnerFuction(str_CN_Length, InnerFunction_Length);
	BindObjectInnerFuction(str_EN_Length, InnerFunction_Length);

}
ScpStringObject::~ScpStringObject()
{
}

ScpObject * ScpStringObject::Clone(std::wstring strObjName)
{
	ScpObject *tmp = new ScpStringObject;
	((ScpStringObject*)tmp)->objname = strObjName;
	((ScpStringObject*)tmp)->content = this->content;
	return tmp;
}	
std::wstring ScpStringObject::ToString()
{
	std::wstring temp;
	temp = content;
	return temp;
}
void ScpStringObject::Release() 
{
	delete this;
}
bool ScpStringObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpStringObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
ScpStringObject * ScpStringObject::Reverse(ScpStringObject * str1)
{
	if(str1)
		str1->content = STDSTRINGEXT::Reverse(str1->content);
	return str1;
}
ScpStringObject * ScpStringObject::ToUpper(ScpStringObject * str1)
{
	if(str1)
		str1->content = STDSTRINGEXT::ToUpperW(str1->content);
	return str1;
}
ScpStringObject * ScpStringObject::ToLower(ScpStringObject * str1)
{
	if(str1)
		str1->content = STDSTRINGEXT::ToLowerW(str1->content);
	return str1;
}
ScpStringObject * ScpStringObject::ToHex(ScpStringObject * str1)
{
	return str1;
}
ScpStringObject *ScpStringObject::SubStr(ScpStringObject * org,ScpStringObject * sub,ULONG start,ULONG length)
{
	if(org && sub)
	{
		if ((start >= 0) && ((start+length) <= +org->content.length()))
		{
			sub->content = org->content.substr(start, length);
		}
	}
	return sub;
}
ScpStringObject *ScpStringObject::SubStr(ULONG start,ULONG length, CScriptEngine * engine)
{
	ScpStringObject * substring = (ScpStringObject * )engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
	if(substring)
	substring->content=this->content.substr(start,length);
	return substring;
}

ScpStringObject * ScpStringObject::SubStr(ULONG start, CScriptEngine * engine)
{
	ScpStringObject * substring = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
	if (substring)
		substring->content = this->content.substr(start);
	return substring;
}


ScpStringObject*  ScpStringObject::Format(ScpStringObject * str1,const wchar_t * strForm,VTPARAMETERS &parameters)
{
	if(parameters.size()==0)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm);
#else 
		swprintf(Buffer,4096,strForm);
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==1)
	{
		std::wstring temp = parameters.at(0);

		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,temp.c_str());
#else 
		swprintf(Buffer,4096,strForm,temp.c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==2)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),parameters.at(1).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),parameters.at(1).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==3)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),parameters.at(1).c_str(),parameters.at(2).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),parameters.at(1).c_str(),parameters.at(2).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==4)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),parameters.at(1).c_str(),parameters.at(2).c_str(),parameters.at(3).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),parameters.at(1).c_str(),parameters.at(2).c_str(),parameters.at(3).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==5)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),parameters.at(1).c_str(),parameters.at(2).c_str(),parameters.at(3).c_str(),parameters.at(4).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),parameters.at(1).c_str(),parameters.at(2).c_str(),parameters.at(3).c_str(),parameters.at(4).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==6)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==7)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==8)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str(),
			parameters.at(7).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str(),
			parameters.at(7).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==9)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str(),
			parameters.at(7).c_str(),
			parameters.at(8).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str(),
			parameters.at(7).c_str(),
			parameters.at(8).c_str());
#endif
		str1->content=Buffer;
	}
	else if (parameters.size()==10)
	{
		wchar_t Buffer[4096]={0};
#ifdef _WIN32
		swprintf(Buffer,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str(),
			parameters.at(7).c_str(),
			parameters.at(8).c_str(),
			parameters.at(9).c_str());
#else 
		swprintf(Buffer,4096,strForm,parameters.at(0).c_str(),
			parameters.at(1).c_str(),
			parameters.at(2).c_str(),
			parameters.at(3).c_str(),
			parameters.at(4).c_str(),
			parameters.at(5).c_str(),
			parameters.at(6).c_str(),
			parameters.at(7).c_str(),
			parameters.at(8).c_str(),
			parameters.at(9).c_str());
#endif
		str1->content=Buffer;
	}
	return str1;
}
void ScpStringObject::Show(CScriptEngine * engine)
{
	engine->PrintError(content);
}
void ScpStringObject::Clear()
{
	content=L"";
}
ULONG ScpStringObject::GetSize()
{
	return content.size();
}
ULONG ScpStringObject::GetLength()
{
	return content.length();
}
ScpStringObject* Connect(ScpStringObject * str1, ScpStringObject * str2, ScpStringObject* result)
{
	ScpStringObject* ret = (ScpStringObject*)result;
	ret->content = str1->content + str2->content;
	return ret;
}

ScpObject * __stdcall ScpStringObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() >= 2)
	{
		std::wstring &strobj = paramters->at(0);
		std::wstring &userobjname = paramters->at(1);
		std::wstring content;
		if (paramters->size() == 3)
			content = paramters->at(2);
		ScpStringObject *obj = new ScpStringObject;
		StringStripQuote(content);
		if (obj)
		{
			obj->content = content.c_str();
			return obj;
		}
	}
	return NULL;
}

ScpObject * ScpStringObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;

}

ScpObject * ScpStringObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
		if (param0 == str_EN_ObjType || param0 == str_CN_ObjType)
		{
			ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_transform(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring transtype = parameters->at(0);
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			transtype = ((ScpStringObject *)objparam0)->content;
		}
		if (transtype == ScpObjectNames::GetSingleInsatnce()->scpStringUpper)
		{
			ToUpper(((ScpStringObject*)thisObject));
			return thisObject;
		}
		else if (transtype == ScpObjectNames::GetSingleInsatnce()->scpStringLower)
		{
			ToLower(((ScpStringObject*)thisObject));
			return thisObject;
		}
		else if (transtype == ScpObjectNames::GetSingleInsatnce()->scpStringReverse)
		{
			Reverse(((ScpStringObject*)thisObject));
			return thisObject;
		}
		else if (transtype == ScpObjectNames::GetSingleInsatnce()->scpStringHex)
		{
			ToHex(((ScpStringObject*)thisObject));
			return thisObject;
		}
		else if (transtype == ScpGlobalObject::GetInstance()->GetTypeName(ObjInt))
		{
			ScpIntObject* obj1 = new ScpIntObject;
			if (IsStaticNumber(((ScpStringObject*)thisObject)->content))
			{
				obj1->value = StringToInt(((ScpStringObject*)thisObject)->content);
			}
			else
			{
				std::wstring ErrorMessage = STDSTRINGEXT::Format(L"%s %s", ((ScpStringObject*)thisObject)->content.c_str(), ScpObjectNames::GetSingleInsatnce()->scpErrorNotInt.c_str());
				engine->PrintError(ErrorMessage);
			}
			return obj1;
		}
		else if (transtype == ScpGlobalObject::GetInstance()->GetTypeName(ObjDouble))
		{
			ScpDoubleObject * obj1 = new ScpDoubleObject;
			if (IsStaticDoubleNumber(((ScpStringObject*)thisObject)->content))
			{
				obj1->value = StringToDouble(((ScpStringObject*)thisObject)->content);
			}
			else if (IsStaticNumber(((ScpStringObject*)thisObject)->content))
			{
				obj1->value = StringToDouble(((ScpStringObject*)thisObject)->content);
			}
			else
			{
				std::wstring ErrorMessage = STDSTRINGEXT::Format(L"%s %s", ((ScpStringObject*)thisObject)->content.c_str(), ScpObjectNames::GetSingleInsatnce()->scpErrorNotNumber.c_str());
				engine->PrintError(ErrorMessage);
			}
			return obj1;
		}
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * size = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (size)
	{
		size->value = ((ScpStringObject*)thisObject)->content.size();
		size->istemp = true;
	}
	return size;
}

ScpObject * ScpStringObject::InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpStringObject*)thisObject)->Clear();
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_getsubstring(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring strstart = parameters->at(0);
		StringStripQuote(strstart);
		ScpIntObject *objs = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(strstart);
		ScpStringObject *subobj = NULL;
		if (objs)
		{
			subobj = ((ScpStringObject*)thisObject)->SubStr(objs->value, engine);
			subobj->istemp = true;
		}
		else
		{
			subobj = ((ScpStringObject*)thisObject)->SubStr(StringToInt(strstart.c_str()), engine);
			subobj->istemp = true;
		}
		return subobj;
	}
	else if (parameters->size() == 2)
	{
		int istart = 0;
		int ilength = 0;
		std::wstring strstart = parameters->at(0);
		std::wstring strlength = parameters->at(1);
		ScpIntObject *objs = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(strstart);
		ScpIntObject *objl = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(strlength);
		if (objs)
		{
			istart = objs->value;
		}
		else
		{
			istart = StringToInt(strstart.c_str());
		}
		if (objl)
		{
			ilength = objl->value;
		}
		else
		{
			ilength = StringToInt(strlength.c_str());
		}
		ScpStringObject *subobj = subobj = ((ScpStringObject*)thisObject)->SubStr(istart, ilength, engine);
		subobj->istemp = true;
		return subobj;
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_hash(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	/*if (parameters->size() == 1)
	{
		std::wstring hashtype = parameters->at(0);
		StringStripQuote(hashtype);
		ScpStringObject * strobjhashtype = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(hashtype);
		if (strobjhashtype)
		{
			hashtype = strobjhashtype->content;
		}
		ScpStringObject * strobj2 = new ScpStringObject;
		if (strobj2)
		{
			ScpEncryptLib encryptlib;
			strobj2->content = encryptlib.HashString(((ScpStringObject*)thisObject)->content, hashtype);
			strobj2->istemp = false;
			return strobj2;
		}
	}*/
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_format(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() >= 1)
	{
		std::wstring wstrForm;
		wstrForm = parameters->at(0);
		StringStripQuote(wstrForm);
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			wstrForm = ((ScpStringObject *)objparam0)->content;
		}
		VTPARAMETERS param;
		if (parameters->size() > 1)
		{
			for (unsigned int i = 1;i < parameters->size();i++)
			{
				ScpObject * obj = (ScpObject*)engine->GetCurrentObjectSpace()->FindObject(parameters->at(i));
				if (obj)
				{
					std::wstring temp = obj->ToString();
					param.push_back(temp);
				}
				else
				{
					param.push_back(parameters->at(i));
				}
			}
		}
		((ScpStringObject*)thisObject)->Format(((ScpStringObject*)thisObject), wstrForm.c_str(), param);
		return thisObject;
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_replace(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		std::wstring substrname = parameters->at(0);
		std::wstring substrname2 = parameters->at(1);
		StringStripQuote(substrname);
		StringStripQuote(substrname2);
		ScpStringObject *subobj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(substrname);
		ScpStringObject *subobj2 = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(substrname2);
		StringStripQuote(substrname2);
		if (subobj2)
			substrname2 = subobj2->content;
		ScpIntObject * replaceret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		size_t pos = ((ScpStringObject*)thisObject)->content.find(subobj->content);
		if (pos != std::wstring::npos)
		{
			((ScpStringObject*)thisObject)->content.replace(pos, substrname2.length(), substrname2);
			replaceret->value = 1;
		}
		else
		{
			replaceret->value = 0;
		}
		replaceret->istemp = true;
		return replaceret;
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring substrname = parameters->at(0);
		StringStripQuote(substrname);
		ScpStringObject *subobj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(substrname);
		if (subobj)
		{
			substrname = subobj->content;
		}
		ScpIntObject * findret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (((ScpStringObject*)thisObject)->content.find(substrname) != std::wstring::npos)
		{
			findret->value = ((ScpStringObject*)thisObject)->content.find(substrname);
		}
		else
		{
			findret->value = -1;
		}
		findret->istemp = true;
		return findret;
	}
	else if (parameters->size() == 2)
	{
		std::wstring substrname = parameters->at(0);
		std::wstring substrpos = parameters->at(1);
		StringStripQuote(substrname);
		StringStripQuote(substrpos);
		int pos = 0;
		ScpStringObject *subobj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(substrname);
		if (subobj)
		{
			substrname = subobj->content;
		}
		ScpIntObject * subobjpoos = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(substrpos);
		if (subobjpoos)
		{
			pos = subobjpoos->value;
		}
		else
		{
			pos = StringToInt(substrpos);
		}
		ScpIntObject * findret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (((ScpStringObject*)thisObject)->content.find(substrname, pos) != std::wstring::npos)
		{
			findret->value = ((ScpStringObject*)thisObject)->content.find(substrname, pos);
		}
		else
		{
			findret->value = -1;
		}
		findret->istemp = true;
		return findret;
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_insert(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		std::wstring substrname = parameters->at(2);
		std::wstring posname = parameters->at(3);
		StringStripQuote(substrname);
		StringStripQuote(posname);
		ScpStringObject * substrobj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(substrname);
		ScpIntObject * intobj = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(posname);
		if (intobj)
		{
			if (substrobj)
			{
				((ScpStringObject*)thisObject)->content.insert(intobj->value, substrobj->content);
			}
			else
			{
				((ScpStringObject*)thisObject)->content.insert(intobj->value, substrname);
			}
		}
		return thisObject;
	}
	return nullptr;
}

//ScpObject * ScpStringObject::InnerFunction_encode(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
//{
	//if (parameters->size() == 1)
	//{
	//	std::wstring wsencodetype = parameters->at(0);
	//	if (wsencodetype == encodetypebase64)
	//	{
	//		ScpStringObject * obj2 = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
	//		std::string objectname1a = STDSTRINGEXT::WToA(((ScpStringObject*)thisObject)->content);
	//		ScpEncryptLib ec;
	//		obj2->content = ec.Base64Encode((unsigned char *)objectname1a.c_str(), objectname1a.length());
	//		obj2->istemp = true;
	//		return obj2;
	//	}
	//}
//	return nullptr;
//}

//ScpObject * ScpStringObject::InnerFunction_decode(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
//{
	/*if (parameters->size() == 1)
	{
		std::wstring wsdecodetype = parameters->at(0);
		if (wsdecodetype == encodetypebase64)
		{
			ScpStringObject * obj2 = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			std::string objectname1a = STDSTRINGEXT::WToA(((ScpStringObject*)thisObject)->content);
			ScpEncryptLib ec;
			obj2->content = ec.Base64Decode((unsigned char *)objectname1a.c_str(), objectname1a.length());
			obj2->istemp = true;
			return obj2;
		}
	}*/
//	return nullptr;
//}

ScpObject * ScpStringObject::InnerFunction_split(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring objname1 = ((ScpStringObject*)thisObject)->content;
		std::wstring objname2 = parameters->at(0);
		StringStripQuote(objname2);
		ScpStringObject * strobj2 = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(objname2);
		if (strobj2)
		{
			objname2 = strobj2->content;
			ScpTableObject * tableobj = new ScpTableObject;
			size_t pos = objname1.find(objname2);
			while (pos != std::wstring::npos)
			{
				std::wstring temp = objname1.substr(0, pos);
				ScpStringObject *  tempstrobj = new ScpStringObject;
				tempstrobj->content = temp;
				engine->GetCurrentObjectSpace()->AddObject(temp, tempstrobj);
				tableobj->AddElement(temp, tempstrobj);
				objname1 = objname1.substr(pos + 1, objname1.length() - pos - 1);
				pos = objname1.find(objname2);
			}
			if (!objname1.empty())
			{
				std::wstring temp = objname1;
				ScpStringObject *  tempstrobj = new ScpStringObject;
				tempstrobj->content = temp;
				engine->GetCurrentObjectSpace()->AddObject(temp, tempstrobj);
				tableobj->AddElement(temp, tempstrobj);
			}
			return tableobj;

		}
	}
	return nullptr;
}

//ScpObject * ScpStringObject::InnerFunction_encrypt(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
//{
	//if (parameters->size() == 1)
	//{
	//	std::wstring key = parameters->at(0);
	//	StringStripQuote(key);
	//	ScpStringObject * strobj1 = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(key);
	//	if (strobj1 && strobj1->GetType() == ObjString)
	//	{
	//		key = strobj1->content;
	//	}
	//	ScpEncryptLib encryptlib;
	//	((ScpStringObject*)thisObject)->content = encryptlib.EncryptString(((ScpStringObject*)thisObject)->content, EncryptTypeRC4, key);
	//	return thisObject;
	//}
//	return nullptr;
//}

//ScpObject * ScpStringObject::InnerFunction_decrypt(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
//{
	//if (parameters->size() == 1)
	//{
	//	std::wstring key = parameters->at(0);
	//	StringStripQuote(key);
	//	ScpStringObject * strobj1 = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(key);
	//	if (strobj1 && strobj1->GetType() == ObjString)
	//	{
	//		key = strobj1->content;
	//	}
	//	ScpEncryptLib encryptlib;
	//	((ScpStringObject*)thisObject)->content = encryptlib.DecryptString(((ScpStringObject*)thisObject)->content, EncryptTypeRC4, key);
	//	return thisObject;
	//}
//	return nullptr;
//}

ScpObject * ScpStringObject::InnerFunction_compare(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring str1 = parameters->at(0);
		StringStripQuote(str1);
		ScpIntObject * compare_ret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		compare_ret->value = 0;
		ScpStringObject *strobj1 = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(str1);
		if (strobj1)
		{
			if (((ScpStringObject*)thisObject)->content == strobj1->content)
			{
				compare_ret->value = 1;
			}
			else
			{
				compare_ret->value = 0;
			}
		}
		compare_ret->istemp = true;
		return compare_ret;
	}
	return nullptr;
}

ScpObject * ScpStringObject::InnerFunction_connect(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() >= 1)
	{
		for (int i = 0;i < parameters->size();i++)
		{
			std::wstring strobj = parameters->at(i);
			StringStripQuote(strobj);
			ScpObject *obj2 = engine->GetCurrentObjectSpace()->FindObject(strobj);
			if (obj2)
			{
				if (obj2->GetType() == ObjString)
				{
					((ScpStringObject*)thisObject)->content += ((ScpStringObject *)obj2)->content;
				}
				else
				{
					((ScpStringObject*)thisObject)->content += obj2->ToString();
				}
			}
		}
	}
	return thisObject;
}

ScpObject * ScpStringObject::InnerFunction_Length(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * objlength = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (objlength)
	{
		objlength->value = ((ScpStringObject*)thisObject)->content.length();
		objlength->istemp = true;
	}
	return objlength;
}
