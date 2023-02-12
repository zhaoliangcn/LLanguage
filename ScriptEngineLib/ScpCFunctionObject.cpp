/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpCFunctionObject.h"
#include "ScpIntObject.h"
#include "ScriptEngine.h"
#include "../Common/commonutil.hpp"

ScpCFunctionObject::ScpCFunctionObject()
{
	objecttype = ObjCFunction;
	ffi = 1;
#ifdef _WIN32
	HMODULE hmodule = LoadLibraryA("Libffi.dll");
	if (hmodule)
	{
		pffi_prep_cif =(func_ffi_prep_cif) GetProcAddress(hmodule, "ffi_prep_cif");
		if (!pffi_prep_cif)
		{
			ffi = 0;
		}
		pffi_call =(func_ffi_call) GetProcAddress(hmodule, "ffi_call");
		if (!pffi_call)
		{
			ffi = 0;
		}
		pffi_type_void = (ffi_type*)GetProcAddress(hmodule, "ffi_type_void");
		if (!pffi_type_void)
		{
			ffi = 0;
		}
		pffi_type_uint8 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_uint8");
		if (!pffi_type_uint8)
		{
			ffi = 0;
		}			
		pffi_type_sint8 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_sint8");
		if (!pffi_type_sint8)
		{
			ffi = 0;
		}
		pffi_type_uint16 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_uint16");
		if (!pffi_type_uint16)
		{
			ffi = 0;
		}		
		pffi_type_sint16 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_sint16");
		if (!pffi_type_sint16)
		{
			ffi = 0;
		}
		pffi_type_uint32 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_uint32");
		if (!pffi_type_uint32)
		{
			ffi = 0;
		}
		pffi_type_sint32 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_sint32");
		if (!pffi_type_sint32)
		{
			ffi = 0;
		}
		pffi_type_uint64 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_uint64");
		if (!pffi_type_uint64)
		{
			ffi = 0;
		}
		pffi_type_sint64 = (ffi_type*)GetProcAddress(hmodule, "ffi_type_sint64");
		if (!pffi_type_sint64)
		{
			ffi = 0;
		}
		pffi_type_float = (ffi_type*)GetProcAddress(hmodule, "ffi_type_float");
		if (!pffi_type_float)
		{
			ffi = 0;
		}
		pffi_type_double = (ffi_type*)GetProcAddress(hmodule, "ffi_type_double");
		if (!pffi_type_double)
		{
			ffi = 0;
		}

		pffi_type_pointer = (ffi_type*)GetProcAddress(hmodule, "ffi_type_pointer");
		if (!pffi_type_pointer)
		{
			ffi = 0;
		}

		
	}
#else
	pffi_prep_cif = (func_ffi_prep_cif)dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_prep_cif");
	if (!pffi_prep_cif)
	{
		ffi = 0;
	}
	pffi_call =(func_ffi_call) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_call");
	if (!pffi_call)
	{
		ffi = 0;
	}
	pffi_type_void = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_void");
	if (!pffi_type_void)
	{
		ffi = 0;
	}
	pffi_type_uint8 = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_uint8");
	if (!pffi_type_uint8)
	{
		ffi = 0;
	}
	pffi_type_sint8 = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_sint8");
	if (!pffi_type_sint8)
	{
		ffi = 0;
	}
	pffi_type_uint16 = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_uint16");
	if (!pffi_type_uint16)
	{
		ffi = 0;
	}
	pffi_type_sint16 = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_sint16");
	if (!pffi_type_sint16)
	{
		ffi = 0;
	}
	pffi_type_uint32 =  (ffi_type*)dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_uint32");
	if (!pffi_type_uint32)
	{
		ffi = 0;
	}
	pffi_type_sint32 =  (ffi_type*)dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_sint32");
	if (!pffi_type_sint32)
	{
		ffi = 0;
	}
	pffi_type_uint64 = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_uint64");
	if (!pffi_type_uint64)
	{
		ffi = 0;
	}
	pffi_type_sint64 = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_sint64");
	if (!pffi_type_sint64)
	{
		ffi = 0;
	}
		
	pffi_type_float = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_float");
	if (!pffi_type_float)
	{
		ffi = 0;
	}
	pffi_type_double = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_double");
	if (!pffi_type_double)
	{
		ffi = 0;
	}
	pffi_type_pointer = (ffi_type*) dlsym(dlopen("libffi.so", RTLD_LAZY), "ffi_type_pointer");
	if (!pffi_type_pointer)
	{
		ffi = 0;
	}
	

#endif

}
ScpCFunctionObject::~ScpCFunctionObject()
{
}
void ScpCFunctionObject::Show(CScriptEngine * engine)
{
	engine->PrintError(ToString());
}
ScpObject * ScpCFunctionObject::Clone(std::string strObjName)
{
	return NULL;
}	
std::string ScpCFunctionObject::ToString()
{
	std::string temp;
	std::string tempfuncbody =FunctionName;
	tempfuncbody+="(";
	for(ITPARAMETERS it =FormalParameters.begin();it!=FormalParameters.end();it++)
	{
		std::string temp = *it;
		tempfuncbody+=temp;
		tempfuncbody+=",";
	}
	tempfuncbody=tempfuncbody.substr(0,tempfuncbody.length()-1);
	tempfuncbody+=")\n";
	temp=tempfuncbody;
	return temp;
}
void ScpCFunctionObject::Release() 
{
	delete this;
}
bool ScpCFunctionObject::IsInnerFunction(std::string & functionname)
{
	return false;
}
ScpObject * ScpCFunctionObject::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void * ScpCFunctionObject::GetApiAddress(std::string CDLLName,std::string CFunctionName)
{
	void * addr=0;
	StringStripQuote(CDLLName);
	StringStripQuote(CFunctionName);
#ifdef _WIN32
	HMODULE hmodule = LoadLibraryA(CDLLName.c_str());
	if(hmodule)
	{
		addr = (void *)GetProcAddress(hmodule,CFunctionName.c_str());			
	}
#else
	addr = dlsym(dlopen(CDLLName.c_str(),RTLD_LAZY),CFunctionName.c_str());

#endif
	return addr;
}
BOOL ScpCFunctionObject::MakeCFunctionInterface(std::string myFunctionName,std::string DllName,std::string myCFunctionName,std::string ReturnType,VTPARAMETERS Parameters)
{
	FunctionName=myFunctionName;
	CFunctionName = myCFunctionName;
	CReturnType=ReturnType;
	CDllName=DllName;
	FormalParameters=Parameters;
	return TRUE;
}
ScpCObject * ScpCFunctionObject::MakeParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,int paramindex)
{
	ScpCObject * param1;
	std::string formaparam1=FormalParameters.at(paramindex);
	std::string realparam1=RealParameters.at(paramindex);
	ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(formaparam1.c_str());
	if(type== objectSpace->GetType(realparam1))
	{
		param1 =(ScpCObject*)objectSpace->FindObject(realparam1);
	}
	return param1;
}
BOOL ScpCFunctionObject::CopyBackParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,ScpCObject * param,int paramindex)
{
	if(objectSpace->GetType(FormalParameters.at(paramindex))==ObjCInt32)
	{
		if(objectSpace->GetType(RealParameters.at(paramindex))==ObjCInt32)
		{

		}
	}
	return TRUE;
}
ScpCObject * ScpCFunctionObject::MakeRetValueObject(std::string retvalue,ScpObjectSpace * objectSpace)
{
	ScpCObject *retValueObj;
	ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str());
	if(type==ObjHandle)
	{
		if(objectSpace->GetType(retvalue.c_str())==ObjHandle)
		{
			retValueObj=(ScpObjHandle*)objectSpace->FindObject(retvalue);
		}
	}
	else if(type==ObjCInt32)
	{
		if(objectSpace->GetType(retvalue.c_str())==ObjCInt32)
		{
			retValueObj=(ScpObjCInt32*)objectSpace->FindObject(retvalue);
		}
	}

	return retValueObj;


}
BOOL ScpCFunctionObject::CopyBackRetValueObject(std::string retvalue,ScpObjectSpace * objectSpace,ScpCObject *retValueObj)
{
	if(ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str())==ObjHandle)
	{
		if(objectSpace->GetType(retvalue.c_str())==ObjHandle)
		{
			
		}
	}
	return TRUE;

}

