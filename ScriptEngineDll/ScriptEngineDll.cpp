// ScriptEngineDll.cpp : 
//

#include "stdafx.h"
#include "ScriptEngineDll.h"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/ScpDoubleObject.h"
#include "../ScriptEngineLib/ScpBigIntObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScriptDebugger.h"
int  ScriptEngineDoString(char * ScriptString)
{
	CScriptEngine scriptengine;
	std::string scriptstring = ScriptString;
	return scriptengine.DoString(scriptstring);
}
int  ScriptEngineDoScriptFile(char * ScriptFileName)
{
	CScriptEngine scriptengine;
	return scriptengine.DoScript(ScriptFileName);
}
int  ScriptEngineDebugScriptFile(char * ScriptFileName)
{
	CScriptEngine scriptengine;
	return scriptengine.DoScript(ScriptFileName,RUN_DEBUG);
}
int  ScriptEngineDebugMemoryScript(char * ScriptFileName)
{
	 CScriptEngine scriptengine;
	return  scriptengine.DebugMemoryScript(ScriptFileName);
}
HANDLE  CreateScriptEngine()
{
	//printf("sizeof(ScpObject)=%d\n", sizeof(ScpObject));
	//printf("sizeof(ScpIntObject)=%d\n", sizeof(ScpIntObject));
	//printf("sizeof(ScpDoubleObject)=%d\n", sizeof(ScpDoubleObject));
	//printf("sizeof(ScpBigIntObject)=%d\n", sizeof(ScpBigIntObject));
	//printf("sizeof(ScpStringObject)=%d\n", sizeof(ScpStringObject));
	//printf("sizeof(std::string)=%d\n", sizeof(std::string));
	return HANDLE(new (CScriptEngine));
}

void  ScriptReleaseScript(VTSTRINGS** body)
{
	if(body)
	{
		delete *body;
		*body=NULL;
	}
}

bool  ScriptReadScript(const char *  scriptfilename,VTSTRINGS** body)
{
	bool ret=false;
	try
	{
		if(body)
		{
			CScriptFile tmpscriptfile;	
			*body=new VTSTRINGS;
			ret = tmpscriptfile.ReadAll(scriptfilename,**body);
		}
	}
	catch(...)
	{

	}	
	return ret;
}
void  ScriptSetDebugEvent(HANDLE hScript)
{
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			//scriptengine->SetDebugEvent();
		}
		catch(...)
		{

		}
	}
}
int  ScriptDumpScript(HANDLE hScript,const char * newscriptfilename)
{
	int ret=0;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ret = scriptengine->DumpScript(newscriptfilename);
		}
		catch(...)
		{

		}
	}
	return ret;
}
void  ScriptDumpObject(HANDLE hScript,const char * objectname)
{
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			scriptengine->DumpObject(objectname);
		}
		catch(...)
		{

		}
	}
}
int  ScriptEraseBreakPoint(HANDLE hScript,int line)
{
	int ret=0;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			//ret = scriptengine->EraseBreakPoint(line);
		}
		catch(...)
		{

		}
	}
	return ret;
}
int  ScriptAddBreakPoints(HANDLE hScript,int line)
{
	int ret=0;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			//ret = scriptengine->AddBreakPoints(line);
		}
		catch(...)
		{

		}
	}
	return ret;
}
int  ScriptDoScript(HANDLE hScript,const char *  scriptfilename,SCRIPTRUNTYPE mode)
{
	int ret=0;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ret = scriptengine->DoScript(scriptfilename,mode);
		}
		catch(...)
		{

		}
	}
	return ret;
}
int  ScriptDebugMemoryScript(HANDLE hScript,char * MemoryScript)
{
	int ret=0;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ret = scriptengine->DebugMemoryScript(MemoryScript);
		}
		catch(...)
		{

		}
	}
	return ret;
}
void  ScriptReleaseObjects(VTSTRINGS**objects)
{
	if(objects)
	{
		delete *objects;
		*objects=NULL;
	}
}
void  ScriptEnumObjects(HANDLE hScript,VTSTRINGS** objects)
{

	if(hScript && objects)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			*objects =new VTSTRINGS;
			**objects = scriptengine->EnumObjects();
		}
		catch(...)
		{

		}
	}

}
int  ScriptGetCurrentCommandLine(HANDLE hScript)
{
	int commandline=0;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			commandline = scriptengine->GetCurrentCommandLine();
		}
		catch(...)
		{

		}
	}
	return commandline;

}
BOOL  ScriptRegisterUICallBack(HANDLE hScript,void * uiclass,UICallBack callback)
{
	BOOL bRet=FALSE;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			bRet= (scriptengine->RegisterUICallBack(uiclass,callback)==0);
		}
		catch(...)
		{

		}
	}
	return bRet;
}
BOOL  ScriptRegisterUIStepCallBack(HANDLE hScript,void * uiclass,UICallBack callback)
{
	BOOL bRet=FALSE;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			bRet= (scriptengine->RegisterUIStepCallBack(uiclass,callback)==0);
		}
		catch(...)
		{

		}
	}
	return bRet;
}
BOOL  LoadScript(HANDLE hScript,const char * ScriptFilePathName)
{
	BOOL bRet=FALSE;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			bRet= (scriptengine->ImportLib(ScriptFilePathName,false)==0);
		}
		catch(...)
		{

		}
	}
	return bRet;
}
BOOL  ScriptObjectToWString(HANDLE hScript,char * ObjectName,char *ObjectBuffer,size_t BufferSize)
{
	BOOL bRet = FALSE;
	if(hScript && ObjectBuffer && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj  = scriptengine->GetCurrentObjectSpace()->FindObject(std::string(ObjectName));
			if(obj)
			{
			#ifdef _WIN32
				strcpy_s(ObjectBuffer,BufferSize,obj->ToString().c_str());
			#else
				strcpy(ObjectBuffer,obj->ToString().c_str());
			#endif
			
				bRet =  TRUE;
			}
		}
		catch(...)
		{

		}
	}
	return bRet;

}
BOOL  ScriptObjectToInt(HANDLE hScript, char * ObjectName, int * Value)
{
	BOOL bRet = FALSE;
	if (hScript && Value && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(std::string(ObjectName));
			if (obj && obj->GetType()==ObjInt)
			{
				*Value = ((ScpIntObject*)obj)->value;
				bRet = TRUE;
			}
		}
		catch (...)
		{

		}
	}
	return bRet;

}
BOOL  ScriptObjectToDouble(HANDLE hScript, char * ObjectName, double * Value)
{
	BOOL bRet = FALSE;
	if (hScript && Value && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(std::string(ObjectName));
			if (obj && obj->GetType() == ObjDouble)
			{
				*Value = ((ScpDoubleObject*)obj)->value;
				bRet = TRUE;
			}
		}
		catch (...)
		{

		}
	}
	return bRet;
}
BOOL  ScriptObjectToInt64(HANDLE hScript, char * ObjectName, __int64 * Value)
{
	BOOL bRet = FALSE;
	if (hScript && Value && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(std::string(ObjectName));
			if (obj && obj->GetType() == ObjBigInt)
			{
				*Value = ((ScpBigIntObject*)obj)->value;
				bRet = TRUE;
			}
		}
		catch (...)
		{

		}
	}
	return bRet;
}
BOOL  ScriptCallFunction(HANDLE hScript,char * FunctionAndParameter)
{
	BOOL bRet = FALSE;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::string scriptline  ;
			if(scriptengine->GetLanguge()==1)
				scriptline	= "call:function,";
			#ifdef _WIN32
			else if(scriptengine->GetLanguge() == 0)
				scriptline = "调用:函数,";
			#else
			#endif
			scriptline+=FunctionAndParameter;
			scriptengine->DoString(scriptline);
			bRet = TRUE;
		}
		catch(...)
		{

		}
	}
	return bRet;
}
void  CloseScriptEngine(HANDLE &hScript)
{
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			delete scriptengine;
			hScript = NULL;
		}
		catch(...)
		{

		}
	}
}
BOOL  ScriptRegisterGlobalCommand(HANDLE hScript, const char * chscommandstring, const char * engcommandstring, DWORD commandid, GlobalCommandFunctionPtr Func)
{
	BOOL bRet = FALSE;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			bRet = scriptengine->RegisterGlobalFunction(chscommandstring, engcommandstring, commandid,(GlobalCommandFunction) Func);
		}
		catch (...)
		{

		}
	}
	return bRet;
}

