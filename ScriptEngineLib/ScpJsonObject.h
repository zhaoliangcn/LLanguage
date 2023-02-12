/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//JSON对象
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
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	BOOL Load(std::string jsonstring);
	BOOL Save(std::string name="");
	BOOL Open(std::string name);
	BOOL Close();	
	BOOL GetValue(std::string tag,std::string& value);
	BOOL GetValue(std::string tag,int & value);
	BOOL SetValue(std::string tag,std::string value);	
	BOOL SetValue(std::string tag,int value);
	std::string jsonfileName;	
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