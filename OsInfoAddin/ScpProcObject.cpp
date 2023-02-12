#include "ScpProcObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../ScriptEngineLib/ScpObjectNammes.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"
#include "../Common/stdstringext.hpp"
#ifdef _WIN32
#include <tlhelp32.h>
#else
#define wcsicmp wcscasecmp
#define _stricmp strcasecmp
#endif

ScpObject * __stdcall ScpProcObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() >= 3)
	{
		ScpProcObject *procobj = new ScpProcObject;
		procobj->procobjname = paramters->at(1);
		procobj->procpathname = paramters->at(2);
		if (paramters->size() == 4)
		{			
			procobj->Parameter = paramters->at(3);		
		}
		StringStripQuote(procobj->procpathname);
		StringStripQuote(procobj->Parameter);
		return procobj;
	}
	else if (paramters->size() == 2)
	{
		ScpProcObject *procobj = new ScpProcObject;
		procobj->procobjname = paramters->at(1);		
		return procobj;
	}
	return NULL;
}
BOOL WINAPI Proc_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		std::string text;
		if (vtparameters->size() == 2)
		{
			text = vtparameters->at(1);
		}
		else if (vtparameters->size() == 1)
		{
			text = vtparameters->at(0);
		}
		ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjProc)
			{
				std::string func = scpcommand_en_shutdown;
				((ScpProcObject *)obj)->CallInnerFunction(func, NULL, engine);
				engine->GetCurrentObjectSpace()->EraseObject(text);
			}
			else if (obj->GetType() == ObjInt)
			{
				DWORD dwPid= ((ScpIntObject*)obj)->value;
				ScpProcObject::ShutDown(dwPid);
			}
			else if (obj->GetType() == ObjString)
			{
				std::string procname = ((ScpStringObject*)obj)->content;
				ScpProcObject::ShutDown(procname);
			}
		}	
		else
		{
			ScpProcObject::ShutDown(text);
		}
	}
	return TRUE;
}
BOOL WINAPI Proc_Wait_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		std::string text;
		if (vtparameters->size() == 1)
		{
			text = vtparameters->at(0);
		}
		ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjProc)
			{

				((ScpProcObject *)obj)->Wait(INFINITE);
			}			
		}		
	}
	return TRUE;
}
BOOL WINAPI Proc_Reboot_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		std::string text;
		if (vtparameters->size() == 2)
		{
			text = vtparameters->at(1);
		}
		else if (vtparameters->size() == 1)
		{
			text = vtparameters->at(0);
		}
		ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjProc)
			{
				std::string func = scpcommand_en_reboot;
				((ScpProcObject *)obj)->CallInnerFunction(func, NULL, engine);
			}
		}		
	}
	return TRUE;
}
BOOL WINAPI Proc_Run_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() >= 2)
	{
		std::string strobjtype = vtparameters->at(0);
		std::string procobjname = vtparameters->at(1);

		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobjtype.c_str());
		if (ObjProc == type)
		{
			if (vtparameters->size() >= 3)
			{
				std::string pathname = vtparameters->at(2);
				std::string parameter;
				if (vtparameters->size() == 4)
				{
					parameter = vtparameters->at(3);
					ScpStringObject *strobjtxt = (ScpStringObject *)currentObjectSpace->FindObject(parameter);
					if (strobjtxt && strobjtxt->GetType()==ObjString)
					{
						parameter = strobjtxt->content.c_str();
					}
				}
				ScpStringObject *strobjpepath = (ScpStringObject *)currentObjectSpace->FindObject(pathname);
				if (strobjpepath && strobjpepath->GetType() == ObjString)
				{
					pathname = strobjpepath->content.c_str();
				}
				ScpProcObject *procobj = (ScpProcObject *)currentObjectSpace->FindObject(procobjname);
				if (!procobj)
				{
					procobj = (ScpProcObject *)new ScpProcObject;
					if (procobj)
					{
						procobj->procobjname = procobjname;
						currentObjectSpace->AddObject(procobjname, procobj);
					}
				}
				if (procobj && procobj->GetType() == ObjProc)
				{
					std::string procpathname;
					if (pathname.at(0) != '\"' && pathname.at(pathname.length() - 1) != '\"')
					{
						procpathname = STDSTRINGEXT::Format("\"%s\"", pathname.c_str());
					}
					else
					{
						procpathname = pathname;
					}
					/*if(parameter.at(0)!='\"' && parameter.at(parameter.length()-1)!='\"')
					{
					procobj->Parameter=STDSTRINGEXT::Format(L"\"%s\"",parameter.c_str());
					}
					else
					{
					procobj->Parameter= parameter;
					}*/
					//procobj->Parameter = parameter;
					//procobj->Open();
					std::string func = scpcommand_en_open;
					VTPARAMETERS param;
					param.push_back(procpathname);
					param.push_back(parameter);
					((ScpProcObject *)procobj)->isUIProcess = true;
					((ScpProcObject *)procobj)->CallInnerFunction(func, &param, engine);


				}

			}
		}
	}
	return TRUE;
}
BOOL WINAPI Proc_Enum_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string strobj = vtparameters->at(0);
		std::string name1 = vtparameters->at(1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjProc == type)
		{
			ScpTableObject * tableobj=(ScpTableObject *)currentObjectSpace->FindObject(name1);
			if(tableobj && tableobj->GetType()==ObjTable)
			{				
			ScpProcObject::Enum(tableobj,"name");
			}
		}
	}
	else if (vtparameters->size() == 3)
	{
		std::string strobj = vtparameters->at(0);
		std::string name1 = vtparameters->at(1);
		std::string name2 = vtparameters->at(2);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjProc == type)
		{		
			ScpTableObject * tableobj=(ScpTableObject *)currentObjectSpace->FindObject(name1);
			if(tableobj && tableobj->GetType()==ObjTable)
			{
				ScpProcObject::Enum(tableobj,name2);
			}
		}
	}
	return TRUE;
}
ScpProcObject::ScpProcObject():isUIProcess(false)
{
	objecttype = ObjProc;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_set, InnerFunction_set);
	BindObjectInnerFuction(scpcommand_en_set, InnerFunction_set);

	BindObjectInnerFuction(scpcommand_cn_shutdown, InnerFunction_shutdown);
	BindObjectInnerFuction(scpcommand_en_shutdown, InnerFunction_shutdown);

	BindObjectInnerFuction(scpcommand_cn_close, InnerFunction_close);
	BindObjectInnerFuction(scpcommand_en_close, InnerFunction_close);

	BindObjectInnerFuction(scpcommand_cn_open, InnerFunction_open);
	BindObjectInnerFuction(scpcommand_en_open, InnerFunction_open);


	BindObjectInnerFuction(scpcommand_cn_wait, InnerFunction_wait);
	BindObjectInnerFuction(scpcommand_en_wait, InnerFunction_wait);


	BindObjectInnerFuction(scpcommand_cn_reboot, InnerFunction_reboot);
	BindObjectInnerFuction(scpcommand_en_reboot, InnerFunction_reboot);


	BindObjectInnerFuction(scpcommand_cn_enum, InnerFunction_enum);
	BindObjectInnerFuction(scpcommand_en_enum, InnerFunction_enum);


	BindObjectInnerFuction(scpcommand_cn_run, InnerFunction_run);
	BindObjectInnerFuction(scpcommand_en_run, InnerFunction_run);

}
ScpProcObject::~ScpProcObject()
{
	
}
ScpObject * ScpProcObject::Clone(std::string strObjName)
{
	ScpProcObject *procobj = new ScpProcObject;
	if (procobj)
	{
		procobj->procobjname = procobjname;
	}
	return procobj;
}	
std::string ScpProcObject::ToString()
{
	std::string temp;
	temp = procpathname;
	return temp;
}
void ScpProcObject::Release() 
{
	delete this;
}
BOOL ScpProcObject::Open(std::string path, std::string param)
{
#ifdef _WIN32
	procpathname = path;
	Parameter = param;
	wchar_t CommandLine[2048]={0};
	swprintf(CommandLine,L"%s %s",STDSTRINGEXT::UTF2W(procpathname).c_str(), STDSTRINGEXT::UTF2W(Parameter).c_str());

	if (!isUIProcess)
	{

		SECURITY_ATTRIBUTES sa, sa2;
		HANDLE hInputRead, hInputWrite;
		HANDLE hOutputRead, hOutputWrite;

		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		if (!CreatePipe(&hOutputRead, &hOutputWrite, &sa, 0))
		{
			//printf("Error On CreatePipe1");
			return FALSE;
		}
		sa2.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa2.lpSecurityDescriptor = NULL;
		sa2.bInheritHandle = TRUE;
		if (!CreatePipe(&hInputRead, &hInputWrite, &sa2, 0))
		{
			//printf("Error On CreatePipe2");
			return FALSE;
		}
		STARTUPINFO si;
		//PROCESS_INFORMATION pi;
		si.cb = sizeof(STARTUPINFO);
		GetStartupInfo(&si);
		si.hStdError = hOutputWrite;
		si.hStdOutput = hOutputWrite;
		si.hStdInput = hInputRead;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

		if (!CreateProcessW(NULL, CommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
		{
			return FALSE;
		}
		CloseHandle(hInputRead);
		CloseHandle(hOutputWrite);
		char buffer[4096] = { 0 };
		DWORD bytesRead;
		while (true)
		{
			if (ReadFile(hOutputRead, buffer, 4095, &bytesRead, NULL) == NULL)
			{
				break;
			}
			procoutput += buffer;
			//printf(buffer);// 输出
			Sleep(500);
		}
		CloseHandle(hInputWrite);
		CloseHandle(hOutputRead);

		return TRUE;
	}
	else
	{
		memset(&si,0,sizeof(si));
		si.cb=sizeof(si);
		memset(&pi,0,sizeof(pi));
		if(!CreateProcess(NULL,
			(LPWSTR)CommandLine,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi))
		{

			return FALSE;
		}
		else
		{		
			return TRUE;
		}
	}

#endif

}
BOOL ScpProcObject::ShutDown(std::string processname)
{
	BOOL bret = FALSE;
#ifdef _WIN32
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return bret;
	}
	PROCESSENTRY32W pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
	{
		std::string tmpProcessName = STDSTRINGEXT::W2UTF(STDSTRINGEXT::ToUpperW(pe.szExeFile));
		processname=STDSTRINGEXT::ToUpperA(processname);
		if(tmpProcessName.find(processname)!=std::string::npos)
		{
			bret =ShutDown(pe.th32ProcessID);			
			break;
		}
	}	
#else 
	std::string syscommand=STDSTRINGEXT::Format("killall %s",processname.c_str());
	system(syscommand.c_str());
	bret=TRUE;
#endif  
	return bret;
}   

 BOOL ScpProcObject::ShutDown(DWORD dwPid)
 {
	 BOOL bret = FALSE;
#ifdef _WIN32			
	 TOKEN_PRIVILEGES tkp;
	 HANDLE hToken;
	 OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,&hToken);
	 LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	 tkp.PrivilegeCount = 1;
	 tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	 AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
	 CloseHandle(hToken);
	 HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwPid );
	 if(hProcess!=INVALID_HANDLE_VALUE)
	 {
		 bret =TerminateProcess(hProcess,0);
	 }
