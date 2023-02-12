/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//内部对象的管理
*/
#include "ScpObjectMgr.h"
#include "ScpOperationMgr.h"
#include "addin.h"
#include "ScpCommonObject.h"
#include "../Common/commonutil.hpp"
#ifdef WIN32
#include <strsafe.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif


CScpObjectMgr::CScpObjectMgr(void)
{
}

CScpObjectMgr::~CScpObjectMgr(void)
{
}
BOOL CScpObjectMgr::IsInnerObject(const char* objtypename)
{
	BOOL bRet = FALSE;
	if (map_name_id.find(objtypename) != map_name_id.end())
	{
		ULONG UniqObjId = map_name_id[objtypename];
		if (map_id_object.find(UniqObjId) != map_id_object.end())
		{
			bRet = TRUE;
		}
	}	
	return bRet;
}
BOOL CScpObjectMgr::IsInnerObject(ULONG UniqObjId)
{
	BOOL bRet = FALSE;
	if (map_id_name.find(UniqObjId) != map_id_name.end())
	{
		if (map_id_object.find(UniqObjId) != map_id_object.end())
		{
			bRet = TRUE;
		}
	}
	return bRet;
}
ULONG CScpObjectMgr::GetObjectId(const char* objtypename)
{
	ULONG id = -1;
	if (map_name_id.find(objtypename) != map_name_id.end())
	{
		id = map_name_id[objtypename];
	}
	return id;
}
ScpObject* CScpObjectMgr::CreateObject(const char* objtypename, VTPARAMETERS* paramters, CScriptEngine* engine)
{
	ScpObject* obj = NULL;
	if (map_name_id.find(objtypename) != map_name_id.end())
	{
		ULONG UniqObjId = map_name_id[objtypename];
		if (map_id_object.find(UniqObjId) != map_id_object.end())
		{
			ObjectItem& item = map_id_object[UniqObjId];
			obj = item.factory(paramters, engine);
		}
	}
	return obj;
}
ScpObject* CScpObjectMgr::CreateObject(ULONG UniqObjId, VTPARAMETERS* paramters, CScriptEngine* engine)
{
	ScpObject* obj = NULL;
	if (map_id_object.find(UniqObjId) != map_id_object.end())
	{
		ObjectItem& item = map_id_object[UniqObjId];
		obj = item.factory(paramters, engine);
	}
	return obj;
}
std::string CScpObjectMgr::GetInnerObjectName(ULONG UniqObjId)
{
	std::string temp;
	if (map_id_name.find(UniqObjId) != map_id_name.end())
	{
		temp = map_id_name[UniqObjId];
	}
	return temp;

}
BOOL CScpObjectMgr::RegisterObject(const char* objtypename_cn, const char* objtypename_en, ULONG UniqObjId, ExtObjCreateFactoryFunction factoryfunc)
{
	if (IsInnerObject(objtypename_cn) || IsInnerObject(objtypename_en) || IsInnerObject(UniqObjId) || UniqObjId == INVALID_OBJECT_ID)
	{
		return FALSE;
	}
	else
	{
		ObjectItem item;
#ifdef WIN32
		StringCchCopyA(item.objtypename_cn, _countof(item.objtypename_cn), objtypename_cn);
		StringCchCopyA(item.objtypename_en, _countof(item.objtypename_en), objtypename_en);
#else 
		strcpy(item.objtypename_cn, objtypename_cn);
		strcpy(item.objtypename_en, objtypename_en);

#endif
		item.uniqobjid = UniqObjId;
		item.factory = factoryfunc;

		map_name_id[objtypename_cn] = UniqObjId;
		map_name_id[objtypename_en] = UniqObjId;
		map_id_name[UniqObjId] = objtypename_en;
		map_id_object[UniqObjId] = item;

		return TRUE;
	}
}

void CScpObjectMgr::ClearInnerObject()
{
	map_name_id.clear();
	map_id_name.clear();
	map_id_object.clear();

}

void CScpObjectMgr::RegisterInnerObjects()
{
	//注册整数对象
	RegisterObject(str_CN_ObjInt, str_EN_ObjInt, ObjInt, ScpIntObjectFactory);
	//注册大整数对象
	RegisterObject(str_CN_ObjBigInt, str_EN_ObjBigInt, ObjBigInt, ScpBigIntObjectFactory);
	//注册字符串对象
	RegisterObject(str_CN_ObjString, str_EN_ObjString, ObjString, ScpStringObjectFactory);
	//注册浮点数对象
	RegisterObject(str_CN_ObjDouble, str_EN_ObjDouble, ObjDouble, ScpDoubleObjectFactory);
	//注册数组对象
	RegisterObject(str_CN_ObjArray, str_EN_ObjArray, ObjArray, ScpArrayObjectFactory);
	//注册Map对象
	RegisterObject(str_CN_ObjMap, str_EN_ObjMap, ObjMap, ScpMapObjectFactory);	
	//注册Null对象
	RegisterObject(str_CN_ObjNull, str_EN_ObjNull, ObjNull, ScpNullObjectFactory);
	//注册文件对象
	RegisterObject(str_CN_ObjFile, str_EN_ObjFile, ObjFile, ScpFileObjectFactory);
	//注册文件夹对象
	RegisterObject(str_CN_ObjDirectory, str_EN_ObjDirectory, ObjDirectory, ScpDirectoryObjectFactory);
	//注册list对象
	RegisterObject(str_CN_ObjList, str_EN_ObjList, ObjList, ScpListObjectFactory);
	//注册json对象
	RegisterObject(str_CN_ObjJson, str_EN_ObjJson, ObjJson, ScpJsonObjectFactory);
	//注册队列对象
	RegisterObject(str_CN_ObjQueue, str_EN_ObjQueue, ObjQueue, ScpQueueObjectFactory);
	//注册Range对象
	RegisterObject(str_CN_ObjRange, str_EN_ObjRange, ObjRange, ScpRangeObjectFactory);
	//注册RegExp对象
	RegisterObject(str_CN_ObjRegExp, str_EN_ObjRegExp, ObjRegExp, ScpRegExpObjectFactory);
	//注册stack对象
	RegisterObject(str_CN_ObjStack, str_EN_ObjStack, ObjStack, ScpStackObjectFactory);
	//注册Table对象
	RegisterObject(str_CN_ObjTable, str_EN_ObjTable, ObjTable, ScpTableObjectFactory);
	//注册内存对象
	RegisterObject(str_CN_ObjMemory, str_EN_ObjMemory, ObjMemory, ScpMemoryObjectFactory);
	//注册随机数对象
	RegisterObject(str_CN_ObjRandomNumber, str_EN_ObjRandomNumber, ObjRandomNumber, ScpRandomNumberObjectFactory);
	//注册Time对象
	RegisterObject(str_CN_ObjTime, str_EN_ObjTime, ObjTime, ScpTimeObjectFactory);
	//注册字符串数组对象
	RegisterObject(str_CN_ObjStringArray, str_EN_ObjStringArray, ObjStringArray, ScpStringArrayObjectFactory);
	
	
	
	
	
	
	

	
	
	
}

