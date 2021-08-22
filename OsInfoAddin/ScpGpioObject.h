#ifndef _H_SCPGPIOOBJECT
#define _H_SCPGPIOOBJECT
#include "ScpObject.h"
const static ScpObjectType	ObjGpio = 67;

const static std::wstring str_CN_ObjGpio = L"GPIO";

const static std::wstring str_EN_ObjGpio = L"gpio";
class ScpGpioObject :
	public ScpObject
{
public:
	ScpGpioObject(void);
	~ScpGpioObject(void);
	virtual ScpObjectType GetType();
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	 virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

};

#endif //_H_SCPGPIOOBJECT