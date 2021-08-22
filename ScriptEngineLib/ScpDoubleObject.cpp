/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpDoubleObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "ScpIntObject.h"
#include "../Common/commonutil.hpp"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include <math.h>
ScpDoubleObject::ScpDoubleObject()
{
	value = 0.0;
	objecttype = ObjDouble;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_transform, InnerFunction_transform);
	BindObjectInnerFuction(scpcommand_en_transform, InnerFunction_transform);

	BindObjectInnerFuction(scpcommand_square_CN, InnerFunction_square);
	BindObjectInnerFuction(scpcommand_square_EN, InnerFunction_square);

	BindObjectInnerFuction(scpcommand_squareroot_CN, InnerFunction_squareroot);
	BindObjectInnerFuction(scpcommand_squareroot_EN, InnerFunction_squareroot);

	BindObjectInnerFuction(scpcommand_cubic_CN, InnerFunction_cubic);
	BindObjectInnerFuction(scpcommand_cubic_EN, InnerFunction_cubic);

	BindObjectInnerFuction(scpcommand_cubic_CN, InnerFunction_cubic);
	BindObjectInnerFuction(scpcommand_cubic_EN, InnerFunction_cubic);

	BindObjectInnerFuction(scpcommand_cuberoot_CN, InnerFunction_cuberoot);
	BindObjectInnerFuction(scpcommand_cuberoot_EN, InnerFunction_cuberoot);

	BindObjectInnerFuction(scpcommand_abs_EN, InnerFunction_abs);
	BindObjectInnerFuction(scpcommand_abs_CN, InnerFunction_abs);

	BindObjectInnerFuction(scpcommand_acos_CN, InnerFunction_acos);
	BindObjectInnerFuction(scpcommand_acos_EN, InnerFunction_acos);

	BindObjectInnerFuction(scpcommand_cos_CN, InnerFunction_cos);
	BindObjectInnerFuction(scpcommand_cos_EN, InnerFunction_cos);

	BindObjectInnerFuction(scpcommand_asin_CN, InnerFunction_asin);
	BindObjectInnerFuction(scpcommand_asin_EN, InnerFunction_asin);

	BindObjectInnerFuction(scpcommand_sin_CN, InnerFunction_sin);
	BindObjectInnerFuction(scpcommand_sin_EN, InnerFunction_sin);

	BindObjectInnerFuction(scpcommand_atan_CN, InnerFunction_atan);
	BindObjectInnerFuction(scpcommand_atan_EN, InnerFunction_atan);

	BindObjectInnerFuction(scpcommand_tan_CN, InnerFunction_tan);
	BindObjectInnerFuction(scpcommand_tan_EN, InnerFunction_tan);
}
ScpDoubleObject::~ScpDoubleObject()
{

}
ScpObject * ScpDoubleObject::Clone(std::wstring strObjName)
{
	ScpObject * tmp=new ScpDoubleObject;
	((ScpDoubleObject*)tmp)->value=this->value;
	return tmp;
}	
std::wstring ScpDoubleObject::ToString()
{
	std::wstring temp;
	wchar_t Buffer[512]={0};
#ifdef _WIN32
    StringCbPrintfW(Buffer,sizeof(Buffer),L"%f",value);
#else 
	swprintf(Buffer,512,L"%f",value);	
#endif
	temp=Buffer;
	return temp;
}
void ScpDoubleObject::Release() 
{
	delete this;
}
void ScpDoubleObject::Show(CScriptEngine * engine)
{
	std::wstring text;
	text=STDSTRINGEXT::Format(L"%08f",value);
	engine->PrintError(text);
}
bool ScpDoubleObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpDoubleObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpDoubleObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpDoubleObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
		if (param0 == str_EN_ObjType ||
			param0 == str_CN_ObjType)
		{
			ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_transform(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * obj = (ScpObject*)engine->GetCurrentObjectSpace()->FindObject(param0);
		if (obj && obj->GetType() == ObjString)
		{
			param0 = ((ScpStringObject*)obj)->content;
		}
		StringStripQuote(param0);
		if (param0 == ScpGlobalObject::GetInstance()->GetTypeName(ObjString))
		{
			ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			tname->content = thisObject->ToString();
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_square(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = ((ScpDoubleObject*)thisObject)->value*((ScpDoubleObject*)thisObject)->value;
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_squareroot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = sqrt(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_cubic(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *tint = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		tint->value = ((ScpDoubleObject*)thisObject)->value*((ScpDoubleObject*)thisObject)->value*((ScpDoubleObject*)thisObject)->value;
		tint->istemp = true;
		return tint;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_cuberoot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = pow(((ScpDoubleObject*)thisObject)->value, 1.0 / 3);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_abs(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *tint = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		tint->value = abs(((ScpDoubleObject*)thisObject)->value);
		tint->istemp = true;
		return tint;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_acos(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = acos(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_cos(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = cos(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_asin(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = asin(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_sin(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = sin(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_atan(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = atan(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * ScpDoubleObject::InnerFunction_tan(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		ScpDoubleObject *td = (ScpDoubleObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjDouble);
		td->value = tan(((ScpDoubleObject*)thisObject)->value);
		td->istemp = true;
		return td;
	}
	return nullptr;
}

ScpObject * __stdcall ScpDoubleObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() >= 2)
	{
		std::wstring &strobj = paramters->at(0);
		std::wstring &userobjname = paramters->at(1);
		std::wstring content;
		if (paramters->size() == 3)
			content = paramters->at(2);
		ScpDoubleObject *obj = new ScpDoubleObject;
		if (obj)
		{
			if (IsStaticDoubleNumber(content))
			{
				obj->value = StringToDouble(content);
			}
			else if (IsStaticNumber(content))
			{
				obj->value = StringToDouble(content);
			}
			else
			{
				obj->value = 0;
			}
			return obj;
		}
	}
	return NULL;
}
