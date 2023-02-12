#ifndef _H_SCRIPTENGINE
#define _H_SCRIPTENGINE
#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#endif
#include <string>
#include <iostream>

#define LangCn (0)
#define LangEn (1)



#include "ScriptFile.h"
#include "ScpScriptCommand.h"
#include "ScpGlobalCommands.h"
#include "ScpObject_uni.h"
#include "ScpRuntimeStack.h"
#include "ScriptScanner.h"
#include "ScpAst.h"
#include "ScriptByteCode.h"
#include "ScpObject.h"
//语法对象

#include "ScpGlobalCommandObject.h"
#include "ScpObjectSpace.h"
#include "ScpUserObject.h"
#include "ScpScriptLex.h"
#include "ScpExpressionAnalyser.h"
#include "ScpExpressionsObject.h"
#include "ScpExtendObjectMgr.h"
#include "ScpObjectMgr.h"
#include "ScpByteCode.h"
#include "ScriptByteCode.h"

#include "ScriptDebugger.h"
#include "UIMessage.h"

class CScriptCommand;
class ScpClassObject;
class ScpObject;

class CScriptEngine
{
public:
	friend class CScriptCommand;
	friend class ScpClassObject;
	friend class ScpFunctionObject;
	friend class ScpWhileStatementObject;
	friend class ScpIfStatementObject;
	friend class ScpExpressionTreeNode;
	friend class ScpExpressionAnalyser;
	friend class ScpExpressionBlock;
	friend class ScpByteCode;
	friend class ScriptByteCode;

	CScriptEngine();
	~CScriptEngine();
	
	/*
	注册界面消息回调
	*/
	BOOL RegisterUICallBack(void * uiclass,UICallBack callback);
	BOOL RegisterUIStepCallBack(void * uiclass,UICallBack callback);
	/*
	以调试模式执行序列化为字符串的脚本
	*/
	int DebugMemoryScript(const char * memroyscript);
	/*
	导入库文件
	*/
	int ImportLib(std::string libfilename,bool islib=true);
	int ImportLibFromMemory(void * Mem,bool islib=true);
	int ParseLibBody(const char * libFileName, VTSTRINGS &LibBody, bool islib);
	/*
	将当前脚本转储为文件
	*/
	int DumpScript(std::string newscriptfilename);
	/*
	执行脚本文件
	*/
	int DoScript(std::string scriptfilename,SCRIPTRUNTYPE mode=RUN_NORMAL); //0 normal run 1 debug 2 singlestep
	/*
	将一行字符串作为脚本执行
	*/
	int DoString(std::string &script);
	/*
	将函数中的一行脚本预编译为内部格式
	*/

	/*
	清理脚本引擎
	*/
	void Cleanup();
	/*
	获得当前执行的脚本的行号
	*/
	int GetCurrentCommandLine();

	/*
	枚举全局名字空间中的对象名
	*/
	VTSTRINGS EnumObjects();
	/*
	显示指定对象的内部信息
	*/
	void DumpObject(std::string objectname);
	
	/*
	获得当前名字空间
	*/
	ScpObjectSpace * GetCurrentObjectSpace();
	/*
	切换当前名字空间
	*/
	void SetCurrentObjectSpace(ScpObjectSpace * objspace);
	/*
	获得上一条错误信息
	*/
	std::string GetLastErrorString();
	/*
	设置最后一条错误消息
	*/
	void SetLastErrorString(const char * error);

	/*
	根据命令名映射命令
	*/
	ULONG QueryCommandValue(const std::string & commandstring);
	/*
	查询当前允许注册的用户命令值
	*/
	ULONG QueryCurrentUserCommand();

	int GetLanguge();
	
	std::string GetCurrentSourceLine();

    bool RegisterGlobalFunction(const std::string chscommandstring, const std::string   engcommandstring, unsigned long commandid, GlobalCommandFunction Func);
    void  RegisterGlobalFunctions();
    ScpGlobalCommandObject globalcommand;

