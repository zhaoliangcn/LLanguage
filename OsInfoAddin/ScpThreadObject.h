#ifndef _H_SCPTHREADOBJECT
#define _H_SCPTHREADOBJECT
#ifdef _WIN32
#include <process.h>
#else 
#include <pthread.h>
#endif
#include "../ScriptEngineLib/ScpObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"


const static ScpObjectType	ObjThread = 47;


const static wchar_t * str_CN_ObjThread = L"线程";

const static wchar_t * str_EN_ObjThread = L"thread";

class ScpThreadObject :
	public ScpObject
{
public:
	friend class  CScriptEngine;

	typedef struct _tag_Param
	{
		CScriptEngine * pscriptengine;
		VTPARAMETERS RealParameters;
		std::wstring ThreadFuncionName;
		
	}Param,*PParam;

	ScpThreadObject(void);
	~ScpThreadObject(void);

	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	void ThreadDefine(std::wstring Name,std::wstring FunctionName);
	void Run(VTPARAMETERS &Parameters,CScriptEngine * pscriptengine);
	void Wait();	

	VTPARAMETERS RealParameters;
	CScriptEngine * scriptengine;
	std::wstring ThreadName;
	std::wstring ThreadFuncionName;

#ifdef WIN32 
	HANDLE hThread;
	static unsigned int __stdcall ThreadBodyFunction(void * parameter);
#else 
	int hThread;
	pthread_t thread1;
	static void *ThreadBodyFunction(void * parameter);
#endif 
	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_wait(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_run(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};


ScpObject * __stdcall ScpThreadObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
BOOL __stdcall Thread_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL __stdcall Thread_Run_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL __stdcall Thread_Wait_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
#endif //_H_SCPTHREADOBJECT