#ifndef _H_SCRIPTSCANNER
#define _H_SCRIPTSCANNER

//�ű�Դ����ɨ����
#include <string>
class ScriptScanner
{
public:
	ScriptScanner();
	~ScriptScanner();

	bool ParseSingleLine(std::wstring & line);
};

#endif //_H_SCRIPTSCANNER