	int DoByteCode(const char * ByteCodeFile, SCRIPTRUNTYPE mode = RUN_NORMAL);
	int DoMemByteCode(const unsigned char* ByteCode, unsigned int length, SCRIPTRUNTYPE mode = RUN_NORMAL);
	ScpByteCode scpbytecode;
	int Jit;
	int Build;
	int DumpByteCode(const char *ByteCodeFile);
	/*
	设置调试器 实例
	*/
	bool SetDebugger(IScriptDebugger * dbg);
	void SetScriptFileName(const char*filePathName);
	std::string GetCurrentScriptfilename() {
		return currentscriptfilename;;
	}
	std::string globallib;
private:
	/*
	创建存储当前命令行参数的表对象
	*/
	void Create_Global_CommndLine_TableObject();
	void Create_Global_Environment_TableObject();
	void Create_Global_CurrentTimeObject();
	/*
	初始化脚本引擎
	*/
	void Init();
	
	/*
	指令派发，一行脚本对应一个指令
	*/
    BOOL FetchCommand(unsigned long commandvalue,VTPARAMETERS * vtparameters =NULL);
	
	/*
	加载脚本
	*/
	bool LoadAllScript(std::string scriptfilename);
	/*
	执行已加载的脚本
	逐行解析并执行脚本
	*/
	int DoloadedScript(SCRIPTRUNTYPE mode=RUN_NORMAL);

	//当前语言标记
	int language;
	//切换语言
	void SwitchLanguage(std::string &comment);
	
	
	ULONG vl_usercommand;
	DWORD dwTimeCount;
	                                                                                                  
	//指向全局名字空间
	ScpObjectSpace * globalObjectSpace;
	//指向当前名字空间
	ScpObjectSpace * currentObjectSpace;
	CScriptCommand * scriptcommand;
		
	//当前运行到的脚本行号
	int currentcommandline;
	//保存所有断点的行号
	VTINT breakpoints;

	//当前脚本文件名
	std::string currentscriptfilename;
	//当前脚本完整内容
	VTSTRINGS allScriptBody;
	//保存已导入的库文件名
	VTSTRINGS importedlibs;

	CScriptFile scriptfile;

	std::string LastErrorString;

	//保存当前脚本的字节码
	ScriptByteCode bytecode;
	
	ScpScriptLex lex;
	ScpExpressionAnalyser ana;

	SCRIPTRUNTYPE runmode;
	IScriptDebugger * debugger;
	
public:

	CScpObjectMgr obj_mgr;
	//扩展模块相关
	ScpExtendObjectMgr extend_obj_mgr;



	//输出重定向
	CUIMessage uimessage;
    void PrintError(const std::wstring& ErrorMessage, bool withnewline = true)
	{
		uimessage.PostUIMessage(ErrorMessage.c_str(), withnewline);
	}
    void PrintError(const std::string& ErrorMessage, bool withnewline = true)
	{
		uimessage.PostUIMessage(ErrorMessage.c_str(), withnewline);
	}
	void PrintError(const wchar_t * ErrorMessage, bool withnewline = true)
	{
		uimessage.PostUIMessage(ErrorMessage,withnewline);
	}
	void PrintError(const char * ErrorMessage, bool withnewline = true)
	{
		uimessage.PostUIMessage(ErrorMessage,withnewline);
	}
	void PrintErrorWithNewLine(const wchar_t * Format, ...)
	{
#ifdef _WIN32
		va_list pArgs;
		va_start(pArgs, Format);
		const static DWORD BufferSize = 4096*2;
		wchar_t * szMessageBuffer = (wchar_t *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
		if (szMessageBuffer)
		{
			memset(szMessageBuffer, 0, BufferSize);
			StringCbVPrintfW(szMessageBuffer, BufferSize, Format, pArgs);
			uimessage.PostUIMessage(szMessageBuffer, TRUE);
			HeapFree(GetProcessHeap(), 0, szMessageBuffer);
		}
		va_end(pArgs);
#else
#endif
	}
};



#endif //_H_SCRIPTENGINE