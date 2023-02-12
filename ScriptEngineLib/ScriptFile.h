/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCRIPT_FILE
#define _H_SCRIPT_FILE


#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>


typedef std::vector<std::string> VTSTRINGS;
typedef std::vector<std::string>::iterator ITSTRINGS;
enum EncodeType
{
	EncodeUnknown,
	Ansi,
	Unicode,
	UnicodeBigEndian,
	Utf8,
	Utf8BOM,
};
class CScriptFile
{
public:
	CScriptFile(void);
	~CScriptFile(void);

	static bool IsValidScript(std::string headline);
	static bool IsValidScript(std::wstring headline);
	static bool IsValidScriptLib(std::string headline);
	static bool IsValidScriptLib(std::wstring headline);
	static bool IsComment(std::string& commandline);
	static bool IsCppComment(std::string& commandline);
	EncodeType GetScriptEncodeType(const wchar_t *scriptfilename);
	bool  ReadAll(const wchar_t *scriptfilename,VTSTRINGS& body);
	bool  ReadAll(const char *scriptfilename, VTSTRINGS& body);
	bool  ReadAllFromMemory(const char *memoryscript,VTSTRINGS& body);
	static std::wstring GetPath(const wchar_t* FullPathName);
	static bool FileExist(std::wstring FilePathName);

	static std::string GetPath(const char* FullPathName);
	static bool FileExist(std::string FilePathName);
};



#endif //