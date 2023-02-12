/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//结构体对象
*/
#ifndef _H_SCPSTRUCTOBJECT
#define _H_SCPSTRUCTOBJECT
#include "ScpObjectSpace.h"
#include "ScpObject.h"

class ScpStructObject :
	public ScpObject
{
public:
	ScpStructObject(void);
	~ScpStructObject(void);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);
	int AllocStructMemory();
	void FreeStructMemory();
	int GetBiggestMemberSize();
	int GetObjectSize(ScpObject * memberobj);
	int GetStructMemorySize();                                        //获得整个结构体占用的内存大小
	void * MemoryBlockAddress;                                        //结构体实际的内存位置
	BOOL FillMember(ScpObject * memberobj,int order);                 //将一个对象填入结构体的紧凑内存中
	BOOL GetMember(ScpObject * memberobj,int order);                  //从结构体的紧凑内存中提取一个对象
	int CalcMemberMemoryPosInStruct(ScpObject * memberobj,int order);//计算对象在结构体中需要占用的内存空间的位置，以字节为单位的偏移
	int bytealignment;                                                //字节对齐,1,2,4,8
	std::string Name;                                                //结构体的名字
	VTSTRINGS Boday;                                                  //原始的结构体定义代码
	VTSTRINGS MemberNameList;                                         //有序的成员名列表  
	VTPOBJECTS MemberObjects;                                         //成员对象数组
	VTINT MemberSizeInStruct;
	VTINT MemberPosInStruct;
	ScpObjectSpace StructObjectSpace;
	int biggestmembersize;
	int structsize;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};

class ScpStructInstanceObject :public ScpStructObject
{
public:
	ScpStructInstanceObject(void)
	{
		objecttype = ObjStructInstance;
	}
	~ScpStructInstanceObject(void)
	{

	}
};

#endif //_H_SCPSTRUCTOBJECT