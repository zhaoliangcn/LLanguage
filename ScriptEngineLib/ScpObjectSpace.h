/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPOBJECTSPACE
#define _H_SCPOBJECTSPACE
#include "ScpObject.h"
#include "ScpUserObject.h"
#include "NumberHelp.h"
#include "ScpIntObject.h"
typedef enum _SPACETYPE
{
	Space_Unkonwn,
	Space_Global,	//全局名字空间
	Space_Class,	//类的名字空间
	Space_Function,	//函数的名字空间
	Space_While,	//循环语句的名字空间
	Space_Block,	//代码块的名字空间（未实现）
	Space_Struct,	//结构体的名字空间
	Space_If,		//条件语句的名字空间
}SPACETYPE;

class ScpObjectSpace
{
public:
	ScpObjectSpace(void);
	~ScpObjectSpace(void);
	/*
	判断一个名字空间对象是否是自己的父名字空间对象
	*/
	BOOL IsMyParentSpace(ScpObjectSpace * space);
	/*
	按照对象名字查找一个对象，如果当前名字空间中找不到，就在父空间中查找，直到最顶层空间
	*/
    ScpObject * FindObject(const std::wstring& objname);
	/*
	在全局名字空间中查找一个对象
	*/
    ScpObject * FindGlobalObject(const std::wstring& objname);
	/*
	在当前名字空间中查找一个对象
	*/
    ScpObject * FindLocalObject(const std::wstring& objname);
	/*
	根据下标格式的表元素，在当前名字空间中查找对应的对象
	table[0]
	table[element1]
	*/
    ScpObject * FindTableElement(const std::wstring& objname);
	/*
	根据下标格式的数组元素，在当前名字空间中查找对应的对象
	table[0]
	table[element1]
	*/
    ScpObject * FindArrayElement(const std::wstring& objname);
	/*
	在当前名字空间中查找类的成员变量
	classname.classmember
	*/
    ScpObject * FindClassMemberVariable(const std::wstring& objname);
	/*
	在当前名字空间中查找结构体的成员
	*/
    ScpObject * FindStructMemberVariable(const std::wstring& objname);

    ScpObject * FindClassOrStructMemberVariable(const std::wstring& objname);
	/*
	获取对象所属名字空间的名字
	*/
	std::wstring GetObjectSpace(std::wstring objname);
	/*
	将一个对象映射到当前名字空间
	*/
	BOOL AddObject(std::wstring strObjname,ScpObject *obj,std::wstring scope=L"");
	/*
	从当前名字空间中删除一个对象
	*/
	void EraseObject(std::wstring strObjname);
	void EraseObject(ScpObject *Obj);
	/*
	从当前名字空间中查找一个对象，返回这个对象的类型
	*/
	ScpObjectType GetType(std::wstring strObjname);
	std::wstring GetObjectName(ScpObject * obj);
	std::wstring GetObjectNameR(ScpObject * obj);

	ScpObject * AcquireTempObject(ScpObjectType type);
	void ReleaseTempObject(ScpObject * tempobj);
	void DestroyTempObjects();

	ScpObject * AcquireTempObjectUni(VTPOBJECTS &TempObjects);
	void ReleaseTempObjectUni(ScpObject * tempobj, VTPOBJECTS &TempObjects);
	void DestroyTempObjectsUni(VTPOBJECTS &TempObjects);

	VTPOBJECTS UnusedTempObjects;
	VTPOBJECTS UnusedTemp_Int_Objects;
	VTPOBJECTS UnusedTemp_Double_Objects;
	VTPOBJECTS UnusedTemp_BigInt_Objects;
	VTPOBJECTS UnusedTemp_String_Objects;
	VTPOBJECTS UnusedTemp_ExpressionNode_Objects;
	

	std::wstring GetNewTempObjectName();

	/*
	//从当前名字空间移动对象到另一个名字空间
	*/
	bool MoveToSpace(ScpObject * obj, ScpObjectSpace * space);
	/*
	//找到全局名字空间
	*/
	ScpObjectSpace * GetGlobalSpace();
	ScpObjectSpace * FindObject_ObjectSpace(ScpObject* obj);



	ScpObjectSpace *parentspace;		//指向父名字空间的指针
	ScpUserObject userobject;			//当前名字空间中保存的对象
	std::wstring spacename;				//当前名字空间的名字
	SPACETYPE ObjectSpaceType;			//当前名字空间的类型
	ScpObject * belongto;				//当前名字空间的属主，如属于一个函数对象或属于一个循环语句对象


	int breakingout;					//针对循环语句对象的名字空间，如果在循环语句中置位，则跳出循环语句
	int continuewhile;					//针对循环语句对象的名字空间，如果在循环语句对象中置位，则回到循环语句的起始位置重新开始下一个循环
	
	int enddepths;//结束语句的深度

	ULONG lastcommand;
	std::wstring LastTempObjectName;
	int LastTempObjAppendix;
	int lastTestResult;

	
};
#endif //_H_SCPOBJECTSPACE