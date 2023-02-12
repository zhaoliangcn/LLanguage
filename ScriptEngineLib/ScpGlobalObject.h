/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPGLOBALOBJECT
#define _H_SCPGLOBALOBJECT
#include "ScpObject.h"
#include "mapobjects.h"
#include "ScpObject_uni.h"
class ScpObject;
class ScpGlobalObject
{
public:
	static ScpGlobalObject *GetInstance()
	{
		return &singleton;
	}	
	~ScpGlobalObject(void);	
	ScpObjectType GetType(const char * strObj);
	void Show(CScriptEngine *engine);
	std::string GetTypeName(ScpObjectType type);	
	void SelectLanguage(int lang);
	BOOL Register(const char * objname_cn,const char * objname_en,ULONG TypeID);
private:
	void Init();
	ScpGlobalObject(void);	
	static ScpGlobalObject singleton;
	CHSOBJECTMAP chsobjectmap;
	CHSOBJECTMAP engobjectmap;
	int language;
};
#endif //_H_SCPGLOBALOBJECT