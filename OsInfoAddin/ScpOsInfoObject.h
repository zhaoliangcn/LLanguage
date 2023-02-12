#pragma once
#include "../ScriptEngineLib/ScpObject.h"

const static char * str_CN_ObjOsInfo = "操作系统信息";
const static char * strOsVersion_CN = "版本号";

const static char * str_EN_ObjOsInfo = "osinfo";
const static char * strOsVersion_EN = "version";
const static ScpObjectType ObjOsInfo = 305;
const static ScpObjectType	ObjScreen = 5;
class ScpOsInfoObject :
	public ScpObject
{
public:
	ScpOsInfoObject();
	~ScpOsInfoObject();


	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};

ScpObject * __stdcall ScpOsInfoObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
