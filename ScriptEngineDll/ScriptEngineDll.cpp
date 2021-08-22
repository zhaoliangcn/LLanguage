// ScriptEngineDll.cpp : 
//

#include "stdafx.h"
#include "ScriptEngineDll.h"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/ScpDoubleObject.h"
#include "../ScriptEngineLib/ScpBigIntObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScriptDebugger.h"
int  ScriptEngineDoString(wchar_t * ScriptString)
{
	CScriptEngine scriptengine;
	std::wstring scriptstring = ScriptString;
	return scriptengine.DoString(scriptstring);
}
int  ScriptEngineDoScriptFile(wchar_t * ScriptFileName)
{
	CScriptEngine scriptengine;
	return scriptengine.DoScript(ScriptFileName);
}
int  ScriptEngineDebugScriptFile(wchar_t * ScriptFileName)
{
	CScriptEngine scriptengine;
	return scriptengine.DoScript(ScriptFileName,RUN_DEBUG);
}
int  ScriptEngineDebugMemoryScript(wchar_t * ScriptFileName)
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
	//printf("sizeof(std::wstring)=%d\n", sizeof(std::wstring));
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

bool  ScriptReadScript(const wchar_t *  scriptfilename,VTSTRINGS** body)
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
int  ScriptDumpScript(HANDLE hScript,const wchar_t * newscriptfilename)
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
void  ScriptDumpObject(HANDLE hScript,const wchar_t * objectname)
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
int  ScriptDoScript(HANDLE hScript,const wchar_t *  scriptfilename,SCRIPTRUNTYPE mode)
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
int  ScriptDebugMemoryScript(HANDLE hScript,wchar_t * MemoryScript)
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
BOOL  LoadScript(HANDLE hScript,const wchar_t * ScriptFilePathName)
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
BOOL  ScriptObjectToWString(HANDLE hScript,wchar_t * ObjectName,wchar_t *ObjectBuffer,size_t BufferSize)
{
	BOOL bRet = FALSE;
	if(hScript && ObjectBuffer && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj  = scriptengine->GetCurrentObjectSpace()->FindObject(std::wstring(ObjectName));
			if(obj)
			{
			#ifdef _WIN32
				wcscpy_s(ObjectBuffer,BufferSize,obj->ToString().c_str());
			#else
					wcscpy(ObjectBuffer,obj->ToString().c_str());
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
BOOL  ScriptObjectToInt(HANDLE hScript, wchar_t * ObjectName, int * Value)
{
	BOOL bRet = FALSE;
	if (hScript && Value && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(std::wstring(ObjectName));
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
BOOL  ScriptObjectToDouble(HANDLE hScript, wchar_t * ObjectName, double * Value)
{
	BOOL bRet = FALSE;
	if (hScript && Value && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(std::wstring(ObjectName));
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
BOOL  ScriptObjectToInt64(HANDLE hScript, wchar_t * ObjectName, __int64 * Value)
{
	BOOL bRet = FALSE;
	if (hScript && Value && ObjectName)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ScpObject * obj = scriptengine->GetCurrentObjectSpace()->FindObject(std::wstring(ObjectName));
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
BOOL  ScriptCallFunction(HANDLE hScript,wchar_t * FunctionAndParameter)
{
	BOOL bRet = FALSE;
	if(hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::wstring scriptline  ;
			if(scriptengine->GetLanguge()==1)
				scriptline	= L"call:function,";
			#ifdef _WIN32
			else if(scriptengine->GetLanguge() == 0)
				scriptline = L"µ÷ÓÃ:º¯Êý,";
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
BOOL  ScriptRegisterGlobalCommand(HANDLE hScript, const wchar_t * chscommandstring, const wchar_t * engcommandstring, DWORD commandid, GlobalCommandFunctionPtr Func)
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

int  ScriptDoByteCode(HANDLE hScript, const wchar_t * bytecodefilename, SCRIPTRUNTYPE mode)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			ret = scriptengine->DoByteCode(STDSTRINGEXT::WToA(bytecodefilename).c_str(), mode);
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

int  ScriptDumpByteCode(HANDLE hScript, const wchar_t * ByteCodeFile)
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

int  ScriptDoString(HANDLE hScript, const wchar_t * ScriptString)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::wstring scriptstr =  ScriptString;
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

int  ScriptSetScriptFileName(HANDLE hScript, const wchar_t * ScriptFileName)
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

int  ScriptGetObjectType(HANDLE hScript, const wchar_t * ObjectName, wchar_t * ObjectTypeBuffer, int BufferLength)
{
	int ret = 0;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::wstring name = ObjectName;
			std::wstring wstype;
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
					wcscpy_s(ObjectTypeBuffer, BufferLength, wstype.c_str());
				#else
					wcscpy(ObjectTypeBuffer, wstype.c_str());
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

int  ScriptGetObjectFuncList(HANDLE hScript, const wchar_t * ObjectName, wchar_t * ObjectFuncBuffer, int BufferLength)
{
	int ret = -1;
	if (hScript)
	{
		try
		{
			CScriptEngine * scriptengine = (CScriptEngine*)hScript;
			std::wstring name = ObjectName;
			std::wstring wsfunclist;
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
					wcscpy_s(ObjectFuncBuffer, BufferLength, wsfunclist.c_str());
					#else
						wcscpy(ObjectFuncBuffer, wsfunclist.c_str());
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
