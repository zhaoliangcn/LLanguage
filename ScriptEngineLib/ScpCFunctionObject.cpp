/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpCFunctionObject.h"
#include "ScpIntObject.h"
#include "ScriptEngine.h"
ScpCFunctionObject::ScpCFunctionObject()
{
	objecttype = ObjCFunction;
}
ScpCFunctionObject::~ScpCFunctionObject()
{
}
void ScpCFunctionObject::Show(CScriptEngine * engine)
{
	engine->PrintError(ToString());
}
ScpObject * ScpCFunctionObject::Clone(std::wstring strObjName)
{
	return NULL;
}	
std::wstring ScpCFunctionObject::ToString()
{
	std::wstring temp;
	std::wstring tempfuncbody =FunctionName;
	tempfuncbody+=L"(";
	for(ITPARAMETERS it =FormalParameters.begin();it!=FormalParameters.end();it++)
	{
		std::wstring temp = *it;
		tempfuncbody+=temp;
		tempfuncbody+=L",";
	}
	tempfuncbody=tempfuncbody.substr(0,tempfuncbody.length()-1);
	tempfuncbody+=L")\n";
	temp=tempfuncbody;
	return temp;
}
void ScpCFunctionObject::Release() 
{
	delete this;
}
bool ScpCFunctionObject::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpCFunctionObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void * ScpCFunctionObject::GetApiAddress(std::wstring CDLLName,std::wstring CFunctionName)
{
	void * addr=0;

#ifdef _WIN32
	HMODULE hmodule = LoadLibraryW(CDLLName.c_str());
	if(hmodule)
	{
		addr = (void *)GetProcAddress(hmodule,STDSTRINGEXT::WToA(CFunctionName).c_str());			
	}
#else

#endif
	return addr;
}
BOOL ScpCFunctionObject::MakeCFunctionInterface(std::wstring myFunctionName,std::wstring DllName,std::wstring myCFunctionName,std::wstring ReturnType,VTPARAMETERS Parameters)
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
	std::wstring formaparam1=FormalParameters.at(paramindex);
	std::wstring realparam1=RealParameters.at(paramindex);
	ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(formaparam1.c_str());
	if(type==ObjCInt32)
	{

		if(objectSpace->GetType(realparam1)==ObjNumber)
		{
			param1=new ScpObjCInt32;
			ScpIntObject * obj1=(ScpIntObject *)objectSpace->FindObject(RealParameters.at(paramindex));
			((ScpObjCInt32*)param1)->Value=obj1->value;
		}
		else if(objectSpace->GetType(realparam1)==ObjCInt32)
		{
			return (ScpObjCInt32*)objectSpace->FindObject(realparam1);
		}
	}
	else if(type==ObjHandle)
	{
		
		if(objectSpace->GetType(realparam1)==ObjHandle)
		{
			param1=(ScpObjHandle*)objectSpace->FindObject(realparam1);
		}
	}
	else if(type==ObjPointerofChar)
	{
		if(objectSpace->GetType(realparam1)==ObjPointerofChar)
		{
			param1=(ScpObjPointerofChar*)objectSpace->FindObject(realparam1);
		}
	}
	else if(type==ObjPointerofWchar)
	{
		if(objectSpace->GetType(realparam1)==ObjPointerofWchar)
		{
			param1=(ScpObjPointerofWchar*)objectSpace->FindObject(realparam1);
		}
	}
	else if(type==ObjUnsignedInt32)
	{
		if(objectSpace->GetType(realparam1)==ObjUnsignedInt32)
		{
			param1=(ScpObjUnsignedInt32*)objectSpace->FindObject(realparam1);
		}
	}
	return param1;
}
BOOL ScpCFunctionObject::CopyBackParamObject(VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace,ScpCObject * param,int paramindex)
{
	if(objectSpace->GetType(FormalParameters.at(paramindex))==ObjCInt32)
	{
		if(objectSpace->GetType(RealParameters.at(paramindex))==ObjNumber)
		{
			ScpIntObject * obj1=(ScpIntObject *)objectSpace->FindObject(RealParameters.at(paramindex));
			obj1->value=((ScpObjCInt32*)param)->Value;
			delete param;
		}
		else if(objectSpace->GetType(RealParameters.at(paramindex))==ObjCInt32)
		{

		}
	}
	return TRUE;
}
ScpCObject * ScpCFunctionObject::MakeRetValueObject(std::wstring retvalue,ScpObjectSpace * objectSpace)
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
BOOL ScpCFunctionObject::CopyBackRetValueObject(std::wstring retvalue,ScpObjectSpace * objectSpace,ScpCObject *retValueObj)
{
	if(ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str())==ObjHandle)
	{
		if(objectSpace->GetType(retvalue.c_str())==ObjHandle)
		{
			
		}
	}
	return TRUE;

}
BOOL ScpCFunctionObject::Call(std::wstring retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace)
{
	if(FormalParameters.size()==RealParameters.size())
	{
		if(RealParameters.size()==0)
		{			
			ScpCObject *retValueObj;
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str());
			if(type==ObjHandle)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);
				STDAPICAll0 api=(STDAPICAll0)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjHandle*)retValueObj)->Value=(HANDLE)api();
			}	
			if(type==ObjCInt32)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);	
				STDAPICAll0 api=(STDAPICAll0)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjCInt32*)retValueObj)->Value=api();
			}
			if(type==ObjVoid)
			{
				STDAPICALL0_NORET api=(STDAPICALL0_NORET)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				api();
			}
			CopyBackRetValueObject(retvalue,objectSpace,retValueObj);			
		}
		if(RealParameters.size()==1)
		{
			ScpCObject * param1=MakeParamObject(RealParameters,objectSpace,0);
			ScpCObject *retValueObj;
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str());
			if(type==ObjHandle)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);
				STDAPICAll1 api=(STDAPICAll1)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjHandle*)retValueObj)->Value=(HANDLE)api(param1->GetValueAddress());
			}	
			if(type==ObjCInt32)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);	
				STDAPICAll1 api=(STDAPICAll1)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjCInt32*)retValueObj)->Value=api(param1->GetValueAddress());
			}
			if(type==ObjVoid)
			{
				STDAPICALL1_NORET api=(STDAPICALL1_NORET)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				api(param1->GetValueAddress());
			}
			CopyBackRetValueObject(retvalue,objectSpace,retValueObj);
			CopyBackParamObject(RealParameters,objectSpace,param1,0);
		}
		if(RealParameters.size()==2)
		{
			ScpCObject * param1=MakeParamObject(RealParameters,objectSpace,0);
			ScpCObject * param2=MakeParamObject(RealParameters,objectSpace,1);
			ScpCObject *retValueObj;
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str());
			if(type==ObjHandle)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);
				STDAPICAll2 api=(STDAPICAll2)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjHandle*)retValueObj)->Value=(HANDLE)api(param1->GetValueAddress(),param2->GetValueAddress());
			}	
			if(type==ObjCInt32)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);	
				STDAPICAll2 api=(STDAPICAll2)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjCInt32*)retValueObj)->Value=api(param1->GetValueAddress(),param2->GetValueAddress());
			}
			if(type==ObjVoid)
			{
				STDAPICALL2_NORET api=(STDAPICALL2_NORET)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				api(param1->GetValueAddress(),param2->GetValueAddress());
			}
			CopyBackRetValueObject(retvalue,objectSpace,retValueObj);
			CopyBackParamObject(RealParameters,objectSpace,param1,0);
			CopyBackParamObject(RealParameters,objectSpace,param2,1);
		}
		else if(RealParameters.size()==3)
		{
			ScpCObject * param1=MakeParamObject(RealParameters,objectSpace,0);
			ScpCObject * param2=MakeParamObject(RealParameters,objectSpace,1);
			ScpCObject * param3=MakeParamObject(RealParameters,objectSpace,2);
			ScpCObject *retValueObj;
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str());
			if(type==ObjHandle)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);
				STDAPICAll3 api=(STDAPICAll3)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjHandle*)retValueObj)->Value=(HANDLE)api(param1->GetValueAddress(),param2->GetValueAddress(),param3->GetValueAddress());
			}	
			if(type==ObjCInt32)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);					
				STDAPICAll3 api=(STDAPICAll3)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
				((ScpObjCInt32*)retValueObj)->Value=api(param1->GetValueAddress(),param2->GetValueAddress(),param3->GetValueAddress());
			}
			CopyBackRetValueObject(retvalue,objectSpace,retValueObj);
			CopyBackParamObject(RealParameters,objectSpace,param1,0);
			CopyBackParamObject(RealParameters,objectSpace,param2,1);
			CopyBackParamObject(RealParameters,objectSpace,param3,2);
		}
		else if(RealParameters.size()==4)
		{
			ScpCObject * param1=MakeParamObject(RealParameters,objectSpace,0);
			ScpCObject * param2=MakeParamObject(RealParameters,objectSpace,1);
			ScpCObject * param3=MakeParamObject(RealParameters,objectSpace,2);
			ScpCObject * param4=MakeParamObject(RealParameters,objectSpace,3);
			ScpCObject *retValueObj;
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(CReturnType.c_str());
			if(type==ObjHandle)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);
				STDAPICAll4 api=(STDAPICAll4)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
					((ScpObjHandle*)retValueObj)->Value=(HANDLE)api(param1->GetValueAddress(),param2->GetValueAddress(),param3->GetValueAddress(),param4->GetValueAddress());
			}	
			if(type==ObjCInt32)
			{
				retValueObj=MakeRetValueObject(retvalue,objectSpace);	
				STDAPICAll4 api=(STDAPICAll4)GetApiAddress(CDllName,CFunctionName);
				if(api!=NULL)
					((ScpObjCInt32*)retValueObj)->Value=api(param1->GetValueAddress(),param2->GetValueAddress(),param3->GetValueAddress(),param4->GetValueAddress());
			}
			CopyBackRetValueObject(retvalue,objectSpace,retValueObj);
			CopyBackParamObject(RealParameters,objectSpace,param1,0);
			CopyBackParamObject(RealParameters,objectSpace,param2,1);
			CopyBackParamObject(RealParameters,objectSpace,param3,2);
			CopyBackParamObject(RealParameters,objectSpace,param3,3);
		}
	}
	return TRUE;
}
BOOL ScpCFunctionObject::AsmCall(std::wstring retvalue,VTPARAMETERS& RealParameters,ScpObjectSpace * objectSpace)
{

	return FALSE;
}
