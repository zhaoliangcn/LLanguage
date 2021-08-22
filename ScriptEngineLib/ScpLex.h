#ifndef _H_SCPLEX
#define _H_SCPLEX
#include "ScpObject.h"

class ScpLex
{
public:	
	explicit ScpLex(std::wstring commandstring);
	~ScpLex(void);
	std::wstring GetNextToken();
	std::wstring GetLastToken();
	std::wstring GetCurrentToken();
	BOOL IsUnaryOperator(std::wstring & Token);  //�Ƿ���һԪ�����
	BOOL IsBinaryOperator(std::wstring & token); //�Ƿ��Ƕ�Ԫ�����
private:
	std::wstring Expression;
	std::wstring last;
	std::wstring current;
	std::wstring next;
	ULONG startpos;
};

#endif //_H_SCPLEX