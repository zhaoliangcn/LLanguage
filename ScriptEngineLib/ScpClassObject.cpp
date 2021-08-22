/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpClassObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "commanddefine_uni.h"
#include "ScriptEngine.h"
#include "ScpFunctionObject.h"
#include "../Common/commonutil.hpp"
ScpClassObject::ScpClassObject(void)
{
	objecttype = ObjClass;
	UserClassObjectSpace.ObjectSpaceType = Space_Class;
	UserClassObjectSpace.belongto = this;
	MemberVariableAttribute = Attr_Private;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);
}

ScpClassObject::~ScpClassObject(void)
{
	
}
void ScpClassObject::Show(CScriptEngine * engine)
{
	for (unsigned int i = 0;i < ClassBody.size();i++)
	{
		engine->PrintError(ClassBody.at(i));
	}
	//auto it = memberattrmap.begin();
	//while (it != memberattrmap.end())
	//{
	//	std::wstring name = it->first;
	//	ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(name);
	//	if (obj)
	//	{
	//		obj->Show(engine);
	//	}
	//	it++;
	//}
}
ScpObject * ScpClassObject::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpClassObject::ToString()
{
	std::wstring temp;
	for (unsigned int i = 0;i < ClassBody.size();i++)
	{
		temp += ClassBody.at(i);
	}
	return temp;
}
void  ScpClassObject::Release()
{
	delete this;
}
bool ScpClassObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	ScpObject * obj = FindMemberVariable(functionname);
	if (obj &&  obj->GetType()==ObjFunction)
	{
		return true;
	}
	return false;
}
ScpObject * ScpClassObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	if (FindMemberVariable(functionname))
	{
		VTPARAMETERS param;
		for (int i = 0;i < parameters->size();i++)
		{
			param.push_back(parameters->at(i));
		}
		return CallMemberFunction(functionname, parameters, engine);
	}
	return NULL;
}
void ScpClassObject::ClassDefine(std::wstring name)
{
	userclassname = name;
}
void  ScpClassObject::AddMemberVariable(std::wstring name, ScpObject * object)
{
	UserClassObjectSpace.AddObject(name, object);
}
void  ScpClassObject::AddMemberFunction(std::wstring name, ScpObject * object)
{
	UserClassObjectSpace.AddObject(name, object);
}
ScpObject * ScpClassObject::FindMemberVariable(std::wstring name)
{
	return UserClassObjectSpace.FindLocalObject(name);
}
ScpObject * ScpClassObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpClassObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
ScpObject * ScpClassObject::CallMemberFunction(std::wstring functionname, VTPARAMETERS * RealParameters, CScriptEngine * engine)
{
	ScpFunctionObject * func = (ScpFunctionObject*)UserClassObjectSpace.FindObject(functionname);
	if (func)
	{
		func->RealParameters.clear();
		if (RealParameters)
		{
			for (int i = 0;i < RealParameters->size();i++)
			{
				func->RealParameters.push_back(RealParameters->at(i));
			}
		}

		ScpObjectSpace * space = engine->GetCurrentObjectSpace();
		ScpObjectSpace * oldparentspace = UserClassObjectSpace.parentspace;
		UserClassObjectSpace.parentspace = space;
		engine->SetCurrentObjectSpace(&UserClassObjectSpace);
		func->Do(engine);
		UserClassObjectSpace.parentspace = oldparentspace;
		engine->SetCurrentObjectSpace(space);
		return func->Result;
	}
	return NULL;
}
