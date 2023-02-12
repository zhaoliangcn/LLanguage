#ifndef _H_SCPPIPEOBJECT
#define _H_SCPPIPEOBJECT
#include "../ScriptEngineLib/ScpObject.h"

const static ScpObjectType	ObjPipe = 57;
#ifdef _WIN32
#include "PipeUtil.h"
#endif
const static char * str_CN_ObjPipe = "管道";

const static char * str_EN_ObjPipe = "pipe";
class ScpPipeObject :
	public ScpObject
{
public:
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

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
	std::string wsPipeName;


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