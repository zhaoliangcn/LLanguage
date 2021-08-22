#pragma once
#include "../ScriptEngineLib/addin.h"
#include "../ScriptEngineLib/ScpObject.h"

#ifdef __cplusplus
extern "C" {
#endif



DWORD GetObjectCount();
BOOL GetObjectNameId(DWORD dwIndex, wchar_t * ObjTypeNameCn, DWORD ObjTypeNameCnSize, wchar_t * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId);


DWORD WINAPI GetUniqObjectIdEx(const wchar_t * ObjTypeName);
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const wchar_t * ObjTypeName);

DWORD WINAPI ExtObjCommandCount(const wchar_t * ObjTypeName);
BOOL WINAPI ExtObjCommandRegisterFunction(const wchar_t * ObjTypeName,DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, wchar_t * CommandNameCn, wchar_t *CommandNameEn, ExtObjectCommandFunction *command);
#ifdef __cplusplus
}
#endif
