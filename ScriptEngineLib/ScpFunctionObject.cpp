/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpFunctionObject.h"
#include "ScpStringObject.h"
#include "ScpDoubleObject.h"
#include "ScpGlobalObject.h"
#include "commanddefine_uni.h"
#include "../Common/DebugUtil.hpp"
#include "../Common/commonutil.hpp"
ScpFunctionObject::ScpFunctionObject():functionexpressionblock(NULL)
{
	objecttype =ObjFunction;
	FunctionObjectSpace = new ScpObjectSpace;
	FunctionObjectSpace->ObjectSpaceType = Space_Function;
	FunctionObjectSpace->belongto = this;
	pBoday=&Boday;
	pFormalParameters=&FormalParameters;
	iscloned = false;
	Result = NULL;
	ByteCode = NULL;
	ByteCodeLength = 0;	
	ParenObject = NULL;
	parentobjectname = L"";

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);
}
ScpFunctionObject::~ScpFunctionObject()
{
	ClearLocalObjects();
	if (functionexpressionblock)
	{
		delete functionexpressionblock;
	}
	delete FunctionObjectSpace;	
}
ScpObject * ScpFunctionObject::Clone(std::wstring strObjName)
{
	ScpFunctionObject * obj = new ScpFunctionObject;	
	obj->pFormalParameters=&this->FormalParameters;
	obj->FunctionObjectSpace->parentspace=this->FunctionObjectSpace->parentspace;
	obj->Name=strObjName;
	obj->iscloned =true;
	return obj;
}	
std::wstring ScpFunctionObject::ToString()
{
	std::wstring temp;

	std::wstring tempfuncbody =Name;
	tempfuncbody+=L"(";
	for(ITPARAMETERS it =FormalParameters.begin();it!=FormalParameters.end();it++)
	{
		std::wstring temp1 = *it;
		tempfuncbody+=temp1;
		tempfuncbody+=L",";
	}
	if(tempfuncbody.substr(tempfuncbody.length()-1,1)==L",")
		tempfuncbody=tempfuncbody.substr(0,tempfuncbody.length()-1);
	tempfuncbody+=L")\n";

	temp=tempfuncbody;
	for(ITSTRINGS it =Boday.begin();it!=Boday.end();it++)
	{
		temp+= *it;
		temp+=L"\r\n";
	}

	return temp;
}

