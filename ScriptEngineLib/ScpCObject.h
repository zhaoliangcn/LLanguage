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
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	char Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjCUnsignedChar:public ScpCObject
{
public:
	ScpObjCUnsignedChar();
	~ScpObjCUnsignedChar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	unsigned char Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjCInt32:public ScpCObject
{
public:
	ScpObjCInt32();
	~ScpObjCInt32();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	int Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};

class ScpObjUnsignedInt32:public ScpCObject
{
public:
	ScpObjUnsignedInt32();
	~ScpObjUnsignedInt32();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	unsigned int Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};


class ScpObjPointerofChar:public ScpCObject
{
public:
	ScpObjPointerofChar();
	~ScpObjPointerofChar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	char * Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjPointerofWchar:public ScpCObject
{
public:
	ScpObjPointerofWchar();
	~ScpObjPointerofWchar();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	wchar_t * Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjHandle:public ScpCObject
{
public:
	ScpObjHandle();
	~ScpObjHandle();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	HANDLE Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjPointer:public ScpCObject
{
public:
	ScpObjPointer();
	~ScpObjPointer();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual void Release();
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual PADDRESS GetValueAddress();
	void * Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjStruct:public ScpCObject
{
public:
	ScpObjStruct();
	~ScpObjStruct();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	void * Value;
	ScpObjectSpace UserStructObjectSpace;
	VTSTRINGS StructBody;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};

class ScpObjCShort:public ScpCObject
{
public:
	ScpObjCShort();
	~ScpObjCShort();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	short Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjCUnsignedShort:public ScpCObject
{
public:
	ScpObjCUnsignedShort();
	~ScpObjCUnsignedShort();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	unsigned short Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);

};
class ScpObjCLong:public ScpCObject
{
public:
	ScpObjCLong();
	~ScpObjCLong();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	long Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
class ScpObjCUnsignedLong:public ScpCObject
{
public:
	ScpObjCUnsignedLong();
	~ScpObjCUnsignedLong();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	virtual void Release();
	virtual PADDRESS GetValueAddress();
	unsigned long Value;
	static ScpObject* InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
};
#endif //_H_SCPCOBJECT