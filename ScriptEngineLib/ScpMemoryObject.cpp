/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpMemoryObject.h"
#include "ScpIntObject.h"
#include "ScpStringObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "NumberHelp.h"
#include "../Common/commonutil.hpp"


static inline void *MH_SearchPattern(void *pStartSearch, unsigned long  dwSearchLen, unsigned char *pPattern, unsigned long  dwPatternLen)
{
    //内存搜索特征码
    unsigned long dwStartAddr = (unsigned long )pStartSearch;
    unsigned long  dwEndAddr = dwStartAddr + dwSearchLen - dwPatternLen;

	while (dwStartAddr < dwEndAddr) //这里从文件的开始位置扫描,如果没有找到指定特征码的位置的话,就会跳出循环并结束扫描工作;否则会返回所查到的址
	{
		bool found = true;

        for (unsigned long  i = 0; i < dwPatternLen; i++)
        {
            unsigned char code = *(unsigned char *)(dwStartAddr + i);
            if (pPattern[i] != code)
            {
                found = false;
                break;
            }
        }

		if (found)
			return (void *)dwStartAddr;

		dwStartAddr++;
	}

	return 0;
}


ScpMemoryObject::ScpMemoryObject()
{
	Address = NULL;
	objecttype = ObjMemory;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_getsize, InnerFunction_getsize);
	BindObjectInnerFuction(scpcommand_en_getsize, InnerFunction_getsize);

	BindObjectInnerFuction(scpcommand_cn_acquire, InnerFunction_acquire);
	BindObjectInnerFuction(scpcommand_en_acquire, InnerFunction_acquire);

	BindObjectInnerFuction(scpcommand_cn_clear, InnerFunction_clear);
	BindObjectInnerFuction(scpcommand_en_clear, InnerFunction_clear);

	BindObjectInnerFuction(scpcommand_cn_encode, InnerFunction_encode);
	BindObjectInnerFuction(scpcommand_en_encode, InnerFunction_encode);

	BindObjectInnerFuction(scpcommand_cn_decode, InnerFunction_decode);
	BindObjectInnerFuction(scpcommand_en_decode, InnerFunction_decode);

	BindObjectInnerFuction(scpcommand_cn_encrypt, InnerFunction_encrypt);
	BindObjectInnerFuction(scpcommand_en_encrypt, InnerFunction_encrypt);

	BindObjectInnerFuction(scpcommand_cn_decrypt, InnerFunction_decrypt);
	BindObjectInnerFuction(scpcommand_en_decrypt, InnerFunction_decrypt);

	BindObjectInnerFuction(scpcommand_cn_read, InnerFunction_read);
	BindObjectInnerFuction(scpcommand_en_read, InnerFunction_read);

	BindObjectInnerFuction(scpcommand_cn_write, InnerFunction_write);
	BindObjectInnerFuction(scpcommand_en_write, InnerFunction_write);

	BindObjectInnerFuction(scpcommand_cn_release, InnerFunction_release);
	BindObjectInnerFuction(scpcommand_en_release, InnerFunction_release);

	BindObjectInnerFuction(scpcommand_cn_compare, InnerFunction_compare);
	BindObjectInnerFuction(scpcommand_en_compare, InnerFunction_compare);

	BindObjectInnerFuction(scpcommand_cn_extend, InnerFunction_extend);
	BindObjectInnerFuction(scpcommand_en_extend, InnerFunction_extend);

	BindObjectInnerFuction(scpcommand_cn_hash, InnerFunction_hash);
	BindObjectInnerFuction(scpcommand_en_hash, InnerFunction_hash);

	BindObjectInnerFuction(scpcommand_cn_find, InnerFunction_find);
	BindObjectInnerFuction(scpcommand_en_find, InnerFunction_find);

	BindObjectInnerFuction(scpcommand_cn_copy, InnerFunction_copy);
	BindObjectInnerFuction(scpcommand_en_copy, InnerFunction_copy);


}
ScpMemoryObject::~ScpMemoryObject()
{
	ReleaseMem();
}

