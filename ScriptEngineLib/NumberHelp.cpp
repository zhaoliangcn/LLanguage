/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "NumberHelp.h"
#include "../Common/stdstringext.hpp"
BOOL IsStaticNumber(std::wstring Expression)
{
	if(Expression.empty())
		return FALSE;
	STDSTRINGEXT::trim(Expression);
	std::wstring::iterator it = Expression.begin();
	if(*it==L'-')
	{
		it++;
	}
	for(;it!=Expression.end();it++)
	{
		if(!iswdigit(*it))
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL IsStaticDoubleNumber(std::wstring Expression)
{
	if(!IsStaticNumber(Expression))
	{
		if(Expression.empty())
		return FALSE;
		STDSTRINGEXT::trim(Expression);
		std::wstring::iterator it = Expression.begin();
		if(*it==L'-')
		{
			it++;
		}
		for(;it!=Expression.end();it++)
		{
			if(!iswdigit(*it) && (*it)!=L'.')
			{
				return FALSE;
			}
		}
		return TRUE;


/*		double dvalue = _wtof(Expression.c_str());
		if(errno!=EINVAL)
		{				
			return TRUE;		
		}*/	
	}
	return FALSE;
}
BOOL IsStaticString(std::wstring Expression)
{
	if (Expression.length()>=2)
	{
		int len = Expression.length();
		if ((Expression.at(0) == L'"') && (Expression.at(len - 1) == L'"'))
		{
			return TRUE;
		}
	}
	return FALSE;
}
int StringToInt(std::string str)
{
	return atoi(str.c_str());
}
int StringToInt(std::wstring str)
{
	return _wtoi(str.c_str());
}
double StringToDouble(std::string str)
{
	return atof(str.c_str());
}
double StringToDouble(std::wstring str)
{
	return _wtof(str.c_str());
}
__int64 StringToInt64(std::string str)
{
	std::wstring temp;
    temp = STDSTRINGEXT::AToW(str);
	return _wtoi64(temp.c_str());
}
__int64 StringToInt64(std::wstring str)
{
	return _wtoi64(str.c_str());
}
std::wstring IntToWString(int value)
{
	std::wstring temp;
	wchar_t Buffer[512]={0};
#ifdef _WIN32			
	swprintf(Buffer,L"%d",value);
#else 
		swprintf(Buffer,512,L"%d",value);
#endif
	temp=Buffer;
	return temp;
}
std::wstring Int64ToWString(__int64 value)
{
	std::wstring temp;
	wchar_t Buffer[512]={0};
#ifdef _WIN32			
	swprintf(Buffer,L"%I64d",value);
#else 
		swprintf(Buffer,512,L"%I64d",value);
#endif
	temp=Buffer;
	return temp;
}
std::wstring DoubleToWString(double value)
{
	std::wstring temp;
	wchar_t Buffer[512]={0};
#ifdef _WIN32			
	swprintf(Buffer,L"%f",value);
#else 
		swprintf(Buffer,512,L"%f",value);
#endif
	temp=Buffer;
	return temp;
}

std::string IntToString(int value)
{
	std::string temp;
	char Buffer[512]={0};
#ifdef _WIN32			
		sprintf(Buffer,"%d",value);
#else 
		sprintf(Buffer,"%d",value);
#endif
	temp=Buffer;
	return temp;
}
std::string Int64ToString(__int64 value)
{
	std::string temp;
	char Buffer[512]={0};
#ifdef _WIN32			
		sprintf(Buffer,"%I64d",value);
#else 
		sprintf(Buffer,"%ld",value);
#endif
	temp=Buffer;
	return temp;
}
std::string DoubleToString(double value)
{
	std::string temp;
	char Buffer[512]={0};
#ifdef _WIN32			
		sprintf(Buffer,"%f",value);
#else 
		sprintf(Buffer,"%f",value);
#endif
	temp=Buffer;
	return temp;
}
