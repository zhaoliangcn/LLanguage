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
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	/*
	获得当前数组对象的大小
	*/
	ULONG GetSize();
	/*
	在当前数组对象中添加一个元素
	*/
	BOOL AddElement(std::wstring elementname,ScpObject * obj);
	BOOL AddElement(std::wstring elementname,ScpObjectSpace * objectSpace);
	BOOL SetElement(std::wstring elementname,ULONG elementindex,ScpObject * obj);
	BOOL SetElement(std::wstring elementname,ULONG elementindex,ScpObjectSpace * objectSpace);
	/*
	删除当前数组对象中的元素
	*/
	BOOL DeleteElement(std::wstring elementname);
	BOOL DeleteElement(ULONG elementindex);
	/*
	替换当前数组对象中的元素
	*/
	BOOL ReplaceElementObj(ScpObject * oldobj,ScpObject * obj);
	BOOL ReplaceElementObj(ULONG elementindex,ScpObject * obj);
	BOOL ReplaceElementObj(std::wstring elementname,ScpObject * obj);
	/*
	获取当前数组对象中的元素的对象指针
	*/
	ScpObject * GetElement(std::wstring elementname);
	ScpObject * GetElement(ULONG elementindex);
	/*
	获取当前数组对象中的元素的类型
	*/
	ScpObjectType GetElementType(std::wstring elementname);	
	ScpObjectType GetElementType(ULONG elementindex);
	/*
	获取当前数组对象中的元素的名字
	*/
	std::wstring GetElementName(ULONG elementindex);

	ULONG Max;
	ScpObjectType Elementtype;				//数组对象中的元素的类型（数组对象中的元素类型唯一）
	ScpUserObject3 arrayobjects;			//数组对象中的元素的集合

	std::wstring arrayname;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};

ScpObject * __stdcall ScpArrayObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
#endif //_H_SCPARRAYOBJECT