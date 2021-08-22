/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPGLOBALCOMMANDOBJECT
#define _H_SCPGLOBALCOMMANDOBJECT
#include "ScpObject.h"
#include "commanddefine.h"
#include "mapobjects.h"

typedef struct _tag_ExtObjectCommand
{
	DWORD dwCommandId;
	std::vector<DWORD> dwObjectIdList;
	std::vector<std::wstring> CommandNames;
	std::vector<ExtObjectCommandFunction> ExtCommands;
}ExtObjectCommand,*PExtObjectCommand;

typedef std::vector<ExtObjectCommand > ExtObjectCommandList;
typedef std::map<DWORD, GlobalCommandFunction> IDGlobalCommandFunctionMap;

#include <functional>


class ScpGlobalCommandObject :
	public ScpObject
{
public:
	ScpGlobalCommandObject(void);
	~ScpGlobalCommandObject(void);
	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	void InitBaseCommand();
	ULONG QueryCommand(std::wstring commandstring);
	BOOL RegisterCommand(int lang,std::wstring commandstring,ULONG commandvalue);
	BOOL UnRegisterCommand(int lang, std::wstring commandstring);


	bool RegisterGlobalFunction(std::wstring chscommandstring, std::wstring engcommandstring, DWORD commandid, GlobalCommandFunction Func);
	GlobalCommandFunction GetGlobalCommandFunction(std::wstring commandstring);
	GlobalCommandFunction GetGlobalCommandFunction(DWORD commandid);
	//extend command
	BOOL RegistExtCommand(ExtObjectCommand extobjcmd);
	ULONG QueryExtCommand(std::wstring commandstring);
	size_t GetExtCommandFunctionCount(std::wstring commandstring);
	size_t GetExtCommandFunctionCount(DWORD commandid);
	ExtObjectCommandFunction GetExtCommandFunctionAddress(std::wstring commandstring, size_t index);
	ExtObjectCommandFunction GetExtCommandFunctionAddress(DWORD commandid, size_t index);
private:
	IDGlobalCommandFunctionMap idcommnadmap;

	CHSCOMMANDMAP chscommandmap;
	CHSCOMMANDMAP engcommandmap;
	ExtObjectCommandList extobjcmdlist;

	std::function< BOOL(VTPARAMETERS * vtparameters, CScriptEngine * engine)> GlobalFuncionRef;
	
};

#endif //_H_SCPGLOBALCOMMANDOBJECT