int ScpFunctionObject::Do(CScriptEngine *engine)
{
	if(engine)
	{
		BOOL bRecurseCall=FALSE;
		ScpObjectSpace * oldparentspace = FunctionObjectSpace->parentspace;  //解决递归调用的问题
		if (FunctionObjectSpace == engine->GetCurrentObjectSpace() || engine->GetCurrentObjectSpace()->IsMyParentSpace(FunctionObjectSpace))
		{
			bRecurseCall=TRUE;				
		}
		else
		{
			FunctionObjectSpace->parentspace=engine->GetCurrentObjectSpace();
			engine->SetCurrentObjectSpace(FunctionObjectSpace);
		}	
			
		Result = NULL;
		if (engine->GetCurrentObjectSpace()->lastcommand == vl_return)
		{
			engine->GetCurrentObjectSpace()->lastcommand = vl_call;
		}
		//ClearLocalObjects();
		if(BindParameters(engine)!=-1)
		{		
			if (functionexpressionblock)
			{
				//functionexpressionblock->Compile(engine);
				functionexpressionblock->Run(engine);
			}			
		}
		//
		UnBindParameters(engine);
		if(!bRecurseCall)
		{
			engine->SetCurrentObjectSpace(FunctionObjectSpace->parentspace);
			FunctionObjectSpace->parentspace = oldparentspace;
		}		
	}
	return 0;
}
int ScpFunctionObject::BindParameters(CScriptEngine *engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	if(pFormalParameters->size()>0)
	{
		if(pFormalParameters->size()==RealParameters.size())
		{			
			//构建形参与实参的映射关系
			for(ULONG i=0;i<pFormalParameters->size();i++)
			{
				//现在因为是在函数自己的局部名字空间里，所以可以不用考虑与全局名字空间的名称冲突问题 
				//因为查找的时候首先是在局部空间里，所以实现了局部名字空间的变量覆盖上一层名字空间的变量
				ScpObject * obj=objectSpace->FindObject(RealParameters.at(i));
				if(obj)
				{
					objectSpace->AddObject(pFormalParameters->at(i),obj);
				}				
				else
				{
					ScpObject * tempobj=NULL;					
					////这样一来，函数的参数也可以是数值常量
					if (IsStaticNumber(RealParameters.at(i)))
					{
						tempobj = new ScpIntObject;
						((ScpIntObject*)tempobj)->value = StringToInt(RealParameters.at(i));
						objectSpace->AddObject(pFormalParameters->at(i), tempobj);
					}
					else if (IsStaticDoubleNumber(RealParameters.at(i)))
					{
						tempobj = new ScpDoubleObject;
						((ScpDoubleObject*)tempobj)->value = StringToDouble(RealParameters.at(i));
						objectSpace->AddObject(pFormalParameters->at(i), tempobj);
					}
					else
					{
						std::wstring Expression = RealParameters.at(i);
						ScpObjectSpace * currentObjectSpace = objectSpace;
						ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(Expression);
						if (root)
						{
							tempobj = root->CalculateEx(engine);
							if (tempobj)
							{
								//objectSpace->EraseObject(pFormalParameters->at(i));
								objectSpace->AddObject(pFormalParameters->at(i), tempobj);
							}
							else
							{
								tempobj = new ScpStringObject;
								((ScpStringObject*)tempobj)->content = RealParameters.at(i);
								objectSpace->AddObject(pFormalParameters->at(i), tempobj);
							}
							root->Destroy(engine->GetCurrentObjectSpace());
							engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
						}
												
					}
							
				}
			}		
		}
		else
		{
			engine->PrintError(L"Invalid Function Parameter");
			return -1;
		}
	}
	return 0;
}
int ScpFunctionObject::UnBindParameters(CScriptEngine *engine)
{
	//撤销形参与是实参之间的映射关系
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	for(ULONG i=0;i<pFormalParameters->size();i++)
	{
		ScpObject * obj=objectSpace->FindObject(pFormalParameters->at(i));
		if(obj)
		{			
			objectSpace->EraseObject(pFormalParameters->at(i));
		}
		else
		{
			continue;
		}
	}
	//删除实参列表
	while(RealParameters.size()>0)
	{
		RealParameters.pop_back();
	}	
	return 0;
}

void ScpFunctionObject::Show(CScriptEngine * engine)
{
	std::wstring tempfuncbody =Name;
	tempfuncbody+=L"(";
	for(ITPARAMETERS it =pFormalParameters->begin();it!=pFormalParameters->end();it++)
	{
		std::wstring temp = *it;
		tempfuncbody+=temp;
		tempfuncbody+=L",";
	}
	if(tempfuncbody.substr(tempfuncbody.length()-1,1)==L",")
		tempfuncbody=tempfuncbody.substr(0,tempfuncbody.length()-1);
	tempfuncbody+=L")\n";
	engine->PrintError(tempfuncbody);
	for(ITSTRINGS it =Boday.begin();it!=Boday.end();it++)
	{
		std::wstring temp = *it;
		engine->PrintError(temp);
	}
}
void ScpFunctionObject::ClearLocalObjects()
{
	FunctionObjectSpace->userobject.Destroy();
}
int ScpFunctionObject::GetFormalParametersCount()
{
	return FormalParameters.size();
}
std::wstring ScpFunctionObject::GetCloneName()
{
	
	std::wstring tempobjname=Name;
	int AppendIndex = 0;
	int AppendIndexLen = 0;
	std::wstring wsAppendIndex;
	size_t pos = Name.rfind(L"LSClone");
	if (pos!=std::wstring::npos)
	{		
		AppendIndexLen = Name.length()-pos - 7;
		wsAppendIndex = Name.substr(pos + 7);
		AppendIndex = StringToInt(wsAppendIndex);		
		AppendIndex += 1;
		tempobjname.replace(pos + 7, AppendIndexLen, STDSTRINGEXT::Format(L"%d", AppendIndex));
	}
	else
	{
		tempobjname = STDSTRINGEXT::Format(L"%sLSClone%d", Name.c_str(),AppendIndex);
	}

	return tempobjname;
}

ScpObject * ScpFunctionObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;

}

ScpObject * ScpFunctionObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
				tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

void ScpFunctionObject::Release() 
{
	delete this;
}
bool ScpFunctionObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpFunctionObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}

	return NULL;
}