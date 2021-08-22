/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPEXPRESSIONBLOCK
#define _H_SCPEXPRESSIONBLOCK
#include "ScpObject.h"
#include "ScpExpressionsObject.h"
#include "ScriptByteCode.h"
#include <vector>
class ScpExpressionBlock;
typedef std::vector<ScpExpressionsObject *> VTExpression;
typedef std::vector<ScpExpressionsObject *>::iterator ITExpression;

typedef std::vector<ScpObject *> VTExpressionBlocks;
typedef std::vector<ScpObject *>::iterator ITExpressionBlocks;

typedef std::vector< ScpExpressionTreeNode *> VTRootNodes;
typedef std::vector< ScpExpressionTreeNode *>::iterator ITRootNodes;
class ScpExpressionBlock :
	public ScpObject
{
public:
	ScpExpressionBlock();
	~ScpExpressionBlock();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	void Append(std::wstring& expression,int line, CScriptEngine * engine);
	void Append(ScpObject * block);
	void Destroy();
	bool GenByteCode(CScriptEngine * engine, ByteCodeMemoryStream &bytecodemem);
	ScpObject * Run(CScriptEngine * engine);
	VTExpressionBlocks expressionblocks;
	std::wstring orgexpression;
	ULONG ulcommand;
	VTPARAMETERS vt_command_parameters;
	ScpObject * result;
	VTRootNodes rootNodes;
	ScpObject * owner;
	bool breakpoint;
	int linenumber;
	
};

#endif //_H_SCPEXPRESSIONBLOCK