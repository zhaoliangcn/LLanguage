/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//表对象
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
	BOOL AddElement(std::string elementname,ScpObject * obj);
	BOOL AddElement(std::string elementname,ScpObjectSpace * objectSpace);
	BOOL DeleteElement(std::string elementname);
	void EmptyElement();
	ScpObject * GetElement(std::string elementname);
	ScpObjectType GetElementType(std::string elementname);
	BOOL DeleteElement(ULONG elementindex);
	ScpObject * GetElement(ULONG elementindex);
	ScpObjectType GetElementType(ULONG elementindex);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	ScpUserObject2 tableobjects;
	std::string tableobjname;


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