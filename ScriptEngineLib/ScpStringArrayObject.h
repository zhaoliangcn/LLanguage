/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPSTRINGARRAYOBJECT
#define _H_SCPSTRINGARRAYOBJECT

#include "ScpObject.h"
class ScpStringArrayObject :
	public ScpObject
{
public:
	ScpStringArrayObject(void);
	~ScpStringArrayObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	void Add(std::wstring strbody);
	void Clear();
	BOOL Del(unsigned int index);
	BOOL Del(std::wstring strbody);
	VTSTRINGS content;

};

#endif //_H_SCPSTRINGARRAYOBJECT