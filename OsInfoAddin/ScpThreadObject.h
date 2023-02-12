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


const static char * str_CN_ObjThread = "线程";

const static char * str_EN_ObjThread = "thread";

class ScpThreadObject :
	public ScpObject
{
public:
	friend class  CScriptEngine;

	typedef struct _tag_Param
	{
		CScriptEngine * pscriptengine;
		VTPARAMETERS RealParameters;
		std::string ThreadFuncionName;
		
	}Param,*PParam;

	ScpThreadObject(void);
	~ScpThreadObject(void);

	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	void ThreadDefine(std::string Name,std::string FunctionName);
	void Run(VTPARAMETERS &Parameters,CScriptEngine * pscriptengine);
	void Wait();	

	VTPARAMETERS RealParameters;
	CScriptEngine * scriptengine;
	std::string ThreadName;
	std::string ThreadFuncionName;

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