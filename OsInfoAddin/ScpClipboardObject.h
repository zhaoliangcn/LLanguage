#pragma once
#include "../ScriptEngineLib/ScpObject.h"

const static wchar_t * str_CN_ObjClipboard = L"剪切板";


const static wchar_t * str_EN_ObjClipboard = L"clipboard";
const static ScpObjectType ObjClipboard = 310;
class ScpClipboardObject :public ScpObject
{
public:
	ScpClipboardObject();
	~ScpClipboardObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_paste(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};


ScpObject * __stdcall ScpClipboardObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);