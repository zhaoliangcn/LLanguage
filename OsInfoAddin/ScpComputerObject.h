#pragma once
#include "../ScriptEngineLib/ScpObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"
const static ScpObjectType	ObjComputer = 1;

const static char * str_CN_ObjComputer = "计算机";
const static char * str_CN_ObjComputer1 = "电脑";

const static char * str_EN_ObjComputer = "computer";
const static char * str_EN_ObjComputer1 = "computer";
class ScpComputerObject :
	public ScpObject
{
public:
	ScpComputerObject(void);
	~ScpComputerObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);
	void Shutdown();
	void Reboot();
	void Suspend();
#ifdef WIN32
	TOKEN_PRIVILEGES tkp;
	HANDLE hToken;
#endif

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_reboot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_suspend(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};
#ifdef __cplusplus
extern "C" {
#endif
ScpObject * __stdcall ScpComputerObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
BOOL WINAPI Computer_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Computer_Reboot_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Computer_Suspend_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
#ifdef __cplusplus
}
#endif
