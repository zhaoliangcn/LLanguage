// OsInfoAddin.cpp : 定义 DLL 应用程序的导出函数。
//
#ifdef _WIN32
#include "stdafx.h"
#else
#define wcsicmp wcscasecmp
#define _stricmp strcasecmp

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
BOOL GetObjectNameId(DWORD dwIndex, char * ObjTypeNameCn, DWORD ObjTypeNameCnSize, char * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId)
{
	if (dwIndex == 0)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjOsInfo);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjOsInfo);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjOsInfo);
		strcpy(ObjTypeNameEn,  str_EN_ObjOsInfo);
#endif
		*dwObjectId = ObjOsInfo;
		return TRUE;
	}
	else if (dwIndex == 1)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjClipboard);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjClipboard);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjClipboard);
		strcpy(ObjTypeNameEn,  str_EN_ObjClipboard);
#endif
		*dwObjectId = ObjClipboard;
		return TRUE;
	}
	else if (dwIndex == 2)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjShareMemory);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjShareMemory);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjShareMemory);
		strcpy(ObjTypeNameEn,  str_EN_ObjShareMemory);
#endif
		*dwObjectId = ObjShareMemory;
		return TRUE;
	}
	else if (dwIndex == 3)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjPipe);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjPipe);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjPipe);
		strcpy(ObjTypeNameEn,  str_EN_ObjPipe);
#endif
		*dwObjectId = ObjPipe;

		return TRUE;
	}
	else if (dwIndex == 4)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjProc);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjProc);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjProc);
		strcpy(ObjTypeNameEn,  str_EN_ObjProc);
#endif
		*dwObjectId = ObjProc;
		return TRUE;
	}
	else if (dwIndex == 5)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjComputer);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjComputer);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjComputer);
		strcpy(ObjTypeNameEn,  str_EN_ObjComputer);
#endif
		*dwObjectId = ObjComputer;
		return TRUE;
	}
	else if (dwIndex == 6)
	{
#ifdef _WIN32
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjThread);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjThread);
#else
		strcpy(ObjTypeNameCn,  str_CN_ObjThread);
		strcpy(ObjTypeNameEn,  str_EN_ObjThread);	
#endif
		*dwObjectId = ObjThread;
		return TRUE;
	}
	return FALSE;
}

DWORD WINAPI GetUniqObjectIdEx(const char * ObjTypeName)
{
	if (_stricmp(ObjTypeName, str_EN_ObjOsInfo) == 0)
		return ObjOsInfo;
	else if(_stricmp(ObjTypeName, str_EN_ObjClipboard)==0)
	{
		return ObjClipboard;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
	{
		return ObjShareMemory;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjPipe) == 0)
	{
		return ObjPipe;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjProc) == 0)
	{
		return ObjProc;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjProc1) == 0)
	{
		return ObjProc;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjComputer) == 0)
	{
		return ObjComputer;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjThread) == 0)
	{
		return ObjThread;
	}
	return INVALID_OBJECT_ID;
}
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const char * ObjTypeName)
{
	if (_stricmp(ObjTypeName, str_EN_ObjOsInfo) == 0)
		return ScpOsInfoObjectFactory;
	else if (_stricmp(ObjTypeName, str_EN_ObjClipboard) == 0)
	{
		return ScpClipboardObjectFactory;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
	{
		return ShareMemroyObjectFactory;
	}	
	else if (_stricmp(ObjTypeName, str_EN_ObjPipe) == 0)
	{
		return PipeObjectFactory;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjProc) == 0)
	{
		return ScpProcObjectFactory;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjProc1) == 0)
	{
		return ScpProcObjectFactory;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjComputer) == 0)
	{
		return ScpComputerObjectFactory;
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjThread) == 0)
	{
		return ScpThreadObjectFactory;
	}
	return NULL;
}

