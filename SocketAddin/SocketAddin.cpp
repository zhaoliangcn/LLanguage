// SocketAddin.cpp: 定义 DLL 应用程序的导出函数。
//

#include "header.h"
#include "ScpSocketObject.h"
#include "ScpNetConnectionObject.h"
#include "ScpAddressObject.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#ifdef _WIN32

#else

#define wcsicmp wcscasecmp
#define _stricmp strcasecmp
static const char * strcpy_s(char * dst,int len,const char * src)
{
	return strcpy(dst,src);
}
#endif
DWORD WINAPI GetObjectCount()
{
	return 3;
}
BOOL WINAPI GetObjectNameId(DWORD dwIndex,char * ObjTypeNameCn, DWORD ObjTypeNameCnSize, char * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId)
{
	if (dwIndex == 0)
	{
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjNetConnection);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjNetConnection);
		*dwObjectId = ObjNetConnection;
		return TRUE;
	}
	else if (dwIndex == 1)
	{
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjSocket);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjSocket);
		*dwObjectId = ObjSocket;
		return TRUE;
	}
	else if (dwIndex == 2)
	{
		strcpy_s(ObjTypeNameCn, ObjTypeNameCnSize, str_CN_ObjAddress);
		strcpy_s(ObjTypeNameEn, ObjTypeNameEnSize, str_EN_ObjAddress);
		*dwObjectId = ObjAddress;
		return TRUE;
	}
	return FALSE;
}

DWORD WINAPI GetUniqObjectIdEx(const char * ObjTypeName)
{
	if (_stricmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
		return ObjNetConnection;
	else if (_stricmp(ObjTypeName, str_EN_ObjSocket) == 0)
		return ObjSocket;
	else if (_stricmp(ObjTypeName, str_EN_ObjAddress) == 0)
		return ObjAddress;
	return INVALID_OBJECT_ID;
}
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const char * ObjTypeName)
{	
	if (_stricmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
		return NetConnectionObjFactory;
	else if (_stricmp(ObjTypeName, str_EN_ObjSocket) == 0)
		return SocketObjFactory;
	else if (_stricmp(ObjTypeName, str_EN_ObjAddress) == 0)
		return ScpAddressObjectFactory;
	return NULL;
}

DWORD WINAPI ExtObjCommandCount(const char * ObjTypeName)
{
	if (ObjTypeName)
	{
		if (_stricmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
		{
			return 5;
		}	
		else if (_stricmp(ObjTypeName, str_EN_ObjAddress) == 0)
		{
			return 1;
		}
	}
	return 0;
}
BOOL WINAPI ExtObjCommandRegisterFunction(const char * ObjTypeName, DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, char * CommandNameCn, char *CommandNameEn, ExtObjectCommandFunction *command)
{
	if (_stricmp(ObjTypeName, str_EN_ObjNetConnection) == 0)
	{
		if (dwIndex == 0)
		{
			*command = NetConnection_Shutdown_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_shutdown;
			strcpy(CommandNameCn, scpcommand_cn_shutdown);
			strcpy(CommandNameEn, scpcommand_en_shutdown);
			return TRUE;
		}
		else if (dwIndex == 1)
		{
			*command = NetConnection_Connect_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_connect;
			strcpy(CommandNameCn, scpcommand_cn_connect);
			strcpy(CommandNameEn, scpcommand_en_connect);
			return TRUE;
		}
		else if (dwIndex == 2)
		{
			*command = NetConnection_Send_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_send;
			strcpy(CommandNameCn, scpcommand_cn_send);
			strcpy(CommandNameEn, scpcommand_en_send);
			return TRUE;
		}
		else if (dwIndex == 3)
		{
			*command = NetConnection_Receive_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_receive;
			strcpy(CommandNameCn, scpcommand_cn_receive);
			strcpy(CommandNameEn, scpcommand_en_receive);
			return TRUE;
		}
		else if (dwIndex == 4)
		{
			*command = NetConnection_Watch_Command;
			*dwObjectId = ObjNetConnection;
			*dwCommandId = vl_watch;
			strcpy(CommandNameCn, scpcommand_cn_watch);
			strcpy(CommandNameEn, scpcommand_en_watch);
			return TRUE;
		}
		
	}
	else if (_stricmp(ObjTypeName, str_EN_ObjAddress) == 0)
	{
		if (dwIndex == 0)
		{
			*command = AddressObject_Set_Command;
			*dwObjectId = ObjAddress;
			*dwCommandId = vl_set;
			strcpy(CommandNameCn, scpcommand_cn_set);
			strcpy(CommandNameEn, scpcommand_en_set);
			return TRUE;
		}
	}
	return FALSE;
}
DWORD WINAPI GetBinaryOperationCount()
{
	return 1;
}
BOOL WINAPI BinaryOperationRegister(DWORD dwIndex, char* Operation, DWORD OperationSize, ScpObjectType& obj1Type, ScpObjectType& obj2Type, pBinaryOpertaion* op)
{
	if (dwIndex == 0)
	{
		strcpy_s(Operation, OperationSize, "=");
		obj1Type = ObjAddress;
		obj2Type = ObjAddress;
		*op = BinaryOpertaionAssign;
		return TRUE;
	}	
	return FALSE;
}

