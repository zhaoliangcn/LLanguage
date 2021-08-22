
#ifndef _H_SCPPROCOBJECT
#define _H_SCPPROCOBJECT
#include "../ScriptEngineLib/ScpObject.h"
#include "../ScriptEngineLib/ScpTableObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpIntObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"

const static wchar_t * str_EN_option = L"option";
const static wchar_t * str_CN_option = L"选项";
const static wchar_t * str_EN_output = L"output";
const static wchar_t * str_CN_output = L"输出";

class ScpProcObject:public ScpObject
{
public:
	ScpProcObject();
	~ScpProcObject();
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	BOOL Open(std::wstring path,std::wstring param);
	BOOL ShutDown();
	BOOL Wait(DWORD dwWaitTime);
	BOOL Restart();
	static BOOL ShutDown(DWORD dwPid);
	static BOOL ShutDown(std::wstring processname);
	static BOOL Enum(ScpObject * tableobj,std::wstring enumtype);
	std::wstring procobjname;
	std::wstring procpathname;
	std::wstring Parameter;
	std::wstring procoutput;
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