int  ScriptDoByteCode(HANDLE hScript, const char * bytecodefilename, SCRIPTRUNTYPE mode)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ret = scriptengine->DoByteCode(bytecodefilename, mode);
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptDoMemByteCode(HANDLE hScript, const unsigned char * membytecode, int length, SCRIPTRUNTYPE mode)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ret = scriptengine->DoMemByteCode(membytecode, length,mode);
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptSetJit(HANDLE hScript, int Jit)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			scriptengine->Jit = Jit;
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptSetBuild(HANDLE hScript, int Build)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine* scriptengine = (CScriptEngine*)hScript;
			scriptengine->Build = Build;
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptDumpByteCode(HANDLE hScript, const char * ByteCodeFile)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			scriptengine->DumpByteCode(NULL);
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptDoString(HANDLE hScript, const char * ScriptString)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::string scriptstr =  ScriptString;
			scriptengine->DoString(scriptstr);
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptSetDebugger(HANDLE hScript, void * debugger)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;			
			scriptengine->SetDebugger((IScriptDebugger*)debugger);
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptSetScriptFileName(HANDLE hScript, const char * ScriptFileName)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			scriptengine->SetScriptFileName(ScriptFileName);
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptGetObjectType(HANDLE hScript, const char * ObjectName, char * ObjectTypeBuffer, int BufferLength)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::string name = ObjectName;
			std::string wstype;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(name);
			if (obj)
			{
				ret = obj->GetType();
				if (scriptengine->extend_obj_mgr.IsExtendObject(ret))
				{
					wstype =  scriptengine->extend_obj_mgr.GetExtendObjectName(ret);					
				}
				else
				{
					wstype = ScpGlobalObject::GetInstance()->GetTypeName(ret);
				}
				if (BufferLength < wstype.length())
				{
					ret = -1;
				}
				else
				{
				#ifdef _WIN32
					strcpy_s(ObjectTypeBuffer, BufferLength, wstype.c_str());
				#else
					strcpy(ObjectTypeBuffer, wstype.c_str());
				#endif
				}
			}
				
		}
		catch (...)
		{

		}
	}
	return ret;
}

int  ScriptGetObjectFuncList(HANDLE hScript, const char * ObjectName, char * ObjectFuncBuffer, int BufferLength)
{
	int ret = -1;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::string name = ObjectName;
			std::string wsfunclist;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(name);
			if (obj)
			{
				wsfunclist = obj->GetInnerFunctionList();
				if (BufferLength < wsfunclist.length())
				{
					ret = -1;
				}
				else
				{
					ret = 0;
					#ifdef _WIN32
					strcpy_s(ObjectFuncBuffer, BufferLength, wsfunclist.c_str());
					#else
					strcpy(ObjectFuncBuffer, wsfunclist.c_str());
					#endif
				}
			}

		}
		catch (...)
		{

		}
	}
	return ret;
}
