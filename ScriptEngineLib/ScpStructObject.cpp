/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpStructObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"
#include "ScpCommonObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpStructObject::ScpStructObject(void)
{
	StructObjectSpace.ObjectSpaceType=Space_Struct;
	StructObjectSpace.belongto=this;
	bytealignment = 4; 
	MemoryBlockAddress = NULL;
	biggestmembersize = 0;
	structsize = 0;
	objecttype = ObjStruct;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);
}


ScpStructObject::~ScpStructObject(void)
{
	FreeStructMemory();
}

ScpObject * ScpStructObject::Clone(std::string strObjName)
{
	return NULL;
}
std::string ScpStructObject::ToString()
{
	std::string temp;
	return temp;
}
void ScpStructObject::Show(CScriptEngine * engine)
{
	for(unsigned int i=0;i<Boday.size();i++)
	{
		engine->PrintError(Boday.at(i));
	}
}
bool ScpStructObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpStructObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
int ScpStructObject::GetBiggestMemberSize()
{
	if(biggestmembersize==0)
	{
		ULONG MemberCount= StructObjectSpace.userobject.GetSize();
		for(ULONG i=0;i<MemberCount;i++)
		{
			ScpObject * obj = StructObjectSpace.userobject.GetObject(i);
			MemberSizeInStruct.push_back(GetObjectSize(obj));
			biggestmembersize=max(biggestmembersize,GetObjectSize(obj));
		}		
	}
	return biggestmembersize;
}
int ScpStructObject::GetStructMemorySize()
{
	if(structsize==0)
	{
		bytealignment=min(bytealignment,GetBiggestMemberSize());
		int size = 0;
		ULONG MemberCount= StructObjectSpace.userobject.GetSize();
		for(ULONG i=0;i<MemberCount;i++)
		{
			ScpObject * obj = StructObjectSpace.userobject.GetObject(i);
			MemberPosInStruct.push_back(CalcMemberMemoryPosInStruct(obj,i));
		}
		size=MemberPosInStruct.at(MemberCount-1)+MemberSizeInStruct.at(MemberCount-1);		
		structsize = size;
	}
	return structsize;
}
BOOL ScpStructObject::FillMember(ScpObject * memberobj,int order)
{
	BOOL bRet = FALSE;
	if(MemoryBlockAddress)
	{
		int pos =CalcMemberMemoryPosInStruct(memberobj,order);
		void * pAddr=(void *)((char *)MemoryBlockAddress+pos);
		if(memberobj->GetType()==ObjCChar)
		{
			memcpy(pAddr,&((ScpObjCChar *)memberobj)->Value,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjCInt32)
		{
			memcpy(pAddr,&((ScpObjCInt32 *)memberobj)->Value,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjPointerofWchar)
		{
			memcpy(pAddr,&((ScpObjPointerofWchar *)memberobj)->Value,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjPointerofChar)
		{
			memcpy(pAddr,&((ScpObjPointerofChar *)memberobj)->Value,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjUnsignedInt32)
		{
			memcpy(pAddr,&((ScpObjUnsignedInt32 *)memberobj)->Value,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjHandle)
		{
			memcpy(pAddr,&((ScpObjHandle *)memberobj)->Value,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjMemory)
		{
			memcpy(pAddr,&((ScpMemoryObject *)memberobj)->Address,GetObjectSize(memberobj));
		}
	}
	return bRet;
}
BOOL ScpStructObject::GetMember(ScpObject * memberobj,int order)
{
	BOOL bRet = FALSE;
	if(MemoryBlockAddress)
	{
		int pos =CalcMemberMemoryPosInStruct(memberobj,order);
		void * pAddr=(void *)((char *)MemoryBlockAddress+pos);
		if(memberobj->GetType()==ObjCChar)
		{
			memcpy(&((ScpObjCChar *)memberobj)->Value,pAddr,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjCInt32)
		{
			memcpy(&((ScpObjCInt32 *)memberobj)->Value,pAddr,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjPointerofWchar)
		{
			memcpy(&((ScpObjPointerofWchar *)memberobj)->Value,pAddr,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjPointerofChar)
		{
			memcpy(&((ScpObjPointerofChar *)memberobj)->Value,pAddr,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjUnsignedInt32)
		{
			memcpy(&((ScpObjUnsignedInt32 *)memberobj)->Value,pAddr,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjHandle)
		{
			memcpy(&((ScpObjHandle *)memberobj)->Value,pAddr,GetObjectSize(memberobj));
		}
		else if(memberobj->GetType()==ObjMemory)
		{
			memcpy(&((ScpMemoryObject *)memberobj)->Address,pAddr,GetObjectSize(memberobj));
		}
	}
	return bRet;
}
int ScpStructObject::GetObjectSize(ScpObject * memberobj)
{
	int size=0;
	if(memberobj->GetType()==ObjCChar)
	{
		size =1 ;
	}
	else if(memberobj->GetType()==ObjCInt32)
	{
		size = 4; 
	}
	else if(memberobj->GetType()==ObjPointerofWchar)
	{
		size = 4;
	}
	else if(memberobj->GetType()==ObjPointerofChar)
	{
		size =4;
	}
	else if(memberobj->GetType()==ObjUnsignedInt32)
	{
		size = 4;
	}
	else if(memberobj->GetType()==ObjHandle)
	{
		size = 4;
	}
	else if(memberobj->GetType()==ObjMemory)
	{
		size = ((ScpMemoryObject*)memberobj)->GetSize();
	}
	return size;
}
int ScpStructObject::CalcMemberMemoryPosInStruct(ScpObject * memberobj,int order)
{
	int pos=0;
	if(order==0)
	{
		pos =0;
	}
	else
	{
		int pos1 = MemberPosInStruct.at(order-1);
		int size = GetObjectSize(memberobj);
		pos1=pos1+MemberSizeInStruct.at(order-1);		
		int memberalignment = min(bytealignment,size);
		int step =0;
		if(memberalignment!=0)
		{
			step=pos1%memberalignment;
		}
		if(step!=0)
		{
			step=memberalignment-step;
		}
		pos=pos1+step;
	}
	return pos;

	
}
ScpObject * ScpStructObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpStructObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string param0 = parameters->at(0);
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
ScpObject * ScpStructObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * size = new ScpIntObject;
	size->value = ((ScpStructObject*)thisObject)->structsize;
	size->istemp = true;
	return size;

}
int ScpStructObject::AllocStructMemory()
{
	if(structsize==0)
	{
		structsize = GetStructMemorySize();
	}
	MemoryBlockAddress = malloc(structsize);
	if(MemoryBlockAddress)
		return structsize;
	return 0;
}
void ScpStructObject::FreeStructMemory()
{
	if(MemoryBlockAddress)
	{
		free(MemoryBlockAddress);
	}
}
void ScpStructObject::Release() 
{
	delete this;
}