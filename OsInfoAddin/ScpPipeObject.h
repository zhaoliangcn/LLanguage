#ifndef _H_SCPPIPEOBJECT
#define _H_SCPPIPEOBJECT
#include "../ScriptEngineLib/ScpObject.h"

const static ScpObjectType	ObjPipe = 57;
#ifdef _WIN32
#include "PipeUtil.h"
#endif
const static wchar_t * str_CN_ObjPipe = L"管道";

const static wchar_t * str_EN_ObjPipe = L"pipe";
class ScpPipeObject :
	public ScpObject
{
public:
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	BOOL Open(const wchar_t * PipeName);
	BOOL Read(char * Buffer,DWORD Len);
	BOOL Write(const char * Buffer,DWORD Len);
	void CLose();
	ScpPipeObject(void);
	~ScpPipeObject(void);
	HANDLE hPipe;
#ifdef _WIN32
	CPipeUtil Pipe;
#endif
	std::wstring wsPipeName;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};




ScpObject *  __stdcall PipeObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
BOOL WINAPI Pipe_Open_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Pipe_Write_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI Pipe_Read_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
#endif //_H_SCPPIPEOBJECT