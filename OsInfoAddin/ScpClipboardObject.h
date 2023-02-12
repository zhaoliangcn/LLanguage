#pragma once
#include "../ScriptEngineLib/ScpObject.h"

const static char * str_CN_ObjClipboard = "剪切板";


const static char * str_EN_ObjClipboard = "clipboard";
const static ScpObjectType ObjClipboard = 310;
class ScpClipboardObject :public ScpObject
{
public:
	ScpClipboardObject();
	~ScpClipboardObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_paste(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};


ScpObject * __stdcall ScpClipboardObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);