#ifndef _H_SCPRANGEOBJECT
#define _H_SCPRANGEOBJECT
#include "ScpObject.h"


const static char  *str_CN_head = "首部";
const static char  *str_CN_tail = "尾部";
const static char  *str_CN_step = "间距";
const static char  *str_CN_reset = "重置";

const static char  *str_EN_head = "head";
const static char  *str_EN_tail = "tai";
const static char  *str_EN_step = "step";
const static char  *str_EN_reset = "reset";

class ScpObjectSpace;
class CScriptEngine;
class ScpRangeObject :
	public ScpObject
{
public:
	ScpRangeObject();
	~ScpRangeObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);

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