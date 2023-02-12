#ifndef _H_SCPLEX
#define _H_SCPLEX
#include "ScpObject.h"

class ScpLex
{
public:	
	explicit ScpLex(std::string commandstring);
	~ScpLex(void);
	std::string GetNextToken();
	std::string GetLastToken();
	std::string GetCurrentToken();
	BOOL IsUnaryOperator(std::string & Token);  //是否是一元运算符
	BOOL IsBinaryOperator(std::string & token); //是否是二元运算符
private:
	std::string Expression;
	std::string last;
	std::string current;
	std::string next;
	ULONG startpos;
};

#endif //_H_SCPLEX