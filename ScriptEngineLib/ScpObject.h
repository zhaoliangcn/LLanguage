/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPOBJECT
#define _H_SCPOBJECT
#ifdef _WIN32

#ifdef _DEBUG
#include <cstdlib>
#include <xdebug>
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
typedef int BOOL;
#define WINAPI 
#endif


#include <functional>
#include <map>
#include "vectorobjects.h"
#include "commanddefine.h"
typedef unsigned short ScpObjectType;


class CScriptEngine;
class ScpObject;
typedef std::function< ScpObject *(ScpObject * thisobject, VTPARAMETERS * vtparameters, CScriptEngine * engine)> ObjectInnerFunction;

/*
为了代码的通用性设计的对象基类
所有对象都必须继承此类
对于整数、浮点数、大整数来说，这样的包装类比较重了，增加了负担，运行时的效率不高
*/
class ScpObject
{
public:
	ScpObject(void) :RefCount(0), istemp(false)
	{
	}
	~ScpObject(void)
	{
	}
	ScpObjectType GetType()
	{
		return objecttype;
	}
	virtual void Show(CScriptEngine * engine) = 0;
	virtual ScpObject * Clone(std::wstring strObjName) = 0;
	virtual std::wstring ToString() = 0;
	virtual void Release() = 0;
	//virtual std::wstring Serialize();
	virtual bool IsInnerFunction(std::wstring & functionname)
	{
		return false;
	}
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		return NULL;
	}
	void AddRef()
	{
		RefCount++;
	}
	void DelRef()
	{
		RefCount--;
		if (RefCount <= 0)
		{
			Release();
		}
	}
	std::map<std::wstring, ObjectInnerFunction> ObjectInnerFunctions;
	BOOL BindObjectInnerFuction(std::wstring functionanme, ObjectInnerFunction innerfunc)
	{
		if (ObjectInnerFunctions.find(functionanme) == ObjectInnerFunctions.end())
		{
			ObjectInnerFunctions[functionanme] = innerfunc;
			return TRUE;
		}
		return FALSE;
	}
	std::wstring GetInnerFunctionList()
	{
		std::wstring temp;
		std::map<std::wstring, ObjectInnerFunction>::iterator it = ObjectInnerFunctions.begin();
		while (it != ObjectInnerFunctions.end())
		{
			temp += it->first;
			temp += L" ";
			it++;
		}
		return temp;
	}
	ScpObjectType objecttype;
	short RefCount;
	bool istemp;
};

typedef ScpObject *  (__stdcall *ExtObjCreateFactoryFunction)(VTPARAMETERS *, CScriptEngine * engine);
typedef BOOL(__stdcall *ExtObjectCommandFunction)(VTPARAMETERS * vtparameters, CScriptEngine * engine);
typedef BOOL(__stdcall *GlobalCommandFunction)(VTPARAMETERS * vtparameters, CScriptEngine * engine);


#endif //_H_SCPOBJECT