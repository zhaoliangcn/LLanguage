/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//全局命令的组织管理
//把一行脚本当作一个命令，或者说是一个函数调用
*/
#include "ScpGlobalCommandObject.h"
#include "commanddefine_uni.h"
#include "ScriptEngine.h"
#include "ScpObjectNammes.h"
//#include "../Common/stdstringext.hpp"

ScpGlobalCommandObject::ScpGlobalCommandObject(void)
{
#ifdef USE_GOOGLE_HASHMAP
	chscommandmap.set_empty_key(L"");
	chscommandmap.set_deleted_key(L"");
#endif
	objecttype = ObjGlobalCommand;
}


ScpGlobalCommandObject::~ScpGlobalCommandObject(void)
{
}


void ScpGlobalCommandObject::Show(CScriptEngine * engine)
{
		
	engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorGlobalComand);
}
ScpObject * ScpGlobalCommandObject::Clone(std::string strObjName)
{
	return NULL;
}	
std::string ScpGlobalCommandObject::ToString()
{
	std::string temp;
	return temp;
}
void ScpGlobalCommandObject::Release() 
{
	delete this;
}
bool ScpGlobalCommandObject::IsInnerFunction(std::string & functionname)
{
	if (functionname == scpcommand_cn_show || functionname == scpcommand_en_show)
	{
		return true;
	}
	return false;
}
ScpObject * ScpGlobalCommandObject::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (functionname == scpcommand_cn_show || functionname == scpcommand_en_show)
	{
		Show(engine);
		return this;
	}
	return NULL;
}
void ScpGlobalCommandObject::InitBaseCommand()
{
	
	chscommandmap[scpcommand_cn_reserved] = vl_reserved ;
	chscommandmap[scpcommand_cn_do]=vl_do;
	chscommandmap[scpcommand_cn_compute]=vl_compute;
	chscommandmap[scpcommand_cn_define]=vl_define;
	chscommandmap[scpcommand_cn_test]=vl_test;
	chscommandmap[scpcommand_cn_end]=vl_end;
	chscommandmap[scpcommand_cn_call]=vl_call;
	chscommandmap[scpcommand_cn_invalid]=vl_invalid;
	chscommandmap[scpcommand_cn_import]=vl_import;
	chscommandmap[scpcommand_cn_while]=vl_while;
	chscommandmap[scpcommand_cn_register]=vl_register;
	chscommandmap[scpcommand_cn_wait]=vl_wait;
	chscommandmap[scpcommand_cn_otherwise]=vl_otherwise;
	chscommandmap[scpcommand_cn_inherit]=vl_inherit;
	chscommandmap[scpcommand_cn_load]=vl_load;
	chscommandmap[scpcommand_cn_exit]=vl_exit;
	chscommandmap[scpcommand_cn_continue]=vl_continue;
	chscommandmap[scpcommand_cn_break]=vl_break;
	chscommandmap[scpcommand_cn_switch]=vl_switch;
	chscommandmap[scpcommand_cn_case]=vl_case;
	chscommandmap[scpcommand_cn_loop]=vl_loop;
	chscommandmap[scpcommand_cn_public]=vl_public;
	chscommandmap[scpcommand_cn_private]=vl_private;
	chscommandmap[scpcommand_cn_return]=vl_return;



	engcommandmap[scpcommand_en_reserved] = vl_reserved ;
	engcommandmap[scpcommand_en_do]=vl_do;
	engcommandmap[scpcommand_en_compute]=vl_compute;
	engcommandmap[scpcommand_en_define]=vl_define;
	engcommandmap[scpcommand_en_test]=vl_test;
	engcommandmap[scpcommand_en_if] = vl_test;
	engcommandmap[scpcommand_en_else] = vl_otherwise;
	engcommandmap[scpcommand_en_end]=vl_end;
	engcommandmap[scpcommand_en_call]=vl_call;
	engcommandmap[scpcommand_en_invalid]=vl_invalid;
	engcommandmap[scpcommand_en_import]=vl_import;
	engcommandmap[scpcommand_en_while]=vl_while;
	engcommandmap[scpcommand_en_register]=vl_register;
	engcommandmap[scpcommand_en_wait]=vl_wait;
	engcommandmap[scpcommand_en_otherwise]=vl_otherwise;
	engcommandmap[scpcommand_en_inherit]=vl_inherit;
	engcommandmap[scpcommand_en_load]=vl_load;
	engcommandmap[scpcommand_en_exit]=vl_exit;
	engcommandmap[scpcommand_en_continue]=vl_continue;
	engcommandmap[scpcommand_en_break]=vl_break;	
	engcommandmap[scpcommand_en_switch]=vl_switch;
	engcommandmap[scpcommand_en_case]=vl_case;
	engcommandmap[scpcommand_en_loop]=vl_loop;	
	engcommandmap[scpcommand_en_public]=vl_public;	
	engcommandmap[scpcommand_en_private]=vl_private;	
	engcommandmap[scpcommand_en_return]=vl_return;	
}
ULONG ScpGlobalCommandObject::QueryCommand(std::string commandstring)
{
	ITCHSCOMMANDMAP it ;
	it = chscommandmap.find(commandstring);
	if (it != chscommandmap.end())
	{
		return it->second;
	}
	it = engcommandmap.find(commandstring);
	if (it != engcommandmap.end())
	{
		return it->second;
	}
	return QueryExtCommand(commandstring);
}
BOOL ScpGlobalCommandObject::RegisterCommand(int lang, std::string commandstring,ULONG commandvalue)
{
	ITCHSCOMMANDMAP it ;
	if(lang ==0)
	{
		it = chscommandmap.find(commandstring);
		if(it==chscommandmap.end())
		{
			chscommandmap[commandstring]=commandvalue;
			return TRUE;
		}
	}
	else if(lang ==1)
	{
		it = engcommandmap.find(commandstring);
		if(it==engcommandmap.end())
		{
			engcommandmap[commandstring]=commandvalue;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ScpGlobalCommandObject::UnRegisterCommand(int lang, std::string commandstring)
{
	ITCHSCOMMANDMAP it ;
	if(lang ==0)
	{
		it = chscommandmap.find(commandstring);
		if(it!=chscommandmap.end())
		{
			chscommandmap.erase(it);
			return TRUE;
		}
	}
	else if(lang ==1)
	{
		it = engcommandmap.find(commandstring);
		if(it!=engcommandmap.end())
		{
			engcommandmap.erase(it);
			return TRUE;
		}
	}
	return FALSE;
}

bool ScpGlobalCommandObject::RegisterGlobalFunction(std::string chscommandstring, std::string engcommandstring, DWORD commandid, GlobalCommandFunction Func)
{
	ULONG command = QueryCommand(engcommandstring);
	if (command == -1)
	{
		if (RegisterCommand(0, chscommandstring, commandid))
		{
			RegisterCommand(1, engcommandstring, commandid);
			if (idcommnadmap.find(commandid) == idcommnadmap.end())
			{
				idcommnadmap[commandid] = Func;
				return true;
			}
		}
		
	}	
	return false;
}

GlobalCommandFunction ScpGlobalCommandObject::GetGlobalCommandFunction(std::string commandstring)
{
	ULONG command = QueryCommand(commandstring);
	return GetGlobalCommandFunction(command);
}

GlobalCommandFunction ScpGlobalCommandObject::GetGlobalCommandFunction(DWORD commandid)
{
	if (idcommnadmap.find(commandid) != idcommnadmap.end())
	{
		return idcommnadmap[commandid];
	}
	return GlobalCommandFunction();
}

bool ScpGlobalCommandObject::IsGlobalCommandFunction(std::string commandstring)
{
	GlobalCommandFunction func = GetGlobalCommandFunction(commandstring);
	if(func == nullptr)
		return false;
	else
		return true;
}

bool ScpGlobalCommandObject::IsGlobalCommandFunction(DWORD commandid)
{
	GlobalCommandFunction func = GetGlobalCommandFunction(commandid);
	if(func == nullptr)
		return false;
	else
		return true;	
}

BOOL ScpGlobalCommandObject::RegistExtCommand(ExtObjectCommand extobjcmd)
{
	if (GetExtCommandFunctionCount(extobjcmd.dwCommandId) > 0)
	{
		for (size_t i = 0; i < extobjcmdlist.size(); i++)
		{
			ExtObjectCommand & cmd = extobjcmdlist.at(i);
			if (cmd.dwCommandId == extobjcmd.dwCommandId)
			{
				for (size_t j = 0; j < extobjcmd.CommandNames.size(); j++)
				{
					BOOL bNotFind = TRUE;
					for (size_t l = 0; l < cmd.CommandNames.size(); l++)
					{
						if (cmd.CommandNames.at(l) == extobjcmd.CommandNames.at(j))
						{
							bNotFind = FALSE;
							break;
						}
					}
					if (bNotFind)
					{
						cmd.CommandNames.push_back(extobjcmd.CommandNames.at(j));
					}
				}

				for (size_t j = 0; j < extobjcmd.ExtCommands.size(); j++)
				{
					cmd.ExtCommands.push_back(extobjcmd.ExtCommands.at(j));
				}
			}
		}
	}
	else
	{
		extobjcmdlist.push_back(extobjcmd);
	}
	return TRUE;
}

ULONG ScpGlobalCommandObject::QueryExtCommand(std::string commandstring)
{
	for (size_t i = 0; i < extobjcmdlist.size(); i++)
	{
		ExtObjectCommand & extobjcmd = extobjcmdlist.at(i);
		for (size_t j = 0; j < extobjcmd.CommandNames.size(); j++)
		{
			if (commandstring == extobjcmd.CommandNames.at(j))
			{
				return extobjcmd.dwCommandId;
			}
		}
	}
	return -1;
}

size_t ScpGlobalCommandObject::GetExtCommandFunctionCount(std::string commandstring)
{
	for (size_t i = 0; i < extobjcmdlist.size(); i++)
	{
		ExtObjectCommand & extobjcmd = extobjcmdlist.at(i);
		for (size_t j = 0; j < extobjcmd.CommandNames.size(); j++)
		{
			if (commandstring == extobjcmd.CommandNames.at(j))
			{
				return extobjcmd.ExtCommands.size();
			}
		}
	}
	return 0;
}

size_t ScpGlobalCommandObject::GetExtCommandFunctionCount(DWORD commandid)
{
	for (size_t i = 0; i < extobjcmdlist.size(); i++)
	{
		ExtObjectCommand & extobjcmd = extobjcmdlist.at(i);
		if (extobjcmd.dwCommandId == commandid)
		{
			return extobjcmd.ExtCommands.size();
		}
	}
	return 0;
}

ExtObjectCommandFunction ScpGlobalCommandObject::GetExtCommandFunctionAddress(std::string commandstring, size_t index)
{
	for (size_t i = 0; i < extobjcmdlist.size(); i++)
	{
		ExtObjectCommand & extobjcmd = extobjcmdlist.at(i);
		for (size_t j = 0; j < extobjcmd.CommandNames.size(); j++)
		{
			if (commandstring == extobjcmd.CommandNames.at(j))
			{
				return extobjcmd.ExtCommands.at(index);
			}
		}
	}
	return NULL;
}

ExtObjectCommandFunction ScpGlobalCommandObject::GetExtCommandFunctionAddress(DWORD commandid, size_t index)
{
	for (size_t i = 0; i < extobjcmdlist.size(); i++)
	{
		ExtObjectCommand & extobjcmd = extobjcmdlist.at(i);
		if (extobjcmd.dwCommandId == commandid)
		{
			return extobjcmd.ExtCommands.at(index);
		}
	}
	return NULL;
}

bool ScpGlobalCommandObject::IsExtCommandFunction(std::string commandstring, size_t index)
{
	ExtObjectCommandFunction func = GetExtCommandFunctionAddress(commandstring, index);
	if(func == nullptr)
		return false;
	else
		return true;
	return false;
}

bool ScpGlobalCommandObject::IsExtCommandFunction(DWORD commandid, size_t index)
{
	ExtObjectCommandFunction func = GetExtCommandFunctionAddress(commandid, index);
	if(func == nullptr)
		return false;
	else
		return true;
	return false;
}