BOOL ScpMemoryObject::Acquare(ULONG aSize)
{
	if(Address)
	{
		if(Size<aSize)
		{
			if(Size != 0)
				free(Address);
			Address=NULL;
		}			
	}		
	Size=aSize;
	if(!Address)
	{			
		Address=(void*)malloc(Size);
		if(Address)
		{
			memset(Address,0,Size);
		}		
	}
	return Address!=NULL;
}
BOOL ScpMemoryObject::Extend(ULONG exSize)
{
	if (Address)
	{
		Address = realloc(Address, Size + exSize);
		Size += exSize;
	}
	else
	{
		Address = (void*)malloc(exSize);
		Size = exSize;
	}
	return Address != NULL;
}
BOOL ScpMemoryObject::ReleaseMem()
{
	if(Address!=NULL)
	{
		free(Address);
		Address=NULL;
		Size = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::Read(void * dest,ULONG aSize)
{
	if((dest!=NULL)&&(aSize<=Size))
	{
		memcpy(dest,Address,aSize);
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::Read(std::wstring & wstr)
{
	wstr=(wchar_t*)Address;
	return TRUE;
}
BOOL ScpMemoryObject::Read(void * dest, ULONG pos, ULONG aSize)
{
	if ((pos < Size) && ((pos + aSize) <= Size))
	{
		memcpy(dest,(char *)Address + pos, aSize);
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::Read(std::wstring & wstr, ULONG pos)
{
	if (pos < Size)
	{
		wstr = (wchar_t*)((unsigned char *)Address+ pos);
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::Write(void * src,ULONG aSize)
{	
	if(aSize<=Size)
	{
		memcpy(Address,src,aSize);
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::Write(std::wstring & wstr)
{
	size_t aSize = (wstr.length() + 1) * sizeof(wchar_t);
	if (Size < aSize)
	{
		Acquare(aSize);
	}
	return Write((void *)wstr.c_str(),wstr.length()*sizeof(wchar_t));
}
BOOL ScpMemoryObject::Write(std::string & astr)
{
	size_t aSize = astr.length();
	if (Size < aSize)
	{
		Acquare(aSize);
	}
	return Write((void *)astr.c_str(), astr.length() );
}
BOOL ScpMemoryObject::Write(void * src, ULONG pos, ULONG aSize)
{
	if ((pos < Size) && ((pos + aSize) <= Size))
	{
		memcpy((char *)Address+pos, src, aSize);
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::Write(std::wstring & wstr, ULONG pos)
{
	return Write((void *)wstr.c_str(), pos, wstr.length() * sizeof(wchar_t));
}
BOOL ScpMemoryObject::CopyTo(ScpMemoryObject * dest)
{
	if(dest!=NULL)
	{
		dest->ReleaseMem();
		dest->Acquare(this->Size);
		memcpy(dest->Address,this->Address,this->Size);
		return TRUE;
	}
	return FALSE;
}
BOOL ScpMemoryObject::CopyFrom(ScpMemoryObject * src)
{
	if(src!=NULL)
	{
		this->ReleaseMem();
		this->Acquare(src->Size);
		memcpy(this->Address,src->Address,src->Size);
		return TRUE;
	}
	return FALSE;
}
void ScpMemoryObject::Show(CScriptEngine * engine)
{
	engine->PrintError(ToString());
}
ScpObject * ScpMemoryObject::Clone(std::wstring strObjName)
{
	ScpMemoryObject * clonemem = new ScpMemoryObject();
	clonemem->Acquare(this->Size);
	return clonemem;
}	
std::wstring ScpMemoryObject::ToString()
{
	std::wstring text;
	if(Address)
	{			
		unsigned char  * temp =(unsigned char *)Address;
		wchar_t buffer[4]={0};
		for(ULONG i=0;i<Size;i++)
		{
#ifdef _WIN32
            StringCbPrintfW(buffer,_countof(buffer),L"%X",temp[i]);
#else 
			swprintf(buffer,4,L"%X",temp[i]);
#endif
			text+=buffer;				
		}			
	}
	return text;
}
void ScpMemoryObject::Release() 
{
	delete this;
}
ULONG ScpMemoryObject::GetSize()
{
	return Size;
}
void ScpMemoryObject::Clear()
{
	if(Address)
	{
		memset(Address,0,Size);
	}
}
int ScpMemoryObject::Find(const char * pattern)
{
	unsigned char * pos = (unsigned char *)MH_SearchPattern(Address, Size, (unsigned char *)pattern, strlen(pattern));
	if (pos)
	{
		return (pos -(unsigned char * )Address);
	}
	return 0;
}
bool ScpMemoryObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpMemoryObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;	
}

ScpObject * __stdcall ScpMemoryObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() >= 2)
	{
		int size = 0;
		std::wstring &memname = paramters->at(1);
		std::wstring memsize = L"0";
		if (paramters->size() == 3)
		{
			memsize = paramters->at(2);
		}
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(memname);
		if (obj)
		{
			//对象已存在
		}
		else
		{
			ScpIntObject * intobj = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(memsize);
			if (intobj && intobj->GetType() == ObjInt)
			{
				size = intobj->value;
			}
			else
			{
				if (IsStaticNumber(memsize))
				{
					size = StringToInt(memsize.c_str());
				}
			}
			ScpMemoryObject * mem = new ScpMemoryObject;
			if (mem)
			{
				mem->Acquare(size);
				return mem;
			}
		}
	}
	return NULL;
}

ScpObject * ScpMemoryObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpMemoryObject::InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * size = new ScpIntObject;
	if (size)
	{
		size->value =((ScpMemoryObject*)thisObject)->Size;
		size->istemp = true;
	}
	return size;
}

ScpObject * ScpMemoryObject::InnerFunction_acquire(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ULONG size = 0;
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (obj && obj->GetType() == ObjInt)
		{
			size = ((ScpIntObject*)obj)->value;
		}
		else
		{
			if (IsStaticNumber(param0))
			{
				size = StringToInt(param0);
			}
		}
		((ScpMemoryObject*)thisObject)->Acquare(size);
	}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpMemoryObject*)thisObject)->Clear();
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_encode(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	/*if (parameters->size() == 1)
	{
		std::wstring wsencodetype = parameters->at(0);
		if (wsencodetype == encodetypebase64)
		{
			ScpStringObject * objStr = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			if (objStr)
			{
				ScpEncryptLib ec;
				std::string temp = STDSTRINGEXT::WToA((wchar_t *)((ScpMemoryObject*)thisObject)->Address);
				((ScpStringObject *)objStr)->content = ec.Base64Encode((unsigned char *)temp.c_str(), temp.length());
				std::string as = STDSTRINGEXT::WToA(objStr->content);
				((ScpMemoryObject*)thisObject)->Write(as);
				return objStr;
			}
		}
	}*/
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_decode(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	//if (parameters->size() == 1)
	//{
	//	std::wstring wsdecodetype = parameters->at(0);
	//	if (wsdecodetype == encodetypebase64)
	//	{
	//		ScpStringObject * objStr = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
	//		if (objStr)
	//		{
	//			ScpEncryptLib ec;
	//			std::string temp = (char *)((ScpMemoryObject*)thisObject)->Address;
	//			objStr->content = ec.Base64Decode((unsigned char *)temp.c_str(), temp.length());
	//			std::string as = STDSTRINGEXT::WToA(objStr->content);
	//			((ScpMemoryObject*)thisObject)->Write(as);
	//			return objStr;
	//		}
	//	}
	//}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_encrypt(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	/*if (parameters->size() == 1)
	{
		std::wstring key = parameters->at(0);
		StringStripQuote(key);
		ScpStringObject * strobj1 = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(key);
		if (strobj1)
		{
			if (strobj1->GetType() == ObjString)
			{
				key = strobj1->content;
				ScpEncryptLib encryptlib;
				encryptlib.EncryptMemory((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), key, EncryptTypeAES);
			}
			else if (strobj1->GetType() == ObjMemory)
			{
				ScpEncryptLib encryptlib;
				encryptlib.EncryptMemoryBlock((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), (unsigned char*)((ScpMemoryObject*)strobj1)->Address, ((ScpMemoryObject*)strobj1)->Size * 8, EncryptTypeAES);
			}
		}
		else
		{
			ScpEncryptLib encryptlib;
			encryptlib.EncryptMemory((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), key, EncryptTypeAES);
		}

	}*/
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_decrypt(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	/*if (parameters->size() == 1)
	{
		std::wstring key = parameters->at(0);
		StringStripQuote(key);
		ScpStringObject * strobj1 = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(key);
		if (strobj1)
		{
			if (strobj1->GetType() == ObjString)
			{
				key = strobj1->content;
				ScpEncryptLib encryptlib;
				encryptlib.DecryptMemory((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), key, EncryptTypeAES);
			}
			else if (strobj1->GetType() == ObjMemory)
			{
				ScpEncryptLib encryptlib;
				encryptlib.DecryptMemoryBlock((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), (unsigned char*)((ScpMemoryObject*)strobj1)->Address, ((ScpMemoryObject*)strobj1)->Size * 8, EncryptTypeAES);
			}

		}
		else
		{
			ScpEncryptLib encryptlib;
			encryptlib.DecryptMemory((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), key, EncryptTypeAES);
		}

	}*/
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring objname = parameters->at(0);
		StringStripQuote(objname);
		ScpObject *obj1 = engine->GetCurrentObjectSpace()->FindObject(objname);
		if (obj1)
		{
			if (obj1->GetType() == ObjString)
			{
				((ScpMemoryObject*)thisObject)->Read(((ScpStringObject *)obj1)->content);
			}
			else if (obj1->GetType() == ObjInt)
			{
				((ScpMemoryObject*)thisObject)->Read(&((ScpIntObject *)obj1)->value, sizeof(int));
			}
		}

	}
	else if (parameters->size() == 2)
	{
		ULONG ulpos = 0;
		std::wstring pos = parameters->at(0);
		std::wstring objname = parameters->at(1);
		StringStripQuote(pos);
		StringStripQuote(objname);
		ScpObject *obj = engine->GetCurrentObjectSpace()->FindObject(pos);
		if (obj)
		{
			if (obj->GetType() == ObjInt)
			{
				ulpos = ((ScpIntObject *)obj)->value;
			}
		}
		else
		{
			if (IsStaticNumber(pos))
			{
				ulpos = StringToInt(pos);
			}
		}
		ScpObject *obj1 = engine->GetCurrentObjectSpace()->FindObject(objname);
		if (obj1)
		{
			if (obj1->GetType() == ObjInt)
			{
				((ScpMemoryObject*)thisObject)->Read(&((ScpIntObject *)obj1)->value, ulpos, sizeof(int));
			}
		}

	}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring objname = parameters->at(0);
		StringStripQuote(objname);
		ScpObject *obj1 = engine->GetCurrentObjectSpace()->FindObject(objname);
		if (obj1)
		{
			if (obj1->GetType() == ObjString)
			{
				((ScpMemoryObject*)thisObject)->Write(((ScpStringObject *)obj1)->content);
			}
			else if (obj1->GetType() == ObjInt)
			{
				((ScpMemoryObject*)thisObject)->Write(&((ScpIntObject *)obj1)->value, sizeof(int));
			}
		}
	}
	else if (parameters->size() == 2)
	{
		ULONG ulpos = 0;
		std::wstring pos = parameters->at(0);
		std::wstring objname = parameters->at(1);
		StringStripQuote(pos);
		StringStripQuote(objname);
		ScpObject *obj = engine->GetCurrentObjectSpace()->FindObject(pos);
		if (obj)
		{
			if (obj->GetType() == ObjInt)
			{
				ulpos = ((ScpIntObject *)obj)->value;
			}
		}
		else
		{
			if (IsStaticNumber(pos))
			{
				ulpos = StringToInt(pos);
			}
		}
		ScpObject *obj1 = engine->GetCurrentObjectSpace()->FindObject(objname);
		if (obj1)
		{
			if (obj1->GetType() == ObjInt)
			{
				((ScpMemoryObject*)thisObject)->Write(&((ScpIntObject *)obj1)->value, ulpos, sizeof(int));
			}
		}
	}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_release(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpMemoryObject*)thisObject)->ReleaseMem();
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_compare(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring str1 = parameters->at(0);
		StringStripQuote(str1);
		ScpIntObject * compare_ret = new ScpIntObject;
		compare_ret->istemp = true;
		compare_ret->value = 0;
		ScpMemoryObject *obj1 = (ScpMemoryObject *)engine->GetCurrentObjectSpace()->FindObject(str1);
		if (obj1)
		{
			if (((ScpMemoryObject*)thisObject)->Size == obj1->Size)
			{
				if (memcmp(((ScpMemoryObject*)thisObject)->Address, obj1->Address, ((ScpMemoryObject*)thisObject)->Size) == 0)
				{
					compare_ret->value = 1;
				}
			}
		}
		return compare_ret;
	}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_extend(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		ULONG exSize = 0;
		std::wstring exsizestr = parameters->at(0);
		StringStripQuote(exsizestr);
		ScpIntObject *intojb = (ScpIntObject *)engine->GetCurrentObjectSpace()->FindObject(exsizestr);
		if (intojb && intojb->GetType() == ObjInt)
		{
			exSize = intojb->value;
		}
		else
		{
			exSize = StringToInt(exsizestr);
		}
		((ScpMemoryObject*)thisObject)->Extend(exSize);
	}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_hash(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	//if (parameters->size() == 1)
	//{
	//	std::wstring hashtype = parameters->at(0);
	//	StringStripQuote(hashtype);
	//	ScpStringObject * strobjhashtype = (ScpStringObject*)engine->GetCurrentObjectSpace()->FindObject(hashtype);
	//	if (strobjhashtype)
	//	{
	//		hashtype = strobjhashtype->content;
	//	}
	//	if (hashtype == HashTypeMd5)
	//	{
	//		ScpMemoryObject * memobj = (ScpMemoryObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjMemory);
	//		if (memobj)
	//		{
	//			memobj->Acquare(16);
	//			ScpEncryptLib encryptlib;
	//			encryptlib.HashMemory((unsigned char *)((ScpMemoryObject*)thisObject)->Address, ((ScpMemoryObject*)thisObject)->GetSize(), (unsigned char *)memobj->Address, memobj->GetSize(), hashtype);

	//		}
	//	}
	//}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring patternstr = parameters->at(0);
		StringStripQuote(patternstr);
		ScpStringObject *obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(patternstr);
		if (obj && obj->GetType() == ObjString)
		{
			patternstr = obj->content;
		}

		ScpIntObject * objInt = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		if (objInt)
		{
			std::string pa = STDSTRINGEXT::WToA(patternstr);
			objInt->value = ((ScpMemoryObject*)thisObject)->Find(pa.c_str());
			return objInt;
		}
	}
	return nullptr;
}

ScpObject * ScpMemoryObject::InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring memsrc = parameters->at(0);
		StringStripQuote(memsrc);
		ScpMemoryObject *obj = (ScpMemoryObject *)engine->GetCurrentObjectSpace()->FindObject(memsrc);
		if (obj && obj->GetType() == ObjMemory)
		{
			((ScpMemoryObject*)thisObject)->CopyFrom(obj);
			return thisObject;
		}
	}
	return nullptr;
}
