#include "ScpThreadObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../ScriptEngineLib/ScpFunctionObject.h"
#include "../ScriptEngineLib/ScpObjectNammes.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpObject * __stdcall ScpThreadObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters && paramters->size() == 3)
	{
		ScpThreadObject * thread = new ScpThreadObject();
		if (thread)
		{
			thread->ThreadDefine(paramters->at(1), paramters->at(2));
			return thread;
		}
	}
	return NULL;
}
BOOL __stdcall Thread_Wait_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::wstring userinputobj = vtparameters->at(0);
		std::wstring strname = vtparameters->at(1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(userinputobj.c_str());
		if (ObjThread == type)
		{
			ScpThreadObject * thread = (ScpThreadObject*)currentObjectSpace->FindObject(strname);
			if (thread)
			{
				CScriptEngine * engine = thread->scriptengine;
				thread->Wait();
			}
		}
	}
	return TRUE;
}
BOOL __stdcall Thread_Run_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() >= 2)
	{
		std::wstring strobjtype = vtparameters->at(0);
		std::wstring procobjname = vtparameters->at(1);

		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobjtype.c_str());
		if (ObjThread == type)
		{
			ScpThreadObject * threadObj = (ScpThreadObject *)currentObjectSpace->FindObject(procobjname);
			if (threadObj)
			{
				//注意多线程时的对象访问问题
				CScriptEngine * pscriptengine = new CScriptEngine;
				ScpObjectSpace *pcurrentObjectSpace = pscriptengine->GetCurrentObjectSpace();
				pcurrentObjectSpace->userobject.Copy(&currentObjectSpace->userobject);
				pcurrentObjectSpace->parentspace = currentObjectSpace->parentspace;
				threadObj->Run(*vtparameters, pscriptengine);
			}
		}
	}
	else
	{
		engine->SetLastErrorString(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidParameter);
	}
	return TRUE;
}

BOOL __stdcall Thread_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 1)
	{
		std::wstring text = vtparameters->at(0);
		{
			ScpObject *obj = (ScpObject *)currentObjectSpace->FindObject(text);
			if (obj)
			{
				if (obj->GetType() == ObjThread)
				{
					currentObjectSpace->EraseObject(text);
				}
			}
			else
			{
				engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidParameter);
			}
		}
	}
	else if (vtparameters->size() == 2)
	{
		std::wstring strobj = vtparameters->at(0);
		std::wstring text = vtparameters->at(1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjThread == type)
		{
			ScpThreadObject * thread = (ScpThreadObject *)currentObjectSpace->FindObject(text);
			if (thread)
			{
				currentObjectSpace->EraseObject(text);
			}
		}
	}
	else
	{
		engine->SetLastErrorString(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidParameter);
	}
	return TRUE;
}
ScpThreadObject::ScpThreadObject(void)
{
	objecttype = ObjThread;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_wait, InnerFunction_wait);
	BindObjectInnerFuction(scpcommand_en_wait, InnerFunction_wait);


	BindObjectInnerFuction(scpcommand_cn_run, InnerFunction_run);
	BindObjectInnerFuction(scpcommand_en_run, InnerFunction_run);
}


ScpThreadObject::~ScpThreadObject(void)
{
}


void ScpThreadObject::Show(CScriptEngine * engine) 
{
}
ScpObject * ScpThreadObject::Clone(std::wstring strObjName)
{
	return NULL;
}	
std::wstring ScpThreadObject::ToString()
{
	std::wstring temp;
	temp+=ThreadName;
	temp+=L"\r\n";
	temp+=ThreadFuncionName;
	return temp;
}
void ScpThreadObject::Release() 
{
	delete this;
}
bool ScpThreadObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpThreadObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
void ScpThreadObject::ThreadDefine(std::wstring Name,std::wstring FunctionName)
{
	ThreadName= Name;
	ThreadFuncionName =FunctionName;
}
void ScpThreadObject::Run(VTPARAMETERS &Parameters,CScriptEngine * pscriptengine)
{
	RealParameters=Parameters;
	scriptengine = pscriptengine;
#ifdef WIN32 
	hThread = (HANDLE) _beginthreadex(NULL,0,ThreadBodyFunction,this,0,NULL);
#else 
	hThread = (unsigned int ) pthread_create(&thread1,NULL,ScpThreadObject::ThreadBodyFunction,this);
#endif 
}
void ScpThreadObject::Wait()
{
#ifdef _WIN32
	WaitForSingleObject(hThread,INFINITE);		
	CloseHandle(hThread);
	hThread=NULL;
#else 
	pthread_join(thread1,NULL);  
#endif 
}
ScpObject * ScpThreadObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpThreadObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}
ScpObject * ScpThreadObject::InnerFunction_wait(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
ScpObject * ScpThreadObject::InnerFunction_run(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}

#ifdef _WIN32
unsigned int __stdcall ScpThreadObject::ThreadBodyFunction(void * parameter)
{
	ScpThreadObject  *thread =(ScpThreadObject*)parameter;
	if(thread)
	{
		ScpFunctionObject* func=NULL;

		ScpObjectSpace * currentObjectSpace = thread->scriptengine->GetCurrentObjectSpace();
		func = (ScpFunctionObject*)currentObjectSpace->FindObject(thread->ThreadFuncionName);
		if (func)
		{
			if (func->GetType() == ObjFunction)
			{
				for (ULONG i = 2;i < thread->RealParameters.size();i++)
				{
					func->RealParameters.push_back(thread->RealParameters.at(i));					
				}
				func->Do(thread->scriptengine);
			}
		}
		//thread->scriptengine->scriptcommand->Do_Call_Command(&thread->RealParameters,thread->scriptengine);
	}
	return 0;
}
#else 
void * ScpThreadObject::ThreadBodyFunction(void * parameter)
{
	ScpThreadObject  *thread =(ScpThreadObject*)parameter;
	if(thread)
	{
ScpFunctionObject* func=NULL;

		ScpObjectSpace * currentObjectSpace = thread->scriptengine->GetCurrentObjectSpace();
		func = (ScpFunctionObject*)currentObjectSpace->FindObject(thread->ThreadFuncionName);
		if (func)
		{
			if (func->GetType() == ObjFunction)
			{
				for (ULONG i = 2;i < thread->RealParameters.size();i++)
				{
					func->RealParameters.push_back(thread->RealParameters.at(i));					
				}
				func->Do(thread->scriptengine);
			}
		}
		//thread->scriptengine->scriptcommand->Do_Call_Command(&thread->RealParameters,thread->scriptengine);
	}
	return NULL;
}

#endif 
