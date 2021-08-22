/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCRIPTCOMMAND
#define _H_SCRIPTCOMMAND


#include "ScriptFile.h"
#include "ScpObject.h"
#ifndef WIN32
#include <pthread.h>
#endif

class CScriptEngine;


class CScriptCommand
{
public:

	CScriptCommand();
	~CScriptCommand();


	//SCP Óï·¨	
	static BOOL Do_Import_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Do_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Return_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	static BOOL Do_Loop_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Public_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Private_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Continue_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Break_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Load_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Inherit_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Register_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_While_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Define_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Compute_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Call_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Exit_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Test_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Otherwise_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_Wait_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	static BOOL Do_End_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	
};
#endif //_H_SCRIPTCOMMAND