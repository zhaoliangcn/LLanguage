#pragma once
#include "../ScriptEngineLib/ScpObject.h"

const static wchar_t * str_CN_ObjOsInfo = L"操作系统信息";
const static wchar_t * strOsVersion_CN = L"版本号";

const static wchar_t * str_EN_ObjOsInfo = L"osinfo";
const static wchar_t * strOsVersion_EN = L"version";
const static ScpObjectType ObjOsInfo = 305;
const static ScpObjectType	ObjScreen = 5;
class ScpOsInfoObject :
	public ScpObject
{
public:
	ScpOsInfoObject();
	~ScpOsInfoObject();


	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};

ScpObject * __stdcall ScpOsInfoObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
