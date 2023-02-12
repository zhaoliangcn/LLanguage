#include "ScpPipeObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpGlobalObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpObject *  __stdcall PipeObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() == 3)
	{
		ScpPipeObject * pipeobj = new ScpPipeObject();
		std::string pipename = paramters->at(2);
		StringStripQuote(pipename);
		pipeobj->wsPipeName = pipename;
		return pipeobj;
	}
	return NULL;
}
BOOL WINAPI Pipe_Open_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string strobj = vtparameters->at(0);
		std::string userobjname = vtparameters->at(1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjPipe == type)
		{
			ScpPipeObject * obj = (ScpPipeObject *)currentObjectSpace->FindObject(userobjname);
			if (obj && obj->GetType() == ObjPipe)
			{
				std::string func = scpcommand_en_open;
				((ScpPipeObject*)obj)->CallInnerFunction(func, NULL, engine);
				return TRUE;
			}
		}		
	}	
	return FALSE;
}

BOOL WINAPI Pipe_Write_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 3)
	{
		std::string memobj = vtparameters->at(0);
		std::string name = vtparameters->at(1);
		std::string objname = vtparameters->at(2);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(memobj.c_str());
		
		if (ObjPipe == type)
		{
			ScpPipeObject * pipe = (ScpPipeObject*)currentObjectSpace->FindObject(name);
			if (pipe)
			{
				if (pipe->GetType() == ObjPipe)
				{

					std::string func = scpcommand_en_write;
					VTPARAMETERS param;
					param.push_back(objname);
					((ScpPipeObject*)pipe)->CallInnerFunction(func, &param, engine);

					/*ScpStringObject *strobj1=(ScpStringObject *)currentObjectSpace->FindObject(objname);
					if(strobj1)
					{
					if(strobj1->GetType()==ObjString)
					{
					std::string content = STDSTRINGEXT::WToA(strobj1->content);
					pipe->Write(content.c_str(),content.length());
					}
					}*/
					return TRUE;
				}
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
			if (ObjPipe == type)
			{
				ScpPipeObject * pipe = (ScpPipeObject*)currentObjectSpace->FindObject(name);
				if (pipe)
				{

					std::string func = scpcommand_en_write;
					VTPARAMETERS param;
					param.push_back(objname);
					((ScpPipeObject*)pipe)->CallInnerFunction(func, &param, engine);
					/*ScpStringObject *strobj1=(ScpStringObject *)currentObjectSpace->FindObject(objname);
					if(strobj1)
					{
					if(strobj1->GetType()==ObjString)
					{
					std::string content = STDSTRINGEXT::WToA(strobj1->content);
					pipe->Write(content.c_str(),content.length());
					}
					}*/
					return TRUE;
				}

			}
		}
	}

	return FALSE;
}
BOOL WINAPI Pipe_Read_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
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
			if (ObjPipe == type)
			{
				ScpPipeObject * pipe = (ScpPipeObject*)currentObjectSpace->FindObject(name);
				if (pipe)
				{

					//std::string func = scpcommand_en_read;
					//VTPARAMETERS param;
					//param.push_back(objname);
					//((ScpPipeObject*)pipe)->CallInnerFunction(func, &param, engine);


					ScpStringObject *strobj1=(ScpStringObject *)currentObjectSpace->FindObject(objname);
					if(strobj1)
					{
						if(strobj1->GetType()==ObjString)
						{
							char * buffer = (char *)malloc(1024);
							if(buffer)
							{
								memset(buffer,0,1024);
								pipe->Read(buffer,1024);
								strobj1->content =buffer;
								free(buffer);
							}
						}
					}
				}
			}
			
		}
	}
	else if (vtparameters->size() == 3)
	{
		std::string memobj = vtparameters->at(0);
		std::string memname = vtparameters->at(1);
		std::string objname = vtparameters->at(2);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(memobj.c_str());
		if (ObjPipe == type)
		{
			ScpPipeObject * pipe = (ScpPipeObject*)currentObjectSpace->FindObject(memname);
			if (pipe)
			{
				if (pipe->GetType() == ObjPipe)
				{
/*					std::string func = scpcommand_en_read;
					VTPARAMETERS param;
					param.push_back(objname);
					ScpStringObject *str = (ScpStringObject *)((ScpPipeObject*)pipe)->CallInnerFunction(func, &param, engine);

					ScpStringObject *strobj1 = (ScpStringObject *)currentObjectSpace->FindObject(objname);
					if (strobj1)
					{
						if (strobj1->GetType() == ObjString)
						{

							if (str)
							{
								strobj1->content = str->content;
							}
						}
					}
*/

					ScpStringObject *strobj1 = (ScpStringObject *)currentObjectSpace->FindObject(objname);
					if (strobj1)
					{
						if (strobj1->GetType() == ObjString)
						{
							char * buffer = (char *)malloc(1024);
							if (buffer)
							{
								memset(buffer, 0, 1024);
								pipe->Read(buffer, 1024);
								strobj1->content = buffer;
								free(buffer);
							}
						}
					}

				}				
			}
		}
	}
	return TRUE;
}
ScpPipeObject::ScpPipeObject(void)
{
	hPipe = NULL;
	objecttype = ObjPipe;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_read, InnerFunction_read);
	BindObjectInnerFuction(scpcommand_en_read, InnerFunction_read);

	BindObjectInnerFuction(scpcommand_cn_write, InnerFunction_write);
	BindObjectInnerFuction(scpcommand_en_write, InnerFunction_write);

	BindObjectInnerFuction(scpcommand_cn_close, InnerFunction_close);
	BindObjectInnerFuction(scpcommand_en_close, InnerFunction_close);

	BindObjectInnerFuction(scpcommand_cn_open, InnerFunction_open);
	BindObjectInnerFuction(scpcommand_en_open, InnerFunction_open);
}

