/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//未完成
//用于实现静态资源的管理，对字节码生成提供支撑
*/
#include "ScpResourcePool.h"



ScpResourcePool::ScpResourcePool()
{

}


ScpResourcePool::~ScpResourcePool()
{
}

unsigned long ScpResourcePool::AppendResource(const std::string & resource)
{
    unsigned long resid = scpFindResource(resource);
    if (resid == -1)
    {
        pool.push_back(resource);
        resid = pool.size() - 1;
    }
    return resid;
}

unsigned long ScpResourcePool::scpFindResource(const std::string & resource)
{
	for (size_t i = 0;i < pool.size();i++)
	{
		if (pool.at(i) == resource)
		{
			return i;
		}
	}
	return -1;
}
std::string & ScpResourcePool::scpGetResource(unsigned long id)
{
	if(id>=0 && id< pool.size())
		return pool.at(id);
	return emptyres;
}

void ScpResourcePool::unMapResource(unsigned long id)
{
	std::map<ULONG, ScpObject *>::iterator it = ResObjMap.find(id);
	if (it != ResObjMap.end())
	{
		ResObjMap.erase(it);
	}
}

void ScpResourcePool::setMappedObject(unsigned long id, ScpObject * obj)
{
	if(obj)
		ResObjMap[id] = obj;
}

ScpObject * ScpResourcePool::getMappedObject(unsigned long id)
{
	if (ResObjMap.find(id) != ResObjMap.end())
	{
		return ResObjMap[id];
	}
	return nullptr;
}
