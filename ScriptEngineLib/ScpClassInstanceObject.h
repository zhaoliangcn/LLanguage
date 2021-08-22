/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//L脚本语言的类实例
*/
#ifndef _H_SCPCLASSINSTANCEOBJECT
#define _H_SCPCLASSINSTANCEOBJECT
#include "ScpClassObject.h"
class ScpClassObject;
class ScpClassInstanceObject :
	public ScpClassObject
{
public:
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	ScpObjectType RealObjType();
	ScpClassInstanceObject(void);
	~ScpClassInstanceObject(void);
	ScpClassObject * instanceOf;
	std::wstring classname;
	ScpObjectType realobjtype;
};

#endif //_H_SCPCLASSINSTANCEOBJECT

