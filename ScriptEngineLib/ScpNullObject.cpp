/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpNullObject.h"
#include "ScriptEngine.h"

ScpNullObject::ScpNullObject(void)
{
	objecttype =ObjNull;
	parentObj = NULL;
}


ScpNullObject::~ScpNullObject(void)
{
}

void ScpNullObject::Show(CScriptEngine * engine)
{

	engine->PrintError(ScpGlobalObject::GetInstance()->GetTypeName(ObjNull));

}
ScpObject * ScpNullObject::Clone(std::wstring strObjName)
{
	ScpNullObject * obj = new ScpNullObject;
	if (obj)
	{
		obj->parentObj = parentObj;
		return obj;
	}
	return NULL;
}	
std::wstring ScpNullObject::ToString()
{
	std::wstring temp;
	return temp;
}
void ScpNullObject::Release() 
{
	delete this;
}

bool ScpNullObject::IsInnerFunction(std::wstring & functionname)
{
	return false;
}

ScpObject * ScpNullObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
