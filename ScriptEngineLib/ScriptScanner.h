#ifndef _H_SCRIPTSCANNER
#define _H_SCRIPTSCANNER

//脚本源代码扫描器
#include <string>
class ScriptScanner
{
public:
	ScriptScanner();
	~ScriptScanner();

	bool ParseSingleLine(std::wstring & line);
};

#endif //_H_SCRIPTSCANNER