#else
	 std::string syscommand=STDSTRINGEXT::Format("kill -s 9 %d",dwPid);
	 system(syscommand.c_str());
	 bret=TRUE;
#endif
	 return bret;
 }
 BOOL ScpProcObject::Enum(ScpObject * tableobj,std::string enumtype)
 {
	 
	 BOOL bret = FALSE;
	 if(!tableobj)
	 {
		 return bret;
	 }
#ifdef _WIN32
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return bret;
	}
	PROCESSENTRY32W pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
	{
		if(enumtype==ScpObjectNames::GetSingleInsatnce()->strObjPid)
		{
			//ScpIntObject * tmpintobj =new ScpIntObject;
			//tmpintobj->value=pe.th32ProcessID;
			//std::string tmpintobjname=STDSTRINGEXT::Format(L"%d",pe.th32ProcessID);
			//((ScpTableObject *)tableobj)->AddElement(tmpintobjname,tmpintobj);


			ScpStringObject * tmpstrobj= new ScpStringObject;
			tmpstrobj->objname= STDSTRINGEXT::W2UTF(pe.szExeFile);
			tmpstrobj->content=STDSTRINGEXT::Format("%s,%d",pe.szExeFile,pe.th32ProcessID);
			((ScpTableObject *)tableobj)->AddElement(tmpstrobj->objname,tmpstrobj);	
		}
		else
		{
			ScpStringObject * tmpstrobj= new ScpStringObject;
			tmpstrobj->objname= STDSTRINGEXT::W2UTF(pe.szExeFile);
			tmpstrobj->content= STDSTRINGEXT::W2UTF(pe.szExeFile);
			((ScpTableObject *)tableobj)->AddElement(tmpstrobj->objname,tmpstrobj);			
		}
	}
	bret =TRUE;
	return bret;
