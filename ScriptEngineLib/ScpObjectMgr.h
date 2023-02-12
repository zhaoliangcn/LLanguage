#ifndef _H_SCOBJECTMGR
#define _H_SCOBJECTMGR
#include "ScpObject.h"
#include "ScpGlobalCommandObject.h"
#include "mapobjects.h"
#include <map>

typedef struct tag_ObjectItem
{
	char objtypename_cn[256];
	char objtypename_en[256];
	ULONG uniqobjid;
	ObjCreateFactoryFunction factory;
}ObjectItem, * PObjectItem;

typedef std::map< ULONG, ObjectItem> MPIDOBJECT;
typedef std::map< ULONG, ObjectItem>::iterator ITMPIDOBJECT;
typedef std::map<std::string, ULONG> MPNAMEID;
typedef std::map<std::string, ULONG>::iterator ITMPNAMEID;
typedef std::map<ULONG, std::string> MPIDNAME;
typedef std::map<ULONG, std::string>::iterator ITMPIDNAME;

class CScpObjectMgr
{

public:


	CScpObjectMgr(void);
	~CScpObjectMgr(void);
	BOOL IsInnerObject(const char* objtypename);
	BOOL IsInnerObject(ULONG UniqObjId);
	ULONG GetObjectId(const char* objtypename);
	ScpObject* CreateObject(const char* objtypename, VTPARAMETERS* paramters, CScriptEngine* engine);
	ScpObject* CreateObject(ULONG UniqObjId, VTPARAMETERS* paramters, CScriptEngine* engine);
	std::string GetInnerObjectName(ULONG UniqObjId);
	/*
	注册对象
	objtypename_cn 对象中文名
	objtypename_en 对象英文名
	UniqObjId 对象唯一ID
	factoryfunc 对象工厂函数地址
	*/
	BOOL RegisterObject(const char* objtypename_cn, const char* objtypename_en, ULONG UniqObjId, ObjCreateFactoryFunction factoryfunc);
	void ClearInnerObject();
	void RegisterInnerObjects();

private:

	MPIDOBJECT map_id_object; 
	MPNAMEID map_name_id;
	MPIDNAME map_id_name;


};
#endif //_H_SCOBJECTMGR


