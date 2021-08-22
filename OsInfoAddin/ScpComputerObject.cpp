#include "ScpComputerObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"
#ifdef WIN32
#include <PowrProf.h>
#pragma comment (lib,"PowrProf.lib")
#endif

ScpObject * __stdcall ScpComputerObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	ScpComputerObject * computer = new ScpComputerObject;
	return computer;
}

BOOL WINAPI Computer_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		if (vtparameters->size() == 1)
		{
			std::wstring text = vtparameters->at(0);
			ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
			if (obj)
			{
				if (obj->GetType() == ObjComputer)
				{
					ScpComputerObject computer;
					computer.Shutdown();
				}
			}
			else
			{
				if (text == str_EN_ObjComputer || text == str_CN_ObjComputer)
				{
					ScpComputerObject computer;
					computer.Shutdown();
				}
			}
		}
	}
	return TRUE;
}
BOOL WINAPI Computer_Reboot_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		if (vtparameters->size() == 1)
		{
			std::wstring text = vtparameters->at(0);
			ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
			if (obj)
			{
				if (obj->GetType() == ObjComputer)
				{
					ScpComputerObject computer;
					computer.Reboot();
				}
			}
			else
			{
				if (text == str_EN_ObjComputer || text == str_CN_ObjComputer)
				{
					ScpComputerObject computer;
					computer.Reboot();
				}
			}

		}
	}
	return TRUE;
}
BOOL WINAPI Computer_Suspend_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		if (vtparameters->size() == 1)
		{
			std::wstring text = vtparameters->at(0);
			ScpObject *obj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(text);
			if (obj)
			{
				if (obj->GetType() == ObjComputer)
				{
					ScpComputerObject computer;
					computer.Suspend();
				}
			}
			else
			{
				if (text == str_EN_ObjComputer || text == str_CN_ObjComputer)
				{
					ScpComputerObject computer;
					computer.Suspend();
				}
			}
		}
	}
	return TRUE;
}
void SuspendComputer()
{
#ifdef WIN32
	SetSuspendState(TRUE,TRUE,TRUE);
#endif
}


ScpComputerObject::ScpComputerObject(void)
{
	objecttype = ObjComputer;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_shutdown, InnerFunction_shutdown);
	BindObjectInnerFuction(scpcommand_en_shutdown, InnerFunction_shutdown);

	BindObjectInnerFuction(scpcommand_cn_reboot, InnerFunction_reboot);
	BindObjectInnerFuction(scpcommand_en_reboot, InnerFunction_reboot);

	BindObjectInnerFuction(scpcommand_cn_suspend, InnerFunction_suspend);
	BindObjectInnerFuction(scpcommand_en_suspend, InnerFunction_suspend);

#ifdef WIN32
	OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
	CloseHandle(hToken);
#endif
}
ScpComputerObject::~ScpComputerObject(void)
{
#ifdef WIN32
	tkp.Privileges[0].Attributes = 0;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
#endif
}

void	ScpComputerObject::Show(CScriptEngine * engine)
{

}
ScpObject *	ScpComputerObject::Clone(std::wstring strObjName)
{
	ScpComputerObject *obj = new ScpComputerObject;
	return obj;
	
}
std::wstring 	ScpComputerObject::ToString()
{
	std::wstring temp;
	return temp;
}
void 	ScpComputerObject::Release()
{
	delete this;
}
bool ScpComputerObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpComputerObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	if(functionname==scpcommand_cn_shutdown ||	functionname==scpcommand_en_shutdown)
	{
		
	}
	else if(functionname==scpcommand_cn_reboot || functionname==scpcommand_en_reboot)
	{
		
	}
	else if(functionname==scpcommand_cn_suspend ||	functionname==scpcommand_en_suspend)
	{
		
	}
	else if(functionname==scpcommand_cn_show || functionname == scpcommand_en_show)
	{
		
	}
	else if(functionname ==scpcommand_cn_get || functionname == scpcommand_en_get)
	{
		
	}
	return NULL;
}

void ScpComputerObject::Shutdown()
{
#ifdef _WIN32
			ExitWindowsEx(EWX_POWEROFF|EWX_SHUTDOWN|EWX_FORCE,0);
#else
			system("shutdown -f -h now");
#endif
}
void ScpComputerObject::Reboot()
{
#ifdef _WIN32
			ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);
			
#else
			system("shutdown -f -r now");
#endif
}
void ScpComputerObject::Suspend()
{
#ifdef _WIN32
	SuspendComputer();
#endif
}

ScpObject * ScpComputerObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpComputerObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
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
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

ScpObject * ScpComputerObject::InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpComputerObject*)thisObject)->Shutdown();
	return thisObject;
}

ScpObject * ScpComputerObject::InnerFunction_reboot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpComputerObject*)thisObject)->Reboot();
	return thisObject;
}

ScpObject * ScpComputerObject::InnerFunction_suspend(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpComputerObject*)thisObject)->Suspend();
	return thisObject;
}
