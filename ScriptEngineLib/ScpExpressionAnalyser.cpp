/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//���ʽ�����������﷨��飬�����﷨��
*/
#include "ScpExpressionAnalyser.h"
#include "ScriptEngine.h"
#include <errno.h>
#include "../Common/commonutil.hpp"
#include "ScpCommonObject.h"
#include "NumberHelp.h"
#include "ScpRuntime.h"
#include "ScpObjectFactory.h"
#include "ScpFunctionObject.h"
#include "ScpIfStatementObject.h"
#include "ScpWhileStatementObject.h"
#include "ScpObjectNammes.h"
#include "commanddefine_uni.h"
ScpExpressionTreeNode::ScpExpressionTreeNode()
{
	LeftChild = NULL ;
	RightChild = NULL;
	nodeobject = NULL;
	objecttype = ObjExpressionNode;
}
ScpExpressionTreeNode::~ScpExpressionTreeNode()
{
	//Destroy();
}
void ScpExpressionTreeNode::Destroy(ScpObjectSpace * currentObjectSpace)
{
	if(LeftChild!=NULL)
	{
		LeftChild->Destroy(currentObjectSpace);
		currentObjectSpace->ReleaseTempObject(LeftChild);
		//currentObjectSpace->EraseObject(LeftChild);
		//LeftChild->DelRef();
		LeftChild = NULL;
	}
	if(RightChild!=NULL) 
	{
		RightChild->Destroy(currentObjectSpace);
		currentObjectSpace->ReleaseTempObject(RightChild);
		//currentObjectSpace->EraseObject(RightChild);
		//RightChild->DelRef();
		RightChild = NULL;
	}
	if (nodeobject != NULL)
	{
		if (nodeobject->istemp)
		{
			if (nodeobject->GetType() == ObjExpressionNode)
			{
				((ScpExpressionTreeNode*)nodeobject)->Destroy(currentObjectSpace);
			}
			currentObjectSpace->ReleaseTempObject(nodeobject);
		}
		nodeobject = NULL;
	}
	Expression.clear();
	while (nodestackobj.size() > 0)
	{
		nodestackobj.pop();
	}
	while (nodestackop.size() > 0)
	{
		nodestackop.pop();
	}
	while (NodeObjectStack.size() > 0)
	{
		NodeObjectStack.pop();
	}
	vtFuncparameters.clear();
	InnerFunctionName.clear();
	ArrayItem.clear();
}
ScpObject * ScpExpressionTreeNode::CalculateEx(CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	if(LeftChild==NULL
		&&RightChild==NULL)
	{
		return CalcStackEx(engine);
	} 
	ScpObject* tempobjLeft = NULL ;
	ScpObject* tempobjRight = NULL ;
	if(LeftChild!=NULL)
	{
		tempobjLeft=(ScpObject*)LeftChild->CalculateEx(engine);
		NodeObjectStack.push(tempobjLeft);
	}
	if (RightChild != NULL)
	{
		tempobjRight = (ScpObject*)RightChild->CalculateEx(engine);
		NodeObjectStack.push(tempobjRight);
	}
	ScpObject* retobj=CalcStackEx(engine);		
	return retobj;
}


