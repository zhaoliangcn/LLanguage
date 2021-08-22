/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPOPERATIONMGR
#define _H_SCPOPERATIONMGR
#include "addin.h"
typedef struct _tag_BinaryOperationItem
{
	std::wstring op;
	ScpObjectType obj1Type;
	ScpObjectType obj2Type;
	pBinaryOpertaion BinaryOpertaionFunc;
}BinaryOperationItem,*pBinaryOperationItem;
//���������
//����ʵ��������Ķ�̬ע�ᣬ�Դ�ʵ�������������
class ScpOperationMgr
{
public:
	ScpOperationMgr();
	~ScpOperationMgr();
	static ScpOperationMgr * GetInstance();
	BOOL RegisterBinaryOperation(const wchar_t * op, ScpObjectType obj1Type,ScpObjectType obj2Type,	pBinaryOpertaion BinaryOpertaionFunc);
	pBinaryOpertaion GetBinaryOperation(const wchar_t * op, ScpObjectType obj1Type, ScpObjectType obj2Type);
	std::vector<BinaryOperationItem> BinaryOperations;
};

#endif //_H_SCPOPERATIONMGR