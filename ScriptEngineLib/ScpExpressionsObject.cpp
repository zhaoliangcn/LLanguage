#include "ScpExpressionsObject.h"


ScpExpressionsObject::ScpExpressionsObject(void)
{
	objecttype = ObjExpressions;
	rootNode=NULL;
}


ScpExpressionsObject::~ScpExpressionsObject(void)
{
	if (rootNode)
	{
		rootNode->DelRef();
	}
}
void ScpExpressionsObject::Show(CScriptEngine * engine) 
{
}
ScpObject * ScpExpressionsObject::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpExpressionsObject::ToString()
{
	std::wstring temp;
	return temp;
}
void ScpExpressionsObject::Release() 
{
	delete this;
}

bool ScpExpressionsObject::IsInnerFunction(std::wstring & functionname)
{
	return false;
}

ScpObject * ScpExpressionsObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return NULL;
}

bool ScpExpressionsObject::Compile(CScriptEngine * engine)
{
	if (rootNode)
	{
		return false;
	}
	else
	{
		rootNode = new ScpExpressionTreeNode;
		rootNode->AddRef();
		return true;
	}
}

ScpObject * ScpExpressionsObject::Run(CScriptEngine * engine)
{
	return NULL;
}
