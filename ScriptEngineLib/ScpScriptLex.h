
#ifndef _H_SCPSCRIPTLEX
#define _H_SCPSCRIPTLEX
#include "ScpObject.h"
#include "ScpObjectSpace.h"
//词法分析的主体


const static char  * scpOperationAdd = "+";
const static char  * scpOperationSubtraction = "-";
const static char  * scpOperationMinus = "-";

const static char  * scpOperationMultiplication = "*";
const static char  * scpOperationDivision = "/";
const static char  * scpOperationMod = "%";

const static char  * scpOperationAssign = "=";
const static char  * scpOperationAddAndAssign = "+=";
const static char  * scpOperationSubAndAssign = "-=";
const static char  * scpOperationMulAndAssign = "*=";
const static char  * scpOperationDivAndAssign = "/=";
const static char  * scpOpeartionModAndAssign = "%=";






const static char  * scpOperationEqual = "==";
const static char  * scpOperationLessthan = "<";
const static char  * scpOperationLessorEqual = "<=";
const static char  * scpOperationBigthan = ">";
const static char  * scpOperationBigorEqual = ">=";
const static char  * scpOperationNot = "!";
const static char  * scpOperationNotEqual = "!=";
const static char  * scpOperationSelfAdd = "++";  //未实现
const static char  * scpOperationSelfSub = "--"; //未实现

const static char  * scpOperationBitAnd = "&";
const static char  * scpOperationBitAndAndAssign = "&=";
const static char  * scpOperationBitOr = "|";
const static char  * scpOperationBitOrAndAssign = "|=";
const static char  * scpOperationBitNot = "~";  
const static char  * scpOperationBitNotAndAssign = "~=";
const static char  * scpOperationBitXor = "^";
const static char  * scpOperationBitXorAndAssign = "^=";
const static char  * scpOperationBitShiftLeft = "<<";
const static char  * scpOpeartionBitShiftLeftAndAssign = "<<=";
const static char  * scpOperationBitShiftRight = ">>";
const static char  * scpOpeartionBitShiftRightAndAssign = ">>=";
const static char  * scpOperationObjectRefrence = ".";

const static char  * scpOperationLogicalAnd = "&&";
const static char  * scpOperationLogicalOr = "||";

const static char  * scpOperationsRegExp = "\\+|\\-|\\*|/|%";
const static char  * scpEndofExpression = "EOF";

const static char  * scpLeftParentheses = "(";
const static char  * scpRightParentheses = ")";

const static char  * scpLeftBrace = "{";
const static char  * scpRightBrace = "}";

const static char  * scpLeftBracket = "[";
const static char  * scpRightBracket = "]";




const static char  * strPathTag = "\\";
const static char  * scpComment = "#";
const static char  * scpDoubleQuote = "\"";

const static char  * scpColon = ":";

const static char  * scpComma = ",";

const static char  * scpCppComment = "//";
const static char  * scpSemicolon = ";";

class CScriptEngine;
class ScpScriptLex
{
public:
	ScpScriptLex();	
	~ScpScriptLex(void);
	void Attach(CScriptEngine * eng);

	void SetExpression(std::string& Expression);

	BOOL ParseCommandLine(std::string& wcommandstring,ULONG& commandvalue,VTPARAMETERS & vtparameters);
	BOOL IsUserFunction(std::string token);
	BOOL IsClassInstance(std::string token);
	std::string GetNextToken(BOOL Convert = FALSE);
	std::string GetPrevToken();
	std::string PeekNextToken(BOOL Convert = FALSE);
	std::string PeekNext2Token(BOOL Convert = FALSE);
	std::string GetCurrentToken();
	BOOL IsOperator(std::string token);
	static BOOL IsBinaryOperator(std::string & token);
	static BOOL IsUnaryOperator(std::string & Token);
	static BOOL IsAssignOperator(std::string & Token);
	int GetBinaryOperationPriority(std::string &strOperation);                     //获得运算符的优先级
	int GetOperationPriority(std::string &strOperation);
	CScriptEngine * engine;
private:
	std::string wcommandline;
	std::string currenttoken;
	std::string prevtoken;
	std::string::iterator currentpos;
};

#endif //_H_SCPSCRIPTLEX