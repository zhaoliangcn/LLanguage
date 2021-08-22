/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//C语言基本数据类型对象，用于实现C语言函数绑定
*/
#ifndef _H_SCPCOBJECT
#define _H_SCPCOBJECT

#ifdef _M_AMD64 
typedef unsigned __int64 PADDRESS;
#else
typedef unsigned long PADDRESS;
#endif

#include "ScpObject.h"
#include "ScpObjectSpace.h"
class ScpCObject:public ScpObject
{
public:
	ScpCObject()
	{

	}
	virtual ~ScpCObject()
	{
	}
	virtual PADDRESS GetValueAddress()=0;

};
class ScpObjCChar:public ScpCObject
{
public:
	ScpObjCChar();
	~ScpObjCChar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	char Value;
};
class ScpObjCUnsignedChar:public ScpCObject
{
public:
	ScpObjCUnsignedChar();
	~ScpObjCUnsignedChar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	unsigned char Value;
};
class ScpObjCInt32:public ScpCObject
{
public:
	ScpObjCInt32();
	~ScpObjCInt32();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	int Value;
};

class ScpObjUnsignedInt32:public ScpCObject
{
public:
	ScpObjUnsignedInt32();
	~ScpObjUnsignedInt32();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	unsigned int Value;
};


class ScpObjPointerofChar:public ScpCObject
{
public:
	ScpObjPointerofChar();
	~ScpObjPointerofChar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	char * Value;
};
class ScpObjPointerofWchar:public ScpCObject
{
public:
	ScpObjPointerofWchar();
	~ScpObjPointerofWchar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	wchar_t * Value;
};
class ScpObjHandle:public ScpCObject
{
public:
	ScpObjHandle();
	~ScpObjHandle();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	HANDLE Value;
};
class ScpObjPointer:public ScpCObject
{
public:
	ScpObjPointer();
	~ScpObjPointer();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual void Release();
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	void * Value;
};
class ScpObjStruct:public ScpCObject
{
public:
	ScpObjStruct();
	~ScpObjStruct();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	void * Value;
	ScpObjectSpace UserStructObjectSpace;
	VTSTRINGS StructBody;
};

class ScpObjCShort:public ScpCObject
{
public:
	ScpObjCShort();
	~ScpObjCShort();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	short Value;
};
class ScpObjCUnsignedShort:public ScpCObject
{
public:
	ScpObjCUnsignedShort();
	~ScpObjCUnsignedShort();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	unsigned short Value;

};
class ScpObjCLong:public ScpCObject
{
public:
	ScpObjCLong();
	~ScpObjCLong();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	long Value;
};
class ScpObjCUnsignedLong:public ScpCObject
{
public:
	ScpObjCUnsignedLong();
	~ScpObjCUnsignedLong();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	unsigned long Value;
};
#endif //_H_SCPCOBJECT