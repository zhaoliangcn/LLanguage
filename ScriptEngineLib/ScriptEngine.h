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
//�﷨����

#include "ScpGlobalCommandObject.h"
#include "ScpObjectSpace.h"
#include "ScpUserObject.h"
#include "ScpScriptLex.h"
#include "ScpExpressionAnalyser.h"
#include "ScpExpressionsObject.h"
#include "ScpExtendObjectMgr.h"
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
	ע�������Ϣ�ص�
	*/
	BOOL RegisterUICallBack(void * uiclass,UICallBack callback);
	BOOL RegisterUIStepCallBack(void * uiclass,UICallBack callback);
	/*
	�Ե���ģʽִ�����л�Ϊ�ַ����Ľű�
	*/
	int DebugMemoryScript(const wchar_t * memroyscript);
	/*
	������ļ�
	*/
	int ImportLib(std::wstring libfilename,bool islib=true);
	int ImportLibFromMemory(void * Mem,bool islib=true);
	int ParseLibBody(const wchar_t * libFileName,VTSTRINGS &LibBody,bool islib);
	/*
	����ǰ�ű�ת��Ϊ�ļ�
	*/
	int DumpScript(std::wstring newscriptfilename);
	/*
	ִ�нű��ļ�
	*/
	int DoScript(std::wstring scriptfilename,SCRIPTRUNTYPE mode=RUN_NORMAL); //0 normal run 1 debug 2 singlestep
	/*
	��һ���ַ�����Ϊ�ű�ִ��
	*/
	int DoString(std::wstring &script);
	/*
	�������е�һ�нű�Ԥ����Ϊ�ڲ���ʽ
	*/

	/*
	����ű�����
	*/
	void Cleanup();
	/*
	��õ�ǰִ�еĽű����к�
	*/
	int GetCurrentCommandLine();

	/*
	ö��ȫ�����ֿռ��еĶ�����
	*/
	VTSTRINGS EnumObjects();
	/*
	��ʾָ��������ڲ���Ϣ
	*/
	void DumpObject(std::wstring objectname);
	
	/*
	��õ�ǰ���ֿռ�
	*/
	ScpObjectSpace * GetCurrentObjectSpace();
	/*
	�л���ǰ���ֿռ�
	*/
	void SetCurrentObjectSpace(ScpObjectSpace * objspace);
	/*
	�����һ��������Ϣ
	*/
	std::wstring GetLastErrorString();
	/*
	�������һ��������Ϣ
	*/
	void SetLastErrorString(std::wstring &error);

	/*
	����������ӳ������
	*/
	ULONG QueryCommandValue(const std::wstring & commandstring);
	/*
	��ѯ��ǰ����ע����û�����ֵ
	*/
	ULONG QueryCurrentUserCommand();

	int GetLanguge();
	
	//std::string GetObjectNames(int lang);

	std::wstring GetCurrentSourceLine();

    bool RegisterGlobalFunction(const std::wstring chscommandstring, const std::wstring   engcommandstring, unsigned long commandid, GlobalCommandFunction Func);
    void  RegisterGlobalFunctions();
    ScpGlobalCommandObject globalcommand;

	int DoByteCode(const char * ByteCodeFile, SCRIPTRUNTYPE mode = RUN_NORMAL);
	int DoMemByteCode(const unsigned char* ByteCode, unsigned int length, SCRIPTRUNTYPE mode = RUN_NORMAL);
	ScpByteCode scpbytecode;
	int Jit;
	int DumpByteCode(const wchar_t *ByteCodeFile);
	/*
	���õ����� ʵ��
	*/
	bool SetDebugger(IScriptDebugger * dbg);
	void SetScriptFileName(const wchar_t*filePathName);
	std::wstring GetCurrentScriptfilename() {
		return currentscriptfilename;;
	}
private:
	/*
	�����洢��ǰ�����в����ı����
	*/
	void Create_Global_CommndLine_TableObject();
	void Create_Global_Environment_TableObject();
	void Create_Global_CurrentTimeObject();
	/*
	��ʼ���ű�����
	*/
	void Init();
	
	/*
	ָ���ɷ���һ�нű���Ӧһ��ָ��
	*/
    BOOL FetchCommand(unsigned long commandvalue,VTPARAMETERS * vtparameters =NULL);
	
	/*
	���ؽű�
	*/
	bool LoadAllScript(std::wstring scriptfilename);
	/*
	ִ���Ѽ��صĽű�
	���н�����ִ�нű�
	*/
	int DoloadedScript(SCRIPTRUNTYPE mode=RUN_NORMAL);

	//��ǰ���Ա��
	int language;
	//�л�����
	void SwitchLanguage(std::wstring &comment);
	
	
	ULONG vl_usercommand;
	DWORD dwTimeCount;
	                                                                                                  
	//ָ��ȫ�����ֿռ�
	ScpObjectSpace * globalObjectSpace;
	//ָ��ǰ���ֿռ�
	ScpObjectSpace * currentObjectSpace;
	CScriptCommand * scriptcommand;
		
	//��ǰ���е��Ľű��к�
	int currentcommandline;
	//�������жϵ���к�
	VTINT breakpoints;

	//��ǰ�ű��ļ���
	std::wstring currentscriptfilename;
	//��ǰ�ű���������
	VTSTRINGS allScriptBody;
	//�����ѵ���Ŀ��ļ���
	VTSTRINGS importedlibs;

	CScriptFile scriptfile;

	std::wstring LastErrorString;

	//���浱ǰ�ű����ֽ���
	ScriptByteCode bytecode;
	
	ScpScriptLex lex;
	ScpExpressionAnalyser ana;

	SCRIPTRUNTYPE runmode;
	IScriptDebugger * debugger;
	
public:
	//��չģ�����
	ScpExtendObjectMgr extend_obj_mgr;

	//����ض���
	CUIMessage uimessage;
    void PrintError(const std::wstring& ErrorMessage, BOOL withnewline = TRUE)
	{
		uimessage.PostUIMessage(ErrorMessage.c_str(), withnewline);
	}
    void PrintError(const std::string& ErrorMessage, BOOL withnewline = TRUE)
	{
		uimessage.PostUIMessage(ErrorMessage.c_str(), withnewline);
	}
	void PrintError(const wchar_t * ErrorMessage, BOOL withnewline = TRUE)
	{
		uimessage.PostUIMessage(ErrorMessage,withnewline);
	}
	void PrintError(const char * ErrorMessage, BOOL withnewline = TRUE)
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