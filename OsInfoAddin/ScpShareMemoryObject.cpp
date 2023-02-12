#include "ScpShareMemoryObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpObject *  __stdcall ShareMemroyObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters)
	{
		if (paramters->size() == 4)
		{
			ScpObject * sharemem = new ScpShareMemoryObject();
			if (sharemem)
			{
				ScpShareMemoryObject  * sharememobj = (ScpShareMemoryObject  *)sharemem;
				std::string sharename = paramters->at(2);
				std::string strSize = paramters->at(3);
				size_t size = 0;
				size = StringToInt(strSize);
				sharememobj->sharememSize = size;
				sharememobj->sharememName = sharename;
				return sharememobj;
			}

		}
	}
	return NULL;
}
BOOL WINAPI ShareMemory_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
		if (vtparameters->size() == 1)
		{
			std::string text = vtparameters->at(0);
			{
				ScpObject *obj = (ScpObject *)currentObjectSpace->FindObject(text);
				if (obj)
				{
					if (obj->GetType() == ObjShareMemory)
					{
						std::string func = scpcommand_en_close;
						((ScpShareMemoryObject*)obj)->CallInnerFunction(func, NULL, engine);
						return TRUE;
					}
				}
			}
		}
		else if (vtparameters->size() == 2)
		{
			std::string strobj = vtparameters->at(0);
			std::string text = vtparameters->at(1);
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
			if (ObjShareMemory == type)
			{
				ScpObject * obj = currentObjectSpace->FindObject(text);
				if (obj)
				{
					std::string func = scpcommand_en_close;
					((ScpShareMemoryObject*)obj)->CallInnerFunction(func, NULL, engine);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
BOOL WINAPI ShareMemory_Open_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
		if (vtparameters->size() == 2)
		{
			std::string strobj = vtparameters->at(0);
			std::string userobjname = vtparameters->at(1);
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
			if (ObjShareMemory == type)
			{
				ScpShareMemoryObject * obj = (ScpShareMemoryObject*)currentObjectSpace->FindObject(userobjname);
				if (obj)
				{
					if (obj->GetType() == ObjShareMemory)
					{
						//obj->Open(obj->sharememName,obj->sharememSize);	
						std::string func = scpcommand_en_open;
						((ScpShareMemoryObject*)obj)->CallInnerFunction(func, NULL, engine);
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}
BOOL WINAPI ShareMemory_Write_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	if (vtparameters)
	{
		ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
		if (vtparameters->size() == 3)
		{
			std::string memobj = vtparameters->at(0);
			std::string name = vtparameters->at(1);
			std::string objname = vtparameters->at(2);
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(memobj.c_str());
			if (ObjShareMemory == type)
			{
				ScpObject * obj = currentObjectSpace->FindObject(name);
				if (obj)
				{
					std::string func = scpcommand_en_write;
					VTPARAMETERS param;
					param.push_back(objname);
					((ScpShareMemoryObject*)obj)->CallInnerFunction(func, &param, engine);

					/*ScpObject *strobj1=currentObjectSpace->FindObject(objname);
					if(strobj1)
					{
					if(strobj1->GetType()==ObjString)
					{
					((ScpShareMemoryObject*)obj)->Write(((ScpStringObject*)strobj1)->content);
					}
					}*/
					return TRUE;
				}
			}
		}
		else if (vtparameters->size() == 2)
		{
			std::string name = vtparameters->at(0);
			std::string objname = vtparameters->at(1);
			ScpObject * obj = currentObjectSpace->FindObject(name);
			if (obj)
			{
				ScpObjectType type = obj->GetType();
				if (ObjShareMemory == type)
				{
					ScpObject * obj = currentObjectSpace->FindObject(name);
					if (obj)
					{
						std::string func = scpcommand_en_write;
						VTPARAMETERS param;
						param.push_back(objname);
						((ScpShareMemoryObject*)obj)->CallInnerFunction(func, &param, engine);

						/*ScpObject *strobj1=currentObjectSpace->FindObject(objname);
						if(strobj1)
						{
						if(strobj1->GetType()==ObjString)
						{
						((ScpShareMemoryObject*)obj)->Write(((ScpStringObject*)strobj1)->content);
						}
						}*/
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}
BOOL WINAPI ShareMemory_Read_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string name = vtparameters->at(0);
		std::string objname = vtparameters->at(1);
		ScpObject * obj = currentObjectSpace->FindObject(name);
		if (obj)
		{
			ScpObjectType type = obj->GetType();
			if (ObjShareMemory == type)
			{
				ScpObject * obj = currentObjectSpace->FindObject(name);
				if (obj)
				{
					ScpObject *strobj1 = currentObjectSpace->FindObject(objname);
					if (strobj1)
					{
						if (strobj1->GetType() == ObjString)
						{
							std::string func = scpcommand_en_read;
							ScpStringObject * str = (ScpStringObject *)((ScpShareMemoryObject*)obj)->CallInnerFunction(func, NULL, engine);
							if (str)
							{
								((ScpStringObject*)strobj1)->content = str->content;
							}
						}
					}
				}
				return TRUE;
			}
		}

	}
	else if (vtparameters->size() == 3)
	{
		std::string memobj = vtparameters->at(0);
		std::string memname = vtparameters->at(1);
		std::string objname = vtparameters->at(2);

		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(memobj.c_str());

		if (ObjShareMemory == type)
		{
			ScpObject * obj = currentObjectSpace->FindObject(memname);
			if (obj)
			{
				ScpObject *strobj1 = currentObjectSpace->FindObject(objname);
				if (strobj1)
				{
					if (strobj1->GetType() == ObjString)
					{
						std::string func = scpcommand_en_read;
						ScpStringObject * str = (ScpStringObject *)((ScpShareMemoryObject*)obj)->CallInnerFunction(func, NULL, engine);
						if (str)
						{
							((ScpStringObject*)strobj1)->content = str->content;
						}
					}
				}
				/*ScpObject *strobj1 = currentObjectSpace->FindObject(objname);
				if (strobj1)
				{
				if (strobj1->GetType() == ObjString)
				{
				((ScpShareMemoryObject*)obj)->Read(((ScpStringObject*)strobj1)->content);
				}
				}*/
			}
			return TRUE;
		}

	}
	return FALSE;
}
ScpShareMemoryObject::ScpShareMemoryObject(void)
{
#ifdef WIN32
	pwinsharemem = NULL;
#endif
	objecttype = ObjShareMemory;


	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_close, InnerFunction_close);
	BindObjectInnerFuction(scpcommand_en_close, InnerFunction_close);

	BindObjectInnerFuction(scpcommand_cn_open, InnerFunction_open);
	BindObjectInnerFuction(scpcommand_en_open, InnerFunction_open);


	BindObjectInnerFuction(scpcommand_cn_read, InnerFunction_read);
	BindObjectInnerFuction(scpcommand_en_read, InnerFunction_read);


	BindObjectInnerFuction(scpcommand_cn_write, InnerFunction_write);
	BindObjectInnerFuction(scpcommand_en_write, InnerFunction_write);

}

ScpShareMemoryObject::~ScpShareMemoryObject(void)
{
}


void ScpShareMemoryObject::Show(CScriptEngine * engine)
{

}
ScpObject * ScpShareMemoryObject::Clone(std::string strObjName)
{
	ScpShareMemoryObject *obj = new ScpShareMemoryObject;
	if (obj)
	{
		obj->sharememName = sharememName;
		obj->sharememSize = sharememSize;
		return obj;
	}
	return NULL;
}
std::string ScpShareMemoryObject::ToString()
{
	std::string temp;
	return temp;
}
void ScpShareMemoryObject::Release()
{
	delete this;
}
bool ScpShareMemoryObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpShareMemoryObject::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}	
	return NULL;
}
BOOL ScpShareMemoryObject::Open(std::string Name, size_t Size)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	if (pwinsharemem == NULL)
	{
		pwinsharemem = new WindowsShareMemory(Size);
		if (pwinsharemem->OpenShareMemory(STDSTRINGEXT::UTF2W(Name).c_str()) != 0)
		{
			if (pwinsharemem->CreateShareMemory(STDSTRINGEXT::UTF2W(Name).c_str()) == 0)
			{
				bRet = TRUE;
			}
		}
		else
		{
			bRet = TRUE;
		}
	}
#else
	std::string shname = "/dev/shm/" + Name;
	key = ftok(shname.c_str(), 0);
	if (key != -1)
	{
		shm_id = shmget(key, Size, IPC_CREAT);
		if (shm_id != -1)
		{
			m_map = (void*)shmat(shm_id, NULL, 0);
		}
	}

#endif
	return bRet;
	}
BOOL ScpShareMemoryObject::Read(void * pBuffer, DWORD dwReadPos, DWORD dwReadCount)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	if (pwinsharemem)
	{
		if (pwinsharemem->ReadShareMemory(pBuffer, dwReadPos, dwReadCount) == 0)
		{
			bRet = TRUE;
		}
	}
#else
	memcpy(pBuffer, (char *)m_map + dwReadPos, dwReadCount);
	bRet = TRUE;
#endif
	return bRet;

	}
BOOL ScpShareMemoryObject::Write(void * pBuffer, DWORD dwWritePos, DWORD dwWriteCount)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	if (pwinsharemem)
	{
		if (pwinsharemem->WriteShareMemory(pBuffer, dwWritePos, dwWriteCount) == 0)
		{
			bRet = TRUE;
		}
	}
#else
	memcpy((char*)m_map + dwWritePos, pBuffer, dwWriteCount);
#endif
	return bRet;
	}
BOOL ScpShareMemoryObject::Close()
{
#ifdef _WIN32
	if (pwinsharemem)
	{
		delete	pwinsharemem;
		pwinsharemem = NULL;
	}
#else
	shmdt(m_map);
#endif
	return TRUE;
	}
ScpObject * ScpShareMemoryObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpShareMemoryObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
ScpObject * ScpShareMemoryObject::InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpStringObject *strobj1 = new ScpStringObject;
	if (strobj1)
	{
		((ScpShareMemoryObject*)thisObject)->Read(strobj1->content);
		strobj1->istemp = true;
		return strobj1;
	}
	return nullptr;
}
ScpObject * ScpShareMemoryObject::InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string objname = parameters->at(0);
		StringStripQuote(objname);
		ScpStringObject *strobj1 = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(objname);
		if (strobj1)
		{
			if (strobj1->GetType() == ObjString)
			{
				objname = strobj1->content;

			}
		}
		((ScpShareMemoryObject*)thisObject)->Write(objname);
	}
	return nullptr;
}
ScpObject * ScpShareMemoryObject::InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{

	((ScpShareMemoryObject*)thisObject)->Close();
	return nullptr;
}
ScpObject * ScpShareMemoryObject::InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters)
	{
		if (parameters->size() == 2)
		{
			std::string sharename = parameters->at(0);
			std::string strSize = parameters->at(1);
			size_t size = 0;
			
			ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(sharename);
			if (objparam0 && objparam0->GetType() == ObjString)
			{
				sharename = ((ScpStringObject *)objparam0)->content;
			}

			ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(strSize);
			if (objparam1 && objparam1->GetType() == ObjInt)
			{
				size = ((ScpIntObject *)objparam1)->value;
			}
			else
			{
				size = StringToInt(strSize);
			}
			
			((ScpShareMemoryObject*)thisObject)->Open(sharename, size);
		}
	}
	else
	{
		((ScpShareMemoryObject*)thisObject)->Open(((ScpShareMemoryObject*)thisObject)->sharememName, ((ScpShareMemoryObject*)thisObject)->sharememSize);
	}
	return nullptr;
}
BOOL ScpShareMemoryObject::Read(std::string & content)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	if (pwinsharemem)
	{
		content = (char*)pwinsharemem->GetShareMemoryAddress();
		bRet = TRUE;
	}
#else
	content = (char*)m_map;
#endif
	return bRet;
	}
BOOL ScpShareMemoryObject::Write(std::string & content)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	if (pwinsharemem)
	{
		bRet = pwinsharemem->WriteShareMemory((void *)content.c_str(), 0, content.length() * sizeof(wchar_t));
	}
#else
	memcpy(m_map, (void*)content.c_str(), content.length() * sizeof(wchar_t));
#endif
	return bRet;
	}