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
#include "ffi.h"
#ifdef _WIN32

#else
#include <sys/types.h>
#include <stdint.h>
#endif
class CScriptEngine;

class ScpCFunctionObject:public ScpObject
{
public:




	ScpCFunctionObject();
	~ScpCFunctionObject();
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	void * GetApiAddress(std::string CDLLName,std::string CFunctionName);
	BOOL MakeCFunctionInterface(std::string myFunctionName,std::string DllName,std::string myCFunctionName,std::string ReturnType,VTPARAMETERS Parameters);
	ScpCObject * MakeParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,int paramindex);
	BOOL CopyBackParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,ScpCObject * param,int paramindex);
	ScpCObject * MakeRetValueObject(std::string retvalue,ScpObjectSpace * objectSpace);
	BOOL CopyBackRetValueObject(std::string retvalue,ScpObjectSpace * objectSpace,ScpCObject *retValueObj);
	BOOL Call(std::string retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace);
	BOOL AsmCall(std::string retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace);


	VTPARAMETERS FormalParameters;	
	std::string FunctionName;
	std::string CFunctionName;
	std::string CDllName;
	std::string CReturnType;


typedef	ffi_status (*func_ffi_prep_cif)(ffi_cif* cif,
		ffi_abi abi,
		unsigned int nargs,
		ffi_type* rtype,
		ffi_type** atypes);
func_ffi_prep_cif pffi_prep_cif;
typedef	void (*func_ffi_call)(ffi_cif* cif,
		void (*fn)(void),
		void* rvalue,
		void** avalue);
func_ffi_call pffi_call;
	ffi_type* pffi_type_void;
	ffi_type* pffi_type_uint8;
	ffi_type* pffi_type_sint8;
	ffi_type* pffi_type_uint16;
	ffi_type* pffi_type_sint16;
	ffi_type* pffi_type_uint32;
	ffi_type* pffi_type_sint32;
	ffi_type* pffi_type_uint64;
	ffi_type* pffi_type_sint64;
	ffi_type* pffi_type_float;
	ffi_type* pffi_type_double;
	ffi_type* pffi_type_pointer;

	
	int ffi;

};
#endif //_H_SCPCFUNCTION