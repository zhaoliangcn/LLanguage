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
	Space_Global,	//ȫ�����ֿռ�
	Space_Class,	//������ֿռ�
	Space_Function,	//���������ֿռ�
	Space_While,	//ѭ���������ֿռ�
	Space_Block,	//���������ֿռ䣨δʵ�֣�
	Space_Struct,	//�ṹ������ֿռ�
	Space_If,		//�����������ֿռ�
}SPACETYPE;

class ScpObjectSpace
{
public:
	ScpObjectSpace(void);
	~ScpObjectSpace(void);
	/*
	�ж�һ�����ֿռ�����Ƿ����Լ��ĸ����ֿռ����
	*/
	BOOL IsMyParentSpace(ScpObjectSpace * space);
	/*
	���ն������ֲ���һ�����������ǰ���ֿռ����Ҳ��������ڸ��ռ��в��ң�ֱ�����ռ�
	*/
    ScpObject * FindObject(const std::wstring& objname);
	/*
	��ȫ�����ֿռ��в���һ������
	*/
    ScpObject * FindGlobalObject(const std::wstring& objname);
	/*
	�ڵ�ǰ���ֿռ��в���һ������
	*/
    ScpObject * FindLocalObject(const std::wstring& objname);
	/*
	�����±��ʽ�ı�Ԫ�أ��ڵ�ǰ���ֿռ��в��Ҷ�Ӧ�Ķ���
	table[0]
	table[element1]
	*/
    ScpObject * FindTableElement(const std::wstring& objname);
	/*
	�����±��ʽ������Ԫ�أ��ڵ�ǰ���ֿռ��в��Ҷ�Ӧ�Ķ���
	table[0]
	table[element1]
	*/
    ScpObject * FindArrayElement(const std::wstring& objname);
	/*
	�ڵ�ǰ���ֿռ��в�����ĳ�Ա����
	classname.classmember
	*/
    ScpObject * FindClassMemberVariable(const std::wstring& objname);
	/*
	�ڵ�ǰ���ֿռ��в��ҽṹ��ĳ�Ա
	*/
    ScpObject * FindStructMemberVariable(const std::wstring& objname);

    ScpObject * FindClassOrStructMemberVariable(const std::wstring& objname);
	/*
	��ȡ�����������ֿռ������
	*/
	std::wstring GetObjectSpace(std::wstring objname);
	/*
	��һ������ӳ�䵽��ǰ���ֿռ�
	*/
	BOOL AddObject(std::wstring strObjname,ScpObject *obj,std::wstring scope=L"");
	/*
	�ӵ�ǰ���ֿռ���ɾ��һ������
	*/
	void EraseObject(std::wstring strObjname);
	void EraseObject(ScpObject *Obj);
	/*
	�ӵ�ǰ���ֿռ��в���һ�����󣬷���������������
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
	//�ӵ�ǰ���ֿռ��ƶ�������һ�����ֿռ�
	*/
	bool MoveToSpace(ScpObject * obj, ScpObjectSpace * space);
	/*
	//�ҵ�ȫ�����ֿռ�
	*/
	ScpObjectSpace * GetGlobalSpace();
	ScpObjectSpace * FindObject_ObjectSpace(ScpObject* obj);



	ScpObjectSpace *parentspace;		//ָ�����ֿռ��ָ��
	ScpUserObject userobject;			//��ǰ���ֿռ��б���Ķ���
	std::wstring spacename;				//��ǰ���ֿռ������
	SPACETYPE ObjectSpaceType;			//��ǰ���ֿռ������
	ScpObject * belongto;				//��ǰ���ֿռ��������������һ���������������һ��ѭ��������


	int breakingout;					//���ѭ������������ֿռ䣬�����ѭ���������λ��������ѭ�����
	int continuewhile;					//���ѭ������������ֿռ䣬�����ѭ������������λ����ص�ѭ��������ʼλ�����¿�ʼ��һ��ѭ��
	
	int enddepths;//�����������

	ULONG lastcommand;
	std::wstring LastTempObjectName;
	int LastTempObjAppendix;
	int lastTestResult;

	
};
#endif //_H_SCPOBJECTSPACE