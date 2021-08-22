/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//����������Ա����֧��
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
	��õ�ǰ�������Ĵ�С
	*/
	ULONG GetSize();
	/*
	�ڵ�ǰ������������һ��Ԫ��
	*/
	BOOL AddElement(std::wstring elementname,ScpObject * obj);
	BOOL AddElement(std::wstring elementname,ScpObjectSpace * objectSpace);
	BOOL SetElement(std::wstring elementname,ULONG elementindex,ScpObject * obj);
	BOOL SetElement(std::wstring elementname,ULONG elementindex,ScpObjectSpace * objectSpace);
	/*
	ɾ����ǰ��������е�Ԫ��
	*/
	BOOL DeleteElement(std::wstring elementname);
	BOOL DeleteElement(ULONG elementindex);
	/*
	�滻��ǰ��������е�Ԫ��
	*/
	BOOL ReplaceElementObj(ScpObject * oldobj,ScpObject * obj);
	BOOL ReplaceElementObj(ULONG elementindex,ScpObject * obj);
	BOOL ReplaceElementObj(std::wstring elementname,ScpObject * obj);
	/*
	��ȡ��ǰ��������е�Ԫ�صĶ���ָ��
	*/
	ScpObject * GetElement(std::wstring elementname);
	ScpObject * GetElement(ULONG elementindex);
	/*
	��ȡ��ǰ��������е�Ԫ�ص�����
	*/
	ScpObjectType GetElementType(std::wstring elementname);	
	ScpObjectType GetElementType(ULONG elementindex);
	/*
	��ȡ��ǰ��������е�Ԫ�ص�����
	*/
	std::wstring GetElementName(ULONG elementindex);

	ULONG Max;
	ScpObjectType Elementtype;				//��������е�Ԫ�ص����ͣ���������е�Ԫ������Ψһ��
	ScpUserObject3 arrayobjects;			//��������е�Ԫ�صļ���

	std::wstring arrayname;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};

ScpObject * __stdcall ScpArrayObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
#endif //_H_SCPARRAYOBJECT