#ifndef _H_SCPLISTOBJECT
#define _H_SCPLISTOBJECT
#include "ScpObject.h"
class ScpObjectSpace;
class CScriptEngine;
typedef std::pair< std::wstring, ScpObject *> NamedPOBJECTS;
typedef std::vector<NamedPOBJECTS> VTNamedPOBJECTS;
typedef std::vector<NamedPOBJECTS>::iterator ITNamedPOBJECTS;

class ScpListObject :
	public ScpObject
{
public:
	ScpListObject();
	~ScpListObject();

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);


	ULONG GetSize();
	void Combine(ScpObject * tbl);
	void Assign(ScpObject * tbl);
	void Exclude(ScpObject * tbl);
	void Intersection(ScpObject * tbl);
	BOOL AddElement(std::wstring elementname, ScpObject * obj);
	BOOL AddElement(std::wstring elementname, ScpObjectSpace * objectSpace);
	BOOL InsertElement(int index,std::wstring elementname, ScpObject * obj);
	BOOL DeleteElement(std::wstring elementname);
	void EmptyElement();
	ScpObject * GetElement(std::wstring elementname);
	ScpObjectType GetElementType(std::wstring elementname);
	BOOL DeleteElement(ULONG elementindex);
	ScpObject * GetElement(ULONG elementindex);
	ScpObjectType GetElementType(ULONG elementindex);

	std::wstring listname;
	VTNamedPOBJECTS members;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_insert(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_append(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_traverse(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getelement(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};

ScpObject * __stdcall ScpListObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPLISTOBJECT