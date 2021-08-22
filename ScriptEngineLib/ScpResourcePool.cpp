/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//δ���
//����ʵ�־�̬��Դ�Ĺ������ֽ��������ṩ֧��
*/
#include "ScpResourcePool.h"



ScpResourcePool::ScpResourcePool()
{

}


ScpResourcePool::~ScpResourcePool()
{
}

unsigned long ScpResourcePool::AppendResource(const std::wstring & resource)
{
    unsigned long resid = scpFindResource(resource);
    if (resid == -1)
    {
        pool.push_back(resource);
        resid = pool.size() - 1;
    }
    return resid;
}

unsigned long ScpResourcePool::scpFindResource(const std::wstring & resource)
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
std::wstring & ScpResourcePool::scpGetResource(unsigned long id)
{
	std::wstring temp;
	if(id>=0 && id< pool.size())
		return pool.at(id);
	return temp;
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
