/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//整数对象及其内部成员函数
*/
#ifndef _H_SCPINTOBJECT
#define _H_SCPINTOBJECT
#include "ScpObject.h"

const static wchar_t* scpcommand_square_CN = L"平方";
const static wchar_t* scpcommand_squareroot_CN = L"平方根";
const static wchar_t* scpcommand_cubic_CN = L"立方";
const static wchar_t* scpcommand_cuberoot_CN = L"立方根";
const static wchar_t* scpcommand_abs_CN = L"绝对值";
const static wchar_t* scpcommand_acos_CN = L"反余弦";
const static wchar_t* scpcommand_cos_CN = L"余弦";
const static wchar_t* scpcommand_asin_CN = L"反正弦";
const static wchar_t* scpcommand_sin_CN = L"正弦";
const static wchar_t* scpcommand_atan_CN = L"反正切";
const static wchar_t* scpcommand_tan_CN = L"正切";

const static wchar_t* scpcommand_square_EN = L"square";
const static wchar_t* scpcommand_squareroot_EN = L"sqrt";
const static wchar_t* scpcommand_cubic_EN = L"cubic";
const static wchar_t* scpcommand_cuberoot_EN = L"cuberoot";
const static wchar_t* scpcommand_abs_EN = L"abs";
const static wchar_t* scpcommand_acos_EN = L"acos";
const static wchar_t* scpcommand_cos_EN = L"cos";
const static wchar_t* scpcommand_asin_EN = L"asin";
const static wchar_t* scpcommand_sin_EN = L"sin";
const static wchar_t* scpcommand_atan_EN = L"atan";
const static wchar_t* scpcommand_tan_EN = L"tan";
class ScpIntObject : public ScpObject
{
public:
	ScpIntObject();
	~ScpIntObject();
	

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);	
	int value;

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_transform(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_square(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_squareroot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_cubic(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_cuberoot(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_abs(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_acos(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_cos(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_asin(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_sin(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_atan(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_tan(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};

ScpObject * __stdcall ScpIntObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
#endif// _H_SCPINTOBJECT