#endif
 }
 BOOL ScpProcObject::Restart()
 {
	 if(ShutDown())
	 {
		 return Open(procpathname,Parameter);
	 }
	 return FALSE;
 }
BOOL ScpProcObject::ShutDown()
{
#ifdef _WIN32
	BOOL bRet = FALSE;
	DWORD dwWaitResult;
	if (pi.hProcess != NULL)
	{
		dwWaitResult = WaitForSingleObject(pi.hProcess, 10);

		if (dwWaitResult == STILL_ACTIVE || dwWaitResult == STATUS_TIMEOUT)
			bRet = TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hProcess);
		pi.hProcess = NULL;
		if (pi.hThread != NULL)
		{
			CloseHandle(pi.hThread);
			pi.hThread = NULL;
		}
	}
	return bRet;
#else
	return FALSE;
#endif
}
void ScpProcObject::Show(CScriptEngine * engine)
{
	engine->PrintError(procpathname);
}
BOOL ScpProcObject::Wait(DWORD dwWaitTime)
{
#ifdef WIN32
	if(pi.hProcess)
	{
		WaitForSingleObject(pi.hProcess,dwWaitTime);
	}
	#else
	#endif // WIN32
	return TRUE;
}
bool ScpProcObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpProcObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}	
	return NULL;
}

