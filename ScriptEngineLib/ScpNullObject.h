/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//空对象
*/
#ifndef _H_SCPNULLOBJECT
#define _H_SCPNULLOBJECT
#include "ScpObject.h"
#include "ScpObject_uni.h"

//NullObject只是用于数组对象定义时的占位
class ScpNullObject :
	public ScpObject
{
public:
	ScpNullObject(void);
	~ScpNullObject(void);
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	ScpObject * parentObj;

	
};
//ScpNullObject的工厂函数
ScpObject * __stdcall ScpNullObjectFactory(VTPARAMETERS* paramters, CScriptEngine* engine);

#endif //_H_SCPNULLOBJECT