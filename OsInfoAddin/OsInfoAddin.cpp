// OsInfoAddin.cpp : 定义 DLL 应用程序的导出函数。
//
#ifdef _WIN32
#include "stdafx.h"
#else
#define wcsicmp wcscasecmp

#endif
#include "OsInfoAddin.h"
#include "ScpOsInfoObject.h"
#include "ScpShareMemoryObject.h"
#include "ScpPipeObject.h"
#include "ScpProcObject.h"
#include "ScpComputerObject.h"
#include "ScpThreadObject.h"
#include "ScpClipboardObject.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
DWORD GetObjectCount()
{
	return 7;
}
BOOL GetObjectNameId(DWORD dwIndex, wchar_t * ObjTypeNameCn, DWORD ObjTypeNameCnSize, wchar_t * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId)
{
	if (dwIndex == 0)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjOsInfo);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjOsInfo);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjOsInfo);
		wcscpy(ObjTypeNameEn,  str_EN_ObjOsInfo);	
#endif
		*dwObjectId = ObjOsInfo;
		return TRUE;
	}
	else if (dwIndex == 1)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjClipboard);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjClipboard);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjClipboard);
		wcscpy(ObjTypeNameEn,  str_EN_ObjClipboard);	
#endif
		*dwObjectId = ObjClipboard;
		return TRUE;
	}
	else if (dwIndex == 2)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjShareMemory);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjShareMemory);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjShareMemory);
		wcscpy(ObjTypeNameEn,  str_EN_ObjShareMemory);	
#endif
		*dwObjectId = ObjShareMemory;
		return TRUE;
	}
	else if (dwIndex == 3)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjPipe);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjPipe);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjPipe);
		wcscpy(ObjTypeNameEn,  str_EN_ObjPipe);	
#endif
		*dwObjectId = ObjPipe;

		return TRUE;
	}
	else if (dwIndex == 4)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjProc);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjProc);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjProc);
		wcscpy(ObjTypeNameEn,  str_EN_ObjProc);	
#endif
		*dwObjectId = ObjProc;
		return TRUE;
	}
	else if (dwIndex == 5)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjComputer);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjComputer);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjComputer);
		wcscpy(ObjTypeNameEn,  str_EN_ObjComputer);	
#endif
		*dwObjectId = ObjComputer;
		return TRUE;
	}
	else if (dwIndex == 6)
	{
#ifdef _WIN32
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjThread);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjThread);
#else
		wcscpy(ObjTypeNameCn,  str_CN_ObjThread);
		wcscpy(ObjTypeNameEn,  str_EN_ObjThread);	
#endif
		*dwObjectId = ObjThread;
		return TRUE;
	}
	return FALSE;
}

DWORD WINAPI GetUniqObjectIdEx(const wchar_t * ObjTypeName)
{
	if (wcsicmp(ObjTypeName, str_EN_ObjOsInfo) == 0)
		return ObjOsInfo;
	else if(wcsicmp(ObjTypeName, str_EN_ObjClipboard)==0)
	{
		return ObjClipboard;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
	{
		return ObjShareMemory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjPipe) == 0)
	{
		return ObjPipe;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjProc) == 0)
	{
		return ObjProc;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjProc1) == 0)
	{
		return ObjProc;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjComputer) == 0)
	{
		return ObjComputer;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjThread) == 0)
	{
		return ObjThread;
	}
	return -1;
}
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const wchar_t * ObjTypeName)
{
	if (wcsicmp(ObjTypeName, str_EN_ObjOsInfo) == 0)
		return ScpOsInfoObjectFactory;
	else if (wcsicmp(ObjTypeName, str_EN_ObjClipboard) == 0)
	{
		return ScpClipboardObjectFactory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
	{
		return ShareMemroyObjectFactory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjPipe) == 0)
	{
		return PipeObjectFactory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjProc) == 0)
	{
		return ScpProcObjectFactory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjProc1) == 0)
	{
		return ScpProcObjectFactory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjComputer) == 0)
	{
		return ScpComputerObjectFactory;
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjThread) == 0)
	{
		return ScpThreadObjectFactory;
	}
	return NULL;
}

