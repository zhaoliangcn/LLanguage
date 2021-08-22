#include "DebugUtil.h"
#include <strsafe.h>

void DebugUtil::TraceA(LPCSTR lpszFormat, ...)
{
	va_list	args;
	int		nBuf;
	char	szBuf[512];


	va_start(args, lpszFormat);
	nBuf = _vsnprintf_s(szBuf, sizeof(szBuf), lpszFormat, args);
	OutputDebugStringA(szBuf);
	va_end(args);
}

void DebugUtil::TraceW(LPCWSTR lpszFormat, ...)
{
	va_list	args;
	int		nBuf;
	wchar_t	szBuf[512];


	va_start(args, lpszFormat);
	nBuf = _vsnwprintf_s(szBuf, sizeof(szBuf) * sizeof(wchar_t), lpszFormat, args);
	OutputDebugStringW(szBuf);
	va_end(args);
}