/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//�ṹ�����
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
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);
	int AllocStructMemory();
	void FreeStructMemory();
	int GetBiggestMemberSize();
	int GetObjectSize(ScpObject * memberobj);
	int GetStructMemorySize();                                        //��������ṹ��ռ�õ��ڴ��С
	void * MemoryBlockAddress;                                        //�ṹ��ʵ�ʵ��ڴ�λ��
	BOOL FillMember(ScpObject * memberobj,int order);                 //��һ����������ṹ��Ľ����ڴ���
	BOOL GetMember(ScpObject * memberobj,int order);                  //�ӽṹ��Ľ����ڴ�����ȡһ������
	int CalcMemberMemoryPosInStruct(ScpObject * memberobj,int order);//��������ڽṹ������Ҫռ�õ��ڴ�ռ��λ�ã����ֽ�Ϊ��λ��ƫ��
	int bytealignment;                                                //�ֽڶ���,1,2,4,8
	std::wstring Name;                                                //�ṹ�������
	VTSTRINGS Boday;                                                  //ԭʼ�Ľṹ�嶨�����
	VTSTRINGS MemberNameList;                                         //����ĳ�Ա���б�  
	VTPOBJECTS MemberObjects;                                         //��Ա��������
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