#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include <stdint.h>
typedef void *HANDLE;
typedef int BOOL;
typedef __int64_t __int64;
typedef unsigned int DWORD;
#endif
#include <string>
#include <vector>
typedef std::vector<std::wstring> VTSTRINGSW;
typedef std::vector<std::wstring>::iterator  ITSTRINGSW;
typedef std::vector<std::string> VTSTRINGS;
typedef std::vector<std::string>::iterator  ITSTRINGS;
typedef void(*UICallBack)(void * UIClass, const char * Message);
typedef BOOL(*GlobalCommandFunctionPtr)(VTSTRINGS * vtparameters, void * engine);
#ifndef _EM_SCRIPTRUNTYPE
#define _EM_SCRIPTRUNTYPE
typedef enum _tag_SCRIPTRUNTYPE
{
	RUN_NORMAL,
	RUN_DEBUG,
	RUN_SINGLESTEP,
}SCRIPTRUNTYPE;

#endif //_EM_SCRIPTRUNTYPE

#ifdef __cplusplus
extern "C" {
#endif
	int 	ScriptEngineDoString(char * ScriptString);
	int 	ScriptEngineDoScriptFile(char * ScriptFileName);
	int 	ScriptEngineDebugScriptFile(char * ScriptFileName);
	int 	ScriptEngineDebugMemoryScript(char * ScriptFileName);

	HANDLE  CreateScriptEngine();
	BOOL 	LoadScript(HANDLE hScript, const char * ScriptFilePathName);
	BOOL 	ScriptObjectToWString(HANDLE hScript, char * ObjectName, char *ObjectBuffer, size_t BufferSize);
	BOOL 	ScriptObjectToInt(HANDLE hScript, char * ObjectName, int * Value);
	BOOL 	ScriptObjectToDouble(HANDLE hScript, char * ObjectName, double * Value);
	BOOL 	ScriptObjectToInt64(HANDLE hScript, char * ObjectName, __int64 * Value);
	BOOL 	ScriptCallFunction(HANDLE hScript, char * FunctionAndParameter);
	void 	CloseScriptEngine(HANDLE &hScript);
	BOOL 	ScriptRegisterUICallBack(HANDLE hScript, void * uiclass, UICallBack callback);
	BOOL 	ScriptRegisterUIStepCallBack(HANDLE hScript, void * uiclass, UICallBack callback);
	int 	ScriptGetCurrentCommandLine(HANDLE hScript);
	void 	ScriptEnumObjects(HANDLE hScript, VTSTRINGS **objects);
	void 	ScriptReleaseObjects(VTSTRINGS**objects);
	int 	ScriptDoScript(HANDLE hScript, const char * scriptfilename, SCRIPTRUNTYPE mode = RUN_NORMAL);
	int 	ScriptDebugMemoryScript(HANDLE hScript, char * MemoryScript);
	int 	ScriptAddBreakPoints(HANDLE hScript, int line); //已废弃
	int 	ScriptEraseBreakPoint(HANDLE hScript, int line);//已废弃
	void 	ScriptDumpObject(HANDLE hScript, const char *  objectname);
	int 	ScriptDumpScript(HANDLE hScript, const char *  newscriptfilename);
	void 	ScriptSetDebugEvent(HANDLE hScript);//已废弃
	bool 	ScriptReadScript(const char *  scriptfilename, VTSTRINGS** body);
	void 	ScriptReleaseScript(VTSTRINGS** body);
	BOOL 	ScriptRegisterGlobalCommand(HANDLE hScript, const char * chscommandstring, const char * engcommandstring, DWORD commandid, GlobalCommandFunctionPtr);
	int 	ScriptDoByteCode(HANDLE hScript, const char * bytecodefilename, SCRIPTRUNTYPE mode = RUN_NORMAL);
	int 	ScriptDoMemByteCode(HANDLE hScript, const unsigned char  * membytecode, int length, SCRIPTRUNTYPE mode = RUN_NORMAL);
	int 	ScriptSetJit(HANDLE hScript, int Jit);
	int		ScriptSetBuild(HANDLE hScript, int Build);
	int 	ScriptDumpByteCode(HANDLE hScript, const char * ByteCodeFile);
	int 	ScriptDoString(HANDLE hScript, const char * ScriptString);
	int 	ScriptSetDebugger(HANDLE hScript, void * debugger);
	int 	ScriptSetScriptFileName(HANDLE hScript, const char * ScriptFileName);
	int 	ScriptGetObjectType(HANDLE hScript, const char * ObjectName, char *ObjectTypeBuffer, int BufferLength);
	int 	ScriptGetObjectFuncList(HANDLE hScript, const char * ObjectName, char *ObjectFuncBuffer, int BufferLength);

	typedef int(		*FUNC_ScriptEngineDoString)(char * ScriptString);
	typedef int(		*FUNC_ScriptEngineDoScriptFile)(char * ScriptFileName);
	typedef int(		*FUNC_ScriptEngineDebugScriptFile)(char * ScriptFileName);
	typedef int(		*FUNC_ScriptEngineDebugMemoryScript)(char * ScriptFileName);

	typedef HANDLE(	*FUNC_CreateScriptEngine)();
	typedef BOOL(		*FUNC_LoadScript)(HANDLE hScript, const char * ScriptFilePathName);
	typedef BOOL(		*FUNC_ScriptObjectToWString)(HANDLE hScript, char * ObjectName, char *ObjectBuffer, size_t BufferSize);
	typedef BOOL(		*FUNC_ScriptObjectToInt)(HANDLE hScript, char * ObjectName, int * Value);
	typedef BOOL(		*FUNC_ScriptObjectToDouble)(HANDLE hScript, char * ObjectName, double * Value);
	typedef BOOL(		*FUNC_ScriptObjectToInt64)(HANDLE hScript, char * ObjectName, __int64 * Value);
	typedef BOOL(		*FUNC_ScriptCallFunction)(HANDLE hScript, char * FunctionAndParameter);
	typedef void(		*FUNC_CloseScriptEngine)(HANDLE &hScript);
	typedef BOOL(		*FUNC_ScriptRegisterUICallBack)(HANDLE hScript, void * uiclass, UICallBack callback);
	typedef BOOL(		*FUNC_ScriptRegisterUIStepCallBack)(HANDLE hScript, void * uiclass, UICallBack callback);
	typedef int(		*FUNC_ScriptGetCurrentCommandLine)(HANDLE hScript);
	typedef void(		*FUNC_ScriptEnumObjects)(HANDLE hScript, VTSTRINGS **objects);
	typedef void(		*FUNC_ScriptReleaseObjects)(VTSTRINGS**objects);
	typedef int(		*FUNC_ScriptDoScript)(HANDLE hScript, const char * scriptfilename, SCRIPTRUNTYPE mode);
	typedef int(		*FUNC_ScriptDebugMemoryScript)(HANDLE hScript, char * MemoryScript);

	typedef int(		*FUNC_ScriptAddBreakPoints)(HANDLE hScript, int line);
	typedef int(		*FUNC_ScriptEraseBreakPoint)(HANDLE hScript, int line);
	typedef void(		*FUNC_ScriptDumpObject)(HANDLE hScript, const char *  objectname);
	typedef int(		*FUNC_ScriptDumpScript)(HANDLE hScript, const char *  newscriptfilename);
	typedef void(		*FUNC_ScriptSetDebugEvent)(HANDLE hScript);
	typedef bool(		*FUNC_ScriptReadScript)(const char *  scriptfilename, VTSTRINGS** body);
	typedef void(		*FUNC_ScriptReleaseScript)(VTSTRINGS** body);
	typedef BOOL(		*FUNC_ScriptRegisterGlobalCommand)(HANDLE hScript, const char * chscommandstring, const char * engcommandstring, DWORD commandid, GlobalCommandFunctionPtr);
	typedef int(		*FUNC_ScriptDoByteCode)(HANDLE hScript, const char * bytecodefilename, SCRIPTRUNTYPE mode);
	typedef int(		*FUNC_ScriptDoMemByteCode)(HANDLE hScript, const unsigned char  * membytecode, int length, SCRIPTRUNTYPE mode);
	typedef int(		*FUNC_ScriptSetJit)(HANDLE hScript, int Jit);
	typedef int(		*FUNC_ScriptSetBuild)(HANDLE hScript, int Build);
	typedef int(		*FUNC_ScriptDumpByteCode)(HANDLE hScript, char * ByteCodeFile);
	typedef int(		*FUNC_ScriptDoString)(HANDLE hScript, const char * ScriptString);
	typedef int(		*FUNC_ScriptSetDebugger)(HANDLE hScript, void * debugger);
	typedef int(		*FUNC_ScriptSetScriptFileName)(HANDLE hScript, const char * ScriptFileName);
	typedef int(		*FUNC_ScriptGetObjectType)(HANDLE hScript, const char * ObjectName, char *ObjectTypeBuffer, int BufferLength);
	typedef int(		*FUNC_ScriptGetObjectFuncList)(HANDLE hScript, const char * ObjectName, char *ObjectFuncBuffer, int BufferLength);
#ifdef __cplusplus
}
#endif

