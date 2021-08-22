/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//随机数对象
*/
#ifndef _H_SCPRANDOMNUMBEROBJECT
#define _H_SCPRANDOMNUMBEROBJECT
#include "ScpObject.h"
#include "ScpIntObject.h"
#include <time.h>
#ifdef _WIN32
#include <random>
using std::tr1::uniform_int ;
#endif
class ScpRandomNumberObject :
	public ScpObject
{
public:
	ScpRandomNumberObject(void);
	~ScpRandomNumberObject(void);
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	static ScpIntObject GetRandom();
	static ScpIntObject Refresh(ScpIntObject &currentvalue);
	void SetValue(const ScpIntObject &v);
	ScpIntObject GetValue();

	ScpIntObject value ;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_refresh(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};


ScpObject * __stdcall ScpRandomNumberObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif  //_H_SCPRANDOMNUMBEROBJECT