/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//对象名和对象实例的映射
*/
#include "ScpUserObject.h"
#include "ScriptEngine.h"
#include "../Common/MapFindKeyByValue.hpp"
#ifndef _WIN32

using namespace __gnu_cxx;
namespace __gnu_cxx {
unsigned int BKDRHash(wchar_t *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}
}

#endif

ScpUserObject::ScpUserObject()
{
#ifdef USE_GOOGLE_HASHMAP	
	userobjmap.set_empty_key(L"");
	userobjmap.set_deleted_key(L"");
	chsobjmap.set_empty_key(L"");
	chsobjmap.set_deleted_key(L"");
#endif
#ifdef WIN32
	InitializeCriticalSection(&cs);
#else
	pthread_mutex_init(&mutex,NULL);
#endif
}
ScpUserObject::~ScpUserObject()
{
		Destroy();
}

ULONG ScpUserObject::GetSize()
{
	return userobjmap.size();
}
int ScpUserObject::IsInMap(const std::string &strObjname)
{
	int ret = 0;
	ITUSEROBJMAP it ;
	Lock();
	it=userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		ret= 1;
	}
	UnLock();
	return ret;
}
ScpObjectType ScpUserObject::GetType(const std::string& strObjname)
{
	ScpObject *  obj=NULL;
	Lock();
	ScpObjectType type=ObjUnknown;
	ITUSEROBJMAP it = userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		obj= userobjmap[strObjname];
		type = obj->GetType();
	}
	UnLock();
	return type;
}
BOOL ScpUserObject::MapObject(const std::string& strObjname,ScpObject *obj,std::string scope)
{
	BOOL ret = FALSE ;	
	if(IsInMap(strObjname)==1)
	{
		ret = TRUE;
	}
	else
	{
		//if (obj->RefCount >= 1)
		//{
		//	printf("map %S %0x\n", strObjname, obj);
		//}		
		Lock();
		userobjmap[strObjname]=obj;
		obj->AddRef();
		UnLock();
		ret = TRUE;
	}	
	return ret;
}
ScpObject * ScpUserObject::GetObject(const std::string& strObjname)
{
	ScpObject * temp = NULL;
	Lock();
	ITUSEROBJMAP it = userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		temp = userobjmap[strObjname];
	}
	UnLock();
	return temp;
}
ScpObject * ScpUserObject::GetObject(unsigned long objindex)
{
	ScpObject *  obj=NULL;
	Lock();
	if(objindex<userobjmap.size())
	{
		ITUSEROBJMAP it = userobjmap.begin();
		while(objindex>0)
		{
			objindex--;
			it++;
		}
		obj=it->second;
	}
	UnLock();
	return obj;
}
void ScpUserObject::UnMapObject(const std::string& strObjname)
{
	ScpObject *  obj=NULL;
	Lock();
	ITUSEROBJMAP it = userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		obj=it->second;
		userobjmap.erase(it);
		if(obj)
		{
			obj->DelRef();
		}
	}
	UnLock();
}
void ScpUserObject::UnMapObject(unsigned long objindex)
{	
	ScpObject *  obj=NULL;
	Lock();
	if(objindex<userobjmap.size())
	{
		ITUSEROBJMAP it = userobjmap.begin();
		while(objindex>0)
		{
			objindex--;
			it++;
		}
		obj=it->second;
		userobjmap.erase(it);
		if(obj)
		{
			obj->DelRef();
		}
	}
	UnLock();
}
std::string  ScpUserObject::GetObjectName(ScpObject *obj)
{
	std::string name;
	Lock();
	name = FindKeyByValue(userobjmap,obj,name);
	UnLock();
	return name;
}
void ScpUserObject::Destroy()
{
//	Lock();
	ITUSEROBJMAP it = userobjmap.begin();
	while(userobjmap.size()>0)
	{
		ScpObject * temp = it->second;	

		//if (temp->RefCount > 1)
		//{
		//	printf("destroy refcount  %d type %d %s %0x\n", temp->RefCount, temp->GetType(),STDSTRINGEXT::WToA(it->first).c_str(),temp);
		//}
		//googlehashmap与stl的hashmap不一样erase不返回下一个迭代，需要用户调用自增操作
		
#ifdef USE_GOOGLE_HASHMAP
		userobjmap.erase(it);
		it++;
#else
#ifdef _WIN32
		it=userobjmap.erase(it);
#else
		userobjmap.erase(it);
		it++;
#endif
#endif
		//处理一个对象有多个名字的情况
		//取元素的时候将对象映射给临时元素名称，但是没有解除映射关系
		//查找重复注册的元素，并且解除映射
		//std::string tempname =FindKeyByValue(userobjmap,temp,tempname);
		//while(!tempname.empty())
		//{
		//	UnMapObject(tempname);
		//	tempname =FindKeyByValue(userobjmap,temp,tempname);
		//}
		if(temp)
		{
			temp->DelRef();
			//delete temp;
		}
	}
//	UnLock();
}
VTSTRINGS ScpUserObject::EnumObjects()
{
		
	VTSTRINGS allobjects;
	ULONG size = GetSize();
	Lock();
	for(ITUSEROBJMAP it =userobjmap.begin();
		it!=userobjmap.end();it++)
	{
		std::string temp;
		temp=it->first;
		temp+=",";
		temp+=ScpGlobalObject::GetInstance()->GetTypeName(it->second->GetType());
		allobjects.push_back(temp);
	}
	UnLock();
	return allobjects;
}
void ScpUserObject::DumpObject(const std::string& objectname, CScriptEngine * engine)
{
	ScpObject *  obj =GetObject(objectname);
	if(obj)
	{
		obj->Show(engine);
	}
}
void ScpUserObject::Copy(ScpUserObject  *userobject)
{
	Lock();
	userobjmap=userobject->userobjmap;
	UnLock();
}
void ScpUserObject::DeepCopy(ScpUserObject * userobject)
{
	Lock();
	ITUSEROBJMAP it = userobject->userobjmap.begin();
	while (it != userobject->userobjmap.end())
	{
		std::string name = it->first;
		ScpObject * obj = it->second;
		if(obj->GetType()!=ObjFunction)
			MapObject(name, it->second->Clone(""));
		else
			MapObject(name, it->second);
		it++;
	}
	UnLock();
}
void ScpUserObject::Lock()
{
#ifdef WIN32
	//EnterCriticalSection(&cs);
#else 
	//递归调用时无法返回,LINUX下不宜使用
	//pthread_mutex_lock(&mutex);
#endif	
}
void ScpUserObject::UnLock()
{
#ifdef WIN32
	//LeaveCriticalSection(&cs);
#else 
	//递归调用时无法返回,LINUX下不宜使用
	//pthread_mutex_unlock(&mutex);
#endif
}





