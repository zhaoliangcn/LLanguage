// header.h: 标准系统包含文件的包含文件，
// or project specific include files
//

#pragma once
#ifdef _WIN32
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>
#endif


// TODO: 在此处引用程序需要的其他头文件
#include "../ScriptEngineLib/addin.h"
#include "../ScriptEngineLib/ScpObject.h"

#ifdef __cplusplus
extern "C" {
#endif 

DWORD WINAPI GetObjectCount();
BOOL WINAPI GetObjectNameId(DWORD dwIndex, char * ObjTypeNameCn, DWORD ObjTypeNameCnSize, char * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId);


DWORD WINAPI GetUniqObjectIdEx(const char * ObjTypeName);
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const char * ObjTypeName);

DWORD WINAPI ExtObjCommandCount(const char * ObjTypeName);
BOOL WINAPI ExtObjCommandRegisterFunction(const char * ObjTypeName, DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, char * CommandNameCn, char *CommandNameEn, ExtObjectCommandFunction *command);

DWORD WINAPI GetBinaryOperationCount();
BOOL WINAPI BinaryOperationRegister(DWORD dwIndex, wchar_t* Operation, DWORD OperationSize, ScpObjectType& obj1Type, ScpObjectType& obj2Type, pBinaryOpertaion* op);

#ifdef __cplusplus
}
#endif 