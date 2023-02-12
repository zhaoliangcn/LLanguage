#ifndef _H_SCPRESOURCEPOOL
#define _H_SCPRESOURCEPOOL
#include "ScpObject.h"
#include<map>
//常量池
class ScpResourcePool
{
public:
    ScpResourcePool();
    ~ScpResourcePool();
    unsigned long AppendResource(const std::string & resource);
    unsigned long scpFindResource(const std::string & resource);
    std::string & scpGetResource(unsigned long id);
    void unMapResource(unsigned long id);
    void setMappedObject(unsigned long id, ScpObject * obj);
    ScpObject * getMappedObject(unsigned long id);
    VTSTRINGS pool;
    std::map<ULONG, ScpObject *> ResObjMap;
	std::string emptyres;
};


#endif //_H_SCPRESOURCEPOOL