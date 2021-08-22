/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPEXTENDOBJECTMGR
#define _H_SCPEXTENDOBJECTMGR
#include "ScpObject.h"
#include "ScpGlobalCommandObject.h"

typedef struct tag_ExtendObjectItem
{
	wchar_t objtypename_cn[256];
	wchar_t objtypename_en[256];
	ULONG uniqobjid;
	ExtObjCreateFactoryFunction factory;
}ExtendObjectItem,*PExtendObjectItem;

typedef std::vector<ExtendObjectItem> VTExtendObject;
typedef std::vector<ExtendObjectItem>::iterator ITExtendObject;

class ScpExtendObjectMgr
{
public:
	
	ScpExtendObjectMgr(void);
	~ScpExtendObjectMgr(void);
	BOOL IsExtendObject(const wchar_t * objtypename);
	BOOL IsExtendObject(ULONG UniqObjId);
	ULONG GetExtendObjectId(const wchar_t * objtypename);
	ScpObject * CreateExtendObject(const wchar_t * objtypename,VTPARAMETERS * paramters, CScriptEngine * engine);
	ScpObject * CreateExtendObject(ULONG UniqObjId, VTPARAMETERS * paramters, CScriptEngine * engine);
	std::wstring GetExtendObjectName(ULONG UniqObjId);
	/*
	注册扩展对象
	objtypename_cn 对象中文名
	objtypename_en 对象英文名
	UniqObjId 对象唯一ID
	factoryfunc 对象工厂函数地址
	*/
	BOOL RegistExtendObject(const wchar_t * objtypename_cn,const wchar_t * objtypename_en,ULONG UniqObjId,ExtObjCreateFactoryFunction factoryfunc);
	void ClearExtendObject();

	BOOL LoadExtensions(const  wchar_t * ModulePathName, ScpGlobalCommandObject * scpglobalcommands);
	BOOL LoadExtension(const  wchar_t * ModuleName, ScpGlobalCommandObject * scpglobalcommands);
	void FreeAllExtensions();
private:
	
	VTExtendObject extendobjects;

	//已加载的扩展对象动态库文件名和模块句柄
	HANDLESMAP map_loadedExtension;

	
};
#endif //_H_SCPEXTENDOBJECTMGR