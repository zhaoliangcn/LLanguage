/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//整数对象及其内部成员函数
*/
#ifndef _H_SCPINTOBJECT
#define _H_SCPINTOBJECT
#include "ScpObject.h"

const static char * scpcommand_square_CN = "平方";
const static char * scpcommand_squareroot_CN = "平方根";
const static char * scpcommand_cubic_CN = "立方";
const static char * scpcommand_cuberoot_CN = "立方根";
const static char * scpcommand_abs_CN = "绝对值";
const static char * scpcommand_acos_CN = "反余弦";
const static char * scpcommand_cos_CN = "余弦";
const static char * scpcommand_asin_CN = "反正弦";
const static char * scpcommand_sin_CN = "正弦";
const static char * scpcommand_atan_CN = "反正切";
const static char * scpcommand_tan_CN = "正切";
const static char * scpcommand_pow_CN = "次方";
const static char * scpcommand_add_CN = "加";
const static char * scpcommand_sub_CN = "减";

const static char * scpcommand_square_EN = "square";
const static char * scpcommand_squareroot_EN = "sqrt";
const static char * scpcommand_cubic_EN = "cubic";
const static char * scpcommand_cuberoot_EN = "cuberoot";
const static char * scpcommand_abs_EN = "abs";
const static char * scpcommand_acos_EN = "acos";
const static char * scpcommand_cos_EN = "cos";
const static char * scpcommand_asin_EN = "asin";
const static char * scpcommand_sin_EN = "sin";
const static char * scpcommand_atan_EN = "atan";
const static char * scpcommand_tan_EN = "tan";
const static char * scpcommand_pow_EN = "pow";
const static char * scpcommand_add_EN = "add";
const static char * scpcommand_sub_EN = "sub";

class ScpIntObject : public ScpObject
{
public:
	ScpIntObject();
	~ScpIntObject();
	

	virtual void Show(CScriptEngine * engine);
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);	
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
	static ScpObject * InnerFunction_pow(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject* InnerFunction_add(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);
	static ScpObject* InnerFunction_sub(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine);

};

ScpObject * __stdcall ScpIntObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
#endif// _H_SCPINTOBJECT