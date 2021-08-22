#ifndef _H_SCPQUEUEOBJECT
#define _H_SCPQUEUEOBJECT
/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//队列对象
*/
#include "ScpObject.h"
#include <queue>
typedef std::deque<ScpObject *> ScpQueue;

class ScpQueueObject :
	public ScpObject
{
public:
	ScpQueueObject();
	~ScpQueueObject();

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	ScpQueue scpqueue;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_add(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_pop(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);	


};


ScpObject * __stdcall ScpQueueObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);


#endif //_H_SCPQUEUEOBJECT