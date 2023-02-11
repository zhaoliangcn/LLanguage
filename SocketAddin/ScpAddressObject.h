#ifndef _H_SCPADDRESSOBJECT
#define _H_SCPADDRESSOBJECT
#include "../ScriptEngineLib/ScpObject.h"
#include "../ScriptEngineLib/ScpObjectSpace.h"
const static ScpObjectType	ObjAddress = 37;

const static char * str_CN_ObjAddress = "地址";
const static char * str_CN_ScpAddressParameterIp = "IP";
const static char * str_CN_ScpAddressParameterPort = "端口";

const static char * str_EN_ObjAddress = "address";
const static char * str_EN_ScpAddressParameterIp = "ip";
const static char * str_EN_ScpAddressParameterPort = "port";
class ScpAddressObject :
	public ScpObject
{
public:
	ScpAddressObject(void);
	~ScpAddressObject(void);
	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	void SetIp(std::string strip);
	void SetPort(std::string strport);
	std::string GetIp();
	std::string GetPortStr();
	int GetPort();
	std::string addressname;
	std::string ip;
	std::string port;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};

ScpObject * __stdcall ScpAddressObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

BOOL WINAPI AddressObject_Set_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
ScpObject* WINAPI BinaryOpertaionAssign(ScpObject* x, ScpObject* y, ScpObjectSpace* objectSpace);

#endif //_H_SCPADDRESSOBJECT