ScpObject * ScpProcObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;

}

ScpObject * ScpProcObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
	}

	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string opt = parameters->at(0);
		StringStripQuote(opt);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(opt);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			opt = ((ScpStringObject *)objparam0)->content;
		}
		if (opt == str_EN_output ||
			opt == str_CN_output)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = ((ScpProcObject*)thisObject)->procoutput;
			tname->istemp = true;
			return tname;
		}
	}
	if (parameters->size() == 2)
	{
		std::string param1 = parameters->at(0);
		std::string param2 = parameters->at(1);
		StringStripQuote(param1);
		StringStripQuote(param2);

		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param1);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			param1 = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objparam2 = engine->GetCurrentObjectSpace()->FindObject(param2);
		if (objparam2 && objparam2->GetType() == ObjString)
		{
			param2 = ((ScpStringObject *)objparam2)->content;
		}

		if (param1 == str_EN_option ||
			param1 == str_CN_option)
		{
			if (_stricmp(param2.c_str(), "UI") == 0)
			{
				((ScpProcObject*)thisObject)->isUIProcess = true;
			}
		}
	}
	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return InnerFunction_close(thisObject,parameters,engine);
}

ScpObject * ScpProcObject::InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters == NULL)
	{
		return NULL;
	}
	if (parameters->size() == 0)
		((ScpProcObject*)thisObject)->ShutDown();
	else if (parameters->size() == 1)
	{
		std::string text = parameters->at(0);
		StringStripQuote(text);
		ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjInt)
			{
				DWORD dwPid = ((ScpIntObject*)obj)->value;
				ScpProcObject::ShutDown(dwPid);
			}
			else if (obj->GetType() == ObjString)
			{
				std::string procname = ((ScpStringObject*)obj)->content;
				ScpProcObject::ShutDown(procname);
			}
		}
	}
	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_wait(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpProcObject*)thisObject)->Wait(INFINITE);
	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_reboot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpProcObject*)thisObject)->Restart();
	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_enum(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters)
	{
		if (parameters->size() == 1)
		{
			std::string name1 = parameters->at(0);
			StringStripQuote(name1);
			ScpTableObject * tableobj = (ScpTableObject *)engine->GetCurrentObjectSpace()->FindObject(name1);
			if (tableobj && tableobj->GetType() == ObjTable)
			{
				((ScpProcObject*)thisObject)->Enum(tableobj, "name");
			}
		}
		else if (parameters->size() == 2)
		{
			std::string name1 = parameters->at(0);
			std::string name2 = parameters->at(0);
			StringStripQuote(name1);
			StringStripQuote(name2);
			ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(name2);
			if (objparam0 && objparam0->GetType() == ObjString)
			{
				name2 = ((ScpStringObject *)objparam0)->content;
			}

			ScpTableObject * tableobj = (ScpTableObject *)engine->GetCurrentObjectSpace()->FindObject(name1);
			if (tableobj && tableobj->GetType() == ObjTable)
			{
				((ScpProcObject*)thisObject)->Enum(tableobj, name2);
			}
		}

	}
	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters && parameters->size() == 2)
	{
		std::string path = parameters->at(0);
		std::string param = parameters->at(1);
		StringStripQuote(path);
		StringStripQuote(param);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(path);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			path = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(param);
		if (objparam1 && objparam1->GetType() == ObjString)
		{
			param = ((ScpStringObject *)objparam1)->content;
		}
		((ScpProcObject*)thisObject)->Open(path, param);
	}
	return nullptr;
}

