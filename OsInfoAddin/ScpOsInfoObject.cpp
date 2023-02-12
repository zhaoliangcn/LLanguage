#include "ScpOsInfoObject.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../Common/commonutil.hpp"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/ScpObjectFactory.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#ifdef WIN32
#include "../OsInfoAddin/VersionHelpers.h"
#include "../Common/netaddressutil.h"
#else 
#define  wcsicmp wcscasecmp
#define _stricmp strcasecmp
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
std::string get_ipaddressall()
{
    std::string ip;
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
        {
        if (!ifa->ifa_addr)
                {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) // check it is IP4
                {
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            ip+=ifa->ifa_name;
            ip+="\t";
            ip+=addressBuffer;
            ip+="\n";
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
                else if (ifa->ifa_addr->sa_family == AF_INET6) // check it is IP6
                {
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            ip+=ifa->ifa_name;
            ip+="\t";
            ip+=addressBuffer;
            ip+="\n";
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL)
        {
                freeifaddrs(ifAddrStruct);
        }

    return ip;
}
std::string get_ipaddress(const char * dev_name,const char * ip_family)
{
    std::string ip;
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
        {
        if (!ifa->ifa_addr)
                {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) // check it is IP4
                {
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if(StringCaseCompare(ifa->ifa_name,dev_name)==0
                    && StringCaseCompare(ip_family,"ip4")==0)
            {
                ip=addressBuffer;
            }
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
                else if (ifa->ifa_addr->sa_family == AF_INET6) // check it is IP6
                {
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            if(StringCaseCompare(ifa->ifa_name,dev_name)==0
                     && StringCaseCompare(ip_family,"ip6")==0)
            {
                ip=addressBuffer;
            }
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL)
        {
                freeifaddrs(ifAddrStruct);
        }

    return ip;
}
#endif
#include "../Common/stdstringext.hpp"

std::wstring GetVersionString()
{
	std::wstring ver;
	#ifdef WIN32
	RTL_OSVERSIONINFOEXW verInfo = { 0 };
	verInfo.dwOSVersionInfoSize = sizeof(verInfo);

	static fnRtlGetVersion RtlGetVersion = (fnRtlGetVersion)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion");

	if (RtlGetVersion != 0 && RtlGetVersion((PRTL_OSVERSIONINFOW)&verInfo) == 0)
	{
		ver = STDSTRINGEXT::Format(L"%d.%d", verInfo.dwMajorVersion, verInfo.dwMinorVersion);
	}
	#endif
	return ver;
}



ScpObject * __stdcall ScpOsInfoObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpOsInfoObject();
}

ScpOsInfoObject::ScpOsInfoObject()
{
	objecttype = ObjOsInfo;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);
}


ScpOsInfoObject::~ScpOsInfoObject()
{
}



void ScpOsInfoObject::Show(CScriptEngine * engine)
{
}

ScpObject * ScpOsInfoObject::Clone(std::string strObjName)
{
	ScpOsInfoObject *obj = new ScpOsInfoObject;
	return obj;
}

std::string ScpOsInfoObject::ToString()
{
	return std::string();
}

void ScpOsInfoObject::Release()
{
}

bool ScpOsInfoObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}

ScpObject * ScpOsInfoObject::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpOsInfoObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpOsInfoObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
			else
			{
				wsparam = ((ScpStringObject *)objparam0)->content;
			}
		}
		if (strOsVersion_CN == wsparam || strOsVersion_EN == wsparam)
		{
			ScpStringObject * obj = (ScpStringObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			obj->content = STDSTRINGEXT::W2UTF(GetVersionString());
			return obj;
		}
		else if (_stricmp(wsparam.c_str(), "ip") == 0)
		{
			std::string ip, mac;
#ifdef _WIN32
			GetIpMacAddressA(ip, mac);
#else
                        ip = get_ipaddressall();
#endif 
			ScpStringObject * obj = (ScpStringObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			obj->content = ip;
			return obj;
		}
		else if (_stricmp(wsparam.c_str(), "mac") == 0)
		{
			std::string ip, mac;
#ifdef _WIN32
			GetIpMacAddressA(ip, mac);
#endif 
			ScpStringObject * obj = (ScpStringObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
			obj->content = mac;
			return obj;
		}

	}
        else if (parameters->size() == 3)
        {
            std::string wsparam = parameters->at(0);
            StringStripQuote(wsparam);
            ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(wsparam);
            if (objparam0 && objparam0->GetType() == ObjString)
            {
                     wsparam = ((ScpStringObject *)objparam0)->content;
            }
            std::string wsparam1 = parameters->at(1);
            StringStripQuote(wsparam1);
            ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(wsparam1);
            if (objparam1 && objparam1->GetType() == ObjString)
            {
                     wsparam1 = ((ScpStringObject *)objparam1)->content;
            }
            std::string wsparam2 = parameters->at(2);
            StringStripQuote(wsparam2);
            ScpObject * objparam2 = engine->GetCurrentObjectSpace()->FindObject(wsparam2);
            if (objparam2 && objparam2->GetType() == ObjString)
            {
                     wsparam2 = ((ScpStringObject *)objparam2)->content;
            }
            if (_stricmp(wsparam.c_str(), "ip") == 0)
            {
                    std::string ip, mac;
#ifdef _WIN32
                    GetIpMacAddressA(ip, mac);
#else
                    ip = get_ipaddress(wsparam1.c_str(), wsparam2.c_str());
#endif
                    ScpStringObject * obj = (ScpStringObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
                    obj->content = ip;
                    return obj;
            }
        }
	return thisObject;
}