DWORD WINAPI ExtObjCommandCount(const char * ObjTypeName)
{
	if (ObjTypeName)
	{
		if (_stricmp(ObjTypeName, str_EN_ObjComputer) == 0)
		{
			return 3;
		}
		else if (_stricmp(ObjTypeName, str_EN_ObjProc) == 0)
		{
			return 5;
		}
		else if (_stricmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
		{
			return 4;
		}
		else if (_stricmp(ObjTypeName, str_EN_ObjPipe) == 0)
		{
			return 3;
		}
		else if (_stricmp(ObjTypeName, str_EN_ObjThread) == 0)
		{
			return 3;
		}
	}
	return 0;
}
BOOL WINAPI ExtObjCommandRegisterFunction(const char * ObjTypeName,DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, char * CommandNameCn, char *CommandNameEn, ExtObjectCommandFunction *command)
{
	if (_stricmp(ObjTypeName, str_EN_ObjComputer) == 0)
	{
		if (dwIndex == 0)
		{
			*command = Computer_Shutdown_Command;
			*dwObjectId = ObjComputer;
			*dwCommandId = vl_shutdown;
			strcpy(CommandNameCn, scpcommand_cn_shutdown);
			strcpy(CommandNameEn, scpcommand_en_shutdown);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = Computer_Reboot_Command;
			*dwObjectId = ObjComputer;
			*dwCommandId = vl_reboot;
			strcpy(CommandNameCn, scpcommand_cn_reboot);
			strcpy(CommandNameEn, scpcommand_en_reboot);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = Computer_Suspend_Command;
			*dwObjectId = ObjComputer;
			*dwCommandId = vl_suspend;
			strcpy(CommandNameCn, scpcommand_cn_suspend);
			strcpy(CommandNameEn, scpcommand_en_suspend);
			return TRUE;
		}
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjProc) == 0)
	{
		if (dwIndex == 0)
		{
			*command = Proc_Reboot_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_reboot;
			strcpy(CommandNameCn, scpcommand_cn_reboot);
			strcpy(CommandNameEn, scpcommand_en_reboot);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = Proc_Shutdown_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_shutdown;
			strcpy(CommandNameCn, scpcommand_cn_shutdown);
			strcpy(CommandNameEn, scpcommand_en_shutdown);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = Proc_Wait_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_wait;
			strcpy(CommandNameCn, scpcommand_cn_wait);
			strcpy(CommandNameEn, scpcommand_en_wait);
			return TRUE;
		}
		else if (dwIndex == 3)
		{
			*command = Proc_Run_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_run;
			strcpy(CommandNameCn, scpcommand_cn_run);
			strcpy(CommandNameEn, scpcommand_en_run);
			return TRUE;
		}
		else if (dwIndex == 4)
		{
			*command = Proc_Enum_Command;
			*dwObjectId = ObjProc;
			*dwCommandId = vl_enum;
			strcpy(CommandNameCn, scpcommand_cn_enum);
			strcpy(CommandNameEn, scpcommand_en_enum);
			return TRUE;
		}
		
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjShareMemory) == 0)
	{
		if (dwIndex == 0)
		{
			*command = ShareMemory_Shutdown_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_shutdown;
			strcpy(CommandNameCn, scpcommand_cn_shutdown);
			strcpy(CommandNameEn, scpcommand_cn_shutdown);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = ShareMemory_Open_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_open;
			strcpy(CommandNameCn, scpcommand_cn_open);
			strcpy(CommandNameEn, scpcommand_en_open);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = ShareMemory_Write_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_write;
			strcpy(CommandNameCn, scpcommand_cn_write);
			strcpy(CommandNameEn, scpcommand_en_write);
			return TRUE;
		}
		else if (dwIndex == 3)
		{
			*command = ShareMemory_Read_Command;
			*dwObjectId = ObjShareMemory;
			*dwCommandId = vl_read;
			strcpy(CommandNameCn, scpcommand_cn_read);
			strcpy(CommandNameEn, scpcommand_en_read);
			return TRUE;
		}
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjPipe) == 0)
	{
		if (dwIndex == 0)
		{
			*command = Pipe_Open_Command;
			*dwObjectId = ObjPipe;
			*dwCommandId = vl_open;
			strcpy(CommandNameCn, scpcommand_cn_open);
			strcpy(CommandNameEn, scpcommand_en_open);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = Pipe_Write_Command;
			*dwObjectId = ObjPipe;
			*dwCommandId = vl_write;
			strcpy(CommandNameCn, scpcommand_cn_write);
			strcpy(CommandNameEn, scpcommand_en_write);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = Pipe_Read_Command;
			*dwObjectId = ObjPipe;
			*dwCommandId = vl_read;
			strcpy(CommandNameCn, scpcommand_cn_read);
			strcpy(CommandNameEn, scpcommand_en_read);
			return TRUE;
		}		
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjThread) == 0)
	{
	if (dwIndex == 0)
	{
		*command = Thread_Shutdown_Command;
		*dwObjectId = ObjThread;
		*dwCommandId = vl_shutdown;
		strcpy(CommandNameCn, scpcommand_cn_shutdown);
		strcpy(CommandNameEn, scpcommand_en_shutdown);
		return TRUE;
	}
	else if (dwIndex == 1)
	{
		*command = Thread_Run_Command;
		*dwObjectId = ObjThread;
		*dwCommandId = vl_run;
		strcpy(CommandNameCn, scpcommand_cn_run);
		strcpy(CommandNameEn, scpcommand_en_run);
		return TRUE;
	}
	else if (dwIndex == 2)
	{
		*command = Thread_Wait_Command;
		*dwObjectId = ObjThread;
		*dwCommandId = vl_wait;
		strcpy(CommandNameCn, scpcommand_cn_wait);
		strcpy(CommandNameEn, scpcommand_en_wait);
		return TRUE;
	}
	}
	return FALSE;
}
