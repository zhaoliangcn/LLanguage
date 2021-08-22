#ifndef _H_SCPADDRESSOBJECT
#define _H_SCPADDRESSOBJECT
#include "../ScriptEngineLib/ScpObject.h"
const static ScpObjectType	ObjAddress = 37;

const static wchar_t * str_CN_ObjAddress = L"地址";
const static wchar_t * str_CN_ScpAddressParameterIp = L"IP";
const static wchar_t * str_CN_ScpAddressParameterPort = L"端口";

const static wchar_t * str_EN_ObjAddress = L"address";
const static wchar_t * str_EN_ScpAddressParameterIp = L"ip";
const static wchar_t * str_EN_ScpAddressParameterPort = L"port";
class ScpAddressObject :
	public ScpObject
{
public:
	ScpAddressObject(void);
	~ScpAddressObject(void);
	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	void SetIp(std::wstring strip);
	void SetPort(std::wstring strport);
	std::wstring GetIp();
	std::wstring GetPortStr();
	int GetPort();
	std::wstring addressname;
	std::wstring ip;
	std::wstring port;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};

ScpObject * __stdcall ScpAddressObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

BOOL WINAPI AddressObject_Set_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);

#endif //_H_SCPADDRESSOBJECT