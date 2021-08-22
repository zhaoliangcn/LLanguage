#ifndef _H_SCPOBJECTNAMES
#define _H_SCPOBJECTNAMES
#include "ScpObject_uni.h"
#include "ScpErrorCode_uni.h"

class ScpObjectNames
{
public:
	static ScpObjectNames * GetSingleInsatnce();
	~ScpObjectNames();
	void SelectLanguage(int lang);
	int GetLanguage()
	{
		return languageid;
	}



	std::wstring strObjClass ;
	std::wstring strObjDll;
	std::wstring strObjExtObj;
	std::wstring strObjCurrentTime ;
	std::wstring strObjPicture ;	
	std::wstring strObjEnvironmentVariable ;	
	std::wstring strObjStruct ;

	
	
	
	std::wstring strObjWhileStatement ;
	std::wstring strObjType ;
	std::wstring strObjStaticInt ;
	std::wstring strObjStaticDouble ;
	std::wstring strObjStaticString ;
	std::wstring strObjIfStatement ;
	std::wstring strObjMainFunction ;


	std::wstring strScpMessageCaption ;
	std::wstring strHour ;
	std::wstring strMinute ;
	std::wstring strSecond ;
	std::wstring scpStringUpper ;
	std::wstring scpStringLower ;
	std::wstring scpStringReverse ;
	std::wstring scpStringHex;
	std::wstring strGlobal ;
	std::wstring strObjPid ;
	std::wstring strCommandParameter ;
	std::wstring strCurrentScriptFile ;
	std::wstring strCurrentScriptPath ;
	std::wstring strObjCurrentDirectory ;
	std::wstring strObjCallStack ;
	std::wstring strObjPackage ;
	std::wstring strObjFileLine ;
	std::wstring strScpDoubleQuoteLeftcn ;
	std::wstring strScpDoubleQuoteRightcn ;
	std::wstring strScpColoncn ;
	std::wstring strScpCommacn ;
	std::wstring strScpLeftParenthesescn ;
	std::wstring strScpRightParenthesescn ;
	std::wstring scpErrorLastErrorString ;
	std::wstring scpErrorInvalidScript ;
	std::wstring scpErrorInvalidParameter ;
	std::wstring scpErrorCommandSuccess ;
	std::wstring scpErrorCommandFailure ;
	std::wstring scpErrorNotCompletedFunctionDefine ;
	std::wstring scpErrorInvalidFunctionCall ;
	std::wstring scpErrorObjExist ;
	std::wstring scpErrorIsNotObjorStaticNumber ;
	std::wstring scpErrorStaticNumberCanNotBeAssign ;
	std::wstring scpErrorBreakpointHit ;
	std::wstring scpErrorLibNotExist ;
	std::wstring scpErrorCannotListening ;
	std::wstring scpErrorConnectionTimeOut ;
	std::wstring scpErrorConnectionClosed ;
	std::wstring scpErrorSendFail ;
	std::wstring scpErrorReceiveFail ;
	std::wstring scpErrorInvalidFunctionParameter;
	std::wstring scpErrorInvalidDividend;
	std::wstring scpErrorInvalidClassDefine ;
	std::wstring scpErrorCode ;
	std::wstring scpErrorGlobalComand ;
	std::wstring scpErrorObjNotExist ;
	std::wstring scpErrorInvalidClassOrFunctionDefine ;
	std::wstring scpErrorObjectInitializeFault ;
	std::wstring scpErrorObjectDoNotSupportCommand ;
	std::wstring scpErrorInvalidArrayElementType ;
	std::wstring scpErrorNestClassDefine ;
	std::wstring scpErrorInvalidStructDefine ;
	std::wstring scpErrorImportLibFailure ;
	std::wstring scpErrorInvalidExpression ;
	std::wstring scpErrorInvalidFunctionDefine;
	std::wstring scpErrorNotInt;
	std::wstring scpErrorNotNumber;
	std::wstring scpErrorIndexOutofSize;
	std::wstring scpErrorInvalidObjectDefine;
	std::wstring scpErrorInvalidLoadCommand;

	static bool IsValidObjectName(std::wstring& objName);
	private:
		int languageid;
	static ScpObjectNames singleton;
	ScpObjectNames();
};
#endif //_H_SCPOBJECTNAMES