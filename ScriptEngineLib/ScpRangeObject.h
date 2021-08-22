#ifndef _H_SCPRANGEOBJECT
#define _H_SCPRANGEOBJECT
#include "ScpObject.h"


const static wchar_t *str_CN_head = L"首部";
const static wchar_t *str_CN_tail = L"尾部";
const static wchar_t *str_CN_step = L"间距";
const static wchar_t *str_CN_reset = L"重置";

const static wchar_t *str_EN_head = L"head";
const static wchar_t *str_EN_tail = L"tail";
const static wchar_t *str_EN_step = L"step";
const static wchar_t *str_EN_reset = L"reset";

class ScpObjectSpace;
class CScriptEngine;
class ScpRangeObject :
	public ScpObject
{
public:
	ScpRangeObject();
	~ScpRangeObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

	int Init();
	std::vector<ScpObject *> Elements;
	int start;
	int end;
	int step;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_head(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_tail(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_step(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_reset(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};


ScpObject * __stdcall ScpRangeObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPRANGEOBJECT