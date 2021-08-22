#ifndef _H_SCPTIMEROBJECT
#define _H_SCPTIMEROBJECT
#include "../ScriptEngineLib/ScpObject.h"
#include "../ScriptEngineLib/ScpFunctionObject.h"
class ScpFunctionObject;
#ifdef _WIN32

#else
typedef void * HWND;
#endif
const static ScpObjectType	ObjTimer = 41;
const static std::wstring str_CN_ObjTimer = L"定时器";

const static std::wstring str_EN_ObjTimer = L"timer";
class ScpTimerObject :
	public ScpObject
{
public:
	ScpTimerObject(void);
	~ScpTimerObject(void);
	void Set(std::wstring timername,ScpFunctionObject * func,ULONG val);
#ifdef _WIN32
	
	static void   __stdcall   TimerProc(HWND   hwnd,unsigned int   uMsg,UINT_PTR   idEvent,DWORD   dwTime);
#endif
	void Start();
	void Stop();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	ScpFunctionObject * timerfunc;
	std::wstring name;
	ULONG interval;
	ULONG eventid;
	//TIMERPROC timerproc;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};

ScpObject * __stdcall ScpTimerObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPTIMEROBJECT