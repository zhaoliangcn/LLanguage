/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//数组对象及其成员访问支持
*/
#ifndef _H_SCPARRAYOBJECT
#define _H_SCPARRAYOBJECT
#include "ScpObject.h"
#include "ScpObjectSpace.h"

class ScpObjectSpace;
class ScpArrayObject :
	public ScpObject
{
public:
	ScpArrayObject(void);
	~ScpArrayObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	/*
	获得当前数组对象的大小
	*/
	ULONG GetSize();
	/*
	在当前数组对象中添加一个元素
	*/
	BOOL AddElement(std::string elementname,ScpObject * obj);
	BOOL AddElement(std::string elementname,ScpObjectSpace * objectSpace);
	BOOL SetElement(std::string elementname,ULONG elementindex,ScpObject * obj);
	BOOL SetElement(std::string elementname,ULONG elementindex,ScpObjectSpace * objectSpace);
	/*
	删除当前数组对象中的元素
	*/
	BOOL DeleteElement(std::string elementname);
	BOOL DeleteElement(ULONG elementindex);
	/*
	替换当前数组对象中的元素
	*/
	BOOL ReplaceElementObj(ScpObject * oldobj,ScpObject * obj);
	BOOL ReplaceElementObj(ULONG elementindex,ScpObject * obj);
	BOOL ReplaceElementObj(std::string elementname,ScpObject * obj);
	/*
	获取当前数组对象中的元素的对象指针
	*/
	ScpObject * GetElement(std::string elementname);
	ScpObject * GetElement(ULONG elementindex);
	/*
	获取当前数组对象中的元素的类型
	*/
	ScpObjectType GetElementType(std::string elementname);	
	ScpObjectType GetElementType(ULONG elementindex);
	/*
	获取当前数组对象中的元素的名字
	*/
	std::string GetElementName(ULONG elementindex);

	ULONG Max;
	ScpObjectType Elementtype;				//数组对象中的元素的类型（数组对象中的元素类型唯一）
	ScpUserObject3 arrayobjects;			//数组对象中的元素的集合

	std::string arrayname;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};

ScpObject * __stdcall ScpArrayObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
#endif //_H_SCPARRAYOBJECT