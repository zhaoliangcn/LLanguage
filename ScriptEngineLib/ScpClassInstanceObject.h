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
	virtual ScpObject * Clone(std::string strObjName);
	ScpObjectType RealObjType();
	ScpClassInstanceObject(void);
	~ScpClassInstanceObject(void);
	ScpClassObject * instanceOf;
	std::string classname;
	ScpObjectType realobjtype;
};

#endif //_H_SCPCLASSINSTANCEOBJECT