ScpPipeObject::~ScpPipeObject(void)
{
}

ScpObject * ScpPipeObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpPipeObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpPipeObject::InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpStringObject *strobj1 = new ScpStringObject;
	if (strobj1)
	{
		char * buffer = (char *)malloc(1024);
		if (buffer)
		{
			memset(buffer, 0, 1024);
			((ScpPipeObject*)thisObject)->Read(buffer, 1024);
			strobj1->content =buffer;
			free(buffer);

		}
		strobj1->istemp = true;
		return strobj1;
	}
	return nullptr;
}

ScpObject * ScpPipeObject::InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string objname = parameters->at(0);
		ScpStringObject *strobj1 = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(objname);
		if (strobj1)
		{
			if (strobj1->GetType() == ObjString)
			{
				std::string content =strobj1->content;
				((ScpPipeObject*)thisObject)->Write(content.c_str(), content.length());
			}
		}
	}
	return nullptr;
}

ScpObject * ScpPipeObject::InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpPipeObject*)thisObject)->CLose();
	return nullptr;
}

ScpObject * ScpPipeObject::InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpPipeObject*)thisObject)->Open(STDSTRINGEXT::UTF2W(((ScpPipeObject*)thisObject)->wsPipeName).c_str());
	return nullptr;
}

ScpObject * ScpPipeObject::Clone(std::string strObjName)
{
	ScpPipeObject * obj = new ScpPipeObject;
	if (obj)
	{
		obj->wsPipeName = wsPipeName;
		return obj;
	}
	return NULL;
}	
std::string ScpPipeObject::ToString()
{
	std::string temp;
	return temp;
}
void ScpPipeObject::Release() 
{
	delete this;
}
void ScpPipeObject::Show(CScriptEngine * engine)
{

}
BOOL ScpPipeObject::Open(const wchar_t * PipeName)
{
#ifdef _WIN32
	hPipe=Pipe.OpenNamedPipeClient(PipeName);
	if(!hPipe)
	{
		hPipe=Pipe.CreateNamedPipeServer(PipeName);
		if(hPipe)
		{
			Pipe.PipeWait(hPipe);
		}
	}
#endif
	return TRUE;
}
BOOL ScpPipeObject::Read(char * Buffer,DWORD Len)
{
#ifdef _WIN32
	return Pipe.ReadPipe(hPipe,Buffer,Len);
#else 
	return TRUE;
#endif
}
BOOL ScpPipeObject::Write(const char * Buffer,DWORD Len)
{
#ifdef _WIN32
	return Pipe.WritePipe(hPipe,Buffer,Len);
#else 
	return TRUE;
#endif
}
void ScpPipeObject::CLose()
{
#ifdef _WIN32
	Pipe.ClosePipe(hPipe);
#endif
}
bool ScpPipeObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpPipeObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}	
	return NULL;
}