/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpTableObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "ScpStringObject.h"
#include "ScpFunctionObject.h"
#include "ScpGlobalObject.h"
#include "ScpObjectNammes.h"
#include "../Common/commonutil.hpp"
ScpTableObject::ScpTableObject()
{
	objecttype = ObjTable;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);

	BindObjectInnerFuction(scpcommand_cn_insert, InnerFunction_insert);
	BindObjectInnerFuction(scpcommand_en_insert, InnerFunction_insert);

	BindObjectInnerFuction(scpcommand_cn_traverse, InnerFunction_traverse);
	BindObjectInnerFuction(scpcommand_en_traverse, InnerFunction_traverse);

	BindObjectInnerFuction(scpcommand_cn_clear, InnerFunction_clear);
	BindObjectInnerFuction(scpcommand_en_clear, InnerFunction_clear);

	BindObjectInnerFuction(scpcommand_cn_getelement, InnerFunction_getelement);
	BindObjectInnerFuction(scpcommand_en_getelement, InnerFunction_getelement);

	BindObjectInnerFuction(scpcommand_cn_delete, InnerFunction_delete);
	BindObjectInnerFuction(scpcommand_en_delete, InnerFunction_delete);

	BindObjectInnerFuction(scpcommand_cn_erase, InnerFunction_erase);
	BindObjectInnerFuction(scpcommand_en_erase, InnerFunction_erase);
}
ScpTableObject::~ScpTableObject()
{
	EmptyElement();
}

ULONG ScpTableObject::GetSize()
{
	return tableobjects.GetSize();
}
BOOL ScpTableObject::AddElement(std::wstring elementname,ScpObject * obj)
{
	return tableobjects.MapObject(elementname,obj);
}
BOOL ScpTableObject::AddElement(std::wstring elementname,ScpObjectSpace * objectSpace)
{

	ScpObject * obj = objectSpace->FindObject(elementname);
	if(obj)
	{
		if(obj!=this)
			return AddElement(elementname,objectSpace->FindObject(elementname));
	}

	return FALSE;
}
BOOL ScpTableObject::DeleteElement(std::wstring elementname)
{
	if(tableobjects.IsInMap(elementname))
	{
		tableobjects.UnMapObject(elementname);
		return TRUE;
	}
	return FALSE;
}
void ScpTableObject::EmptyElement()
{
	while(tableobjects.GetSize()>0)
	{
		tableobjects.UnMapObject(0);
	}
}
ScpObject * ScpTableObject::GetElement(std::wstring elementname)
{
	if(tableobjects.IsInMap(elementname))
	{
		return tableobjects.GetObject(elementname);
	}
	return NULL;
}
ScpObjectType ScpTableObject::GetElementType(std::wstring elementname)
{
	return tableobjects.GetType(elementname);
}
BOOL ScpTableObject::DeleteElement(ULONG elementindex)
{
	return FALSE;
}
ScpObject * ScpTableObject::GetElement(ULONG elementindex)
{
	return tableobjects.GetObject(elementindex);
}
ScpObjectType ScpTableObject::GetElementType(ULONG elementindex)
{
	return ObjUnknown;
}

void ScpTableObject::Show(CScriptEngine * engine)
{
	ULONG size = GetSize();
	for(ULONG i=0;i<size;i++)
	{
		ScpObject * element = (ScpObject *)GetElement(i);
		element->Show(engine);
	}
}
void ScpTableObject::Exclude(ScpObject * tbl)
{
	ULONG size=((ScpTableObject*)tbl)->tableobjects.GetSize();
	for(unsigned int i=0;i<size;i++)
	{
		if(this->tableobjects.IsInMap(((ScpTableObject*)tbl)->tableobjects.GetObjectName(i)))
		{
			this->DeleteElement(((ScpTableObject*)tbl)->tableobjects.GetObjectName(i));
		}		
	}
}
void ScpTableObject::Intersection(ScpObject * tbl)
{
	for(unsigned int i=0;i<((ScpTableObject*)tbl)->tableobjects.GetSize();i++)
	{
		if(!this->tableobjects.IsInMap(((ScpTableObject*)tbl)->tableobjects.GetObjectName(i)))
		{
			this->DeleteElement(((ScpTableObject*)tbl)->tableobjects.GetObjectName(i));			
		}		
	}
	for(unsigned int i=0;i<this->tableobjects.GetSize();i++)
	{
		if(!((ScpTableObject*)tbl)->tableobjects.IsInMap(this->tableobjects.GetObjectName(i)))
		{
			this->DeleteElement(this->tableobjects.GetObjectName(i));
			i--;
		}		
	}
}
void ScpTableObject::Assign(ScpObject * tbl)
{
	this->EmptyElement();
	Combine(tbl);
}
void ScpTableObject::Combine(ScpObject * tbl)
{
	ULONG size=((ScpTableObject*)tbl)->tableobjects.GetSize();
	for(unsigned int i=0;i<size;i++)
	{
		if(!this->tableobjects.IsInMap(((ScpTableObject*)tbl)->tableobjects.GetObjectName(i)))
		{
			this->AddElement(((ScpTableObject*)tbl)->tableobjects.GetObjectName(i),((ScpTableObject*)tbl)->tableobjects.GetObject(i));
		}		
	}
}
ScpObject * ScpTableObject::Clone(std::wstring strObjName)
{
	ScpTableObject * tmpobj=new ScpTableObject;
	tmpobj->tableobjname=strObjName;
	tmpobj->Combine(this);
	return tmpobj;
}	
std::wstring ScpTableObject::ToString()
{
	std::wstring temp;
	ULONG size = GetSize();
	for(ULONG i=0;i<size;i++)
	{
		ScpObject * element = (ScpObject *)GetElement(i);
		temp +=element->ToString();
		temp+=L",";
	}
	return temp;
}
void ScpTableObject::Release() 
{
	delete this;
}
bool ScpTableObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpTableObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpTableObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
	return nullptr;
}

