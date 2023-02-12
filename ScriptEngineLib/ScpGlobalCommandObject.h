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
	std::vector<std::string> CommandNames;
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
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine);
	void InitBaseCommand();
	ULONG QueryCommand(std::string commandstring);
	BOOL RegisterCommand(int lang,std::string commandstring,ULONG commandvalue);
	BOOL UnRegisterCommand(int lang, std::string commandstring);


	bool RegisterGlobalFunction(std::string chscommandstring, std::string engcommandstring, DWORD commandid, GlobalCommandFunction Func);
	GlobalCommandFunction GetGlobalCommandFunction(std::string commandstring);
	GlobalCommandFunction GetGlobalCommandFunction(DWORD commandid);
	bool IsGlobalCommandFunction(std::string commandstring);
	bool IsGlobalCommandFunction(DWORD commandid);
	//extend command
	BOOL RegistExtCommand(ExtObjectCommand extobjcmd);
	ULONG QueryExtCommand(std::string commandstring);
	size_t GetExtCommandFunctionCount(std::string commandstring);
	size_t GetExtCommandFunctionCount(DWORD commandid);
	ExtObjectCommandFunction GetExtCommandFunctionAddress(std::string commandstring, size_t index);
	ExtObjectCommandFunction GetExtCommandFunctionAddress(DWORD commandid, size_t index);
	bool IsExtCommandFunction(std::string commandstring, size_t index);
	bool IsExtCommandFunction(DWORD commandid, size_t index);
private:
	IDGlobalCommandFunctionMap idcommnadmap;

	CHSCOMMANDMAP chscommandmap;
	CHSCOMMANDMAP engcommandmap;
	ExtObjectCommandList extobjcmdlist;

	std::function< BOOL(VTPARAMETERS * vtparameters, CScriptEngine * engine)> GlobalFuncionRef;
	
};

#endif //_H_SCPGLOBALCOMMANDOBJECT