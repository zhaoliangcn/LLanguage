/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//’ª∂‘œÛ
*/
#ifndef _H_SCPSTACKOBJECT
#define _H_SCPSTACKOBJECT
#include "ScpObject.h"
#include <queue>
typedef std::deque<ScpObject *> ScpStack;



class ScpStackObject :
	public ScpObject
{
public:
	ScpStackObject();
	~ScpStackObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	ScpStack scpstack;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_push(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_pop(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};


ScpObject * __stdcall ScpStackObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPSTACKOBJECT