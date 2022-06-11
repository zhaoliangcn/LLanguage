#ifndef _H_SCPRESOURCEPOOL
#define _H_SCPRESOURCEPOOL
#include "ScpObject.h"
#include<map>
//³£Á¿³Ø
class ScpResourcePool
{
public:
    ScpResourcePool();
    ~ScpResourcePool();
    unsigned long AppendResource(const std::wstring & resource);
    unsigned long scpFindResource(const std::wstring & resource);
    const wchar_t * scpGetResource(unsigned long id);
    void unMapResource(unsigned long id);
    void setMappedObject(unsigned long id, ScpObject * obj);
    ScpObject * getMappedObject(unsigned long id);
    VTSTRINGS pool;
    std::map<ULONG, ScpObject *> ResObjMap;

};


#endif //_H_SCPRESOURCEPOOL
