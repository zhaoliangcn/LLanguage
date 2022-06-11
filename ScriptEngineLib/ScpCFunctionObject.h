/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//C语言函数对象
//用于实现对C函数的调用和绑定到L脚本语言的函数
*/
#ifndef _H_SCPCFUNCTION
#define _H_SCPCFUNCTION
#include "ScpObject.h"
#include "ScpObjectSpace.h"
#include "ScpCObject.h"
class CScriptEngine;

class ScpCFunctionObject:public ScpObject
{
public:
#ifdef _M_AMD64
	typedef unsigned __int64 QWORD;
	typedef QWORD (__stdcall *STDAPICAll0)();
	typedef QWORD (__stdcall *STDAPICAll1)(QWORD);
	typedef QWORD (__stdcall *STDAPICAll2)(QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll3)(QWORD, QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll4)(QWORD, QWORD, QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll5)(QWORD, QWORD, QWORD, QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll6)(QWORD, QWORD, QWORD, QWORD, QWORD, QWORD);


	typedef void (__stdcall *STDAPICALL0_NORET)();
	typedef void (__stdcall *STDAPICALL1_NORET)(QWORD);
	typedef void (__stdcall *STDAPICALL2_NORET)(QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll3_NORET)(QWORD, QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll4_NORET)(QWORD, QWORD, QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll5_NORET)(QWORD, QWORD, QWORD, QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll6_NORET)(QWORD, QWORD, QWORD, QWORD, QWORD, QWORD);
#else
#ifdef Linux64
	typedef unsigned long long QWORD;
	typedef QWORD (__stdcall *STDAPICAll0)();
	typedef QWORD (__stdcall *STDAPICAll1)(QWORD);
	typedef QWORD (__stdcall *STDAPICAll2)(QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll3)(QWORD, QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll4)(QWORD, QWORD, QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll5)(QWORD, QWORD, QWORD, QWORD, QWORD);
	typedef QWORD (__stdcall *STDAPICAll6)(QWORD, QWORD, QWORD, QWORD, QWORD, QWORD);


	typedef void (__stdcall *STDAPICALL0_NORET)();
	typedef void (__stdcall *STDAPICALL1_NORET)(QWORD);
	typedef void (__stdcall *STDAPICALL2_NORET)(QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll3_NORET)(QWORD, QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll4_NORET)(QWORD, QWORD, QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll5_NORET)(QWORD, QWORD, QWORD, QWORD, QWORD);
	typedef void (__stdcall *STDAPICAll6_NORET)(QWORD, QWORD, QWORD, QWORD, QWORD, QWORD);
#else
	typedef DWORD(__stdcall *STDAPICAll0)();
	typedef DWORD(__stdcall *STDAPICAll1)(DWORD);
	typedef DWORD(__stdcall *STDAPICAll2)(DWORD, DWORD);
	typedef DWORD(__stdcall *STDAPICAll3)(DWORD, DWORD, DWORD);
	typedef DWORD(__stdcall *STDAPICAll4)(DWORD, DWORD, DWORD, DWORD);
	typedef DWORD(__stdcall *STDAPICAll5)(DWORD, DWORD, DWORD, DWORD, DWORD);
	typedef DWORD(__stdcall *STDAPICAll6)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);


	typedef void(__stdcall *STDAPICALL0_NORET)();
	typedef void(__stdcall *STDAPICALL1_NORET)(DWORD);
	typedef void(__stdcall *STDAPICALL2_NORET)(DWORD, DWORD);
	typedef void(__stdcall *STDAPICAll3_NORET)(DWORD, DWORD, DWORD);
	typedef void(__stdcall *STDAPICAll4_NORET)(DWORD, DWORD, DWORD, DWORD);
	typedef void(__stdcall *STDAPICAll5_NORET)(DWORD, DWORD, DWORD, DWORD, DWORD);
	typedef void(__stdcall *STDAPICAll6_NORET)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
#endif
#endif
	ScpCFunctionObject();
	~ScpCFunctionObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	void * GetApiAddress(std::wstring CDLLName,std::wstring CFunctionName);
	BOOL MakeCFunctionInterface(std::wstring myFunctionName,std::wstring DllName,std::wstring myCFunctionName,std::wstring ReturnType,VTPARAMETERS Parameters);
	ScpCObject * MakeParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,int paramindex);
	BOOL CopyBackParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,ScpCObject * param,int paramindex);
	ScpCObject * MakeRetValueObject(std::wstring retvalue,ScpObjectSpace * objectSpace);
	BOOL CopyBackRetValueObject(std::wstring retvalue,ScpObjectSpace * objectSpace,ScpCObject *retValueObj);
	BOOL Call(std::wstring retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace);
	BOOL AsmCall(std::wstring retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace);


	VTPARAMETERS FormalParameters;	
	std::wstring FunctionName;
	std::wstring CFunctionName;
	std::wstring CDllName;
	std::wstring CReturnType;
};
#endif //_H_SCPCFUNCTION
