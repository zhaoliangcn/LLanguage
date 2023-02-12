/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
扩展对象需要实现并导出的接口函数
*/
#ifndef _H_ADDIN
#define _H_ADDIN

#include "ScpObject.h"
#include "ScpObjectSpace.h"
#ifdef WIN32
#include <Windows.h>
#endif

typedef DWORD (__stdcall *pGetUniqObjectId)();
typedef ExtObjCreateFactoryFunction (__stdcall *pGetObjFactory)();

//扩展对象管理器通过该函数获得扩展对象的对象类型ID
typedef DWORD(__stdcall *pGetUniqObjectIdEx)(const char * ObjTypeName);

//扩展对象管理器通过该函数获得扩展对象的工厂函数
typedef ExtObjCreateFactoryFunction (__stdcall *pGetObjFactoryEx)(const char * ObjTypeName);

//扩展对象管理器通过该函数获得该扩展对象支持的命令个数
typedef DWORD(__stdcall * pExtObjCommandCount)(const char * ObjTypeName);

//扩展对象管理器通过该函数实现对扩展对象的动态注册
typedef BOOL (__stdcall * pExtObjCommandRegisterFunction)(const char * ObjTypeName, DWORD dwIndex,DWORD *dwObjectId, DWORD* dwCommandId, char * CommandNameCn, char *CommandNameEn, ExtObjectCommandFunction *command);

//扩展对象管理器通过该函数获得动态库中实现的扩展对象个数
typedef DWORD(__stdcall *pGetObjectCount)();

//扩展对象管理器通过该函数获得动态库中各个扩展对象的名称、类型ID
typedef BOOL(__stdcall *pGetObjectNameId)(DWORD dwIndex, char * ObjTypeNameCn, DWORD ObjTypeNameCnSize, char * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId);

//二元运算符函数原型
typedef ScpObject * (__stdcall *pBinaryOpertaion)(ScpObject * x, ScpObject * y, ScpObjectSpace * objectSpace);

//扩展对象管理器通过该函数获得动态库中重载的二元运算符个数
typedef DWORD(__stdcall *pGetBinaryOperationCount)();

//扩展对象管理器通过该函数实现动态库中二元运算符的动态注册
typedef BOOL(__stdcall *pBinaryOperationRegister)(DWORD dwIndex, char * Operation, DWORD OperationSize, ScpObjectType &obj1Type, ScpObjectType &obj2Type, pBinaryOpertaion * op);

#endif //_H_ADDIN