BOOL ScpCFunctionObject::Call(std::string retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace)
{
	if(FormalParameters.size()==RealParameters.size())
	{
		ScpCObject* retValueObj;
		void* api = GetApiAddress(CDllName, CFunctionName);
		if (ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str()) != ObjVoid)
		{
			retValueObj = MakeRetValueObject(retvalue, objectSpace);
		}
		if (api != NULL && ffi==1)
		{
			void (*functionPtr)();
			functionPtr = (void (*)())api;
			int argCount = RealParameters.size();

			ffi_type** ffiArgTypes = (ffi_type**)malloc(sizeof(ffi_type*) * argCount);

			void** ffiArgs = (void**)malloc(sizeof(void*) * argCount);
			for (int i = 0; i < argCount; i++)
			{
				if (ObjPointerofChar == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_pointer;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					*(PADDRESS*)ffiArgPtr = param->GetValueAddress();
					ffiArgs[i] = ffiArgPtr;
				}
				else if(ObjCInt32 == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_sint32;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					*(int*)ffiArgPtr = ((ScpObjCInt32*)param)->Value;
					ffiArgs[i] = ffiArgPtr;
				}
				else if(ObjUnsignedInt32 == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_uint32;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					*(unsigned int*)ffiArgPtr = ((ScpObjUnsignedInt32*)param)->Value;
					ffiArgs[i] = ffiArgPtr;
				}
				else if(ObjPointerofWchar == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_pointer;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					void* p = (void*)param->GetValueAddress();
					ffiArgs[i] = &p;
				}
				else if(ObjPointerofChar == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_pointer;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					void* p = (void*)param->GetValueAddress();
					ffiArgs[i] = &p;
				}
				else if(ObjHandle == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_pointer;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					void* p = (void*)param->GetValueAddress();
					ffiArgs[i] = &p;
				}
				else if(ObjPointer == ScpGlobalObject::GetInstance()->GetType(FormalParameters.at(i).c_str()))
				{
					ScpCObject* param = MakeParamObject(RealParameters, objectSpace, i);
					ffiArgTypes[i] = pffi_type_pointer;
					void* ffiArgPtr = malloc(ffiArgTypes[i]->size);
					void* p = (void*)param->GetValueAddress();
					ffiArgs[i] = &p;
				}
			}

			ffi_cif cif;
			ffi_type* returnFfiType = NULL;
			if (ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str()) == ObjVoid)
			{
				returnFfiType = pffi_type_void;
			}
			else if (ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str()) == ObjCInt32)
			{
				returnFfiType = pffi_type_sint32;
			}
			else if (ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str()) == ObjHandle)
			{
				returnFfiType = pffi_type_pointer;
			}
			ffi_status ffiPrepStatus = pffi_prep_cif(&cif, FFI_DEFAULT_ABI, (unsigned int)argCount, returnFfiType, ffiArgTypes);

			if (ffiPrepStatus == FFI_OK) {

				void* returnPtr = NULL;
				if (returnFfiType->size) {
					returnPtr = malloc(returnFfiType->size);
				}

				pffi_call(&cif, functionPtr, returnPtr, ffiArgs);

				if (ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str()) == ObjCInt32)
				{
					((ScpObjCInt32*)retValueObj)->Value = *(int*)returnPtr;
				}
				else if (ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str()) == ObjHandle)
				{
					((ScpObjHandle*)retValueObj)->Value =*(HANDLE*)returnPtr;
				}

			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ScpCFunctionObject::AsmCall(std::string retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace)
{

	return FALSE;
}
