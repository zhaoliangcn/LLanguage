/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//二元运算符管理，用于实现二元运算符的重载
*/
#include "ScpOperationMgr.h"

ScpOperationMgr g_opmgr;

ScpOperationMgr::ScpOperationMgr()
{
}


ScpOperationMgr::~ScpOperationMgr()
{
}
ScpOperationMgr * ScpOperationMgr::GetInstance()
{
	return &g_opmgr;
}
BOOL ScpOperationMgr::RegisterBinaryOperation(const char * op, ScpObjectType obj1Type, ScpObjectType obj2Type, pBinaryOpertaion BinaryOpertaionFunc)
{
	BOOL bRet = FALSE;
	for (int i = 0;i < BinaryOperations.size();i++)
	{
		BinaryOperationItem & item = BinaryOperations.at(i);
		if (item.op == op && item.obj1Type == obj1Type && item.obj2Type == obj2Type)
		{
			return FALSE;
		}
	}
	BinaryOperationItem item;
	item.op = op;
	item.obj1Type = obj1Type;
	item.obj2Type = obj2Type;
	item.BinaryOpertaionFunc = BinaryOpertaionFunc;
	BinaryOperations.push_back(item);
	return TRUE;
}

pBinaryOpertaion ScpOperationMgr::GetBinaryOperation(const char * op, ScpObjectType obj1Type, ScpObjectType obj2Type)
{
	pBinaryOpertaion opFunc = NULL;
	for (int i = 0;i < BinaryOperations.size();i++)
	{
		if (BinaryOperations.at(i).op == op && BinaryOperations.at(i).obj1Type == obj1Type && BinaryOperations.at(i).obj2Type == obj2Type)
		{
			opFunc = BinaryOperations.at(i).BinaryOpertaionFunc;
			break;
		}
	}
	return opFunc;
}
