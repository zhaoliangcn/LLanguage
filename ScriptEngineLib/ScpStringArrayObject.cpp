/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpStringArrayObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"

ScpStringArrayObject::ScpStringArrayObject(void)
{
	objecttype = ObjStringArray;
}


ScpStringArrayObject::~ScpStringArrayObject(void)
{
}

void ScpStringArrayObject::Show(CScriptEngine * engine)
{
	for(ITSTRINGS it = content.begin();it!=content.end();it++)
	{
		engine->PrintError(*it);
	}		
}
ScpObject * ScpStringArrayObject::Clone(std::wstring strObjName)
{
	ScpStringArrayObject * obj = new ScpStringArrayObject;
	if (obj)
	{
		obj->content = content;
		return obj;
	}

	return NULL;
}	
std::wstring ScpStringArrayObject::ToString()
{
	std::wstring temp;

	for(ITSTRINGS it = content.begin();it!=content.end();it++)
	{
		temp+=*it;
		temp+=L"\r\n";
	}
	return temp;
}
void ScpStringArrayObject::Release() 
{
	delete this;
}
bool ScpStringArrayObject::IsInnerFunction(std::wstring & functionname)
{
	if (functionname == scpcommand_cn_show || functionname == scpcommand_en_show)
	{
		return true;
	}
	return false;
}
ScpObject * ScpStringArrayObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (functionname == scpcommand_cn_show || functionname == scpcommand_en_show)
	{
		Show(engine);
		return this;
	}
	return NULL;
}
void ScpStringArrayObject::Add(std::wstring strbody)
{
	content.push_back(strbody);
}
void ScpStringArrayObject::Clear()
{
	content.clear();
}
BOOL ScpStringArrayObject::Del(unsigned int index)
{
	BOOL ret = FALSE;
	VTSTRINGS::iterator it = content.begin();
	if(index <content.size())
	{
		content.erase(it+index);
	}
	return ret;
}
BOOL ScpStringArrayObject::Del(std::wstring strbody)
{
	BOOL ret = FALSE;
	for(VTSTRINGS::iterator it = content.begin();it!=content.end();it++)
	{
		if(*it==strbody)
		{
			it=	content.erase(it);
			ret = TRUE;
			break;
		}
	}
	return ret;
}
