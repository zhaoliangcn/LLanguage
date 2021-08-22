#include "ScpGpioObject.h"
#include "ScpStringObject.h"
#include "ScpGlobalObject.h"

ScpGpioObject::ScpGpioObject(void)
{
}


ScpGpioObject::~ScpGpioObject(void)
{
}
ScpObjectType ScpGpioObject::GetType()
{
	return ObjGpio;
}
ScpObject * ScpGpioObject::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpGpioObject::ToString()
{
	std::wstring temp;
	return temp;
}
void ScpGpioObject::Show(CScriptEngine * engine)
{

}
void ScpGpioObject::Release() 
{
	delete this;
}
bool ScpGpioObject::IsInnerFunction(std::wstring & functionname)
{
	if(functionname==scpcommand_cn_show || functionname == scpcommand_en_show||
		functionname ==scpcommand_cn_get || functionname == scpcommand_en_get)
	{
		return true;
	}
	return false;
}
ScpObject * ScpGpioObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	if(functionname==scpcommand_cn_show || functionname == scpcommand_en_show)
	{
		Show(engine);
		return this;
	}	
	else if(functionname ==scpcommand_cn_get || functionname == scpcommand_en_get)
	{
		if(parameters->size()==1)
		{
			if(parameters->at(0)==ScpObjectNames::GetSingleInsatnce()->strObjType)
			{
				ScpStringObject * tname=new ScpStringObject ;
				tname->content = ScpGlobalObject::GetInstance()->GetTypeName(this->GetType());
				tname->istemp=true;
				return tname;
			}
		}
	}
	return NULL;
}