
#ifndef _H_SCPPROCOBJECT
#define _H_SCPPROCOBJECT
#include "../ScriptEngineLib/ScpObject.h"
#include "../ScriptEngineLib/ScpTableObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpIntObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"

const static char * str_EN_option = "option";
const static char * str_CN_option = "选项";
const static char * str_EN_output = "output";
const static char * str_CN_output = "输出";

class ScpProcObject:public ScpObject
{
public:
	ScpProcObject();
	~ScpProcObject();
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	BOOL Open(std::string path,std::string param);
	BOOL ShutDown();
	BOOL Wait(DWORD dwWaitTime);
	BOOL Restart();
	static BOOL ShutDown(DWORD dwPid);
	static BOOL ShutDown(std::string processname);
	static BOOL Enum(ScpObject * tableobj,std::string enumtype);
	std::string procobjname;
	std::string procpathname;
	std::string Parameter;
	std::string procoutput;
	bool isUIProcess;
	
#ifdef _WIN32
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
#endif


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_wait(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_reboot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_enum(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_run(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};


ScpObject * __stdcall ScpProcObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
BOOL WINAPI Proc_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Proc_Reboot_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Proc_Wait_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Proc_Run_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Proc_Enum_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
#endif //_H_SCPPROCOBJECT