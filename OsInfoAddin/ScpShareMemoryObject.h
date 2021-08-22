#ifndef _H_SCPSHAREMEMORYOBJECT
#define _H_SCPSHAREMEMORYOBJECT
#include "../ScriptEngineLib/ScpObject.h"
const static ScpObjectType	ObjShareMemory = 80;

#ifdef _WIN32
#include "windowsSharememory.h"

#else
#include <sys/ipc.h>
#include <sys/shm.h>
#endif
const static wchar_t * str_CN_ObjShareMemory = L"共享内存";

const static wchar_t * str_EN_ObjShareMemory = L"sharememory";
class ScpShareMemoryObject :
	public ScpObject
{
public:
	ScpShareMemoryObject(void);
	~ScpShareMemoryObject(void);


	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	BOOL Open(std::wstring Name,size_t Size);
	BOOL Read(std::wstring & content);
	BOOL Write(std::wstring & content);
	BOOL Read(void * pBuffer,DWORD dwReadPos,DWORD dwReadCount);
	BOOL Write(void * pBuffer,DWORD dwWritePos,DWORD dwWriteCount);
	BOOL Close();

	size_t sharememSize;
	std::wstring sharememName;


#ifdef _WIN32
	WindowsShareMemory *pwinsharemem;
	#else
	int shm_id;
	key_t key;
	void * m_map;
#endif

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};



ScpObject *  __stdcall ShareMemroyObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
BOOL WINAPI ShareMemory_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI ShareMemory_Open_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI ShareMemory_Write_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
BOOL WINAPI ShareMemory_Read_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
#endif //_H_SCPSHAREMEMORYOBJECT