ScpObject * ScpTableObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpTableObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * size = new ScpIntObject;
	if (size)
	{
		size->value = ((ScpTableObject*)thisObject)->GetSize();
		size->istemp = true;
	}
	return size;
}

ScpObject * ScpTableObject::InnerFunction_insert(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	for (int i = 0;i < parameters->size();i++)
	{
		//由于可能是在函数中调用，不能绑定为形式参数的名称，需要向上递归查找到真实名称
		std::wstring name = parameters->at(i);
		StringStripQuote(name);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(name);
		if (obj)
		{
			bool bfindRealName = false;
			if (engine->GetCurrentObjectSpace()->ObjectSpaceType == Space_Function)
			{
				ScpFunctionObject *func = (ScpFunctionObject *)engine->GetCurrentObjectSpace()->belongto;
				while (func)
				{
					for (int j = 0;j < func->FormalParameters.size();j++)
					{
						if (func->FormalParameters.at(j) == name)
						{
							name = func->RealParameters.at(j);
							//bfindRealName = true;
							break;
						}
					}
					//if (bfindRealName)
					//	break;
					ScpObjectSpace*parentspace = func->FunctionObjectSpace->parentspace;
					while (parentspace)
					{
						if (parentspace->ObjectSpaceType == Space_Function)
						{
							func = (ScpFunctionObject *)parentspace->belongto;
							break;
						}
						else
						{
							parentspace = parentspace->parentspace;
						}
					}
					if (parentspace == NULL)
					{
						break;
					}
				}
			}
			((ScpTableObject*)thisObject)->AddElement(name, obj);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + parameters->at(0));
		}
	}
	return thisObject;
}

ScpObject * ScpTableObject::InnerFunction_traverse(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (parameters->size() == 1)
	{
		std::wstring funcname = parameters->at(0);
		StringStripQuote(funcname);
		ScpTableObject * tableobj = (ScpTableObject * )thisObject;
		ScpFunctionObject * func = (ScpFunctionObject*)currentObjectSpace->FindObject(funcname);
		if (func && (func->FormalParameters.size() == 1))
		{
			int count = 0;
			count = tableobj->GetSize();
			for (int index = 0;index < count;index++)
			{
				ScpObject * elementobj = tableobj->GetElement(index);
				if (elementobj)
				{
					std::wstring elementname = currentObjectSpace->userobject.GetObjectName(elementobj);

					BOOL Clone = FALSE;
					std::wstring OldName;
					if (currentObjectSpace->IsMyParentSpace(func->FunctionObjectSpace) || currentObjectSpace == func->FunctionObjectSpace)
					{
						//	//说明是递归的函数调用		
						Clone = TRUE;
					}
					ScpObjectSpace * OldObjectSpace = NULL;
					VTPARAMETERS OldRealParameters;
					if (func)
					{
						if (func->GetType() == ObjFunction)
						{
							if (Clone)
							{
								OldObjectSpace = func->FunctionObjectSpace;
								OldName = func->Name;
								func->FunctionObjectSpace = new ScpObjectSpace;
								func->FunctionObjectSpace->belongto = func;
								func->FunctionObjectSpace->parentspace = OldObjectSpace->parentspace;
								func->FunctionObjectSpace->ObjectSpaceType = Space_Function;
								OldRealParameters = func->RealParameters;
								func->RealParameters.clear();
								func->Name = func->GetCloneName();
							}
							if (func->RealParameters.size() == 0)
							{
								func->RealParameters.push_back(elementname);
							}
							func->Do(engine);
						}
						if (Clone)
						{
							ScpObjectSpace * tempObjectSpace = func->FunctionObjectSpace;
							func->FunctionObjectSpace = OldObjectSpace;
							delete tempObjectSpace;
							func->RealParameters = OldRealParameters;
							func->Name = OldName;
						}
					}
				}
			}
		}
		return thisObject;
	}
	return nullptr;
}

ScpObject * ScpTableObject::InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpTableObject*)thisObject)->EmptyElement();
	return nullptr;
}

ScpObject * ScpTableObject::InnerFunction_getelement(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring &indexstr = parameters->at(0);
		StringStripQuote(indexstr);
		ScpObject * elementobj = ((ScpTableObject*)thisObject)->GetElement(indexstr);
		if (elementobj)
		{
			return elementobj;
		}
		else
		{
			int index = -1;
			ScpObject * intobj = engine->GetCurrentObjectSpace()->FindObject(indexstr);
			if (intobj && intobj->GetType() == ObjInt)
			{
				index = ((ScpIntObject*)intobj)->value;
			}
			else
			{
				if (IsStaticNumber(indexstr))
				{
					index = StringToInt(indexstr);
				}
			}
			if (index<0 || index>(((ScpTableObject*)thisObject)->GetSize() - 1))
			{
				engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorIndexOutofSize);
			}
			else
			{
				ScpObject * elementobj = ((ScpTableObject*)thisObject)->GetElement(index);
				return elementobj;
			}
		}
		return NULL;
	}
	return nullptr;
}

ScpObject * ScpTableObject::InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (obj)
		{
			((ScpTableObject*)thisObject)->DeleteElement(param0);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + param0);
		}
	}
	return thisObject;
}

ScpObject * ScpTableObject::InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (obj)
		{
			((ScpTableObject*)thisObject)->DeleteElement(param0);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + param0);
		}
	}
	return thisObject;

}

ScpObject * __stdcall ScpTableObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpTableObject;
}
