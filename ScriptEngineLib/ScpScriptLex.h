
#ifndef _H_SCPSCRIPTLEX
#define _H_SCPSCRIPTLEX
#include "ScpObject.h"
#include "ScpObjectSpace.h"
//词法分析的主体


const static wchar_t * scpOperationAdd = L"+";
const static wchar_t * scpOperationSubtraction = L"-";
const static wchar_t * scpOperationMinus = L"-";

const static wchar_t * scpOperationMultiplication = L"*";
const static wchar_t * scpOperationDivision = L"/";
const static wchar_t * scpOperationMod = L"%";

const static wchar_t * scpOperationAssign = L"=";
const static wchar_t * scpOperationAddAndAssign = L"+=";
const static wchar_t * scpOperationSubAndAssign = L"-=";
const static wchar_t * scpOperationMulAndAssign = L"*=";
const static wchar_t * scpOperationDivAndAssign = L"/=";
const static wchar_t * scpOpeartionModAndAssign = L"%=";






const static wchar_t * scpOperationEqual = L"==";
const static wchar_t * scpOperationLessthan = L"<";
const static wchar_t * scpOperationLessorEqual = L"<=";
const static wchar_t * scpOperationBigthan = L">";
const static wchar_t * scpOperationBigorEqual = L">=";
const static wchar_t * scpOperationNot = L"!";
const static wchar_t * scpOperationNotEqual = L"!=";
const static wchar_t * scpOperationSelfAdd = L"++";  //未实现
const static wchar_t * scpOperationSelfSub = L"--"; //未实现

const static wchar_t * scpOperationBitAnd = L"&";
const static wchar_t * scpOperationBitAndAndAssign = L"&=";
const static wchar_t * scpOperationBitOr = L"|";
const static wchar_t * scpOperationBitOrAndAssign = L"|=";
const static wchar_t * scpOperationBitNot = L"~";  
const static wchar_t * scpOperationBitNotAndAssign = L"~=";
const static wchar_t * scpOperationBitXor = L"^";
const static wchar_t * scpOperationBitXorAndAssign = L"^=";
const static wchar_t * scpOperationBitShiftLeft = L"<<";
const static wchar_t * scpOpeartionBitShiftLeftAndAssign = L"<<=";
const static wchar_t * scpOperationBitShiftRight = L">>";
const static wchar_t * scpOpeartionBitShiftRightAndAssign = L">>=";
const static wchar_t * scpOperationObjectRefrence = L".";

const static wchar_t * scpOperationLogicalAnd = L"&&";
const static wchar_t * scpOperationLogicalOr = L"||";

const static wchar_t * scpOperationsRegExp = L"\\+|\\-|\\*|/|%";
const static wchar_t * scpEndofExpression = L"EOF";

const static wchar_t * scpLeftParentheses = L"(";
const static wchar_t * scpRightParentheses = L")";

const static wchar_t * scpLeftBrace = L"{";
const static wchar_t * scpRightBrace = L"}";

const static wchar_t * scpLeftBracket = L"[";
const static wchar_t * scpRightBracket = L"]";




const static wchar_t * strPathTag = L"\\";
const static wchar_t * scpComment = L"#";
const static wchar_t * scpDoubleQuote = L"\"";

const static wchar_t * scpColon = L":";

const static wchar_t * scpComma = L",";

const static wchar_t * scpCppComment = L"//";
const static wchar_t * scpSemicolon = L";";

class CScriptEngine;
class ScpScriptLex
{
public:
	ScpScriptLex();	
	~ScpScriptLex(void);
	void Attach(CScriptEngine * eng);

	void SetExpression(std::wstring& Expression);

	BOOL ParseCommandLine(std::wstring& wcommandstring,ULONG& commandvalue,VTPARAMETERS & vtparameters);
	BOOL IsUserFunction(std::wstring token);
	BOOL IsClassInstance(std::wstring token);
	std::wstring GetNextToken(BOOL Convert = FALSE);
	std::wstring GetPrevToken();
	std::wstring PeekNextToken(BOOL Convert = FALSE);
	std::wstring PeekNext2Token(BOOL Convert = FALSE);
	std::wstring GetCurrentToken();
	BOOL IsOperator(std::wstring token);
	static BOOL IsBinaryOperator(std::wstring & token);
	static BOOL IsUnaryOperator(std::wstring & Token);
	static BOOL IsAssignOperator(std::wstring & Token);
	int GetBinaryOperationPriority(std::wstring &strOperation);                     //获得运算符的优先级
	int GetOperationPriority(std::wstring &strOperation);
	CScriptEngine * engine;
private:
	std::wstring wcommandline;
	std::wstring currenttoken;
	std::wstring prevtoken;
	std::wstring::iterator currentpos;
};

#endif //_H_SCPSCRIPTLEX