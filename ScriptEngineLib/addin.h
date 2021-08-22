/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
��չ������Ҫʵ�ֲ������Ľӿں���
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

//��չ���������ͨ���ú��������չ����Ķ�������ID
typedef DWORD(__stdcall *pGetUniqObjectIdEx)(const wchar_t * ObjTypeName);

//��չ���������ͨ���ú��������չ����Ĺ�������
typedef ExtObjCreateFactoryFunction (__stdcall *pGetObjFactoryEx)(const wchar_t * ObjTypeName);

//��չ���������ͨ���ú�����ø���չ����֧�ֵ��������
typedef DWORD(__stdcall * pExtObjCommandCount)(const wchar_t * ObjTypeName);

//��չ���������ͨ���ú���ʵ�ֶ���չ����Ķ�̬ע��
typedef BOOL (__stdcall * pExtObjCommandRegisterFunction)(const wchar_t * ObjTypeName, DWORD dwIndex,DWORD *dwObjectId, DWORD* dwCommandId, wchar_t * CommandNameCn, wchar_t *CommandNameEn, ExtObjectCommandFunction *command);

//��չ���������ͨ���ú�����ö�̬����ʵ�ֵ���չ�������
typedef DWORD(__stdcall *pGetObjectCount)();

//��չ���������ͨ���ú�����ö�̬���и�����չ��������ơ�����ID
typedef BOOL(__stdcall *pGetObjectNameId)(DWORD dwIndex, wchar_t * ObjTypeNameCn, DWORD ObjTypeNameCnSize,wchar_t * ObjTypeNameEn, DWORD ObjTypeNameEnSize, DWORD * dwObjectId);

//��Ԫ���������ԭ��
typedef ScpObject * (__stdcall *pBinaryOpertaion)(ScpObject * x, ScpObject * y, ScpObjectSpace * objectSpace);

//��չ���������ͨ���ú�����ö�̬�������صĶ�Ԫ���������
typedef DWORD(__stdcall *pGetBinaryOperationCount)();

//��չ���������ͨ���ú���ʵ�ֶ�̬���ж�Ԫ������Ķ�̬ע��
typedef BOOL(__stdcall *pBinaryOperationRegister)(DWORD dwIndex, wchar_t * Operation, DWORD OperationSize, ScpObjectType &obj1Type, ScpObjectType &obj2Type, pBinaryOpertaion * op);

#endif //_H_ADDIN