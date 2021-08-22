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
	BOOL IsUnaryOperator(std::wstring & Token);  //是否是一元运算符
	BOOL IsBinaryOperator(std::wstring & token); //是否是二元运算符
private:
	std::wstring Expression;
	std::wstring last;
	std::wstring current;
	std::wstring next;
	ULONG startpos;
};

#endif //_H_SCPLEX