ScpObject * ScpProcObject::InnerFunction_run(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * ret = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (ret)
	{
		if (parameters->size() == 0)
		{
			ret->value = ((ScpProcObject*)thisObject)->Open(((ScpProcObject*)thisObject)->procpathname, ((ScpProcObject*)thisObject)->Parameter) ? 1 : 0;
		}
		else if (parameters->size() == 1)
		{
			if (((ScpProcObject*)thisObject)->procpathname.empty())
			{
				std::string name = parameters->at(0);
				StringStripQuote(name);
				ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(name);
				if (obj && obj->GetType() == ObjString)
				{
					((ScpProcObject*)thisObject)->procpathname = ((ScpStringObject*)obj)->content;
				}
				else
				{
					((ScpProcObject*)thisObject)->procpathname = name;
				}
			}
			else
			{
				std::string temp = parameters->at(0);
				StringStripQuote(temp);
				ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(temp);
				if (obj && obj->GetType() == ObjString)
				{
					temp = ((ScpStringObject*)obj)->content;
				}
				((ScpProcObject*)thisObject)->Parameter = temp;
			}
			ret->value = ((ScpProcObject*)thisObject)->Open(((ScpProcObject*)thisObject)->procpathname, ((ScpProcObject*)thisObject)->Parameter) ? 1 : 0;
		}
		else if (parameters->size() == 2)
		{
			if (((ScpProcObject*)thisObject)->procpathname.empty())
			{
				std::string name = parameters->at(0);
				StringStripQuote(name);
				ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(name);
				if (obj && obj->GetType() == ObjString)
				{
					((ScpProcObject*)thisObject)->procpathname = ((ScpStringObject*)obj)->content;
				}
				else
				{
					((ScpProcObject*)thisObject)->procpathname = name;
				}
				std::string temp = parameters->at(1);
				StringStripQuote(temp);
				ScpObject * objparam = engine->GetCurrentObjectSpace()->FindObject(temp);
				if (objparam && objparam->GetType() == ObjString)
				{
					temp = ((ScpStringObject*)objparam)->content;
				}
				((ScpProcObject*)thisObject)->Parameter = temp;
				ret->value = ((ScpProcObject*)thisObject)->Open(((ScpProcObject*)thisObject)->procpathname, ((ScpProcObject*)thisObject)->Parameter) ? 1 : 0;
			}
			else
			{
				((ScpProcObject*)thisObject)->Parameter = "";
				for (int i = 0;i < parameters->size();i++)
				{
					std::string temp = parameters->at(i);
					StringStripQuote(temp);
					ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(temp);
					if (obj && obj->GetType() == ObjString)
					{
						temp = ((ScpStringObject*)obj)->content;
					}
					((ScpProcObject*)thisObject)->Parameter += temp;
					((ScpProcObject*)thisObject)->Parameter += " ";
				}
				ret->value = ((ScpProcObject*)thisObject)->Open(((ScpProcObject*)thisObject)->procpathname, ((ScpProcObject*)thisObject)->Parameter) ? 1 : 0;
			}

		}
		else if (parameters->size() >= 2)
		{
			if (((ScpProcObject*)thisObject)->procpathname.empty())
			{
				std::string name = parameters->at(0);
				StringStripQuote(name);
				ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(name);
				if (obj && obj->GetType() == ObjString)
				{
					((ScpProcObject*)thisObject)->procpathname = ((ScpStringObject*)obj)->content;
				}
				else
				{
					((ScpProcObject*)thisObject)->procpathname = name;
				}
				((ScpProcObject*)thisObject)->Parameter = "";
				for (int i = 1;i < parameters->size();i++)
				{
					std::string temp = parameters->at(i);
					StringStripQuote(temp);
					ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(temp);
					if (obj && obj->GetType() == ObjString)
					{
						temp = ((ScpStringObject*)obj)->content;
					}
					((ScpProcObject*)thisObject)->Parameter += temp;
					((ScpProcObject*)thisObject)->Parameter += " ";
				}
				ret->value = ((ScpProcObject*)thisObject)->Open(((ScpProcObject*)thisObject)->procpathname, ((ScpProcObject*)thisObject)->Parameter) ? 1 : 0;
			}
			else
			{
				((ScpProcObject*)thisObject)->Parameter = "";
				for (int i = 0;i < parameters->size();i++)
				{
					std::string temp = parameters->at(i);
					StringStripQuote(temp);
					ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(temp);
					if (obj && obj->GetType() == ObjString)
					{
						temp = ((ScpStringObject*)obj)->content;
					}
					((ScpProcObject*)thisObject)->Parameter += temp;
					((ScpProcObject*)thisObject)->Parameter += " ";
				}
				ret->value = ((ScpProcObject*)thisObject)->Open(((ScpProcObject*)thisObject)->procpathname, ((ScpProcObject*)thisObject)->Parameter) ? 1 : 0;
			}
		}
	}
	return ret;
}