ScpUserObject2::ScpUserObject2()
{
#ifdef WIN32
	InitializeCriticalSection(&cs);
#else
	pthread_mutex_init(&mutex,NULL);
#endif
}
ScpUserObject2::~ScpUserObject2()
{
		Destroy();
}
ULONG ScpUserObject2::GetSize()
{
	return userobjmap.size();
}
int ScpUserObject2::IsInMap(std::string strObjname)
{
	int ret = 0;
	ITUSEROBJMAP2 it ;
	Lock();
	it=userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		ret = 1;
	}
	UnLock();
	return ret;
}
ScpObjectType ScpUserObject2::GetType(const std::string& strObjname)
{
	ScpObject *  obj=NULL;
	Lock();
	ScpObjectType type=ObjUnknown;
	ITUSEROBJMAP2 it = userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		obj= userobjmap[strObjname];
		type = obj->GetType();
	}
	UnLock();
	return type;
}
BOOL ScpUserObject2::MapObject(const std::string& strObjname,ScpObject *obj,std::string scope)
{
	BOOL ret = FALSE ;
	
	if(obj)
	{
		if(IsInMap(strObjname)==1)
		{
			;
		}
		else
		{
			Lock();
			userobjmap[strObjname]=obj;
			obj->AddRef();
			UnLock();
		}
	}
	else
	{
		Lock();
		userobjmap[strObjname]=obj;
		UnLock();
	}
	return ret;
}
ScpObject * ScpUserObject2::GetObject(const std::string& strObjname)
{
	ScpObject * temp = NULL;
	Lock();
	ITUSEROBJMAP2 it = userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		temp =  userobjmap[strObjname];
	}
	UnLock();
	return temp;
}
ScpObject * ScpUserObject2::GetObject(unsigned long objindex)
{
	ScpObject *  obj=NULL;
	Lock();
	if(objindex<userobjmap.size())
	{
		ITUSEROBJMAP2 it = userobjmap.begin();
		while(objindex>0)
		{
			objindex--;
			it++;
		}
		obj=it->second;
	}
	UnLock();
	return obj;
}
ScpObject * ScpUserObject2::UnMapObject(const std::string& strObjname)
{
	ScpObject *  obj=NULL;
	Lock();
	ITUSEROBJMAP2 it = userobjmap.find(strObjname);
	if(it!=userobjmap.end())
	{
		obj=it->second;
		userobjmap.erase(it);
		if(obj)
		{
			obj->DelRef();
		}
	}
	UnLock();
	return NULL;
}
void ScpUserObject2::UnMapObject(unsigned long objindex)
{	
	ScpObject *  obj=NULL;
	Lock();
	if(objindex<userobjmap.size())
	{
		ITUSEROBJMAP2 it = userobjmap.begin();
		while(objindex>0)
		{
			objindex--;
			it++;
		}
		obj=it->second;
		userobjmap.erase(it);
		if(obj)
		{
			obj->DelRef();
		}
	}
	UnLock();
}
std::string  ScpUserObject2::GetObjectName(ScpObject *obj)
{
	std::string name;
	Lock();
	name = FindKeyByValue(userobjmap,obj,name);
	UnLock();
	return name;
}
std::string ScpUserObject2::GetObjectName(unsigned long objIndex)
{
	std::string name;
	Lock();
	ITUSEROBJMAP2 it = userobjmap.begin();
	while(it!=userobjmap.end() && (objIndex>0))
	{
		it++;
		objIndex--;
	}
	name= it->first;
	UnLock();
	return name;
}
void ScpUserObject2::Destroy()
{
//	Lock();
	ITUSEROBJMAP2 it = userobjmap.begin();
	while(userobjmap.size()>0)
	{
		ScpObject * temp = it->second;	

#ifdef _WIN32
		it=userobjmap.erase(it);
#else
		userobjmap.erase(it);
		it++;
#endif

		//处理一个对象有多个名字的情况
		//取元素的时候将对象映射给临时元素名称，但是没有解除映射关系
		//查找重复注册的元素，并且解除映射
		//std::string tempname =FindKeyByValue(userobjmap,temp,tempname);
		//while(!tempname.empty())
		//{
		//	UnMapObject(tempname);
		//	tempname =FindKeyByValue(userobjmap,temp,tempname);
		//}
		if(temp)
		{
			temp->DelRef();
			//delete temp;
		}
	}
//	UnLock();
}
VTSTRINGS ScpUserObject2::EnumObjects()
{
		
	VTSTRINGS allobjects;
	ULONG size = GetSize();
	Lock();
	for(ITUSEROBJMAP2 it =userobjmap.begin();
		it!=userobjmap.end();it++)
	{
		std::string temp;
		temp=it->first;
		temp+=",";
		temp+=ScpGlobalObject::GetInstance()->GetTypeName(it->second->GetType());
		allobjects.push_back(temp);
	}
	UnLock();
	return allobjects;
}
void ScpUserObject2::DumpObject(const std::string& objectname, CScriptEngine * engine)
{
	ScpObject *  obj =GetObject(objectname);
	if(obj)
	{
		obj->Show(engine);
	}
}
void ScpUserObject2::Copy(ScpUserObject2  *userobject)
{
	Lock();
	userobjmap=userobject->userobjmap;
	UnLock();
}
void ScpUserObject2::Lock()
{
#ifdef WIN32
	//EnterCriticalSection(&cs);
#else 
	//递归调用时无法返回,LINUX下不宜使用
	//pthread_mutex_lock(&mutex);
#endif	
}
void ScpUserObject2::UnLock()
{
#ifdef WIN32
	//LeaveCriticalSection(&cs);
#else 
	//递归调用时无法返回,LINUX下不宜使用
	//pthread_mutex_unlock(&mutex);
#endif
}


