/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//±Ì∂‘œÛ
*/
#ifndef _H_SCPTABLEOBJECT 
#define _H_SCPTABLEOBJECT

#include "ScpObject.h"
#include "ScpUserObject.h"

class ScpObjectSpace;
class CScriptEngine;
class ScpTableObject:public ScpObject
{
public:
	ScpTableObject();
	~ScpTableObject();
	
	ULONG GetSize();
	void Combine(ScpObject * tbl);
	void Assign(ScpObject * tbl);
	void Exclude(ScpObject * tbl);
	void Intersection(ScpObject * tbl);
	BOOL AddElement(std::wstring elementname,ScpObject * obj);
	BOOL AddElement(std::wstring elementname,ScpObjectSpace * objectSpace);
	BOOL DeleteElement(std::wstring elementname);
	void EmptyElement();
	ScpObject * GetElement(std::wstring elementname);
	ScpObjectType GetElementType(std::wstring elementname);
	BOOL DeleteElement(ULONG elementindex);
	ScpObject * GetElement(ULONG elementindex);
	ScpObjectType GetElementType(ULONG elementindex);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	ScpUserObject2 tableobjects;
	std::wstring tableobjname;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_insert(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_traverse(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getelement(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

} ;

ScpObject * __stdcall ScpTableObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);


#endif //_H_SCPTABLEOBJECT