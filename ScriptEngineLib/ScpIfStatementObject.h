/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//条件语句对象
*/
#ifndef _H_SCPIFSTATEMENTOBJECT
#define _H_SCPIFSTATEMENTOBJECT
#include "ScpObject.h"
#include "ScpObjectSpace.h"
#include "ScriptEngine.h"
#include "ScpExpressionBlock.h"
class CScriptEngine;
class ScpIfStatementObject :
	public ScpObject
{
public:
	friend class CScriptEngine;
	ScpIfStatementObject(CScriptEngine *eg);
	~ScpIfStatementObject(void);


	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	

	int Do(CScriptEngine *engine);
	void ClearLocalObjects();
	int ReComputeCondition();

	//IF语句的条件表达式
	std::string ConditionExpression;
	int ConditionResult;
	bool TrueBody;
	std::string Name;
	ScpObjectSpace IfStatementObjectSpace;
	CScriptEngine *engine;	
	ScpExpressionBlock *trueblock;
	ScpExpressionBlock *falseblock;
	
	
	bool MakeConditionByteCode();

	ByteCodeMemoryStream condition_bytecodemem;
	ByteCodeMemoryStream trueblock_bytecodemem;
	ByteCodeMemoryStream falseblock_bytecodemem;

	ByteCodeMemoryStream bytecodemem_ifstmt;
};

#endif //_H_SCPIFSTATEMENTOBJECT