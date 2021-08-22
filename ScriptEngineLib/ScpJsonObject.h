/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//JSON∂‘œÛ
*/
#ifndef _H_SCPJSONOBJECT
#define _H_SCPJSONOBJECT
#include "ScpObject.h"
#ifdef _WIN32

#else

#endif
#include "../EasyJson/EasyJson/CppEasyJson.h"
class ScpJsonObject :
	public ScpObject
{
public:
	ScpJsonObject(void);
	~ScpJsonObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	BOOL Load(std::wstring jsonstring);
	BOOL Save(std::wstring name=L"");
	BOOL Open(std::wstring name);
	BOOL Close();	
	BOOL GetValue(std::wstring tag,std::wstring& value);
	BOOL GetValue(std::wstring tag,int & value);
	BOOL SetValue(std::wstring tag,std::wstring value);	
	BOOL SetValue(std::wstring tag,int value);
	std::wstring jsonfileName;	
	CppEasyJson ejson;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_load(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_save(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};

ScpObject * __stdcall ScpJsonObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPJSONOBJECT