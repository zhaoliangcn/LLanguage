#include "ScpListObject.h"
#include "ScriptEngine.h"
#include "ScpStringObject.h"
#include "ScpFunctionObject.h"
#include "ScpGlobalObject.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"
#include "ScpObjectNammes.h"

ScpListObject::ScpListObject()
{
	objecttype = ObjList;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);

	BindObjectInnerFuction(scpcommand_cn_insert, InnerFunction_insert);
	BindObjectInnerFuction(scpcommand_en_insert, InnerFunction_insert);

	BindObjectInnerFuction(scpcommand_cn_append, InnerFunction_append);
	BindObjectInnerFuction(scpcommand_en_append, InnerFunction_append);

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


ScpListObject::~ScpListObject()
{
	EmptyElement();
}

void ScpListObject::Show(CScriptEngine * engine)
{
	ULONG size = GetSize();
	for (ULONG i = 0;i < size;i++)
	{
		ScpObject * element = (ScpObject *)GetElement(i);
		element->Show(engine);
	}
}

ScpObject * ScpListObject::Clone(std::wstring strObjName)
{
	ScpListObject * tmpobj = new ScpListObject;
	tmpobj->listname = strObjName;
	tmpobj->Combine(this);
	return tmpobj;
}

std::wstring ScpListObject::ToString()
{
	std::wstring temp;
	ULONG size = GetSize();
	for (ULONG i = 0;i < size;i++)
	{
		ScpObject * element = (ScpObject *)GetElement(i);
		temp += element->ToString();
		temp += L",";
	}
	return temp;
}

void ScpListObject::Release()
{
	delete this;
}

bool ScpListObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}

ScpObject * ScpListObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ULONG ScpListObject::GetSize()
{
	return members.size();
}

void ScpListObject::Combine(ScpObject * tbl)
{
	ULONG size = ((ScpListObject*)tbl)->members.size();
	for (unsigned int i = 0;i < size;i++)
	{
		std::wstring & elementname = ((ScpListObject*)tbl)->members.at(i).first;
		ScpObject * obj = ((ScpListObject*)tbl)->members.at(i).second;
		if (!this->GetElement(elementname))
		{
			this->AddElement(elementname, obj);
		}
	}
}

void ScpListObject::Assign(ScpObject * tbl)
{
	this->EmptyElement();
	Combine(tbl);
}

void ScpListObject::Exclude(ScpObject * tbl)
{
	ULONG size = ((ScpListObject*)tbl)->members.size();
	for (unsigned int i = 0;i < size;i++)
	{
		std::wstring & elementname = ((ScpListObject*)tbl)->members.at(i).first;
		if (this->GetElement(elementname))
		{
			this->DeleteElement(elementname);
		}
	}
}

void ScpListObject::Intersection(ScpObject * tbl)
{
	for (unsigned int i = 0;i < ((ScpListObject*)tbl)->GetSize();i++)
	{
		std::wstring & elementname = ((ScpListObject*)tbl)->members.at(i).first;
		if (!this->GetElement(elementname))
		{
			this->DeleteElement(elementname);
		}
	}
	for (unsigned int i = 0;i < ((ScpListObject*)tbl)->GetSize();i++)
	{
		std::wstring & elementname = ((ScpListObject*)tbl)->members.at(i).first;
		if (!((ScpListObject*)tbl)->GetElement(this->members.at(i).first))
		{
			this->DeleteElement(this->members.at(i).first);
			i--;
		}
	}
}

BOOL ScpListObject::AddElement(std::wstring elementname, ScpObject * obj)
{
	if (!GetElement(elementname))
	{
		NamedPOBJECTS namedobj = std::make_pair(elementname, obj);
		members.push_back(namedobj);
		return TRUE;
	}
	return FALSE;
}

BOOL ScpListObject::AddElement(std::wstring elementname, ScpObjectSpace * objectSpace)
{
	ScpObject * obj = objectSpace->FindObject(elementname);
	if (obj)
	{
		if (obj != this)
			return AddElement(elementname, objectSpace->FindObject(elementname));	}

	return FALSE;
}

BOOL ScpListObject::InsertElement(int index, std::wstring elementname, ScpObject * obj)
{
	if (!GetElement(elementname))
	{
		NamedPOBJECTS namedobj = std::make_pair(elementname, obj);
		members.insert(members.begin() + index, namedobj);
		return TRUE;
	}
	return FALSE;
	return 0;
}

BOOL ScpListObject::DeleteElement(std::wstring elementname)
{
	for(ITNamedPOBJECTS it = members.begin();it!= members.end();it++)
	{
		if (it->first == elementname)
		{
			members.erase(it);
			return TRUE;
		}	
	}
	return FALSE;
}

void ScpListObject::EmptyElement()
{
	ITNamedPOBJECTS it = members.begin();
	while (it != members.end())
	{
		it = members.erase(it);
	}
}

