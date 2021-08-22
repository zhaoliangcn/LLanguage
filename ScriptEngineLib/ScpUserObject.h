/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPUSEROBJECT
#define _H_SCPUSEROBJECT
#include "ScpObject.h"
#include "ScpGlobalObject.h"
#include "mapobjects.h"


class ScpUserObject
{
public:
    ScpUserObject();
    ~ScpUserObject();
    ULONG GetSize();
    int IsInMap(const std::wstring &strObjname);
    ScpObjectType GetType(const std::wstring& strObjname);
    BOOL MapObject(const std::wstring& strObjname,ScpObject *obj,std::wstring scope=L"");
    ScpObject * GetObject(const std::wstring& strObjname);
    ScpObject * GetObject(unsigned long objindex);
    void UnMapObject(const std::wstring& strObjname);
    void UnMapObject(unsigned long objindex);
    std::wstring GetObjectName(ScpObject *obj);
    void Destroy();
    VTSTRINGS EnumObjects();
    void DumpObject(const std::wstring& objectname, CScriptEngine * engine);
    void Copy(ScpUserObject  *userobject);
    void DeepCopy(ScpUserObject  *userobject);
    void Lock();
    void UnLock();
private:
	USEROBJMAP userobjmap;
#ifdef WIN32
	CRITICAL_SECTION cs;
#else 
	pthread_mutex_t mutex ;
#endif
};

class ScpUserObject2
{
public:
    ScpUserObject2();
    ~ScpUserObject2();
    ULONG GetSize();
    int IsInMap(std::wstring strObjname);
    ScpObjectType GetType(const std::wstring& strObjname);
    BOOL MapObject(const std::wstring& strObjname,ScpObject *obj,std::wstring scope=L"");
    ScpObject * GetObject(const std::wstring& strObjname);
    ScpObject * GetObject(unsigned long objindex);
    ScpObject * UnMapObject(const std::wstring& strObjname);
    void UnMapObject(unsigned long objindex);
    std::wstring GetObjectName(ScpObject *obj);
    std::wstring GetObjectName(unsigned long objIndex);
    void Destroy();
    VTSTRINGS EnumObjects();
    void DumpObject(const std::wstring& objectname, CScriptEngine * engine);
    void Copy(ScpUserObject2  *userobject);
    void Lock();
    void UnLock();
private:
	USEROBJMAP2 userobjmap;
#ifdef WIN32
	CRITICAL_SECTION cs;
#else 
	pthread_mutex_t mutex ;
#endif
};

class ScpUserObject3
{
public:
    ScpUserObject3();
    ~ScpUserObject3();
    ULONG GetSize();
    int IsInMap(const std::wstring &strObjname);
    int IsInMap(ScpObject * obj);
    ScpObjectType GetType(const std::wstring& strObjname);
    BOOL MapObject(const std::wstring& strObjname,ScpObject *obj,std::wstring scope=L"");
    ScpObject * GetObject(const std::wstring& strObjname);
    ScpObject * GetObject(unsigned long objindex);
    BOOL SetObject(unsigned long objindex,const std::wstring& strObjname,ScpObject *obj);
    ScpObject * UnMapObject(const std::wstring& strObjname);
    void UnMapObject(unsigned long objindex);
    std::wstring GetObjectName(ScpObject *obj);
    std::wstring GetObjectName(unsigned long objIndex);
    ULONG GetObjectIndex(const std::wstring& objectname);
    void Destroy();
    VTSTRINGS EnumObjects();
    void DumpObject(const std::wstring& objectname, CScriptEngine * engine);
    void Copy(ScpUserObject3  *userobject);
    void DeepCopy(ScpUserObject3  *userobject);
    void Lock();
    void UnLock();
private:
	USEROBJMAP3 userobjmap;
#ifdef WIN32
	CRITICAL_SECTION cs;
#else 
	pthread_mutex_t mutex ;
#endif
};


#endif //_H_SCPUSEROBJECT