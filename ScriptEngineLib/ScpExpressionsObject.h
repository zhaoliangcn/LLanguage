#ifndef _H_SCPEXPRESSIONSOBJECT
#define _H_SCPEXPRESSIONSOBJECT
#include "ScpObject.h"
#include "ScpExpressionAnalyser.h"
class ScpExpressionsObject :
	public ScpObject
{
public:
	ScpExpressionsObject(void);
	~ScpExpressionsObject(void);
	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	bool Compile(CScriptEngine * engine);
	ScpObject * Run(CScriptEngine * engine);

	std::wstring orgexpression;
	ScpObject * result;
	ScpExpressionTreeNode * rootNode;
};

#endif //_H_SCPEXPRESSIONSOBJECT