ScpObject * ScpExpressionTreeNode::CalcStackEx(CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	//�����������ֽ���
	ScpObject * numvalue=NULL;
	if(nodestackop.size()==1)
	{
		std::wstring op = nodestackop.top();
		//nodestackop.pop();
		ScpObject* tempobjLeft = NULL ;
		ScpObject* tempobjRight = NULL ;
		//������������
		if(NodeObjectStack.size()==1)
		{
			tempobjLeft=NodeObjectStack.top();
			NodeObjectStack.pop();
			if(tempobjLeft)
			{				
				ScpObjectType type1 =tempobjLeft->GetType();
				if (op==scpOperationSubtraction)
				{					
					numvalue = Minus(tempobjLeft, engine);
				}
				else if (op==scpOperationNot)
				{
					//�߼���
					numvalue = Not(tempobjLeft, engine);
				}
				else if (op==scpOperationBitNot)
				{
					//��λ��
					numvalue = BitNot(tempobjLeft, engine);
				}
				else if (op == scpOperationSelfAdd)
				{
					//����
					numvalue = PostSelfAdd(tempobjLeft, engine);
				}
				else if (op == scpOperationSelfSub)
				{
					//�Լ�
					numvalue = PostSelfSub(tempobjLeft, engine);
				}

			}
		}
		if(NodeObjectStack.size()>=2)
		{			
			tempobjRight=NodeObjectStack.top();
			NodeObjectStack.pop();
			tempobjLeft=NodeObjectStack.top();
			NodeObjectStack.pop();			
			if(tempobjRight && tempobjLeft)
			{
				ScpObjectType type1 = tempobjLeft->GetType();
				ScpObjectType type2 = tempobjRight->GetType();
				//NULL �����ܲ����κ�����
				//�����ڶ�NULL������в���ʱ����ת��Ϊ��һ�������Ķ�������
				if (type1 == ObjNull && type2 == ObjInt)
				{
					ScpArrayObject * arrayobj = (ScpArrayObject *)((ScpNullObject*)tempobjLeft)->parentObj;
					if (arrayobj)
					{
						ScpIntObject * intobj = (ScpIntObject *)BaseObjectFactory(ObjInt);
						arrayobj->ReplaceElementObj(tempobjLeft, (ScpObject *)intobj);
						tempobjLeft = intobj;
						type1 = tempobjLeft->GetType();
					}
				}
				if (type1 == ObjNull && type2 == ObjString)
				{
					ScpArrayObject * arrayobj = (ScpArrayObject *)((ScpNullObject*)tempobjLeft)->parentObj;
					if (arrayobj)
					{
						ScpStringObject * strobj = (ScpStringObject*)BaseObjectFactory(ObjString);
						arrayobj->ReplaceElementObj(tempobjLeft, (ScpObject *)strobj);
						tempobjLeft = strobj;
						type1 = tempobjLeft->GetType();
					}
				}
				if (op == scpOperationAssign)
				{
					//���ʽ����������
					//����һ������ͬʱҲ�Ƿ���ֵ����������ʱ����
					numvalue = Assign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationAddAndAssign)
				{
					numvalue = AddAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationSubAndAssign)
				{
					numvalue = SubAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				if (op == scpOperationMulAndAssign)
				{
					numvalue = MulAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationDivAndAssign)
				{
					numvalue = DivAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOpeartionModAndAssign)
				{
					numvalue = ModAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationBitAndAndAssign)
				{
					numvalue = BitAndAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationBitOrAndAssign)
				{
					numvalue = BitOrAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationBitNotAndAssign)
				{
					numvalue = BitNotAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOperationBitXorAndAssign)
				{
					numvalue = BitXorAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOpeartionBitShiftLeftAndAssign)
				{
					numvalue = BitShiftLeftAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else if (op == scpOpeartionBitShiftRightAndAssign)
				{
					numvalue = BitShiftRightAndAssign(tempobjLeft, tempobjRight, engine);
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
				}
				else
				{
					//���ʽ������������
					//������������ʱ���󣬷���ֵ��Ӧ����ʱ����
					if (op == scpOperationEqual)
					{
						numvalue = Equal(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationNotEqual)
					{
						numvalue = NotEqual(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationAdd)
					{
						numvalue = Add(tempobjLeft, tempobjRight, engine);

					}
					else if (op == scpOperationSubtraction)
					{
						numvalue = Sub(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationMultiplication)
					{
						numvalue = Mul(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationDivision)
					{
						numvalue = Div(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationMod)
					{
						numvalue = Mod(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationLessthan)
					{
						numvalue = Lessthan(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationLessorEqual)
					{
						numvalue = LessorEqual(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBigthan)
					{
						numvalue = Bigthan(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBigorEqual)
					{
						numvalue = BigorEqual(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitAnd)
					{
						numvalue = BitAnd(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitOr)
					{
						numvalue = BitOr(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitXor)
					{
						numvalue = BitXor(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationLogicalAnd)
					{
						numvalue = LogicalAnd(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationLogicalOr)
					{
						numvalue = LogicalOr(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitShiftLeft)
					{
						numvalue = BitShiftLeft(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitShiftRight)
					{
						numvalue = BitShiftRight(tempobjLeft, tempobjRight, engine);
					}
					//������ʱ����
					if (tempobjRight->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjRight);
					}
					if (tempobjLeft->istemp)
					{
						objectSpace->ReleaseTempObject(tempobjLeft);
					}
				}
			}
		}
	}
	else
	{
		if (nodeobject)
		{
			if(nodeobject->GetType()==ObjExpressionNode)
			{			
				numvalue = ((ScpExpressionTreeNode*)nodeobject)->CalculateEx(engine);	
				if(!InnerFunctionName.empty())
				{
					//ע��:������޸Ĳ���ȷ��
					if(numvalue)
					//numvalue = numvalue->CallInnerFunction(InnerFunctionName,&((ScpExpressionTreeNode*)nodeobject)->vtFuncparameters,engine);
					numvalue = numvalue->CallInnerFunction(InnerFunctionName, &vtFuncparameters, engine);
				}
			}
			else
			{			
				if (!ArrayItem.empty())
				{
					numvalue = DoArrayItemRef(engine);
				}
				else
				{
					numvalue = PerformFunctionCall(engine);
				}
							
			}
		}

	}
	return numvalue;

}
ScpObject * ScpExpressionTreeNode::MakeByteCode(CScriptEngine * engine, ByteCodeMemoryStream & memstream)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	if (LeftChild == NULL
		&& RightChild == NULL)
	{
		return MakeByteCodeStack(engine, memstream);
	}
	ScpObject* tempobjLeft = NULL;
	ScpObject* tempobjRight = NULL;
	if (LeftChild != NULL)
	{
		tempobjLeft = (ScpObject*)LeftChild->MakeByteCode(engine, memstream);
		NodeObjectStack.push(tempobjLeft);
	}
	if (RightChild != NULL)
	{
		tempobjRight = (ScpObject*)RightChild->MakeByteCode(engine, memstream);
		NodeObjectStack.push(tempobjRight);
	}
	return  MakeByteCodeStack(engine, memstream);

}
ScpObject * ScpExpressionTreeNode::MakeByteCodeStack(CScriptEngine * engine, ByteCodeMemoryStream & memstream)
{
	ULONG resultresid;
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	//�����������ֽ���
	ScpObject * numvalue = NULL;
	if (nodestackop.size() == 1)
	{
		std::wstring op = nodestackop.top();
		//nodestackop.pop();
		ScpObject* tempobjLeft = NULL;
		ScpObject* tempobjRight = NULL;
		if (NodeObjectStack.size() == 1)
		{
			tempobjLeft = NodeObjectStack.top();
			NodeObjectStack.pop();
			if (tempobjLeft)
			{
				ScpObjectType type1 = tempobjLeft->GetType();
				if (op == scpOperationSubtraction)
				{
					numvalue = Minus(tempobjLeft, engine);
				}
				else if (op == scpOperationNot)
				{
					numvalue = Not(tempobjLeft, engine);
				}
				else if (op == scpOperationBitNot)
				{
					numvalue = BitNot(tempobjLeft, engine);
				}
				else if (op == scpOperationSelfAdd)
				{
					numvalue = PostSelfAdd(tempobjLeft, engine);
				}
				else if (op == scpOperationSelfSub)
				{
					numvalue = PostSelfSub(tempobjLeft, engine);
				}
				std::wstring name = objectSpace->GetObjectNameR(tempobjLeft);
				if (!name.empty())
				{
					ULONG idleft = engine->bytecode.resourcepool->scpFindResource(name);
					ByteCodeMemoryStream stream;
					engine->bytecode.GenByteCodeUnaryOp(op, idleft, stream);
					memstream.AppendByteCode(&stream);
				}
			}
		}
		if (NodeObjectStack.size() >= 2)
		{
			tempobjRight = NodeObjectStack.top();
			NodeObjectStack.pop();
			tempobjLeft = NodeObjectStack.top();
			NodeObjectStack.pop();
			if (tempobjRight && tempobjLeft)
			{

				std::wstring name = objectSpace->GetObjectNameR(tempobjLeft);		
				ULONG idleft = engine->bytecode.resourcepool->scpFindResource(name);
				if (name.empty())
				{
					if (tempobjLeft->GetType() == ObjInt)
					{						
						if (((ScpIntObject*)tempobjLeft)->value == 0)
						{
							idleft = residzero;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 1)
						{
							idleft = residone;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 2)
						{
							idleft = residtwo;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 3)
						{
							idleft = residthree;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 4)
						{
							idleft = residfour;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 5)
						{
							idleft = residfive;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 6)
						{
							idleft = residsix;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 7)
						{
							idleft = residseven;
						}
						else if (((ScpIntObject*)tempobjLeft)->value == 8)
						{
							idleft = resideight;
						}
						else if (((ScpIntObject*)tempobjLeft)->value ==9)
						{
							idleft = residnine;
						}
						else
						{
							std::wstring lname = L"tempint";
							lname += IntToWString(((ScpIntObject*)tempobjLeft)->value);
							idleft = engine->bytecode.resourcepool->AppendResource(lname);
							ByteCodeMemoryStream stream;
							engine->bytecode.GetByteCodeInitRes(lname, stream, idleft);
							engine->bytecode.bytecodemem->AppendByteCode(&stream);
							stream.Release();

							VTPARAMETERS param;
							param.push_back(L"int");
							param.push_back(lname);
							param.push_back(IntToWString(((ScpIntObject*)tempobjLeft)->value));
							engine->bytecode.GenByteCodeObjectDefine(tempobjLeft->GetType(), param, stream);
							engine->bytecode.bytecodemem->AppendByteCode(&stream);
							stream.Release();
						}
					}
				}
				
				if (idleft == -1)
				{
					idleft = engine->bytecode.resourcepool->AppendResource(name);
					ByteCodeMemoryStream stream;
					engine->bytecode.GetByteCodeInitRes(name, stream, idleft);
					engine->bytecode.bytecodemem->AppendByteCode(&stream);
					stream.Release();

					VTPARAMETERS param;
					param.push_back(L"int");
					param.push_back(name);
					engine->bytecode.GenByteCodeObjectDefine(tempobjLeft->GetType(), param, stream);
					engine->bytecode.bytecodemem->AppendByteCode(&stream);
					stream.Release();
				}
				name = objectSpace->GetObjectNameR(tempobjRight);				
				ULONG idright = 0;
				if (name.empty())
				{
					idright = GenTempObjectByteCode(tempobjRight, name, engine,false);					
				}
				else
				{
					idright = engine->bytecode.resourcepool->scpFindResource(name);
					if (idright == -1)
					{
						idright = engine->bytecode.resourcepool->AppendResource(name);
						ByteCodeMemoryStream stream;
						engine->bytecode.GetByteCodeInitRes(name, stream, idright);
						engine->bytecode.bytecodemem->AppendByteCode(&stream);
						stream.Release();

						VTPARAMETERS param;
						param.push_back(L"int");
						param.push_back(name);
						engine->bytecode.GenByteCodeObjectDefine(tempobjRight->GetType(), param, stream);
						engine->bytecode.bytecodemem->AppendByteCode(&stream);
						stream.Release();
					}
				}

				ScpObjectType type1 = tempobjLeft->GetType();
				ScpObjectType type2 = tempobjRight->GetType();
				//NULL �����ܲ����κ�����
				//�����ڶ�NULL������в���ʱ����ת��Ϊ��һ�������Ķ�������
				if (type1 == ObjNull && type2 == ObjInt)
				{
					ScpArrayObject * arrayobj = (ScpArrayObject *)((ScpNullObject*)tempobjLeft)->parentObj;
					if (arrayobj)
					{
						ScpIntObject * intobj = (ScpIntObject *)BaseObjectFactory(ObjInt);
						arrayobj->ReplaceElementObj(tempobjLeft, (ScpObject *)intobj);
						tempobjLeft = intobj;
						type1 = tempobjLeft->GetType();
					}
				}
				if (type1 == ObjNull && type2 == ObjString)
				{
					ScpArrayObject * arrayobj = (ScpArrayObject *)((ScpNullObject*)tempobjLeft)->parentObj;
					if (arrayobj)
					{
						ScpStringObject * strobj = (ScpStringObject*)BaseObjectFactory(ObjString);
						arrayobj->ReplaceElementObj(tempobjLeft, (ScpObject *)strobj);
						tempobjLeft = strobj;
						type1 = tempobjLeft->GetType();
					}
				}
				if (op == scpOperationAssign||
					op == scpOperationAddAndAssign||
					op == scpOperationSubAndAssign ||
					op == scpOperationMulAndAssign ||
					op == scpOperationDivAndAssign ||
					op == scpOpeartionModAndAssign ||
					op == scpOperationBitAndAndAssign ||
					op == scpOperationBitOrAndAssign ||
					op == scpOperationBitNotAndAssign ||
					op == scpOperationBitXorAndAssign ||
					op == scpOpeartionBitShiftLeftAndAssign ||
					op == scpOpeartionBitShiftRightAndAssign)
				{
					//���ʽ����������
					//����һ������ͬʱҲ�Ƿ���ֵ����������ʱ����

										
					ByteCodeMemoryStream stream;
					engine->bytecode.GetByteCodeBinaryOp(op, -1, idleft, idright, stream);
					memstream.AppendByteCode(&stream);
					//if (engine->GetCurrentObjectSpace()->ObjectSpaceType == Space_Global)
					//	engine->bytecode.bytecodemem->AppendByteCode(&stream);
					//else
					//	memstream.AppendByteCode(&stream);
					stream.Release();
					resultresid = idleft;
					if (op == scpOperationAssign)
					{
						numvalue = Assign(tempobjLeft, tempobjRight, engine);
					}					
					else if (op == scpOperationAddAndAssign)
					{
						numvalue = AddAndAssign(tempobjLeft, tempobjRight, engine);						
					}
					else if (op == scpOperationSubAndAssign)
					{
						numvalue = SubAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationMulAndAssign)
					{
						numvalue = MulAndAssign(tempobjLeft, tempobjRight, engine);						
					}
					else if (op == scpOperationDivAndAssign)
					{
						numvalue = DivAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOpeartionModAndAssign)
					{
						numvalue = ModAndAssign(tempobjLeft, tempobjRight, engine);						
					}
					else if (op == scpOperationBitAndAndAssign)
					{
						numvalue = BitAndAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitOrAndAssign)
					{
						numvalue = BitOrAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitNotAndAssign)
					{
						numvalue = BitNotAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOperationBitXorAndAssign)
					{
						numvalue = BitXorAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOpeartionBitShiftLeftAndAssign)
					{
						numvalue = BitShiftLeftAndAssign(tempobjLeft, tempobjRight, engine);
					}
					else if (op == scpOpeartionBitShiftRightAndAssign)
					{
						numvalue = BitShiftRightAndAssign(tempobjLeft, tempobjRight, engine);
					}
					//if (tempobjRight->istemp)
					//{
					//	objectSpace->ReleaseTempObject(tempobjRight);
					//}
				}			
				else
				{
					//���ʽ������������
					//������������ʱ���󣬷���ֵ��Ӧ����ʱ����
					
					
					if (op == scpOperationAdd||
						op == scpOperationSubtraction||
						op == scpOperationMultiplication||
						op == scpOperationDivision||
						op == scpOperationMod||
						op == scpOperationLessthan ||
						op == scpOperationLessorEqual||
						op == scpOperationBigthan ||
						op == scpOperationBigorEqual||
						op == scpOperationEqual||
						op == scpOperationNotEqual||						
						op == scpOperationBitAnd||
						op == scpOperationBitOr||
						op == scpOperationBitXor ||
						op == scpOperationLogicalAnd||
						op == scpOperationLogicalOr||
						op == scpOperationBitShiftLeft||
						op == scpOperationBitShiftRight)
					{						
						if (op == scpOperationAdd)
						{
							numvalue = Add(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationLessthan)
						{
							numvalue = Lessthan(tempobjLeft, tempobjRight, engine);
						}						
						else if (op == scpOperationLessorEqual)
						{
							numvalue = LessorEqual(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBigthan)
						{
							numvalue = Bigthan(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBigorEqual)
						{
							numvalue = BigorEqual(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationEqual)
						{
							numvalue = Equal(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationNotEqual)
						{
							numvalue = NotEqual(tempobjLeft, tempobjRight, engine);
						}
						if (op == scpOperationSubtraction)
						{
							numvalue = Sub(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationMultiplication)
						{
							numvalue = Mul(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationDivision)
						{
							numvalue = Div(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationMod)
						{
							numvalue = Mod(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBitAnd)
						{
							numvalue = BitAnd(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBitOr)
						{
							numvalue = BitOr(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBitXor)
						{
							numvalue = BitXor(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationLogicalAnd)
						{
							numvalue = LogicalAnd(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationLogicalOr)
						{
							numvalue = LogicalOr(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBitShiftLeft)
						{
							numvalue = BitShiftLeft(tempobjLeft, tempobjRight, engine);
						}
						else if (op == scpOperationBitShiftRight)
						{
							numvalue = BitShiftRight(tempobjLeft, tempobjRight, engine);
						}
						std::wstring name;
						ULONG idret =GenTempObjectByteCode(numvalue, name, engine,true);

						ByteCodeMemoryStream stream;
						engine->bytecode.GetByteCodeBinaryOp(op, idret, idleft, idright, stream);
						if (engine->GetCurrentObjectSpace()->ObjectSpaceType == Space_Global)
							engine->bytecode.bytecodemem->AppendByteCode(&stream);
						else
							memstream.AppendByteCode(&stream);
						stream.Release();						
					}			
					
					//������ʱ����
					//if (tempobjRight->istemp)
					//{
					//	objectSpace->ReleaseTempObject(tempobjRight);
					//}
					//if (tempobjLeft->istemp)
					//{
					//	objectSpace->ReleaseTempObject(tempobjLeft);
					//}
				}
			}
		}
	}
	else
	{
		if (nodeobject)
		{
			if (nodeobject->GetType() == ObjExpressionNode)
			{
				numvalue = ((ScpExpressionTreeNode*)nodeobject)->MakeByteCode(engine, memstream);
				if (!InnerFunctionName.empty())
				{
					if (numvalue)
					{
						for (int i = 0;i <vtFuncparameters.size();i++)
						{
							ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
							if (obj && obj->GetType() == ObjExpressionNode)
							{
								ScpObject * objret = ((ScpExpressionTreeNode*)obj)->CalculateEx(engine);
								objectSpace->EraseObject(vtFuncparameters.at(i));
								objectSpace->AddObject(vtFuncparameters.at(i), objret);
							}
						}
						std::wstring name = objectSpace->GetObjectNameR(numvalue);
						if (name.empty())
						{
							GenTempObjectByteCode(numvalue, name, engine,false);
						}
						

						ByteCodeMemoryStream stream;
						engine->bytecode.GenByteCodeCallInner(name, InnerFunctionName, vtFuncparameters, stream);
						memstream.AppendByteCode(&stream);
						stream.Release();

						//numvalue = ((ScpExpressionTreeNode*)nodeobject)->MakeByteCodePerformFunctionCall(engine, memstream);
						numvalue = numvalue->CallInnerFunction(InnerFunctionName, &((ScpExpressionTreeNode*)nodeobject)->vtFuncparameters, engine);
					
					}
				}
			}
			else
			{
				if (!ArrayItem.empty())
				{
					numvalue = DoArrayItemRef(engine);
				}
				else
				{
					numvalue = MakeByteCodePerformFunctionCall(engine, memstream);
				}

			}
		}

	}
	return numvalue;
}
ScpObject * ScpExpressionTreeNode::MakeByteCodePerformFunctionCall(CScriptEngine * engine, ByteCodeMemoryStream & memstream)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * retobj = NULL;
	if (nodeobject)
	{
		if (!InnerFunctionName.empty())
		{
			for (int i = 0;i < vtFuncparameters.size();i++)
			{
				ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
				if (obj && obj->GetType() == ObjExpressionNode)
				{
					ScpObject * objret = ((ScpExpressionTreeNode*)obj)->CalculateEx(engine);
					objectSpace->EraseObject(vtFuncparameters.at(i));
					objectSpace->AddObject(vtFuncparameters.at(i), objret);
				}
			}

			std::wstring objname = objectSpace->GetObjectNameR(nodeobject);

			ULONG idobject = engine->bytecode.resourcepool->scpFindResource(objname);
			if (idobject == -1)
			{
				idobject = engine->bytecode.resourcepool->AppendResource(objname);
				ByteCodeMemoryStream stream;
				engine->bytecode.GetByteCodeInitRes(objname, stream, idobject);
				engine->bytecode.bytecodemem->AppendByteCode(&stream);
				stream.Release();
				std::wstring type_name = L"int";
				type_name = ScpGlobalObject::GetInstance()->GetTypeName(objectSpace->GetType(objname));

				VTPARAMETERS param;
				param.push_back(type_name);
				param.push_back(objname);
				if (objectSpace->GetType(objname) == ObjString)
				{
					param.push_back(((ScpStringObject*)objectSpace->FindObject(objname))->content);
				}
				else
				{
					param.push_back(objectSpace->FindObject(objname)->ToString());
				}
				engine->bytecode.GenByteCodeObjectDefine(nodeobject->GetType(), param, stream);
				engine->bytecode.bytecodemem->AppendByteCode(&stream);
				stream.Release();
			}
			ULONG idfunc = engine->bytecode.resourcepool->scpFindResource(InnerFunctionName);
			if (idfunc == -1)
			{
				idfunc = engine->bytecode.resourcepool->AppendResource(InnerFunctionName);
				ByteCodeMemoryStream stream;
				engine->bytecode.GetByteCodeInitRes(InnerFunctionName, stream, idfunc);
				engine->bytecode.bytecodemem->AppendByteCode(&stream);
				stream.Release();

			}

			//������ĳ�Ա����
			//�����ֽ��뻹û������
			//��Ķ����Ѿ����ɣ������ֽ��벻�ɲ��뵽��Ķ�����
			//����Ҫ�ŵ�ȫ�ֿռ�
			
			if (nodeobject->GetType() == ObjClass || nodeobject->GetType() == ObjClassInstance)
			{
				//((ScpClassObject*)nodeobject)->UserClassObjectSpace.parentspace;
				//((ScpClassObject*)nodeobject)->UserClassObjectSpace.parentspace = engine->GetCurrentObjectSpace();
				ScpFunctionObject * func = (ScpFunctionObject *)((ScpClassObject*)nodeobject)->FindMemberVariable(InnerFunctionName);
				ScpObjectSpace* oldparent = NULL;
				if (func)
				{
					oldparent = func->FunctionObjectSpace->parentspace->parentspace;
					func->FunctionObjectSpace->parentspace->parentspace = engine->GetCurrentObjectSpace();;

					if (vtFuncparameters.size() >= 0)
					{

						engine->SetCurrentObjectSpace(func->FunctionObjectSpace);
						func->RealParameters.clear();
						if (func->RealParameters.size() == 0)
						{
							for (ULONG i = 0;i < vtFuncparameters.size();i++)
							{
								ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
								if (obj)
								{
									func->RealParameters.push_back(vtFuncparameters.at(i));
								}
								else
								{
									//������Ҫ���Ǻ����Ĳ����Ǳ��ʽ�����
									std::wstring Expression = vtFuncparameters.at(i);
									ULONG residexp = engine->bytecode.resourcepool->scpFindResource(Expression);
									ULONG residname;
									if (residexp == -1)
									{
										ByteCodeMemoryStream stream;
										VTPARAMETERS param;
										if (IsStaticNumber(Expression))
										{
											std::wstring name = L"tempint";
											residname = engine->bytecode.resourcepool->scpFindResource(name);
											while (residname != -1)
											{
												name += L"0";
												residname = engine->bytecode.resourcepool->scpFindResource(name);
											}
											residname = engine->bytecode.resourcepool->AppendResource(name);

											engine->bytecode.GetByteCodeInitRes(name, stream, residname);
											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();

											param.push_back(L"int");
											param.push_back(name);
											param.push_back(Expression);
											engine->bytecode.GenByteCodeObjectDefine(ObjInt, param, stream);

											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();
											
											ScpObject * tempobj = new ScpIntObject;
											tempobj->istemp = true;
											((ScpIntObject*)tempobj)->value = StringToInt(Expression);
											objectSpace->AddObject(name, tempobj);
											vtFuncparameters.at(i) = name;
											func->RealParameters.push_back(name);
										}
										else if (IsStaticString(Expression))
										{
											std::wstring name = L"tempstring";
											residname = engine->bytecode.resourcepool->scpFindResource(name);
											while (residname != -1)
											{
												name += L"0";
												residname = engine->bytecode.resourcepool->scpFindResource(name);
											}
											residname = engine->bytecode.resourcepool->AppendResource(name);

											engine->bytecode.GetByteCodeInitRes(name, stream, residname);
											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();

											param.push_back(L"string");
											param.push_back(name);
											param.push_back(Expression);
											engine->bytecode.GenByteCodeObjectDefine(ObjString, param, stream);

											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();
											ScpObject * tempobj = new ScpStringObject;
											tempobj->istemp = true;
											((ScpStringObject*)tempobj)->content = Expression;
											objectSpace->AddObject(name, tempobj);
											vtFuncparameters.at(i) = name;
											func->RealParameters.push_back(name);
										}

									}
									else
									{
										ByteCodeMemoryStream stream;
										VTPARAMETERS param;
										if (Expression == L"0")
										{
											std::wstring numname = L"gl_";
											numname += L"zero";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{												
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj0 = new ScpIntObject();
												obj0->value = 0;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj0);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"1")
										{
											std::wstring numname = L"gl_";
											numname += L"one";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj1 = new ScpIntObject();
												obj1->value = 1;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj1);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"2")
										{
											std::wstring numname = L"gl_";
											numname += L"two";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj2 = new ScpIntObject();
												obj2->value = 2;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj2);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"3")
										{
											std::wstring numname = L"gl_";
											numname += L"three";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj3 = new ScpIntObject();
												obj3->value = 3;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj3);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"4")
										{
											std::wstring numname = L"gl_";
											numname += L"four";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj4 = new ScpIntObject();
												obj4->value = 4;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj4);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"5")
										{
											std::wstring numname = L"gl_";
											numname += L"five";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj5 = new ScpIntObject();
												obj5->value = 5;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj5);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"6")
										{
											std::wstring numname = L"gl_";
											numname += L"six";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj6 = new ScpIntObject();
												obj6->value = 6;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj6);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"7")
										{
											std::wstring numname = L"gl_";
											numname += L"seven";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj7 = new ScpIntObject();
												obj7->value = 7;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj7);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"8")
										{
											std::wstring numname = L"gl_";
											numname += L"eight";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj8 = new ScpIntObject();
												obj8->value = 8;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj8);
												func->RealParameters.push_back(numname);
											}
										}
										else if (Expression == L"9")
										{
											std::wstring numname = L"gl_";
											numname += L"nine";
											if (engine->GetCurrentObjectSpace()->FindObject(numname))
											{
												func->RealParameters.push_back(numname);
											}
											else
											{
												residname = engine->bytecode.resourcepool->scpFindResource(numname);
												if (residname == -1)
												{
													residname = engine->bytecode.resourcepool->AppendResource(numname);
												}
												engine->bytecode.GetByteCodeInitRes(numname, stream, residname);
												engine->bytecode.bytecodemem->AppendByteCode(&stream);
												stream.Release();

												ScpIntObject * obj9 = new ScpIntObject();
												obj9->value = 9;
												engine->GetCurrentObjectSpace()->AddObject(numname, obj9);
												func->RealParameters.push_back(numname);
											}
										}										
										else if (IsStaticNumber(Expression))
										{
											std::wstring name = L"tempint";
											residname = engine->bytecode.resourcepool->scpFindResource(name);
											while (residname != -1)
											{
												name += L"0";
												residname = engine->bytecode.resourcepool->scpFindResource(name);
											}
											residname = engine->bytecode.resourcepool->AppendResource(name);

											engine->bytecode.GetByteCodeInitRes(name, stream, residname);
											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();

											param.push_back(L"int");
											param.push_back(name);
											param.push_back(Expression);
											engine->bytecode.GenByteCodeObjectDefine(ObjInt, param, stream);

											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();
											func->RealParameters.push_back(name);
										}
										else if (IsStaticString(Expression))
										{
											std::wstring name = L"tempstring";
											residname = engine->bytecode.resourcepool->scpFindResource(name);
											while (residname != -1)
											{
												name += L"0";
												residname = engine->bytecode.resourcepool->scpFindResource(name);
											}
											residname = engine->bytecode.resourcepool->AppendResource(name);

											engine->bytecode.GetByteCodeInitRes(name, stream, residname);
											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();

											param.push_back(L"string");
											param.push_back(name);
											param.push_back(Expression);
											engine->bytecode.GenByteCodeObjectDefine(ObjString, param, stream);

											engine->bytecode.bytecodemem->AppendByteCode(&stream);
											stream.Release();
											func->RealParameters.push_back(name);
										}
									}
									//func->RealParameters.push_back(vtFuncparameters.at(i));
									//engine->PrintError(scpErrorInvalidFunctionParameter);
								}
							}
						}
						if (func->BindParameters(engine) != -1)
						{
							std::wstring objname = objectSpace->GetObjectNameR(nodeobject);

							VTPARAMETERS param;
							for (int i = 0;i < func->RealParameters.size();i++)
							{
								param.push_back(func->RealParameters.at(i));
							}
							if (func->bytecodemem_funcbody.codelength == 0)
							{

								ByteCodeMemoryStream stream;
								func->functionexpressionblock->GenByteCode(engine, stream);
								engine->bytecode.GenByteCodeFunctionBody(stream);
								func->bytecodemem_funcbody.AppendByteCode(&stream);
								engine->bytecode.bytecodemem->AppendByteCode(&func->bytecodemem_funcdef);
								engine->bytecode.bytecodemem->AppendByteCode(&func->bytecodemem_funcbody);

							}
						}
						engine->SetCurrentObjectSpace(objectSpace);
						if (func)
							func->FunctionObjectSpace->parentspace->parentspace = oldparent;
						//((ScpClassObject*)nodeobject)->UserClassObjectSpace.parentspace = oldparent;
					}
				}
				else
				{
					//�����û�����ĳ�Ա�������������ú���
					if (vtFuncparameters.size() > 0)
					{
						for (ULONG i = 0;i < vtFuncparameters.size();i++)
						{
							ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
							if (!obj)
							{
								//������Ҫ���Ǻ����Ĳ����Ǳ��ʽ�����
								std::wstring Expression = vtFuncparameters.at(i);
								ULONG residexp = engine->bytecode.resourcepool->scpFindResource(Expression);
								ULONG residname;
								if (residexp == -1)
								{
									ByteCodeMemoryStream stream;
									VTPARAMETERS param;
									if (IsStaticNumber(Expression))
									{
										std::wstring name = L"tempint";
										residname = engine->bytecode.resourcepool->scpFindResource(name);
										while (residname != -1)
										{
											name += L"0";
											residname = engine->bytecode.resourcepool->scpFindResource(name);
										}
										residname = engine->bytecode.resourcepool->AppendResource(name);

										engine->bytecode.GetByteCodeInitRes(name, stream, residname);
										engine->bytecode.bytecodemem->AppendByteCode(&stream);
										stream.Release();

										param.push_back(L"int");
										param.push_back(name);
										param.push_back(Expression);
										engine->bytecode.GenByteCodeObjectDefine(ObjInt, param, stream);

										engine->bytecode.bytecodemem->AppendByteCode(&stream);
										stream.Release();
									}
									else if (IsStaticString(Expression))
									{
										std::wstring name = L"tempstring";
										residname = engine->bytecode.resourcepool->scpFindResource(name);
										while (residname != -1)
										{
											name += L"0";
											residname = engine->bytecode.resourcepool->scpFindResource(name);
										}
										residname = engine->bytecode.resourcepool->AppendResource(name);

										engine->bytecode.GetByteCodeInitRes(name, stream, residname);
										engine->bytecode.bytecodemem->AppendByteCode(&stream);
										stream.Release();

										param.push_back(L"string");
										param.push_back(name);
										param.push_back(Expression);
										engine->bytecode.GenByteCodeObjectDefine(ObjString, param, stream);

										engine->bytecode.bytecodemem->AppendByteCode(&stream);
										stream.Release();
									}

								}
							}
						}
					}
				}
				
			}
			else
			{
				if (vtFuncparameters.size() > 0)
				{
					for (ULONG i = 0;i < vtFuncparameters.size();i++)
					{
						ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
						if (!obj)
						{
							//������Ҫ���Ǻ����Ĳ����Ǳ��ʽ�����
							std::wstring Expression = vtFuncparameters.at(i);
							ULONG residexp = engine->bytecode.resourcepool->scpFindResource(Expression);
							ULONG residname;
							if (residexp == -1)
							{
								ByteCodeMemoryStream stream;
								VTPARAMETERS param;
								if (IsStaticNumber(Expression))
								{
									std::wstring name = L"tempint";
									residname = engine->bytecode.resourcepool->scpFindResource(name);
									while (residname != -1)
									{
										name += L"0";
										residname = engine->bytecode.resourcepool->scpFindResource(name);
									}
									residname = engine->bytecode.resourcepool->AppendResource(name);

									engine->bytecode.GetByteCodeInitRes(name, stream, residname);
									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();

									param.push_back(L"int");
									param.push_back(name);
									param.push_back(Expression);
									engine->bytecode.GenByteCodeObjectDefine(ObjInt, param, stream);
									vtFuncparameters.at(i) = name;
									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();
								}
								else if (IsStaticString(Expression))
								{
									std::wstring name = L"tempstring";
									residname = engine->bytecode.resourcepool->scpFindResource(name);
									while (residname != -1)
									{
										name += L"0";
										residname = engine->bytecode.resourcepool->scpFindResource(name);
									}
									residname = engine->bytecode.resourcepool->AppendResource(name);

									engine->bytecode.GetByteCodeInitRes(name, stream, residname);
									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();

									param.push_back(L"string");
									param.push_back(name);
									param.push_back(Expression);
									engine->bytecode.GenByteCodeObjectDefine(ObjString, param, stream);
									vtFuncparameters.at(i) = name;
									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();
								}

							}
						}
					}					
				}
			}
			ByteCodeMemoryStream stream;
			engine->bytecode.GenByteCodeCallInner(objname, InnerFunctionName, vtFuncparameters, stream);
			memstream.AppendByteCode(&stream);
			stream.Release();
			retobj = nodeobject->CallInnerFunction(InnerFunctionName, &vtFuncparameters, engine);
		}
		else if (nodeobject->GetType() == ObjFunction)
		{
			if (vtFuncparameters.size() > 0)
			{				
				ScpFunctionObject * func = (ScpFunctionObject*)nodeobject;

				
				engine->SetCurrentObjectSpace(func->FunctionObjectSpace);
				func->RealParameters.clear();
				if (func->RealParameters.size() == 0)
				{
					for (ULONG i = 1;i < vtFuncparameters.size();i++)
					{
						ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
						if (obj)
						{
							func->RealParameters.push_back(vtFuncparameters.at(i));
						}
						else
						{

							//������Ҫ���Ǻ����Ĳ����Ǳ��ʽ�����
							std::wstring Expression = vtFuncparameters.at(i);
							ULONG residexp = engine->bytecode.resourcepool->scpFindResource(vtFuncparameters.at(i));
							ULONG residname;
							if (residexp == -1)
							{
								ByteCodeMemoryStream stream;
								VTPARAMETERS param;
								if (IsStaticNumber(Expression))
								{
									std::wstring name = L"tempint";
									residname = engine->bytecode.resourcepool->scpFindResource(name);
									while (residname != -1)
									{
										name += L"0";
										residname = engine->bytecode.resourcepool->scpFindResource(name);
									}
									residname = engine->bytecode.resourcepool->AppendResource(name);

									engine->bytecode.GetByteCodeInitRes(name, stream, residname);
									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();

									param.push_back(L"int");
									param.push_back(name);
									param.push_back(Expression);
									engine->bytecode.GenByteCodeObjectDefine(ObjInt, param, stream);

									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();
									func->RealParameters.push_back(name);

									ScpIntObject * intobj = new  ScpIntObject;
									intobj->value = StringToInt(Expression);
									ScpObjectSpace * globalObjectSpace = engine->GetCurrentObjectSpace();
									while (globalObjectSpace->parentspace != NULL)
									{
										globalObjectSpace = globalObjectSpace->parentspace;
									}
									globalObjectSpace->AddObject(name, intobj);
								}
								else if (IsStaticString(Expression))
								{
									std::wstring name = L"tempstring";
									residname = engine->bytecode.resourcepool->scpFindResource(name);
									while (residname != -1)
									{
										name += L"0";
										residname = engine->bytecode.resourcepool->scpFindResource(name);
									}
									residname = engine->bytecode.resourcepool->AppendResource(name);

									engine->bytecode.GetByteCodeInitRes(name, stream, residname);
									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();

									param.push_back(L"string");
									param.push_back(name);
									param.push_back(Expression);
									engine->bytecode.GenByteCodeObjectDefine(ObjString, param, stream);

									engine->bytecode.bytecodemem->AppendByteCode(&stream);
									stream.Release();
									func->RealParameters.push_back(name);

									ScpStringObject * StrObj = new  ScpStringObject;
									StringStripQuote(Expression);
									StrObj->content = Expression;
									ScpObjectSpace * globalObjectSpace = engine->GetCurrentObjectSpace();
									while (globalObjectSpace->parentspace != NULL)
									{
										globalObjectSpace = globalObjectSpace->parentspace;
									}
									globalObjectSpace->AddObject(name, StrObj);
								}

							}
							//func->RealParameters.push_back(vtFuncparameters.at(i));
							//engine->PrintError(scpErrorInvalidFunctionParameter);
						}
					}
				}
				if (func->BindParameters(engine) != -1)
				{
					std::wstring objname = objectSpace->GetObjectNameR(nodeobject);

					VTPARAMETERS param;
					for (int i = 1;i < vtFuncparameters.size();i++)
					{
						param.push_back(vtFuncparameters.at(i));
					}
					int gencode = 0;
					if (func->bytecodemem_funcbody.codelength == 0)
					{
						gencode = 1;
						ByteCodeMemoryStream stream;
						func->functionexpressionblock->GenByteCode(engine, stream);
						engine->bytecode.GenByteCodeFunctionBody(stream);
						func->bytecodemem_funcbody.AppendByteCode(&stream);	

						engine->bytecode.bytecodemem->AppendByteCode(&func->bytecodemem_funcdef);
						engine->bytecode.bytecodemem->AppendByteCode(&func->bytecodemem_funcbody);	
							
					}

					ByteCodeMemoryStream stream;
					engine->bytecode.GenByteCodeCallFunc(objname, param, stream);
					memstream.AppendByteCode(&stream);
					stream.Release();
					if (gencode==0)
						func->Do(engine);
					func->UnBindParameters(engine);
					func->RealParameters.clear();
				}
				engine->SetCurrentObjectSpace(objectSpace);				
				
				//engine->scriptcommand->Do_Call_Command(&vtFuncparameters, engine);
				retobj = ((ScpFunctionObject *)nodeobject)->Result;
			}
			else
			{
				retobj = nodeobject;
			}
		}
		else
		{
			retobj = nodeobject;
		}
	}
	return retobj;
}
ULONG ScpExpressionTreeNode::GenTempObjectByteCode(ScpObject* obj, std::wstring &name, CScriptEngine* engine, bool retvalue)
{
	ULONG idret;
	if (obj)
	{
		if (obj->GetType() == ObjInt)
		{
			if (!retvalue)
			{
				if (((ScpIntObject*)obj)->value == 0)
				{
					idret = residzero;
				}
				else if (((ScpIntObject*)obj)->value == 1)
				{
					idret = residone;
				}
				if (((ScpIntObject*)obj)->value == 0)
				{
					idret = residzero;
				}
				else if (((ScpIntObject*)obj)->value == 1)
				{
					idret = residone;
				}
				else if (((ScpIntObject*)obj)->value == 2)
				{
					idret = residtwo;
				}
				else if (((ScpIntObject*)obj)->value == 3)
				{
					idret = residthree;
				}
				else if (((ScpIntObject*)obj)->value == 4)
				{
					idret = residfour;
				}
				else if (((ScpIntObject*)obj)->value == 5)
				{
					idret = residfive;
				}
				else if (((ScpIntObject*)obj)->value == 6)
				{
					idret = residsix;
				}
				else if (((ScpIntObject*)obj)->value == 7)
				{
					idret = residseven;
				}
				else if (((ScpIntObject*)obj)->value == 8)
				{
					idret = resideight;
				}
				else if (((ScpIntObject*)obj)->value == 9)
				{
					idret = residnine;
				}
				name = L"tempint";
				idret = engine->bytecode.resourcepool->scpFindResource(name);
				while (idret != -1)
				{
					name += L"0";
					idret = engine->bytecode.resourcepool->scpFindResource(name);
				}
			}			
			else
			{
				//˵���Ǽ�������ֵ�ķ���ֵ��������Ԥ��С������Դ
				name = L"tempint";
				idret = engine->bytecode.resourcepool->scpFindResource(name);
				while (idret != -1)
				{
					name += L"0";
					idret = engine->bytecode.resourcepool->scpFindResource(name);
				}
			}			
		}
		else if (obj->GetType() == ObjString)
		{
			name = L"tempstring";
			idret = engine->bytecode.resourcepool->scpFindResource(name);
			while (idret != -1)
			{
				name += L"0";
				idret = engine->bytecode.resourcepool->scpFindResource(name);
			}
		}
		else if (obj->GetType() == ObjDouble)
		{
			name = L"tempdouble";
			idret = engine->bytecode.resourcepool->scpFindResource(name);
			while (idret != -1)
			{
				name += L"0";
				idret = engine->bytecode.resourcepool->scpFindResource(name);
			}
		}
		else if (obj->GetType() == ObjBigInt)
		{
			name = L"tempbigint";
			idret = engine->bytecode.resourcepool->scpFindResource(name);
			while (idret != -1)
			{
				name += L"0";
				idret = engine->bytecode.resourcepool->scpFindResource(name);
			}
		}
		else if (obj->GetType() == ObjTable)
		{
			name = L"temptable";
			idret = engine->bytecode.resourcepool->scpFindResource(name);
			while (idret != -1)
			{
				name += L"0";
				idret = engine->bytecode.resourcepool->scpFindResource(name);
			}
		}
		if (idret == -1)
		{
			idret = engine->bytecode.resourcepool->AppendResource(name);
			ByteCodeMemoryStream stream;
			engine->bytecode.GetByteCodeInitRes(name, stream, idret);
			engine->bytecode.bytecodemem->AppendByteCode(&stream);
			stream.Release();
			VTPARAMETERS param;
			if (obj->GetType() == ObjInt)
				param.push_back(L"int");
			else if (obj->GetType() == ObjString)
				param.push_back(L"string");
			else if (obj->GetType() == ObjDouble)
				param.push_back(L"double");
			else if (obj->GetType() == ObjBigInt)
				param.push_back(L"int64");
			else if (obj->GetType() == ObjTable)
				param.push_back(L"table");
			param.push_back(name);
			
			if (obj->GetType() == ObjInt)
			{
				param.push_back(obj->ToString());
				engine->bytecode.GenByteCodeObjectDefine(ObjInt, param, stream);
			}
			else if (obj->GetType() == ObjString)
			{
				param.push_back(obj->ToString());
				engine->bytecode.GenByteCodeObjectDefine(ObjString, param, stream);
			}				
			else if (obj->GetType() == ObjDouble)
			{
				param.push_back(obj->ToString());
				engine->bytecode.GenByteCodeObjectDefine(ObjDouble, param, stream);
			}				
			else if (obj->GetType() == ObjBigInt)
			{
				param.push_back(obj->ToString());
				engine->bytecode.GenByteCodeObjectDefine(ObjBigInt, param, stream);

			}				
			else if (obj->GetType() == ObjTable)
				engine->bytecode.GenByteCodeObjectDefine(ObjTable, param, stream);
			engine->bytecode.bytecodemem->AppendByteCode(&stream);
			stream.Release();


			ScpObjectSpace* globalObjectSpace = engine->GetCurrentObjectSpace();
			while (globalObjectSpace->parentspace != NULL)
			{
				globalObjectSpace = globalObjectSpace->parentspace;
			}
			globalObjectSpace->AddObject(name, obj);
		}

	}
	return idret;
}
ScpObject * ScpExpressionTreeNode::PerformFunctionCall(CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * retobj =NULL;
	if(nodeobject)
	{ 		
		if(!InnerFunctionName.empty())
		{
			for (int i = 0;i < vtFuncparameters.size();i++)
			{
				ScpObject * obj = objectSpace->FindObject(vtFuncparameters.at(i));
				if (obj && obj->GetType() == ObjExpressionNode)
				{
					ScpObject * objret = ((ScpExpressionTreeNode*)obj)->CalculateEx(engine);
					objectSpace->EraseObject(vtFuncparameters.at(i));
					objectSpace->AddObject(vtFuncparameters.at(i), objret);
				}
			}
			retobj = nodeobject->CallInnerFunction(InnerFunctionName,&vtFuncparameters,engine);
		}		
		else if(nodeobject->GetType()==ObjFunction)
		{
			if (vtFuncparameters.size() > 0)
			{
				engine->scriptcommand->Do_Call_Command(&vtFuncparameters, engine);
				retobj = ((ScpFunctionObject *)nodeobject)->Result;
			}
			else
			{
				retobj = nodeobject;
			}
		}
		else
		{
			retobj = nodeobject;
		}
	}
	return retobj;
}

ScpObject * ScpExpressionTreeNode::DoArrayItemRef(CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * retobj = NULL;
	if (nodeobject)
	{
		if (!ArrayItem.empty())
		{
			int index = -1;
			if (IsStaticNumber(ArrayItem))
			{
				index = StringToInt(ArrayItem);
			}
			else
			{
				StringStripQuote(ArrayItem);
				ScpIntObject * itemindex = (ScpIntObject *)objectSpace->FindObject(ArrayItem);
				if (itemindex)
				{
					if (itemindex->GetType() == ObjInt)
					{
						index = itemindex->value;
					}
				}

			}
			if (index != -1)
			{
				if (nodeobject->GetType() == ObjArray)
				{
					retobj = ((ScpArrayObject*)nodeobject)->GetElement(index);
				}
				else if (nodeobject->GetType() == ObjTable)
				{
					retobj = ((ScpTableObject*)nodeobject)->GetElement(index);
				}
				else if (nodeobject->GetType() == ObjList)
				{
					retobj = ((ScpListObject*)nodeobject)->GetElement(index);
				}
			}
			else
			{
				if (nodeobject->GetType() == ObjArray)
				{
					retobj = ((ScpArrayObject*)nodeobject)->GetElement(ArrayItem);
				}
				else if (nodeobject->GetType() == ObjTable)
				{
					retobj = ((ScpTableObject*)nodeobject)->GetElement(ArrayItem);
				}
				else if (nodeobject->GetType() == ObjList)
				{
					retobj = ((ScpListObject*)nodeobject)->GetElement(ArrayItem);
				}
			}

		}		
	}
	return retobj;
}

ScpExpressionAnalyser::ScpExpressionAnalyser()
{
}

ScpExpressionAnalyser::ScpExpressionAnalyser(CScriptEngine * eg)
{
	lex.Attach(eg);
	engine =eg;
}
ScpExpressionAnalyser::~ScpExpressionAnalyser()
{
	ClearNodeStack();
}
void ScpExpressionAnalyser::Attach(CScriptEngine * eng)
{
	lex.Attach(eng);
	engine = eng;
}
ScpExpressionTreeNode *ScpExpressionAnalyser::BuildExressionTreeNode(std::wstring Expression, size_t &startpos)
{
	ScpExpressionTreeNode * thisnode =(ScpExpressionTreeNode * ) engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
	//thisnode->AddRef();
	std::wstring NewExpression;
	std::wstring token;

	token=lex.GetNextToken();
	while(token!=scpEndofExpression)
	{
		engine->PrintError(token);
		if(token==scpLeftParentheses)
		{				
			thisnode->LeftChild=BuildExressionTreeNode(Expression,startpos);
		}
		else if (token==scpRightParentheses)
		{				
			return thisnode->LeftChild;
		}		
		else if (token==scpOperationAdd)
		{	
			if(thisnode->nodestackop.size()==1)
			{
				thisnode->LeftChild= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
				//thisnode->LeftChild->AddRef();
				thisnode->LeftChild->nodestackobj=thisnode->nodestackobj;
				thisnode->nodestackobj.pop();
				thisnode->nodestackobj.pop();
				thisnode->LeftChild->nodestackop=thisnode->nodestackop;
				thisnode->nodestackop.pop();
			}
			thisnode->nodestackop.push(token);
		}
		else if (token==scpOperationSubtraction)
		{
			if(thisnode->nodestackop.size()==1)
			{
				thisnode->LeftChild= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
				//thisnode->LeftChild->AddRef();
				thisnode->LeftChild->nodestackobj=thisnode->nodestackobj;
				thisnode->nodestackobj.pop();
				thisnode->nodestackobj.pop();
				thisnode->LeftChild->nodestackop=thisnode->nodestackop;
				thisnode->nodestackop.pop();
			}
			thisnode->nodestackop.push(token);				
		}
		else if (token==scpOperationMultiplication)
		{
			if(thisnode->nodestackop.size()==1)
			{
				if(thisnode->nodestackop.top()==scpOperationSubtraction
					||thisnode->nodestackop.top()==scpOperationAdd)
				{
					thisnode->RightChild= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
					//thisnode->RightChild->AddRef();
					thisnode->RightChild->nodestackobj.push(thisnode->nodestackobj.top());
					thisnode->nodestackobj.pop();
				}
				else
				{
					ScpExpressionTreeNode* temp=thisnode;
					ScpExpressionTreeNode* topnod= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
					//topnod->AddRef();
					topnod->LeftChild=temp;
					topnod->nodestackobj.push(temp->nodestackobj.top());
					temp->nodestackobj.pop();
					thisnode=topnod;
				}
			}
			thisnode->nodestackop.push(token);
		}
		else if (token==scpOperationDivision)
		{
			if(thisnode->nodestackop.size()==1)
			{
				if(thisnode->nodestackop.top()==scpOperationSubtraction
					||thisnode->nodestackop.top()==scpOperationAdd)
				{
					thisnode->RightChild= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
					//thisnode->RightChild->AddRef();
					thisnode->RightChild->nodestackobj.push(thisnode->nodestackobj.top());
					thisnode->nodestackobj.pop();
					thisnode->RightChild->nodestackop=thisnode->nodestackop;
					thisnode->nodestackop.pop();	
				}
				else
				{
					ScpExpressionTreeNode* temp=thisnode;
					ScpExpressionTreeNode* topnod= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
					//topnod->AddRef();
					topnod->LeftChild=temp;
					topnod->nodestackobj.push(temp->nodestackobj.top());
					temp->nodestackobj.pop();
					thisnode=topnod;
				}
			}
			thisnode->nodestackop.push(token);
		}
		else if (token==scpOperationMod)
		{
			thisnode->nodestackop.push(token);
		}	
		else if(token==scpOperationAssign)
		{
			thisnode->RightChild = BuildExressionTreeNode(Expression,startpos);
			thisnode->nodestackop.push(token);
		}
		else if(token == scpOperationAddAndAssign
			||token == scpOperationSubAndAssign
			||token == scpOperationMulAndAssign
			||token == scpOperationDivAndAssign
			||token == scpOpeartionModAndAssign
			||token == scpOperationBitAndAndAssign
			||token == scpOperationBitOrAndAssign
			|| token == scpOperationBitNotAndAssign
			|| token == scpOperationBitXorAndAssign
			|| token == scpOpeartionBitShiftLeftAndAssign
			|| token == scpOpeartionBitShiftRightAndAssign)
		{
			thisnode->RightChild = BuildExressionTreeNode(Expression,startpos);
			thisnode->nodestackop.push(token);
		}
		else if(token==scpOperationEqual)
		{
			thisnode->nodestackop.push(token);
		}
		else if(token==scpOperationLessthan)
		{
			thisnode->nodestackop.push(token);
		}
		else if(token==scpOperationLessorEqual)
		{
			thisnode->nodestackop.push(token);
		}	
		else if(token==scpOperationBigthan)
		{
			thisnode->nodestackop.push(token);
		}	
		else if(token==scpOperationBigorEqual)
		{
			thisnode->nodestackop.push(token);
		}
		else if(token==scpOperationNot)
		{
			thisnode->nodestackop.push(token);
		}
		else if(token==scpOperationNotEqual)
		{
			thisnode->nodestackop.push(token);
		}
		else if(token ==scpOperationBitAnd)
		{
			thisnode->nodestackop.push(token);
		}
		else if (token ==scpOperationBitOr)
		{
			thisnode->nodestackop.push(token);
		}
		else if (token ==scpOperationBitXor)
		{
			thisnode->nodestackop.push(token);
		}
		else if (token ==scpOperationLogicalAnd)
		{
			thisnode->nodestackop.push(token);
		}
		else if (token ==scpOperationLogicalOr)
		{
			thisnode->nodestackop.push(token);
		}
		else if (token ==scpOperationBitShiftLeft)
		{
			thisnode->nodestackop.push(token);
		}
		else if (token ==scpOperationBitShiftRight)
		{
			thisnode->nodestackop.push(token);
		}
		else 
		{
			thisnode->nodestackobj.push(token);
		}


		token=lex.GetNextToken();
	}
	return thisnode;


}
void ScpExpressionAnalyser::PopStack(std::wstring &PostFixExpression,ScpObjStack &OperationStack)
{

	while(OperationStack.size()>0)
	{
		if(OperationStack.top()!=scpLeftParentheses)
		{
			if(!PostFixExpression.empty())
			{
				PostFixExpression+=L",";				
			}
			PostFixExpression+=OperationStack.top();
			OperationStack.pop();
		}
		else
		{
			OperationStack.pop();
			break;
		}
	}
}
void ScpExpressionAnalyser::EmptyStack(std::wstring &PostFixExpression,ScpObjStack &OperationStack)
{
	while(OperationStack.size()>0)
	{
		if(OperationStack.top()!=scpLeftParentheses)
		{
			if(!PostFixExpression.empty())
			{
				PostFixExpression+=L",";				
			}
			PostFixExpression+=OperationStack.top();
			OperationStack.pop();
		}
		else
		{
			OperationStack.pop();
		}
	}
}

ScpExpressionTreeNode *  ScpExpressionAnalyser::ParseFunctionCall(ScpObject * obj,std::wstring token,ScpObjectSpace * objectSpace)
{
	ScpExpressionTreeNode * FuncCallNode=NULL;
	BOOL bInnerFunctionCall = FALSE;
	if(obj->IsInnerFunction(token))
	{
		bInnerFunctionCall = TRUE;
	}
	std::wstring temptoken=lex.PeekNextToken();
	if(temptoken== scpLeftParentheses)
	{
		FuncCallNode= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
		//����Ҫӳ�䵽���ֿռ��У��������ﲻ�������ü���
		//FuncCallNode->AddRef();
		FuncCallNode->nodeobject = obj;
		if (bInnerFunctionCall)
		{
			FuncCallNode->InnerFunctionName = token;
		}
		else
		{
			FuncCallNode->vtFuncparameters.push_back(token);
		}
		temptoken=lex.GetNextToken();
		temptoken=lex.GetNextToken();
		std::wstring parameterExpression;
		while(!temptoken.empty())
		{				
			if(temptoken!= scpComma 
				&& temptoken != ScpObjectNames::GetSingleInsatnce()->strScpCommacn
				&& temptoken != scpLeftParentheses
				&& temptoken != scpRightParentheses
				&& temptoken != scpColon
				&& temptoken != ScpObjectNames::GetSingleInsatnce()->strScpColoncn
				&& temptoken != scpOperationObjectRefrence)
			{
				parameterExpression += temptoken;
				temptoken = lex.PeekNextToken();
				if(temptoken!= scpLeftParentheses)
				temptoken = lex.GetNextToken();											
			}
			else
			{
				if (!parameterExpression.empty())
				{
					ScpObject * obj2 = objectSpace->FindObject(parameterExpression);
					if (obj2)
					{
						if (obj2->GetType() == ObjFunction)
						{
							ScpObject * retobj2 = ParseFunctionCall(obj2, parameterExpression,objectSpace);
							if (retobj2)
							{					
								std::wstring tempobjname = objectSpace->GetNewTempObjectName();
								objectSpace->AddObject(tempobjname,retobj2);
								FuncCallNode->vtFuncparameters.push_back(tempobjname);							
							}
							else
							{
								FuncCallNode->vtFuncparameters.push_back(parameterExpression);
							}
						}
						else if(obj2->GetType()==ObjClassInstance)
						{
							if(temptoken==scpColon ||temptoken==scpOperationObjectRefrence ||temptoken==ScpObjectNames::GetSingleInsatnce()->strScpColoncn)
							{
								std::wstring temptoken1=lex.PeekNextToken();						
								ScpObject * obj1 =((ScpClassObject * )obj2)->UserClassObjectSpace.FindObject(temptoken1);
								if(obj1 )
								{
									if(obj1->GetType()==ObjFunction)
									{
										//class MemberFuncion Call
										parameterExpression+=temptoken;
										parameterExpression+=temptoken1;
										lex.GetNextToken();
										ScpObject * retobj= ParseFunctionCall(obj1,parameterExpression,objectSpace);	
										if(retobj)
										{		
											std::wstring tempobjname = objectSpace->GetNewTempObjectName();
											objectSpace->AddObject(tempobjname,retobj);
											FuncCallNode->vtFuncparameters.push_back(tempobjname);		
										}
									}
									else
									{
										lex.GetNextToken();
										std::wstring tempobjname = objectSpace->GetNewTempObjectName();
										objectSpace->AddObject(tempobjname, obj1);
										FuncCallNode->vtFuncparameters.push_back(tempobjname);
										
									}
								}
							}
							else
							{
								FuncCallNode->vtFuncparameters.push_back(parameterExpression);
							}
						}						
						else
						{	
							if(temptoken ==scpOperationObjectRefrence)
							{
								std::wstring temptoken2=lex.PeekNextToken();	
								if(obj2->IsInnerFunction(temptoken2))
								{
									lex.GetNextToken();
									//lex.GetNextToken();

									ScpObject * retobj= ParseFunctionCall(obj2,temptoken2,objectSpace);	
									if(retobj)
									{
										std::wstring tempobjname = objectSpace->GetNewTempObjectName();
										objectSpace->AddObject(tempobjname,retobj);
										parameterExpression=tempobjname;
									}
									else
									{
										//error invalid function call
									}
								}
								temptoken = lex.GetNextToken();	
								continue;
							}
							else
							{					
								FuncCallNode->vtFuncparameters.push_back(parameterExpression);							
							}
						}
					}
					else
					{
						//�����޸ĺ󣬺����Ĳ���������ԭʼ�ַ�����������ʱ�ַ�������
						if(//ScpObjectNames::IsValidObjectName(parameterExpression)||
							IsStaticNumber(parameterExpression)||
							IsStaticDoubleNumber(parameterExpression))
							FuncCallNode->vtFuncparameters.push_back(parameterExpression);
						else
						{
							ScpExpressionAnalyser ana(engine);
							ScpExpressionTreeNode *root = ana.BuildExressionTreeEx(parameterExpression);
							if (root)
							{
								ScpObject * tempobj = NULL;
								tempobj = root->CalculateEx(engine);
								std::wstring tempobjname = objectSpace->GetNewTempObjectName();
								if(tempobj)
								objectSpace->AddObject(tempobjname, tempobj);
								FuncCallNode->vtFuncparameters.push_back(tempobjname);
								//root->Destroy(engine->GetCurrentObjectSpace());
								//engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
							}
						}
												
					}
					parameterExpression = L"";
					if (temptoken == scpRightParentheses)
					{
						break;
					}
					temptoken = lex.GetNextToken();					
				}
				else
				{
					if (temptoken == scpRightParentheses)
					{
						break;
					}
					else
					{
						temptoken = lex.GetNextToken();
					}
				}
				if (temptoken == scpRightParentheses)
				{
					break;
				}
				
			}			
		}
	}
	else
	{
		//std::wstring error= L"error invalid function call ";
		//error += engine->GetCurrentSourceLine();
		//engine->PrintError(error);
		return NULL;
	}
	return FuncCallNode;
}
bool ScpExpressionAnalyser::ParseClassDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline)
{
	bool bret = true;
	//��ǰ���ڶ���һ����
	std::wstring & wcommandline = ScriptBody.at(currentcommandline);
	//���ȼ����Զϵ�
	if (engine->debugger)
	{
		engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
	}
	ULONG value;
	VTPARAMETERS vtparameters;
	lex.ParseCommandLine(wcommandline, value, vtparameters);
	engine->FetchCommand(value, &vtparameters);
	currentcommandline++;

	bool parsed = false;

	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	ScpClassObject * classobj = (ScpClassObject *)currentObjectSpace->belongto;
	//��������������ֽ���Ŀ���
	if (engine->Jit)
	{
		ByteCodeMemoryStream stream;
		engine->bytecode.GenByteCodeFromCommand(value, vtparameters, stream, engine);
		classobj->bytecodeclassdef.AppendByteCode(&stream);
		stream.Release();
	}


	//�����ǰ�����ƿռ������࣬��û���л�Ϊ��ĳ�Ա����
	while (currentObjectSpace->ObjectSpaceType == Space_Class)
	{
		if (currentcommandline >= ScriptBody.size())
		{
			break;
		}
		wcommandline = ScriptBody.at(currentcommandline);
		
		ULONG value;
		VTPARAMETERS vtparameters;
		if (!lex.ParseCommandLine(wcommandline, value, vtparameters))
		{
			engine->SwitchLanguage(wcommandline);
			currentcommandline++;
			continue;
		}
		if (value != vl_define&&value != vl_start&&value != vl_end&&value != vl_register&&value != vl_public&&value != vl_private)
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidClassDefine);
			bret = false;
			break;
		}
		
		
		if (value == vl_define )
		{
			if (vtparameters.size() > 0)
			{
				if (vtparameters.at(0) == ScpGlobalObject::GetInstance()->GetTypeName(ObjFunction))
				{
					if (!ParseFunctionDefine(ScriptFile,ScriptBody, currentcommandline))
					{
						break;
					}
					else
					{
						continue;
					}
				}//����ڲ����ܶ����� Ҳ��������������ѭ�����
				else if (vtparameters.at(0) == ScpObjectNames::GetSingleInsatnce()->strObjClass ||
					vtparameters.at(0) == ScpObjectNames::GetSingleInsatnce()->strObjIfStatement||
					vtparameters.at(0) == ScpObjectNames::GetSingleInsatnce()->strObjWhileStatement)
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidClassDefine);
					bret = false;
					break;
				}
			}			
		}
		if (value != vl_end)
		{
			classobj->ClassBody.push_back(wcommandline);
		}
		if (engine->Jit)
		{
			if (value != vl_end)
			{
				ByteCodeMemoryStream memstream;
				engine->bytecode.GenByteCodeFromCommand(value, vtparameters, memstream, engine);
				classobj->bytecodeclassbody.AppendByteCode(memstream.membuf, memstream.codelength);
				memstream.Release();
			}
			else
			{
				//���ﲻҪ��������ֽ���
				//�ȵ��״η������Ա������ʱ��������
				engine->bytecode.bytecodemem->AppendByteCode(&classobj->bytecodeclassdef);
				engine->bytecode.bytecodemem->AppendByteCode(&classobj->bytecodeclassbody);
				engine->bytecode.bytecodemem->AppendByteCode((unsigned char*)&BC_END, 1);
			}
		}
		if (engine->debugger)
		{
			engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
		}
		engine->FetchCommand(value, &vtparameters);
		engine->GetCurrentObjectSpace()->lastcommand = value;
		currentcommandline++;
		currentObjectSpace = engine->GetCurrentObjectSpace();
		if (value == vl_end)
		{
			parsed = true;
			break;
		}
	}
	if (!parsed)
	{
		engine->PrintError(L"Error Invalid Class Define");
	}
	return bret;
}
bool ScpExpressionAnalyser::ParseStructDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline)
{
	bool bret = true;
	std::wstring & wcommandline = ScriptBody.at(currentcommandline);
	if (engine->debugger)
	{
		engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
	}
	ULONG value;
	VTPARAMETERS vtparameters;
	lex.ParseCommandLine(wcommandline, value, vtparameters);
	engine->FetchCommand(value, &vtparameters);
	currentcommandline++;
	bool parsed = false;
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	//�����ǰ���ƿռ��ǽṹ�壬����resultָ��ṹ�����
	while (currentObjectSpace->ObjectSpaceType == Space_Struct)
	{
		if (currentcommandline >= ScriptBody.size())
		{
			break;
		}
		std::wstring & wcommandline = ScriptBody.at(currentcommandline);
		ULONG value;
		VTPARAMETERS vtparameters;
		if (!lex.ParseCommandLine(wcommandline, value, vtparameters))
		{
			engine->SwitchLanguage(wcommandline);
			currentcommandline++;	
			continue;
		}
		ScpStructObject * structobj = (ScpStructObject*)currentObjectSpace->belongto;;
		if (value != vl_define&&value != vl_start&&value != vl_end)
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidClassDefine);
			bret = false;
			break;
		}
		if (engine->debugger)
		{
			engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
		}
		structobj->Boday.push_back(wcommandline);
		engine->FetchCommand(value, &vtparameters);
		engine->GetCurrentObjectSpace()->lastcommand = value;
		currentcommandline++;
		currentObjectSpace = engine->GetCurrentObjectSpace();
		parsed = true;
	}
	if (!parsed)
	{
		engine->PrintError(L"Error Invalid Struct Define");
	}
	return bret;
}
bool ScpExpressionAnalyser::ParseFunctionDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline)
{
	bool bret = true;
	std::wstring & wcommandline = ScriptBody.at(currentcommandline);
	if (engine->debugger)
	{
		engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
	}
	ULONG value;
	VTPARAMETERS vtparameters;
	lex.ParseCommandLine(wcommandline, value, vtparameters);

	
	engine->FetchCommand(value, &vtparameters);
	currentcommandline++;
	bool parsed = false;
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	//�����ǰ�����ƿռ��Ǻ�������ѭ�����
	ScpFunctionObject * func = NULL;
	if (currentObjectSpace->belongto)
	{
		if (currentObjectSpace->belongto->GetType() == ObjFunction)
		{
			func = (ScpFunctionObject*)currentObjectSpace->belongto;
			if (func->functionexpressionblock == NULL)
			{
				func->functionexpressionblock = new ScpExpressionBlock;
			}
			if (engine->Jit)
			{
				if (currentObjectSpace->parentspace->ObjectSpaceType == Space_Class)
				{
					func->ParenObject = currentObjectSpace->parentspace->belongto;
					func->parentobjectname = currentObjectSpace->GetObjectNameR(func->ParenObject);
				}
				ByteCodeMemoryStream stream;
				engine->bytecode.GenByteCodeFromCommand(value, vtparameters, stream, engine);
				func->bytecodemem_funcdef.AppendByteCode(&stream);
				stream.Release();
				
			}
			
		}
	}
	while (currentObjectSpace->ObjectSpaceType == Space_Function )
	{
		if (currentcommandline >= ScriptBody.size())
		{
			break;
		}
		wcommandline = ScriptBody.at(currentcommandline);
		ULONG value;
		VTPARAMETERS vtparameters;
		if (!lex.ParseCommandLine(wcommandline, value, vtparameters))
		{
			engine->SwitchLanguage(wcommandline);
			currentcommandline++;		
			continue;
		}
		if (value == vl_test && vtparameters.size() == 1)
		{
			ScpIfStatementObject * ifobj =(ScpIfStatementObject * ) ParseIfDefine(ScriptFile, ScriptBody, currentcommandline, false);
			if (func->functionexpressionblock)
			{
				ifobj->AddRef();
				func->functionexpressionblock->Append(ifobj);
			}
			continue;
		}
		else if (value == vl_while && vtparameters.size() > 0)
		{
			ScpWhileStatementObject * whileobj = (ScpWhileStatementObject *)ParseWhileDefine(ScriptFile, ScriptBody, currentcommandline, false);
			if (func->functionexpressionblock)
			{
				whileobj->AddRef();
				func->functionexpressionblock->Append(whileobj);
			}
			continue;
		}	
		if(value==vl_end)		
		{				
			engine->FetchCommand(value, &vtparameters);			
			engine->GetCurrentObjectSpace()->lastcommand = value;
			currentcommandline++;
			parsed = true;
			break;
		}
		else
		{
			
			if (value == vl_define)
			{
				//�����ڲ����ܶ�����
				if (vtparameters.at(0) == ScpObjectNames::GetSingleInsatnce()->strObjClass)
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidFunctionDefine);
					bret = false;
					break;
				}
				
				//engine->FetchCommand(value, &vtparameters);
				if (func->functionexpressionblock)
				{
					func->functionexpressionblock->Append(wcommandline, currentcommandline,engine);
				}
			}
			else
			{
				if (func->functionexpressionblock)
				{
					func->functionexpressionblock->Append(wcommandline, currentcommandline, engine);
				}
			}
			currentcommandline++;
		}		
	}
	if (!parsed)
	{
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidFunctionDefine);
	}
	return bret;
}
ScpObject *  ScpExpressionAnalyser::ParseWhileDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline, bool doimmediately)
{
	ScpObject *  obj = NULL;
	std::wstring & wcommandline = ScriptBody.at(currentcommandline);
	if (engine->debugger &&  doimmediately)
	{
		engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
	}
	ULONG value;
	VTPARAMETERS vtparameters;
	lex.ParseCommandLine(wcommandline, value, vtparameters);
	engine->FetchCommand(value, &vtparameters);
	currentcommandline++;
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	ScpWhileStatementObject * whileobj = NULL;
	if (currentObjectSpace->belongto)
	{
		if (currentObjectSpace->belongto->GetType() == ObjWhileStatement)
		{
			whileobj = (ScpWhileStatementObject*)currentObjectSpace->belongto;
			obj = whileobj;
			whileobj->whilexpressionblock = new ScpExpressionBlock;
		}
	}
	bool parsed = false;
	//�����ǰ�����ƿռ��Ǻ�������ѭ�����
	while ( currentObjectSpace->ObjectSpaceType == Space_While)
	{
		if (currentcommandline >= ScriptBody.size())
		{
			break;
		}
		std::wstring & wcommandline = ScriptBody.at(currentcommandline);
		if (engine->debugger && doimmediately)
		{
			engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
		}
		ULONG value;
		VTPARAMETERS vtparameters;
		if (!lex.ParseCommandLine(wcommandline, value, vtparameters))
		{
			engine->SwitchLanguage(wcommandline);
			currentcommandline++;
			continue;
		}
		if (value == vl_test && vtparameters.size() == 1)
		{
			ScpIfStatementObject * ifobj = (ScpIfStatementObject *)ParseIfDefine(ScriptFile, ScriptBody, currentcommandline, false);
			whileobj->whilexpressionblock->Append(ifobj);
			continue;
		}
		else if (value == vl_while && vtparameters.size() > 0)
		{
			ScpWhileStatementObject * whileobj1 = (ScpWhileStatementObject *)ParseWhileDefine(ScriptFile, ScriptBody, currentcommandline, false);
			whileobj->whilexpressionblock->Append(whileobj1);
			continue;
		}
		if (value == vl_end)
		{
			ByteCodeMemoryStream stream;
			if (engine->Jit && whileobj->WhileStatementObjectSpace.parentspace->ObjectSpaceType == Space_Global)
			{
				whileobj->MakeConditionByteCode();
				whileobj->whilexpressionblock->GenByteCode(engine, whileobj->whileblock_bytecodemem);
				
				engine->bytecode.GenByteCodeWhilestatement(whileobj->condition_bytecodemem,
					whileobj->whileblock_bytecodemem,
					stream);
			}
								
			if (doimmediately)
			{
				engine->FetchCommand(value, &vtparameters);
				engine->GetCurrentObjectSpace()->lastcommand = value;				
			}
			else
			{
				engine->SetCurrentObjectSpace(whileobj->WhileStatementObjectSpace.parentspace);
			}
			if (engine->Jit)
			{
				if (engine->GetCurrentObjectSpace()->ObjectSpaceType == Space_Global)
				{
					engine->bytecode.bytecodemem->AppendByteCode(&stream);
				}
				else
				{
					//whileobj->bytecodemem_whilestmt.AppendByteCode(&stream);
				}
				stream.Release();
			}
			currentcommandline++;
			parsed = true;
			break;
		}
		else
		{
			
			if (value == vl_define)
			{
				
				engine->FetchCommand(value, &vtparameters);
			}
			else
			{
				if (whileobj->whilexpressionblock)
				{
					whileobj->whilexpressionblock->Append(wcommandline, currentcommandline, engine);
				}
			}
	
			currentcommandline++;
		}	
	}
	if (!parsed)
	{
		engine->PrintError(L"Error Invalid while statement");
	}
	return obj;
}
ScpObject *  ScpExpressionAnalyser::ParseIfDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline, bool doimmediately)
{
	ScpObject *  obj = NULL;
	std::wstring & wcommandline = ScriptBody.at(currentcommandline);
	if (engine->debugger && doimmediately)
	{
		engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
	}
	ULONG value;
	VTPARAMETERS vtparameters;
	lex.ParseCommandLine(wcommandline, value, vtparameters);
	engine->FetchCommand(value, &vtparameters);
	currentcommandline++;
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	ScpIfStatementObject * ifstmtobj = NULL;
	//�����ǰ���ƿռ����������
	if (currentObjectSpace->belongto)
	{
		if (currentObjectSpace->belongto->GetType() == ObjIfStatement)
		{
			ifstmtobj = (ScpIfStatementObject *)currentObjectSpace->belongto;
			obj = ifstmtobj;
			ifstmtobj->trueblock = new ScpExpressionBlock;
		}
	}
	bool parsed = false;
	
	while(currentObjectSpace->ObjectSpaceType == Space_If)
	{
		if (currentcommandline >= ScriptBody.size())
		{
			break;
		}
		std::wstring & wcommandline = ScriptBody.at(currentcommandline);
		if (engine->debugger && doimmediately)
		{
			engine->debugger->CheckDebugEvent(ScriptFile, currentcommandline, INFINITE);
		}
		ULONG value;
		VTPARAMETERS vtparameters;
		if (!lex.ParseCommandLine(wcommandline, value, vtparameters))
		{
			engine->SwitchLanguage(wcommandline);
			currentcommandline++;	
			continue;
		}	
		if (value == vl_otherwise && vtparameters.size() == 0)
		{
			ifstmtobj->TrueBody = false;
			ifstmtobj->falseblock = new ScpExpressionBlock;
			currentcommandline++;
			continue;
		}
		if (value == vl_test && vtparameters.size() == 1)
		{
			ScpIfStatementObject * ifobj = (ScpIfStatementObject *)ParseIfDefine(ScriptFile, ScriptBody, currentcommandline, false);
			if (ifstmtobj->TrueBody)
			{
				ifstmtobj->trueblock->Append(ifobj);
			}
			else
			{
				ifstmtobj->falseblock->Append(ifobj);
			}			
			continue;
		}
		else if (value == vl_while && vtparameters.size() > 0)
		{
			ScpWhileStatementObject * whileobj = (ScpWhileStatementObject *)ParseWhileDefine(ScriptFile, ScriptBody, currentcommandline, false);
			if (ifstmtobj->TrueBody)
			{
				ifstmtobj->trueblock->Append(whileobj);
			}
			else
			{
				ifstmtobj->falseblock->Append(whileobj);
			}
			continue;
		}
		if (value == vl_end)
		{
			ByteCodeMemoryStream stream;
			if (engine->Jit && ifstmtobj->IfStatementObjectSpace.parentspace->ObjectSpaceType == Space_Global)
			{
				ifstmtobj->MakeConditionByteCode();
				if (ifstmtobj->trueblock)
					ifstmtobj->trueblock->GenByteCode(engine, ifstmtobj->trueblock_bytecodemem);
				if (ifstmtobj->falseblock)
					ifstmtobj->falseblock->GenByteCode(engine, ifstmtobj->falseblock_bytecodemem);

				engine->bytecode.GenByteCodeIfstatement(ifstmtobj->condition_bytecodemem,
					ifstmtobj->trueblock_bytecodemem,
					ifstmtobj->falseblock_bytecodemem,
					stream);
			}
			
			if (doimmediately)
			{
				engine->FetchCommand(value, &vtparameters);
				engine->GetCurrentObjectSpace()->lastcommand = value;						
			}
			else
			{
				engine->SetCurrentObjectSpace(ifstmtobj->IfStatementObjectSpace.parentspace);
			}			
			if (engine->Jit)
			{
				if (engine->GetCurrentObjectSpace()->ObjectSpaceType == Space_Global)
				{
					engine->bytecode.bytecodemem->AppendByteCode(&stream);
				}
				else
				{
					//ifstmtobj->bytecodemem_ifstmt.AppendByteCode(&stream);
				}
			}
			stream.Release();
			currentcommandline++;
			parsed = true;
			break;
		}
		else
		{
			
			if (value == vl_define)
			{
				
				engine->FetchCommand(value, &vtparameters);
			}
			else
			{
				if (ifstmtobj->TrueBody)
				{
					ifstmtobj->trueblock->Append(wcommandline, currentcommandline, engine);
				}
				else
				{
					ifstmtobj->falseblock->Append(wcommandline, currentcommandline, engine);
				}
			}

			currentcommandline++;
		}

	}
	if (!parsed)
	{
		engine->PrintError(L"Error Invalid if statement");
	}
	return obj;
}
void ScpExpressionAnalyser::ClearNodeStack()
{
	while (thenodestack.size() > 0)
	{
		thenodestack.pop();
	}
}
ScpExpressionTreeNode * ScpExpressionAnalyser::InFixToPostFixEx(std::wstring &InFixExpression,std::wstring &PostFixExpression,ScpObjectSpace * objectSpace, size_t &startpos)
{
	ScpExpressionTreeNode * node= NULL;
	std::wstring token;
	ScpObjStack OperationStack;
	token=lex.GetNextToken();
	while(token!=scpEndofExpression && token!=L"")
	{
		//	engine->PrintError(token);
		if(token==scpLeftParentheses)
		{			
			//�����ţ������ӱ��ʽ
			std::wstring temp ;
			ScpExpressionTreeNode * subnode= InFixToPostFixEx(InFixExpression,temp,objectSpace,startpos);	
			if(subnode)
			{
				
				if(!PostFixExpression.empty())
				{
					PostFixExpression+=L",";				
				}
				
				std::wstring temptoken = lex.PeekNextToken();
				if(temptoken==scpOperationObjectRefrence)					
				{						
					std::wstring temptoken1=lex.PeekNext2Token();	
					if(subnode->IsInnerFunction(temptoken1))
					{
						lex.GetNextToken();
						lex.GetNextToken();

						ScpObject * retobj= ParseFunctionCall(subnode,temptoken1,objectSpace);	
						if(retobj)
						{
							std::wstring tempobjname1 = objectSpace->GetNewTempObjectName();
							objectSpace->AddObject(tempobjname1,retobj);
							PostFixExpression+=tempobjname1;
						}
						else
						{
							//error invalid function call
						}
					}
				}
				else
				{
					std::wstring tempobjname = objectSpace->GetNewTempObjectName();
					objectSpace->AddObject(tempobjname, subnode);
					PostFixExpression+=tempobjname;
				}
			}
		}
		else if (token==scpRightParentheses)
		{		
			//�����ţ������ӱ��ʽ
			EmptyStack(PostFixExpression,OperationStack);
			node = PostFixExpressionToTree(PostFixExpression);
			return node;
		}		
		else if(ScpScriptLex::IsBinaryOperator(token))
		{	
			//˫���������������������������ȼ��ж��Ƿ񵯳���ջ�е���һ�������
			if((OperationStack.size()>0)  && lex.GetBinaryOperationPriority(OperationStack.top())<=lex.GetBinaryOperationPriority(token))
				PopStack(PostFixExpression,OperationStack);
			OperationStack.push(token);

		}		
		else if(ScpScriptLex::IsAssignOperator(token))
		{
			//��ֵ����Ҫ�ѵȺ��ұߵĲ��ֵ���һ���ӱ��ʽ
			std::wstring temp ;
			node = InFixToPostFixEx(InFixExpression,temp,objectSpace,startpos);
			ScpExpressionTreeNode * subnodeop = (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
			//subnodeop->AddRef();
			ScpExpressionTreeNode * subnode = (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
			//subnode->AddRef();
			ScpObject * objLeft = objectSpace->FindObject(PostFixExpression);
			if (objLeft == NULL)
			{
				//��ֵ���󲻴���
			}
			subnode->nodeobject = objLeft;
			subnodeop->nodestackop.push(token) ;
			subnodeop->LeftChild = subnode;
			subnodeop->RightChild = node ;
			node = subnodeop;
			return node;
		}					
		else if(token==scpOperationNot
			||token==scpOperationBitNot
			)
		{
			//�������������,ǰ��
			std::wstring temptoken=lex.PeekNextToken();
			ScpObject * obj =objectSpace->FindObject(temptoken);
			if(obj )
			{
				OperationStack.push(token);
			}
		}	
		else if ( token == scpOperationSelfAdd
			|| token == scpOperationSelfSub)
		{
			//����������������������Լ�
			std::wstring temptoken = lex.PeekNextToken();
			ScpObject * obj = objectSpace->FindObject(temptoken);
			if (obj)
			{
				//���������������˵����ǰ������
			}
			OperationStack.push(token);
		}
		else 
		{
			if(!PostFixExpression.empty())
			{
				if(token!=scpComma)
				{
					PostFixExpression+=scpComma;				
				}
			}
			if(ScpObjectNames::IsValidObjectName(token))
			{
				ScpObject * obj =objectSpace->FindObject(token);
				if(obj )
				{		
					std::wstring temptoken=lex.PeekNextToken();
					//��������������
					if (temptoken == scpLeftBracket)
					{
						if (obj->GetType() == ObjArray || obj->GetType() == ObjTable || obj->GetType() == ObjList)
						{
							ScpObject * ArrayItemNode = ParseArrayItemRefrence(obj, objectSpace);
							if (ArrayItemNode)
							{
								std::wstring tempobjname = objectSpace->GetNewTempObjectName();
								objectSpace->AddObject(tempobjname, ArrayItemNode);
								token = tempobjname;

								std::wstring temptoken1 = lex.PeekNextToken();
								if (temptoken1 == scpOperationObjectRefrence)
								{
									token = ParseObjectRefrence(ArrayItemNode, objectSpace);
								}
							}
							else {
								return node;
							}
						}
					}
					//������������
					else if (temptoken == scpOperationObjectRefrence)
					{
						token = ParseObjectRefrence(obj, objectSpace);
					}
					//build function call node 
					else if( obj->GetType()==ObjFunction)
					{
						//ֱ�Ӻ�������
						ScpObject * retobj = ParseFunctionCall(obj, token, objectSpace);
						if (retobj)
						{
							std::wstring tempobjname = objectSpace->GetNewTempObjectName();
							objectSpace->AddObject(tempobjname, retobj);
							std::wstring temptoken1 = lex.PeekNextToken();
							if (temptoken1 == scpOperationObjectRefrence)
							{
								token = ParseObjectRefrence(retobj, objectSpace);
							}
							else
							{
								token = tempobjname;
							}
						}
						else
						{
							//error invalid function call
						}
					}					
				}
				else
				{
					std::wstring temptoken = lex.PeekNextToken();
					//����Ծ�̬�ַ����Ĳ���
					if (temptoken == scpOperationObjectRefrence || ScpScriptLex::IsAssignOperator(temptoken)|| ScpScriptLex::IsBinaryOperator(temptoken))
					{	
						if(!IsStaticString(token))
							engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist+ token);
						//������󲻴���
					}
				}
			}
			if(token!=scpComma)
			{
				PostFixExpression+=token;
			}
		}
		token=lex.GetNextToken();
	}
	EmptyStack(PostFixExpression,OperationStack);
	node = PostFixExpressionToTree(PostFixExpression);	
	if (node == NULL)
	{
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidExpression+ InFixExpression);
	}
	return node;
}
ScpExpressionTreeNode *  ScpExpressionAnalyser::ParseArrayItemRefrence(ScpObject * arrayObj,ScpObjectSpace * objectSpace)
{
	ScpExpressionTreeNode * ArrayItemNode=NULL;
	std::wstring temptoken=lex.GetNextToken();
	if(temptoken==scpLeftBracket)
	{
		
		temptoken=lex.GetNextToken();		
		std::wstring temptoken1=lex.GetNextToken();
		if(temptoken1==scpRightBracket)
		{
			ArrayItemNode = (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
			//����Ҫӳ�䵽���ֿռ��У��������ﲻ�������ü���
			//ArrayItemNode->AddRef();			
			ArrayItemNode->ArrayItem=temptoken;
			ArrayItemNode->nodeobject=arrayObj;
			return ArrayItemNode;
		}
	}
	return ArrayItemNode;

}
std::wstring ScpExpressionAnalyser::ParseObjectRefrence(ScpObject * obj, ScpObjectSpace * objectSpace)
{
	std::wstring token;
	std::wstring temptoken1 = lex.PeekNext2Token();
	if (obj->GetType() == ObjClassInstance)
	{
		ScpObject * obj1 = ((ScpClassObject *)obj)->UserClassObjectSpace.FindObject(temptoken1);
		if (obj1)
		{
			//���ж��Ƿ���˽�г�Ա
			if (((ScpClassObject *)obj)->memberattrmap[temptoken1] == ScpClassObject::Attr_Private)
			{
				if (obj1->GetType() == ObjFunction)
					engine->PrintError(L"Member Function is Private Access");
				else
					engine->PrintError(L"Member Variable is Private Access");
			}
			else
			{
				if (obj1->GetType() == ObjFunction)
				{
					//class MemberFuncion Call
					//token += temptoken;
					token += temptoken1;
					lex.GetNextToken();
					lex.GetNextToken();

					ScpObject * retobj = ParseFunctionCall(obj, token, objectSpace);
					if (retobj)
					{
						std::wstring tempobjname = objectSpace->GetNewTempObjectName();
						objectSpace->AddObject(tempobjname, retobj);
						std::wstring temptoken2 = lex.PeekNextToken();
						if (temptoken2 == scpOperationObjectRefrence)
						{
							token = ParseObjectRefrence(retobj, objectSpace);
						}
						else
						{
							token = tempobjname;
						}
					}

				}
				else
				{
					//���Ա�����ķ���
					//token += temptoken;
					token += temptoken1;
					lex.GetNextToken();
					lex.GetNextToken();

					ScpObject * retobj = ((ScpClassObject *)obj)->UserClassObjectSpace.FindObject(token);
					if (retobj)
					{
						std::wstring tempobjname = objectSpace->GetNewTempObjectName();
						objectSpace->AddObject(tempobjname, retobj);
						std::wstring temptoken2 = lex.PeekNextToken();
						if (temptoken2 == scpOperationObjectRefrence)
						{
							token = ParseObjectRefrence(retobj, objectSpace);
						}
						else if (lex.IsBinaryOperator(temptoken2) || lex.IsAssignOperator(temptoken2))
						{
							token = tempobjname;
							//continue;
						}
						else
						{
							ScpObject * ArrayItemNode = ParseArrayItemRefrence(retobj, objectSpace);
							if (ArrayItemNode)
							{
								std::wstring tempobjname = objectSpace->GetNewTempObjectName();
								objectSpace->AddObject(tempobjname, ArrayItemNode);
								token = tempobjname;

								std::wstring temptoken1 = lex.PeekNextToken();
								if (temptoken1 == scpOperationObjectRefrence)
								{
									token = ParseObjectRefrence(ArrayItemNode, objectSpace);
								}
							}
							else {
								token = tempobjname;
							}
							//token = tempobjname;
						}
					}

				}
			}
			return token;
		}
	}
	if (obj->IsInnerFunction(temptoken1))
	{
		lex.GetNextToken();
		lex.GetNextToken();

		ScpObject * retobj = ParseFunctionCall(obj, temptoken1, objectSpace);
		if (retobj)
		{
			std::wstring tempobjname = objectSpace->GetNewTempObjectName();
			objectSpace->AddObject(tempobjname, retobj);

			std::wstring temptoken2 = lex.PeekNextToken();
			if (temptoken2 == scpOperationObjectRefrence)
			{
				token = ParseObjectRefrence(retobj, objectSpace);
			}
			else
			{
				token = tempobjname;
			}

		}
		else
		{
			//error invalid function call
		}
	}

	return token;
}
std::wstring ScpExpressionAnalyser::GetATokenFromPostFix(std::wstring &PostFixExpression,size_t &startpos)
{
	//�Ӻ�׺���ʽ�л��һ��token
	std::wstring temp ;
	if (startpos !=std::wstring::npos)
	{
		if (PostFixExpression.at(startpos) == L',')
		{
			startpos++;
		}
		if (PostFixExpression.at(startpos) == L'\"')
		{
			do
			{
				temp += PostFixExpression.at(startpos);
				startpos++;
			} while (PostFixExpression.at(startpos) != L'\"');
			if (PostFixExpression.at(startpos) == L'\"')
			{
				temp += PostFixExpression.at(startpos);
				startpos++;
				if (startpos >= PostFixExpression.length())
				{
					startpos = std::wstring::npos;
				}
				return temp;
			}
		}
		size_t pos = PostFixExpression.find(scpComma,startpos) ;
		if(pos!=std::wstring::npos)
		{		
			temp=PostFixExpression.substr(startpos,pos-startpos);	
			startpos=pos+1;
		}
		else 
		{
			if(startpos!=std::wstring::npos)
			{
				temp=PostFixExpression.substr(startpos,PostFixExpression.length()-startpos);
				startpos=pos;
			}
		}
		STDSTRINGEXT::trim(temp);
	}

	return temp;
}

ScpExpressionTreeNode *  ScpExpressionAnalyser::BuildExressionTreeEx(std::wstring Expression)
{	
	ClearNodeStack();
	lex.SetExpression(Expression);
	size_t startpos = 0 ;
	std::wstring PostFixExpression ;	
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	//�������ʽ��֮��ͨ��������ȱ�����ʵ���ֽ�������ɣ������ÿһ�ν���ִ��ʱһ����
	return InFixToPostFixEx(Expression,PostFixExpression,objectSpace,startpos);	
}
ScpExpressionTreeNode *  ScpExpressionAnalyser::PostFixExpressionToTree(std::wstring PostFixExpression)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpExpressionTreeNode * root=NULL;//=new ScpExpressionTreeNode;
	std::wstring  token;
	size_t startpos=0;
	token= GetATokenFromPostFix(PostFixExpression,startpos);
	while(!token.empty())
	{
		if(ScpScriptLex::IsBinaryOperator(token) ||
			ScpScriptLex::IsAssignOperator(token))
		{	
			if(thenodestack.size()>=2)
			{
				ScpExpressionTreeNode * subnode= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
				//subnode->AddRef();
				subnode->RightChild=thenodestack.top();
				thenodestack.pop();
				subnode->LeftChild=thenodestack.top();
				thenodestack.pop();
				subnode->nodestackop.push(token);
				thenodestack.push(subnode);
			}	
			else if(thenodestack.size()==1)
			{
				ScpExpressionTreeNode * subnode= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
				//subnode->AddRef();
				subnode->RightChild=NULL;
				subnode->LeftChild=thenodestack.top();
				thenodestack.pop();
				subnode->nodestackop.push(token);
				thenodestack.push(subnode);
			}	
		}		
		else if (token==scpOperationNot||token==scpOperationBitNot||token==scpOperationSelfAdd||token==scpOperationSelfSub)
		{
			if(thenodestack.size()>=1)
			{
				ScpExpressionTreeNode * subnode= (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
				//subnode->AddRef();
				subnode->RightChild=NULL;
				subnode->LeftChild=thenodestack.top();
				thenodestack.pop();
				subnode->nodestackop.push(token);
				thenodestack.push(subnode);
			}	
		}
		else 
		{	
			ScpExpressionTreeNode * subnode=NULL;
			std::wstring elementname= token;
			ScpObject * tempobj =NULL;
			if(ScpObjectNames::IsValidObjectName(token))
				tempobj = objectSpace->FindObject(token);
			if(tempobj)
			{
				if(tempobj->GetType()==ObjExpressionNode)
				{					
					subnode= (ScpExpressionTreeNode*)tempobj;
				}
				else
				{
					subnode = (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
					//subnode->AddRef();
					subnode->nodeobject = tempobj;
					if(tempobj->istemp)
						tempobj->AddRef();
				}
			}
			else
			{
				subnode = (ScpExpressionTreeNode *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjExpressionNode);
				//subnode->AddRef();
				if(IsStaticNumber(token))
				{
					tempobj = objectSpace->AcquireTempObject(ObjInt);
					((ScpIntObject*)tempobj)->value = StringToInt(token);
				}
				else if(IsStaticDoubleNumber(token))
				{
					tempobj = objectSpace->AcquireTempObject(ObjDouble);
					((ScpDoubleObject*)tempobj)->value = StringToDouble(token);
				}
				else 
				{
					tempobj = objectSpace->AcquireTempObject(ObjString);
					std::wstring content = token;
					StringStripQuote(content);
					((ScpStringObject*)tempobj)->content = content;					
				}
				tempobj->istemp = true;
				subnode->nodeobject = tempobj;
				//objectSpace->AddTempObject(tempobj);
			}
			thenodestack.push(subnode);
		}	
		token= GetATokenFromPostFix(PostFixExpression,startpos);
	}
	if(thenodestack.size()==1)
	{
		root=thenodestack.top();
		thenodestack.pop();
	}	
	if (root == NULL)
	{
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidExpression);
	}
	return root;
}



int ScpExpressionTreeNode::GenTempObjectByteCodeOfExpression(std::wstring Expression, CScriptEngine* engine)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return 0;
}
