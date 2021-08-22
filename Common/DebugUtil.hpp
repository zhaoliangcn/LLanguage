#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <strsafe.h>
namespace DebugUtil
{
	static inline void TraceA(LPCSTR lpszFormat, ...)
	{
		va_list	args;
		int		nBuf;
		char	szBuf[512];


		va_start(args, lpszFormat);
		nBuf = _vsnprintf_s(szBuf, sizeof(szBuf), lpszFormat, args);
		OutputDebugStringA(szBuf);
		va_end(args);
	}

	static inline void TraceW(LPCWSTR lpszFormat, ...)
	{
		va_list	args;
		int		nBuf;
		wchar_t	szBuf[512];


		va_start(args, lpszFormat);
		nBuf = _vsnwprintf_s(szBuf, sizeof(szBuf) * sizeof(wchar_t), lpszFormat, args);
		OutputDebugStringW(szBuf);
		va_end(args);
	}
};
#else 
#include <stdarg.h>
namespace DebugUtil
{
	static inline void TraceA(const char * lpszFormat, ...)
	{
		va_list	args;
		int		nBuf;
		char	szBuf[512];


		va_start(args, lpszFormat);
		nBuf = snprintf(szBuf, sizeof(szBuf),lpszFormat, args);
		printf("%s",szBuf);
		va_end(args);
	}

	static inline void TraceW(const wchar_t * lpszFormat, ...)
	{
		va_list	args;
		int		nBuf;
		wchar_t	szBuf[512];


		va_start(args, lpszFormat);
		//nBuf = _vsnwprintf(szBuf,lpszFormat, args);
		printf("%S",szBuf);
		va_end(args);
	}
};
#endif
