/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPEXPRESSIONANALYSER
#define _H_SCPEXPRESSIONANALYSER

#include "ScpObject.h"
#include "ScpObjectSpace.h"
#include "ScpScriptLex.h"
#include "ScriptByteCode.h"
#include <stack>
class ScpExpressionTreeNode;
typedef std::stack<std::wstring> ScpObjStack;
typedef std::stack<ScpExpressionTreeNode*> TheNodeStack;
typedef std::stack<ScpObject*> TheObjectStack;

/*
���ʽ�﷨���ڵ���
*/
class ScpExpressionTreeNode:public ScpObject
{
public:
	ScpExpressionTreeNode();
	~ScpExpressionTreeNode();

	virtual void Show(CScriptEngine * engine)
	{
		
	}
	virtual ScpObject * Clone(std::wstring strObjName)
	{
		return NULL;
	}
	virtual std::wstring ToString()
	{
		return L"";
	}
	virtual void Release()
	{
		delete this;
	}
	virtual bool IsInnerFunction(std::wstring & functionname)
	{
		if (nodeobject && InnerFunctionName.empty())
		{
			//�������ڵ���һ�����顢�б����Ա���ýڵ㣬����Ҫ���������Ա���ٶ����Ա����IsInnerFunction
			if (!ArrayItem.empty())
			{
				return true;
			}
			else
			return nodeobject->IsInnerFunction(functionname);
		}
		else
		{
			return true;
		}
		return false;
	}
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		if (nodeobject)
		{
			return nodeobject->CallInnerFunction(functionname, parameters,engine);
		}
		else
		{
			return ScpObject::CallInnerFunction(functionname, parameters, engine);
		}
		return NULL;
	}
	void Destroy(ScpObjectSpace * currentObjectSpace);


	ScpExpressionTreeNode * LeftChild;
	ScpExpressionTreeNode * RightChild;
	
	ScpObject *  CalculateEx(CScriptEngine * engine);
	ScpObject *  CalcStackEx(CScriptEngine * engine);
	ScpObject * MakeByteCode(CScriptEngine * engine, ByteCodeMemoryStream &memstream);
	ScpObject * MakeByteCodeStack(CScriptEngine * engine, ByteCodeMemoryStream &memstream);
	ScpObject * MakeByteCodePerformFunctionCall(CScriptEngine * engine, ByteCodeMemoryStream &memstream);
	ULONG GenTempObjectByteCode(ScpObject* obj, std::wstring &name, CScriptEngine* engine,bool retvalue);

	ScpObject * nodeobject;  //��ǰ�ڵ��б���Ķ���
	std::wstring Expression;
	ScpObjStack nodestackobj;
	ScpObjStack nodestackop;
	TheObjectStack NodeObjectStack;
	ScpObject * PerformFunctionCall(CScriptEngine * engine);
	ScpObject * DoArrayItemRef(CScriptEngine * engine);
	VTPARAMETERS vtFuncparameters;   //�������ò���
	std::wstring InnerFunctionName;  //���ڵ��ʾ�����Ա�����ĵ���
	std::wstring ArrayItem;
	int GenTempObjectByteCodeOfExpression(std::wstring Expression, CScriptEngine* engine);
};



/*
���ʽ��������
*/
class ScpExpressionAnalyser
{
public:
	ScpExpressionAnalyser();
	ScpExpressionAnalyser(CScriptEngine * eg);
	~ScpExpressionAnalyser();
	void Attach(CScriptEngine * eng);
	


	ScpExpressionTreeNode *  BuildExressionTreeEx(std::wstring Expression);   //�������ʽ���﷨��
	ScpExpressionTreeNode *  PostFixExpressionToTree(std::wstring PostFixExpression);   //ͨ����׺���ʽ�����﷨��
	void EmptyStack(std::wstring &PostFixExpression,ScpObjStack &OperationStack);
	void PopStack(std::wstring &PostFixExpression,ScpObjStack &OperationStack);
	/*
	����׺���ʽת��Ϊ��׺���ʽ��ͬʱ���ɱ��ʽ��
	*/
	ScpExpressionTreeNode * InFixToPostFixEx(std::wstring &InFixExpression,std::wstring &PostFixExpression,ScpObjectSpace * objectSpace, size_t &startpos);
	

	std::wstring GetATokenFromPostFix(std::wstring& PostFixExpression, size_t &startpos); //�Ӻ�׺���ʽ�л��һ��token
	ScpExpressionTreeNode * BuildExressionTreeNode(std::wstring Expression, size_t &startpos);
	ScpExpressionTreeNode * ParseFunctionCall(ScpObject * obj,std::wstring token,ScpObjectSpace * objectSpace);
	ScpExpressionTreeNode * ParseArrayItemRefrence(ScpObject * arrayObj,ScpObjectSpace * objectSpace);
	std::wstring ParseObjectRefrence(ScpObject * obj, ScpObjectSpace * objectSpace);
	bool ParseClassDefine(const wchar_t * ScriptFile,VTSTRINGS & ScriptBody,int & currentcommandline);
	bool ParseStructDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline);
	bool ParseFunctionDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline);
	ScpObject * ParseWhileDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline,bool doimmediately);
	ScpObject * ParseIfDefine(const wchar_t * ScriptFile, VTSTRINGS & ScriptBody,int & currentcommandline, bool doimmediately);

	void ClearNodeStack();
	TheNodeStack thenodestack;
	ScpScriptLex  lex; 
	CScriptEngine * engine;
	
};
#endif //_H_SCPEXPRESSIONANALYSER