ScpObject * ScpListObject::GetElement(std::wstring elementname)
{
	ScpObject * obj = nullptr;
	for (int i = 0;i < members.size();i++)
	{
		if (members.at(i).first == elementname)
		{
			obj = members.at(i).second;
		}
	}
	return obj;
}

ScpObjectType ScpListObject::GetElementType(std::wstring elementname)
{
	ScpObject * obj = GetElement(elementname);
	if (obj)
		return obj->GetType();
	return ScpObjectType(ObjUnknown);
}

BOOL ScpListObject::DeleteElement(ULONG elementindex)
{
	if (elementindex >= 0 && elementindex < members.size())
	{
		ITNamedPOBJECTS it = members.begin() + elementindex;
		members.erase(it);
		return TRUE;
	}
	return FALSE;
}

ScpObject * ScpListObject::GetElement(ULONG elementindex)
{
	ScpObject * obj = NULL;
	if (elementindex >= 0 && elementindex < members.size())
	{
		ITNamedPOBJECTS it = members.begin() + elementindex;
		obj = it->second;
	}
	return obj;
}

ScpObjectType ScpListObject::GetElementType(ULONG elementindex)
{
	ScpObject * obj = NULL;
	if (elementindex >= 0 && elementindex < members.size())
	{
		ITNamedPOBJECTS it = members.begin() + elementindex;
		obj = it->second;
		if(obj)
		return obj->GetType();
	}	
	return ScpObjectType(ObjUnknown);
}

ScpObject * ScpListObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpListObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpListObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * size = new ScpIntObject;
	if (size)
	{
		size->value = ((ScpListObject*)thisObject)->GetSize();
		size->istemp = true;
	}
	return size;
}

ScpObject * ScpListObject::InnerFunction_insert(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		int index = -1;
		std::wstring indexstr = parameters->at(0);
		StringStripQuote(indexstr);
		ScpObject * intobj = engine->GetCurrentObjectSpace()->FindObject(indexstr);
		if (intobj && intobj->GetType() == ObjInt)
		{
			index = ((ScpIntObject*)intobj)->value;
		}
		else if (IsStaticNumber(indexstr))
		{
			index = StringToInt(indexstr);
		}
		if (index<0 || index>(((ScpListObject*)thisObject)->GetSize() - 1))
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorIndexOutofSize);
			return NULL;
		}
		//由于可能是在函数中调用，不能绑定为形式参数的名称，需要向上递归查找到真实名称
		std::wstring name = parameters->at(1);
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
			((ScpListObject*)thisObject)->InsertElement(index, name, obj);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + parameters->at(1));
			return NULL;
		}

	}
	return thisObject;
}

ScpObject * ScpListObject::InnerFunction_append(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
			((ScpListObject*)thisObject)->AddElement(name, obj);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + parameters->at(0));
		}
	}
	return thisObject;

}

ScpObject * ScpListObject::InnerFunction_traverse(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (parameters->size() == 1)
	{
		std::wstring funcname = parameters->at(0);
		StringStripQuote(funcname);
		ScpListObject * listobj = (ScpListObject*)thisObject;
		ScpFunctionObject * func = (ScpFunctionObject*)currentObjectSpace->FindObject(funcname);
		if (func && (func->FormalParameters.size() == 1))
		{
			int count = 0;
			count = listobj->GetSize();
			for (int index = 0;index < count;index++)
			{
				ScpObject * elementobj = listobj->GetElement(index);
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

ScpObject * ScpListObject::InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpListObject*)thisObject)->EmptyElement();
	return nullptr;
}

ScpObject * ScpListObject::InnerFunction_getelement(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring &indexstr = parameters->at(0);
		StringStripQuote(indexstr);
		//先按名字查找
		ScpObject * elementobj = ((ScpListObject*)thisObject)->GetElement(indexstr);
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
			else if (IsStaticNumber(indexstr))
			{
				index = StringToInt(indexstr);
			}
			if (index<0 || index>(((ScpListObject*)thisObject)->GetSize() - 1))
			{
				engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorIndexOutofSize);
			}
			else
			{
				ScpObject * elementobj = ((ScpListObject*)thisObject)->GetElement(index);
				if (elementobj)
				{
					return elementobj;
				}
			}
		}
		return NULL;
	}
	return nullptr;
}

ScpObject * ScpListObject::InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (obj)
		{
			((ScpListObject*)thisObject)->DeleteElement(param0);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + param0);
		}
	}
	return thisObject;
}

ScpObject * ScpListObject::InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (obj)
		{
			((ScpListObject*)thisObject)->DeleteElement(param0);
		}
		else
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjNotExist + param0);
		}
	}
	return thisObject;
}

ScpObject * __stdcall ScpListObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpListObject;
}