DWORD WINAPI ExtObjCommandCount(const wchar_t * ObjTypeName)
{
	if (ObjTypeName)
	{
		if (wcsicmp(ObjTypeName, str_EN_ObjComputer) == 0)
		{
			return 3;
		}
		else if (wcsicmp(ObjTypeName, str_EN_ObjProc) == 0)
		{
			return 5;
		}
		else if (wcsicmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
		{
			return 4;
		}
		else if (wcsicmp(ObjTypeName, str_EN_ObjPipe) == 0)
		{
			return 3;
		}
		else if (wcsicmp(ObjTypeName, str_EN_ObjThread) == 0)
		{
			return 3;
		}
	}
	return 0;
}
BOOL WINAPI ExtObjCommandRegisterFunction(const wchar_t * ObjTypeName,DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, wchar_t * CommandNameCn, wchar_t *CommandNameEn, ExtObjectCommandFunction *command)
{
	if (wcsicmp(ObjTypeName, str_EN_ObjComputer) == 0)
	{
		if (dwIndex == 0)
		{
			*command = Computer_Shutdown_Command;
			*dwObjectId = ObjComputer;
			*dwCommandId = vl_shutdown;
			wcscpy(CommandNameCn, scpcommand_cn_shutdown);
			wcscpy(CommandNameEn, scpcommand_en_shutdown);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = Computer_Reboot_Command;
			*dwObjectId = ObjComputer;
			*dwCommandId = vl_reboot;
			wcscpy(CommandNameCn, scpcommand_cn_reboot);
			wcscpy(CommandNameEn, scpcommand_en_reboot);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = Computer_Suspend_Command;
			*dwObjectId = ObjComputer;
			*dwCommandId = vl_suspend;
			wcscpy(CommandNameCn, scpcommand_cn_suspend);
			wcscpy(CommandNameEn, scpcommand_en_suspend);
			return TRUE;
		}
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjProc) == 0)
	{
		if (dwIndex == 0)
		{
			*command = Proc_Reboot_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_reboot;
			wcscpy(CommandNameCn, scpcommand_cn_reboot);
			wcscpy(CommandNameEn, scpcommand_en_reboot);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = Proc_Shutdown_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_shutdown;
			wcscpy(CommandNameCn, scpcommand_cn_shutdown);
			wcscpy(CommandNameEn, scpcommand_en_shutdown);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = Proc_Wait_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_wait;
			wcscpy(CommandNameCn, scpcommand_cn_wait);
			wcscpy(CommandNameEn, scpcommand_en_wait);
			return TRUE;
		}
		else if (dwIndex == 3)
		{
			*command = Proc_Run_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_run;
			wcscpy(CommandNameCn, scpcommand_cn_run);
			wcscpy(CommandNameEn, scpcommand_en_run);
			return TRUE;
		}
		else if (dwIndex == 4)
		{
			*command = Proc_Enum_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_enum;
			wcscpy(CommandNameCn, scpcommand_cn_enum);
			wcscpy(CommandNameEn, scpcommand_en_enum);
			return TRUE;
		}
		
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
	{
		if (dwIndex == 0)
		{
			*command = ShareMemory_Shutdown_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_shutdown;
			wcscpy(CommandNameCn, scpcommand_cn_shutdown);
			wcscpy(CommandNameEn, scpcommand_cn_shutdown);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = ShareMemory_Open_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_open;
			wcscpy(CommandNameCn, scpcommand_cn_open);
			wcscpy(CommandNameEn, scpcommand_en_open);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = ShareMemory_Write_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_write;
			wcscpy(CommandNameCn, scpcommand_cn_write);
			wcscpy(CommandNameEn, scpcommand_en_write);
			return TRUE;
		}
		else if (dwIndex == 3)
		{
			*command = ShareMemory_Read_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_read;
			wcscpy(CommandNameCn, scpcommand_cn_read);
			wcscpy(CommandNameEn, scpcommand_en_read);
			return TRUE;
		}
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjPipe) == 0)
	{
		if (dwIndex == 0)
		{
			*command = Pipe_Open_Command;
			*dwObjectId = ObjPipe;
			*dwCommandId = vl_open;
			wcscpy(CommandNameCn, scpcommand_cn_open);
			wcscpy(CommandNameEn, scpcommand_en_open);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = Pipe_Write_Command;
			*dwObjectId = ObjPipe;
			*dwCommandId = vl_write;
			wcscpy(CommandNameCn, scpcommand_cn_write);
			wcscpy(CommandNameEn, scpcommand_en_write);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = Pipe_Read_Command;
			*dwObjectId = ObjPipe;
			*dwCommandId = vl_read;
			wcscpy(CommandNameCn, scpcommand_cn_read);
			wcscpy(CommandNameEn, scpcommand_en_read);
			return TRUE;
		}		
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjThread) == 0)
	{
	if (dwIndex == 0)
	{
		*command = Thread_Shutdown_Command;
		*dwObjectId = ObjThread;
		*dwCommandId = vl_shutdown;
		wcscpy(CommandNameCn, scpcommand_cn_shutdown);
		wcscpy(CommandNameEn, scpcommand_en_shutdown);
		return TRUE;
	}
	else if (dwIndex == 1)
	{
		*command = Thread_Run_Command;
		*dwObjectId = ObjThread;
		*dwCommandId = vl_run;
		wcscpy(CommandNameCn, scpcommand_cn_run);
		wcscpy(CommandNameEn, scpcommand_en_run);
		return TRUE;
	}
	else if (dwIndex == 2)
	{
		*command = Thread_Wait_Command;
		*dwObjectId = ObjThread;
		*dwCommandId = vl_wait;
		wcscpy(CommandNameCn, scpcommand_cn_wait);
		wcscpy(CommandNameEn, scpcommand_en_wait);
		return TRUE;
	}
	}
	return FALSE;
}