ScpUserObject3::ScpUserObject3()
{
#ifdef WIN32
	InitializeCriticalSection(&cs);
#else
	pthread_mutex_init(&mutex,NULL);
#endif
}
ScpUserObject3::~ScpUserObject3()
{
		Destroy();
}
ULONG ScpUserObject3::GetSize()
{
	return userobjmap.size();
}
int ScpUserObject3::IsInMap(ScpObject * obj)
{
	int ret = 0;
	ITUSEROBJMAP3 it ;
	Lock();
	it=userobjmap.begin();
	while(it!=userobjmap.end())
	{
		if(it->second==obj)
		{
			ret = 1;
		}
		it++;
	}
	UnLock();
	return ret;
}
int ScpUserObject3::IsInMap(const std::string &strObjname)
{
	int ret = 0;
	ITUSEROBJMAP3 it ;
	Lock();
	it=userobjmap.begin();
	while(it!=userobjmap.end())
	{
		if(it->first==strObjname)
		{
			ret = 1;
		}
		it++;
	}
	UnLock();
	return ret;
}
ScpObjectType ScpUserObject3::GetType(const std::string& strObjname)
{
	ScpObject *  obj=NULL;
	Lock();
	ScpObjectType type=ObjUnknown;
	ITUSEROBJMAP3 it = it=userobjmap.begin();
	while(it!=userobjmap.end())
	{
		if(it->first==strObjname)
		{
			obj= it->second;
			type = obj->GetType();
		}	
		it++;
	}
	UnLock();
	return type;
}
BOOL ScpUserObject3::MapObject(const std::string& strObjname,ScpObject *obj,std::string scope)
{
	BOOL ret = FALSE ;
	
	if(obj)
	{
		if(IsInMap(strObjname)==1)
		{
			;
		}
		else
		{
			Lock();
			userobjmap.push_back(std::pair<std::string,ScpObject *>(strObjname,obj));
			obj->AddRef();
			UnLock();
		}
	}
	else
	{
		Lock();
		userobjmap.push_back(std::pair<std::string,ScpObject *>(strObjname,obj));
		UnLock();
	}
	
	return ret;
}
ScpObject * ScpUserObject3::GetObject(const std::string& strObjname)
{
	ScpObject * temp = NULL;
	Lock();
	ITUSEROBJMAP3 it = it=userobjmap.begin();
	while(it!=userobjmap.end())
	{
		if(it->first==strObjname)
		{
			temp = it->second;
		}
		it++;
	}
	UnLock();
	return temp;
}
ScpObject * ScpUserObject3::GetObject(unsigned long objindex)
{
	ScpObject *  obj=NULL;
	Lock();
	obj = userobjmap.at(objindex).second;
	UnLock();
	return obj;
}
BOOL ScpUserObject3::SetObject(unsigned long objindex,const std::string& strObjname,ScpObject *obj)
{
	Lock();
	userobjmap.at(objindex).first = strObjname;
	userobjmap.at(objindex).second = obj;
	UnLock();
	return TRUE;
}
ScpObject * ScpUserObject3::UnMapObject(const std::string& strObjname)
{
	ScpObject *  obj=NULL;
	Lock();

	ITUSEROBJMAP3 it = it=userobjmap.begin();
	while(it!=userobjmap.end())
	{
		if(it->first==strObjname)
		{
			obj=it->second;
			userobjmap.erase(it);
			if(obj)
			{
				obj->DelRef();
			}
			break;
		}
		it++;
	}	
	UnLock();
	return NULL;
}
void ScpUserObject3::UnMapObject(unsigned long objindex)
{	
	ScpObject *  obj=NULL;
	Lock();	
	if(objindex<userobjmap.size())
	{
		ITUSEROBJMAP3 it = it=userobjmap.begin();
		while(it!=userobjmap.end() && objindex>0)
		{
			it++;
			objindex--;
		}
		obj=it->second;
		userobjmap.erase(it);
		if(obj)
		{
			obj->DelRef();
		}
	}
	UnLock();
}
std::string  ScpUserObject3::GetObjectName(ScpObject *obj)
{
	std::string name;
	
	Lock();
	ITUSEROBJMAP3 it = it=userobjmap.begin();
	while(it!=userobjmap.end())
	{
		ScpObject *  tempobj=NULL;
		tempobj=it->second;
		if(tempobj==obj)
		{
			name =it->first ;
			break;		
		}
		it++;
	}
	return name;
}
ULONG ScpUserObject3::GetObjectIndex(const std::string& objectname)
{
	ULONG uRet=-1;
	ULONG index=0;
	Lock();
	
	ITUSEROBJMAP3 it = userobjmap.begin();
	while(it!=userobjmap.end())
	{
		if(objectname==it->first)
		{
			uRet=index;
			break;
		}
		it++;
		index++;
	}
	UnLock();
	return uRet;
}
std::string ScpUserObject3::GetObjectName(unsigned long objIndex)
{
	std::string name;
	Lock();
	ITUSEROBJMAP3 it = userobjmap.begin();
	while(it!=userobjmap.end() && (objIndex>0))
	{
		it++;
		objIndex--;
	}
	name= it->first;
	UnLock();
	return name;
}
void ScpUserObject3::Destroy()
{
//	Lock();
	ITUSEROBJMAP3 it = userobjmap.begin();
	while(userobjmap.size()>0)
	{
		ScpObject * temp = it->second;	

#ifdef _WIN32
		it=userobjmap.erase(it);
#else
		userobjmap.erase(it);
		it++;
#endif

		//处理一个对象有多个名字的情况
		//取元素的时候将对象映射给临时元素名称，但是没有解除映射关系
		//查找重复注册的元素，并且解除映射
		//std::string tempname =FindKeyByValue(userobjmap,temp,tempname);
		//while(!tempname.empty())
		//{
		//	UnMapObject(tempname);
		//	tempname =FindKeyByValue(userobjmap,temp,tempname);
		//}
		if(temp)
		{
			temp->DelRef();
			//delete temp;
		}
	}
//	UnLock();
}
VTSTRINGS ScpUserObject3::EnumObjects()
{
		
	VTSTRINGS allobjects;
	ULONG size = GetSize();
	Lock();
	for(ITUSEROBJMAP3 it =userobjmap.begin();
		it!=userobjmap.end();it++)
	{
		std::string temp;
		temp=it->first;
		temp+=",";
		temp+=ScpGlobalObject::GetInstance()->GetTypeName(it->second->GetType());
		allobjects.push_back(temp);
	}
	UnLock();
	return allobjects;
}
void ScpUserObject3::DumpObject(const std::string& objectname, CScriptEngine * engine)
{
	ScpObject *  obj =GetObject(objectname);
	if(obj)
	{
		obj->Show(engine);
	}
}
void ScpUserObject3::Copy(ScpUserObject3  *userobject)
{
	Lock();
	userobjmap=userobject->userobjmap;
	UnLock();
}
void ScpUserObject3::DeepCopy(ScpUserObject3 * userobject)
{
	Lock();
	ITUSEROBJMAP3 it = userobject->userobjmap.begin();
	while (it != userobject->userobjmap.end())
	{
		std::string name = it->first;
		ScpObject * obj = it->second;
		if (obj->GetType() != ObjFunction)
			MapObject(name, it->second->Clone(""));
		else
			MapObject(name, it->second);
		it++;
	}
	UnLock();
}
void ScpUserObject3::Lock()
{
#ifdef WIN32
	//EnterCriticalSection(&cs);
#else 
	//递归调用时无法返回,LINUX下不宜使用
	//pthread_mutex_lock(&mutex);
#endif	
}
void ScpUserObject3::UnLock()
{
#ifdef WIN32
	//LeaveCriticalSection(&cs);
#else 
	//递归调用时无法返回,LINUX下不宜使用
	//pthread_mutex_unlock(&mutex);
#endif
}
