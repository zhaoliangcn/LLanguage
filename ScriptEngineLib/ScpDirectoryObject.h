/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
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
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release();

	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);


	BOOL Open(std::string dir);
	void ShowAllFiles(CScriptEngine * engine);
	void ShowAllSubdir(CScriptEngine * engine);
	void ShowAll(CScriptEngine * engine);
	void EnumAll();
	BOOL FindAllFiles(ScpObjectSpace * currentObjectSpace,ScpTableObject * tableobj,std::string driectory,std::string matchrule, bool findfile);
	ScpTableObject * EnumAllFiles(ScpObjectSpace * currentObjectSpace);
	ScpTableObject * EnumAllFiles(ScpObjectSpace * currentObjectSpace,ScpObject * reobj);
	ScpTableObject * EnumAllSubDir(ScpObjectSpace * currentObjectSpace);	
	static BOOL Copy(std::string source,std::string dest);
	static BOOL Move(std::string source,std::string dest);
	BOOL Delete();
	static BOOL Delete(std::string dir);
	static BOOL PathOrFileExist(std::string dir);
	static BOOL IsDir(std::string dir);
	static BOOL Create(std::string dir);
	std::string directory;
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