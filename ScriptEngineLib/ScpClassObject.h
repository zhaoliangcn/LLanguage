/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//类对象及其成员变量、成员函数的管理
*/
#ifndef _H_SCPCLASSOBJECT
#define _H_SCPCLASSOBJECT
#include "ScpObject.h"
#include "ScpExpressionBlock.h"
#include "ScpObjectSpace.h"

class CScriptEngine;
class ScpClassObject :
	public ScpObject
{
public:
	friend class CScriptEngine;
	ScpClassObject(void);
	~ScpClassObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	void ClassDefine(std::wstring name);
	ScpObject * CallMemberFunction(std::wstring functionname,VTPARAMETERS * RealParameters,CScriptEngine * engine);
	void AddMemberVariable(std::wstring name,ScpObject * object);
	void AddMemberFunction(std::wstring name,ScpObject * object);
	ScpObject * FindMemberVariable(std::wstring name);
	std::wstring userclassname ;
	ScpObjectSpace UserClassObjectSpace;
	VTSTRINGS ClassBody;
	CScriptEngine * scriptengine;
	static const ULONG Attr_Private =0;
	static const ULONG Attr_Public =1;
	ULONG MemberVariableAttribute ;
	MEMBERATTRMAP memberattrmap;
	ScpExpressionBlock classexpressionblock;

	ByteCodeMemoryStream bytecodeclassdef;
	ByteCodeMemoryStream bytecodeclassbody;
	ByteCodeMemoryStream bytecodeclassmemberfunc;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};


#endif //_H_SCPCLASSOBJECT