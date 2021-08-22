/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//�������󣬺����βκ�ʵ�εİ󶨣���󣬺�����ĵ���
*/
#ifndef _H_SCPFUNCTIONOBJECT
#define _H_SCPFUNCTIONOBJECT

#include "ScpObjectSpace.h"
#include "ScriptEngine.h"
#include "NumberHelp.h"
#include "ScpExpressionBlock.h"
class CScriptEngine;
class ScpFunctionObject:public ScpObject
{
public:

	friend class CScriptEngine;

	ScpFunctionObject();
	~ScpFunctionObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	int Do(CScriptEngine *engine);	
	int BindParameters(CScriptEngine *engine);
	int UnBindParameters(CScriptEngine *engine);
	void ClearLocalObjects();
	int GetFormalParametersCount();
	std::wstring GetCloneName();
	VTSTRINGS Boday;
	VTPARAMETERS FormalParameters;
	VTPARAMETERS RealParameters;
	VTSTRINGS *pBoday;
	VTPARAMETERS *pFormalParameters;
	std::wstring Name;
	ScpObjectSpace * FunctionObjectSpace;
	bool iscloned;
	ScpObject * Result;
	ScpExpressionBlock *functionexpressionblock;
	unsigned char * ByteCode;
	int ByteCodeLength;
	//���ں����Ĳ�������δ֪��������Ҫ�ں���������ʱ�����ɺ������ֽ���
	//Ϊ��ʵ�ֺ����Ķ�̬�����ԶԲ�ͬ�Ĳ����������ɲ�ͬ���ֽ���
	ByteCodeMemoryStream bytecodemem_funcdef;
	ByteCodeMemoryStream bytecodemem_funcbody;
	//������ĳ�Ա���������ﱣ���������
	std::wstring parentobjectname;
	ScpObject * ParenObject;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};
#endif //_H_SCPFUNCTIONOBJECT