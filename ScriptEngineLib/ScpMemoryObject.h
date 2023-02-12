/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//内存对象
*/
#ifndef _H_SCPMEMORYOBJECT
#define _H_SCPMEMORYOBJECT
#include "ScpObject.h"
static const char * scpcommand_cn_extend = "扩展";
static const char * scpcommand_en_extend = "extend";



class ScpMemoryObject:public ScpObject
{
public:
	ScpMemoryObject();
	~ScpMemoryObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);
	BOOL Acquare(ULONG aSize);
	BOOL Extend(ULONG exSize);
	BOOL ReleaseMem();
	BOOL Read(void * dest,ULONG aSize);
	BOOL Read(std::string & wstr);
	BOOL Read(void * dest, ULONG pos, ULONG aSize);
	BOOL Read(std::string & wstr, ULONG pos);
	BOOL Write(void * src,ULONG aSize);
	BOOL Write(std::wstring & wstr);
	BOOL Write(std::string & astr);
	BOOL Write(void * src, ULONG pos,ULONG aSize);
	BOOL Write(std::string & wstr,ULONG pos );
	BOOL CopyTo(ScpMemoryObject * dest);
	BOOL CopyFrom(ScpMemoryObject * src);
	ULONG GetSize();
	void Clear();
	int Find(const char * pattern);
	
	

	ULONG Size;
	void * Address;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_acquire(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_encode(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_decode(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_encrypt(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_decrypt(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_release(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_compare(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_extend(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	//static ScpObject * InnerFunction_hash(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};

ScpObject * __stdcall ScpMemoryObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif//_H_SCPMEMORYOBJECT