/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//�ն���
*/
#ifndef _H_SCPNULLOBJECT
#define _H_SCPNULLOBJECT
#include "ScpObject.h"
#include "ScpObject_uni.h"

//NullObjectֻ���������������ʱ��ռλ
class ScpNullObject :
	public ScpObject
{
public:
	ScpNullObject(void);
	~ScpNullObject(void);
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	ScpObject * parentObj;

	
};

#endif //_H_SCPNULLOBJECT