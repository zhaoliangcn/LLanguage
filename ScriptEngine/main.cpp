#include <stdio.h>


void Useage()
{
	printf("author: zhaoliangcn@126.com\r\n");
	printf("ScriptEngine.exe scriptfile.scp\r\n");
}
#ifndef _WIN32
#include "../Common/stdstringext.hpp"
#include "../ScriptEngineLib/ScriptEngine.h"
int main(int argc, char* argv[])
{
	//	system("pause");
	if(argc>=2)
	{
		int Jit = 0;
		int Build = 0;
		for (int i = 1;i < argc;i++)
		{
			if (strcasecmp(argv[i], "/g") == 0 ||
				strcasecmp(argv[i], "-g") == 0)
			{
				Jit = 1;
			}
			if (strcasecmp(argv[i], "/b") == 0 ||
				strcasecmp(argv[i], "-b") == 0)
			{
				Build = 1;
			}
		}
		CScriptEngine scriptengine;

		scriptengine.SetScriptFileName(argv[1]);

		if (Jit)
		{
			scriptengine.Jit = Jit;
		}
		if (Build)
		{
			scriptengine.Build = Build;
		}
		if (strstr(argv[1], ".scpb") != 0)
		{
			scriptengine.DoByteCode(argv[1]);
		}
		else
		{
			scriptengine.DoScript(argv[1]);
		}
		//system("pause");
	}
	else 
	{
		Useage();
	}
	return 0 ;
}
#else
#include "../ScriptEngineDll/ScriptEngineDll.h"
#include <tchar.h>
#include <stdlib.h>
#include "../Common/commonutil.hpp"

#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
struct ScriptEngineContext
{
	HMODULE hDLL;
	HANDLE hscript;
	FUNC_CreateScriptEngine  CreateScriptEngine;
	FUNC_ScriptDoScript ScriptDoScript;
	FUNC_CloseScriptEngine CloseScriptEngine ;
	FUNC_ScriptRegisterGlobalCommand ScriptRegisterGlobalCommand;
	FUNC_ScriptDoByteCode ScriptDoByteCode ;
	FUNC_ScriptSetJit ScriptSetJit ;
	FUNC_ScriptDumpByteCode ScriptDumpByteCode;
	FUNC_ScriptSetBuild ScriptSetBuild;
}g_context;
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
bool ctrlhandler(DWORD fdwctrltype)
{
	switch (fdwctrltype)
	{
		// handle the ctrl-c signal.
	case CTRL_C_EVENT:
		if (g_context.ScriptDumpByteCode)
		{
			g_context.ScriptDumpByteCode(g_context.hscript,NULL);
		}
		return(false);
		// ctrl-close: confirm that the user wants to exit.
		//case CTRL_CLOSE_EVENT:
		//	printf("ctrl-close event\n\n");
		//	return(true);
		//	// pass other signals to the next handler.
		//case CTRL_BREAK_EVENT:
		//	printf("ctrl-break event\n\n");
		//	return false;
		//case CTRL_LOGOFF_EVENT:
		//	printf("ctrl-logoff event\n\n");
		//	return false;
		//case CTRL_SHUTDOWN_EVENT:
		//	printf("ctrl-shutdown event\n\n");
		//	return false;
	default:
		return false;
	}
}
void Leak()
{
	//_CrtSetBreakAlloc(1024);
	for (int i = 0;i < 100;i++)
	{
		char * testleak = (char*)malloc(1024);
	}
	
}

#else
#endif

int main(int argc, char* argv[])
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	//	system("pause");
	
	if(argc>=2)
	{
		//Leak();
		DWORD dwStart = GetCurrentTickCount();
		memset(&g_context, 0, sizeof(g_context));
		SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true);
		int Jit = 0;
		int Build = 0;
		int CountTime = 0;
		for (int i=1;i<argc;i++)
		{
			if ((_stricmp(argv[i], "/g") == 0) || (_stricmp(argv[i], "-g") == 0))
			{
				Jit = 1;
			}
			else if ((_stricmp(argv[i], "/b") == 0) || (_stricmp(argv[i], "--build") == 0) || (_stricmp(argv[i], "-b") == 0))
			{
				Jit = 1;
				Build = 1;
			}
			if ((_stricmp(argv[i], "/t") == 0) || (_stricmp(argv[i], "-t") == 0))
			{
				CountTime = 1;
			}
		}
		g_context.hDLL = LoadLibraryW(L"ScriptEngineDll.dll");
		if(g_context.hDLL)
		{
			g_context.CreateScriptEngine=(FUNC_CreateScriptEngine)GetProcAddress(g_context.hDLL,"CreateScriptEngine");
			g_context.ScriptDoScript =(FUNC_ScriptDoScript)GetProcAddress(g_context.hDLL,"ScriptDoScript");
			g_context.CloseScriptEngine = (FUNC_CloseScriptEngine)GetProcAddress(g_context.hDLL,"CloseScriptEngine");
			g_context.ScriptRegisterGlobalCommand=(FUNC_ScriptRegisterGlobalCommand)GetProcAddress(g_context.hDLL, "ScriptRegisterGlobalCommand");
			g_context.ScriptDoByteCode=(FUNC_ScriptDoByteCode)GetProcAddress(g_context.hDLL, "ScriptDoByteCode");
			g_context.ScriptSetJit = (FUNC_ScriptSetJit)GetProcAddress(g_context.hDLL, "ScriptSetJit");
			g_context.ScriptDumpByteCode = (FUNC_ScriptDumpByteCode)GetProcAddress(g_context.hDLL, "ScriptDumpByteCode");
			g_context.ScriptSetBuild = (FUNC_ScriptSetBuild)GetProcAddress(g_context.hDLL, "ScriptSetBuild");
			if(g_context.CreateScriptEngine && 
				g_context.ScriptDoScript && 
				g_context.CloseScriptEngine &&
				g_context.ScriptRegisterGlobalCommand &&
				g_context.ScriptDoByteCode && 
				g_context.ScriptSetJit &&
				g_context.ScriptDumpByteCode &&
				g_context.ScriptSetBuild)
			{
				g_context.hscript = g_context.CreateScriptEngine();
				if(g_context.hscript)
				{					
					if (Jit)
					{
						
						if (g_context.ScriptSetJit)
						{
							g_context.ScriptSetJit(g_context.hscript, 1);
						}
					}
					if(Build)
					{
						if (g_context.ScriptSetBuild)
						{
							g_context.ScriptSetBuild(g_context.hscript, 1);
						}
					}
					if (strstr(argv[1], ".scpb") != 0)
					{
						g_context.ScriptDoByteCode(g_context.hscript,argv[1], RUN_NORMAL);
					}
					else
					{
						g_context.ScriptDoScript(g_context.hscript, argv[1], RUN_NORMAL);
					}
					//system("pause");
					g_context.CloseScriptEngine(g_context.hscript);
				}
			}
		}

		//system("pause");
		if (CountTime)
		{
			DWORD dwEnd = GetCurrentTickCount();
			printf("%d\n", dwEnd - dwStart);
		}
	}
	else 
	{
		Useage();
	}
	
	//_CrtDumpMemoryLeaks();
	return 0 ;
}
#endif
