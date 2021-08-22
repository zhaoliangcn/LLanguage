/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//—≠ª∑”Ôæ‰∂‘œÛ
*/
#ifndef _H_WHILESTATEMENTOBJECT
#define _H_WHILESTATEMENTOBJECT
#include "ScpObject.h"
#include "ScpObjectSpace.h"
#include "ScriptEngine.h"
#include "ScpExpressionBlock.h"
class CScriptEngine;
class ScpWhileStatementObject :
	public ScpObject
{
public:
	friend class CScriptEngine;

	ScpWhileStatementObject(CScriptEngine * eg);
	~ScpWhileStatementObject(void);


	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	int Do(CScriptEngine *engine);
	void ClearLocalObjects();
	void SetCondition(std::wstring condition);
	int ReComputeConditionResult();

	
	std::wstring ConditionExpression;
	std::wstring Name;
	ScpObjectSpace WhileStatementObjectSpace;
	CScriptEngine * engine;
	ScpExpressionBlock *whilexpressionblock;
	int ConditionResult;

	bool MakeConditionByteCode();

	ByteCodeMemoryStream condition_bytecodemem;
	ByteCodeMemoryStream whileblock_bytecodemem;
	ByteCodeMemoryStream bytecodemem_whilestmt;
	
};

#endif //_H_WHILESTATEMENTOBJECT