#ifndef _H_COMMANDDEFINE
#define _H_COMMANDDEFINE
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <wchar.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <sys/time.h>
#define MAX_PATH (260)
typedef int BOOL;
typedef int LONG;
typedef unsigned int ULONG;
#define TRUE 1
#define FALSE 0
typedef unsigned int DWORD;
#define IN
#define OUT
typedef void * HANDLE;
typedef __int64_t __int64;
typedef void * HKEY;
#define MAX_PATH (260)
#define INFINITE 0xFFFFFFFF
#include "Cross.h"
#define GetObject GetObjectW
#ifdef __GNUC__
#define __stdcall __attribute__((stdcall))
#endif
#endif


#ifdef WIN32
#include <tchar.h>
#else
#define _T(x)       __T(x)
#ifdef _UNICODE
#define  TCHAR wchar_t
#define __T(x)      L ## x
#else
#define  TCHAR char
#define __T(x)       x
#endif
#endif


const static ULONG vl_maxbasecommand = 256;


#endif //_H_COMMANDDEFINE