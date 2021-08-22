// SocketAddin.cpp: 定义 DLL 应用程序的导出函数。
//

#include "header.h"
#include "ScpSocketObject.h"
#include "ScpNetConnectionObject.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#ifdef _WIN32

#else

#define wcsicmp wcscasecmp
static wchar_t* wcscpy_s(wchar_t * dst,int len,const wchar_t * src)
{
	return wcscpy(dst,src);
}
#endif
DWORD WINAPI GetObjectCount()
{
	return 3;
}
BOOL WINAPI GetObjectNameId(DWORD dwIndex,wchar_t * ObjTypeNameCn, DWORD ObjTypeNameCnSize, wchar_t * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId)
{
	if (dwIndex == 0)
	{
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjNetConnection);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjNetConnection);
		*dwObjectId = ObjNetConnection;
		return TRUE;
	}
	else if (dwIndex == 1)
	{
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjSocket);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjSocket);
		*dwObjectId = ObjSocket;
		return TRUE;
	}
	else if (dwIndex == 2)
	{
		wcscpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjAddress);
		wcscpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjAddress);
		*dwObjectId = ObjAddress;
		return TRUE;
	}
	return FALSE;
}

DWORD WINAPI GetUniqObjectIdEx(const wchar_t * ObjTypeName)
{
	if (wcsicmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
		return ObjNetConnection;
	else if (wcsicmp(ObjTypeName, str_EN_ObjSocket) == 0)
		return ObjSocket;
	else if (wcsicmp(ObjTypeName, str_EN_ObjAddress) == 0)
		return ObjAddress;
	return -1;
}
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const wchar_t * ObjTypeName)
{	
	if (wcsicmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
		return NetConnectionObjFactory;
	else if (wcsicmp(ObjTypeName, str_EN_ObjSocket) == 0)
		return SocketObjFactory;
	else if (wcsicmp(ObjTypeName, str_EN_ObjAddress) == 0)
		return ScpAddressObjectFactory;
	return NULL;
}

DWORD WINAPI ExtObjCommandCount(const wchar_t * ObjTypeName)
{
	if (ObjTypeName)
	{
		if (wcsicmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
		{
			return 5;
		}	
		else if (wcsicmp(ObjTypeName, str_EN_ObjAddress) == 0)
		{
			return 1;
		}
	}
	return 0;
}
BOOL WINAPI ExtObjCommandRegisterFunction(const wchar_t * ObjTypeName, DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, wchar_t * CommandNameCn, wchar_t *CommandNameEn, ExtObjectCommandFunction *command)
{
	if (wcsicmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
	{
		if (dwIndex == 0)
		{
			*command = NetConnection_Shutdown_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_shutdown;
			wcscpy(CommandNameCn, scpcommand_cn_shutdown);
			wcscpy(CommandNameEn, scpcommand_en_shutdown);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = NetConnection_Connect_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_connect;
			wcscpy(CommandNameCn, scpcommand_cn_connect);
			wcscpy(CommandNameEn, scpcommand_en_connect);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = NetConnection_Send_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_send;
			wcscpy(CommandNameCn, scpcommand_cn_send);
			wcscpy(CommandNameEn, scpcommand_en_send);
			return TRUE;
		}
		else if (dwIndex == 3)
		{
			*command = NetConnection_Receive_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_receive;
			wcscpy(CommandNameCn, scpcommand_cn_receive);
			wcscpy(CommandNameEn, scpcommand_en_receive);
			return TRUE;
		}
		else if (dwIndex == 4)
		{
			*command = NetConnection_Watch_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_watch;
			wcscpy(CommandNameCn, scpcommand_cn_watch);
			wcscpy(CommandNameEn, scpcommand_en_watch);
			return TRUE;
		}
		
	}
	else if (wcsicmp(ObjTypeName, str_EN_ObjAddress) == 0)
	{
		if (dwIndex == 0)
		{
			*command = AddressObject_Set_Command;
			*dwObjectId = ObjAddress;
			*dwCommandId = vl_set;
			wcscpy(CommandNameCn, scpcommand_cn_set);
			wcscpy(CommandNameEn, scpcommand_en_set);
			return TRUE;
		}
	}
	return FALSE;
}
