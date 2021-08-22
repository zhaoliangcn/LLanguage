/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpClassInstanceObject.h"


void ScpClassInstanceObject::Show(CScriptEngine * engine)
{
	ScpClassObject::Show(engine);
}

ScpObject * ScpClassInstanceObject::Clone(std::wstring strObjName)
{
	ScpClassInstanceObject * obj = new ScpClassInstanceObject;
	if (obj)
	{
		obj->classname = classname;
		obj->ClassBody = ClassBody;
		obj->memberattrmap = memberattrmap;
		obj->realobjtype = realobjtype;
		obj->instanceOf = instanceOf;
		obj->scriptengine = scriptengine;
		obj->ObjectInnerFunctions = ObjectInnerFunctions;
		obj->UserClassObjectSpace.userobject.DeepCopy(&UserClassObjectSpace.userobject);
	}
	return obj;
}

ScpClassInstanceObject::ScpClassInstanceObject(void)
{
	instanceOf = NULL;
	objecttype = ObjClassInstance;
}


ScpClassInstanceObject::~ScpClassInstanceObject(void)
{
	
}
ScpObjectType ScpClassInstanceObject::RealObjType()
{
	return realobjtype;
}