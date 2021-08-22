#pragma once
#include <string.h>
#ifndef _WIN32
#include <sys/types.h>
typedef __int64_t __int64;
int _wtoi(const wchar_t *wstr);
__int64 _wtoi64(const wchar_t *wstr);
float _wtof(const wchar_t* wstr);
#else

#endif
static inline int StringCaseCompare(const char * src, const char* dest)
{
#ifdef _WIN32
	return stricmp(src, dest);
#else
	return strcasecmp(src, dest);
#endif 
}