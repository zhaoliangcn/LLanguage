/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//Ä¿Â¼¶ÔÏó
*/
#ifndef _H_SCPDIRECTORYOBJECT
#define _H_SCPDIRECTORYOBJECT

#include "ScpObject.h"
#include "ScpTableObject.h"

#ifdef _WIN32

#else
#include <stdlib.h>
#include <unistd.h>	
#include <dirent.h>
#endif


class ScpDirectoryObject :
	public ScpObject
{
public:
	ScpDirectoryObject(void);
	~ScpDirectoryObject(void);

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release();

	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);


	BOOL Open(std::wstring dir);
	void ShowAllFiles(CScriptEngine * engine);
	void ShowAllSubdir(CScriptEngine * engine);
	void ShowAll(CScriptEngine * engine);
	void EnumAll();
	BOOL FindAllFiles(ScpObjectSpace * currentObjectSpace,ScpTableObject * tableobj,std::wstring driectory,std::wstring matchrule);
	ScpTableObject * EnumAllFiles(ScpObjectSpace * currentObjectSpace);
	ScpTableObject * EnumAllFiles(ScpObjectSpace * currentObjectSpace,ScpObject * reobj);
	ScpTableObject * EnumAllSubDir(ScpObjectSpace * currentObjectSpace);	
	static BOOL Copy(std::wstring source,std::wstring dest);
	static BOOL Move(std::wstring source,std::wstring dest);
	BOOL Delete();
	static BOOL Delete(std::wstring dir);
	static BOOL PathOrFileExist(std::wstring dir);
	static BOOL IsDir(std::wstring dir);
	static BOOL Create(std::wstring dir);
	std::wstring directory;
	VTSTRINGS all;
	VTSTRINGS allfiles;
	VTSTRINGS allsubdir;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject * InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_enum(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_move(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_create(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};

ScpObject * __stdcall ScpDirectoryObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPDIRECTORYOBJECT