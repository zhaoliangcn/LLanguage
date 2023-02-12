#pragma once
#include "../ScriptEngineLib/addin.h"
#include "../ScriptEngineLib/ScpObject.h"

#ifdef __cplusplus
extern "C" {
#endif



DWORD GetObjectCount();
BOOL GetObjectNameId(DWORD dwIndex, char * ObjTypeNameCn, DWORD ObjTypeNameCnSize, char * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId);


DWORD WINAPI GetUniqObjectIdEx(const char * ObjTypeName);
ExtObjCreateFactoryFunction WINAPI GetObjFactoryEx(const char * ObjTypeName);

DWORD WINAPI ExtObjCommandCount(const char * ObjTypeName);
BOOL WINAPI ExtObjCommandRegisterFunction(const char * ObjTypeName,DWORD dwIndex, DWORD *dwObjectId, DWORD* dwCommandId, char * CommandNameCn, char *CommandNameEn, ExtObjectCommandFunction *command);
#ifdef __cplusplus
}
#endif
