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
BOOL WINAPI GetObjectNameId(DWORD dwIndex, wchar_t * ObjTypeNameCn, DWORD ObjTypeNameCnSize, wchar_t * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId);


DWORD WINAPI GetUniqObjectIdEx(const wchar_t * ObjTypeName);
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const wchar_t * ObjTypeName);

DWORD WINAPI ExtObjCommandCount(const wchar_t * ObjTypeName);
BOOL WINAPI ExtObjCommandRegisterFunction(const wchar_t * ObjTypeName, DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, wchar_t * CommandNameCn, wchar_t *CommandNameEn, ExtObjectCommandFunction *command);

#ifdef __cplusplus
}
#endif 