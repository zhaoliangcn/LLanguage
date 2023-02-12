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

#define INVALID_OBJECT_ID (-1)
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
	// 输出对象的内容
	virtual void Show(CScriptEngine * engine) = 0;
	// 对象克隆，即对象的 深拷贝
	virtual ScpObject * Clone(std::string strObjName) = 0;
	// 对象的内容转换为字符串
	virtual std::string ToString() = 0;
	// 释放对象的内存空间
	virtual void Release() = 0;
	//TODO : 对象的序列化，用于支持对象的发送，可以是跨进程发送对象也可以是跨网络
	//virtual std::wstring Serialize();
	virtual bool IsInnerFunction(std::string & functionname)
	{
		return false;
	}
	//支持在对象内部成员函数未知的情况下，通过统一接口调用内部成员函数
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
	{
		return NULL;
	}
	//增加对象引用计数
	void AddRef()
	{
		RefCount++;
	}
	//减少对象引用计数，并在引用计数归零时调用Release释放对象所占内存空间
	void DelRef()
	{
		RefCount--;
		if (RefCount <= 0)
		{
			Release();
		}
	}
	//对象绑定的接口函数，用于实现对象反射，即从外部获取对象内部的函数列表
	//反射存在的意义是，解释器需要能够在运行时获得这些信息，辅助进行语法解析
	std::map<std::string, ObjectInnerFunction> ObjectInnerFunctions;
	BOOL BindObjectInnerFuction(std::string functionanme, ObjectInnerFunction innerfunc)
	{
		if (ObjectInnerFunctions.find(functionanme) == ObjectInnerFunctions.end())
		{
			ObjectInnerFunctions[functionanme] = innerfunc;
			return TRUE;
		}
		return FALSE;
	}
	//获取对象内部的函数名列表，可用于实现编辑器中的对象成员函数的"联想输入"功能
	std::string GetInnerFunctionList()
	{
		std::string temp;
		std::map<std::string, ObjectInnerFunction>::iterator it = ObjectInnerFunctions.begin();
		while (it != ObjectInnerFunctions.end())
		{
			temp += it->first;
			temp += " ";
			it++;
		}
		return temp;
	}
	ScpObjectType objecttype;
	short RefCount;
	bool istemp;
};

//创建扩展对象的工厂类函数定义
typedef ScpObject *  (__stdcall *ExtObjCreateFactoryFunction)(VTPARAMETERS *, CScriptEngine * engine);
typedef ScpObject* (__stdcall* ObjCreateFactoryFunction)(VTPARAMETERS*, CScriptEngine* engine);
typedef BOOL(__stdcall *ExtObjectCommandFunction)(VTPARAMETERS * vtparameters, CScriptEngine * engine);
typedef BOOL(__stdcall *GlobalCommandFunction)(VTPARAMETERS * vtparameters, CScriptEngine * engine);


#endif //_H_SCPOBJECT