/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpCObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
ScpObjCChar::ScpObjCChar()
{
	objecttype = ObjCChar;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCChar::~ScpObjCChar()
{
}
void ScpObjCChar::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%s", &Value);
	engine->PrintError(text.substr(0, 1));
}
ScpObject * ScpObjCChar::Clone(std::string strObjName)
{
	return NULL;
}
std::string ScpObjCChar::ToString()
{
	std::string temp;
	return temp;
}
void ScpObjCChar::Release()
{
	delete this;
}
bool ScpObjCChar::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCChar::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjCChar::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCChar::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObjCUnsignedChar::ScpObjCUnsignedChar()
{
	objecttype = ObjCUnsignedChar;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCUnsignedChar::~ScpObjCUnsignedChar()
{
}
void ScpObjCUnsignedChar::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%d", Value);
	engine->PrintError(text);
}
ScpObject * ScpObjCUnsignedChar::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjCUnsignedChar::Release()
{
	delete this;
}
std::string ScpObjCUnsignedChar::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjCUnsignedChar::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCUnsignedChar::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjCUnsignedChar::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCUnsignedChar::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}


ScpObjCInt32::ScpObjCInt32()
{
	objecttype = ObjCInt32;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCInt32::~ScpObjCInt32()
{
}
void ScpObjCInt32::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%d", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjCInt32::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjCInt32::Release()
{
	delete this;
}
std::string ScpObjCInt32::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjCInt32::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCInt32::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjCInt32::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCInt32::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}


ScpObjUnsignedInt32::ScpObjUnsignedInt32()
{
	objecttype = ObjUnsignedInt32;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjUnsignedInt32::~ScpObjUnsignedInt32()
{
}
void ScpObjUnsignedInt32::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%u", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjUnsignedInt32::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjUnsignedInt32::Release()
{
	delete this;
}
std::string ScpObjUnsignedInt32::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjUnsignedInt32::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjUnsignedInt32::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjUnsignedInt32::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjUnsignedInt32::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}

bool ScpObjPointerofChar::IsInnerFunction(std::string& functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject* ScpObjPointerofChar::CallInnerFunction(std::string& functionname, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;

}
ScpObject* ScpObjPointerofChar::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObjPointerofChar::ScpObjPointerofChar()
{
	objecttype = ObjPointerofChar;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjPointerofChar::~ScpObjPointerofChar()
{

}
void ScpObjPointerofChar::Show(CScriptEngine * engine)
{
	std::string text;
	//text = STDSTRINGEXT::Format("%02X", Value);
	text = Value;
	engine->PrintError(text);
}
ScpObject * ScpObjPointerofChar::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjPointerofChar::Release()
{
	delete this;
}
std::string ScpObjPointerofChar::ToString()
{
	std::string temp;
	return temp;
}

PADDRESS ScpObjPointerofChar::GetValueAddress()
{
	return (PADDRESS)Value;
}


ScpObjPointerofWchar::ScpObjPointerofWchar()
{
	objecttype = ObjPointerofWchar;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjPointerofWchar::~ScpObjPointerofWchar()
{
}
void ScpObjPointerofWchar::Show(CScriptEngine * engine)
{
	std::string text;
	//	text=STDSTRINGEXT::Format("%02X",Value);
	text = STDSTRINGEXT::Format("%s", Value);
	engine->PrintError(text);
}
ScpObject * ScpObjPointerofWchar::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjPointerofWchar::Release()
{
	delete this;
}
std::string ScpObjPointerofWchar::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjPointerofWchar::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjPointerofWchar::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjPointerofWchar::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjPointerofWchar::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}



ScpObjHandle::ScpObjHandle()
{
	objecttype = ObjHandle;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjHandle::~ScpObjHandle()
{
}
void ScpObjHandle::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%02X", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjHandle::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjHandle::Release()
{
	delete this;
}
std::string ScpObjHandle::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjHandle::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjHandle::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjHandle::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjHandle::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}



ScpObjPointer::ScpObjPointer()
{
	objecttype = ObjPointer;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjPointer::~ScpObjPointer()
{
}
void ScpObjPointer::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%02X", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjPointer::Clone(std::string strObjName)
{
	return NULL;
}
void ScpObjPointer::Release()
{
	delete this;
}
std::string ScpObjPointer::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjPointer::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjPointer::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
PADDRESS ScpObjPointer::GetValueAddress()
{
	return (PADDRESS)&Value;
}

ScpObject* ScpObjPointer::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}


ScpObjStruct::ScpObjStruct()
{
	objecttype = ObjStruct;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjStruct::~ScpObjStruct()
{
}
void  ScpObjStruct::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%02X", Value);
	engine->PrintError(text);
}
ScpObject *  ScpObjStruct::Clone(std::string strObjName)
{
	return NULL;
}
std::string  ScpObjStruct::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjStruct::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjStruct::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
void  ScpObjStruct::Release()
{
	delete this;
}
PADDRESS  ScpObjStruct::GetValueAddress()
{
	return (PADDRESS)&Value;
}

ScpObject* ScpObjStruct::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}




ScpObjCShort::ScpObjCShort()
{
	objecttype = ObjCShort;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCShort::~ScpObjCShort()
{
}
void  ScpObjCShort::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%d", Value);
	engine->PrintError(text);
}
ScpObject *  ScpObjCShort::Clone(std::string strObjName)
{
	return NULL;
}
std::string  ScpObjCShort::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjCShort::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCShort::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
void  ScpObjCShort::Release()
{
	delete this;
}
PADDRESS  ScpObjCShort::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCShort::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}


ScpObjCUnsignedShort::ScpObjCUnsignedShort()
{
	objecttype = ObjCUnsignedShort;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCUnsignedShort::~ScpObjCUnsignedShort()
{
}
void ScpObjCUnsignedShort::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%d", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjCUnsignedShort::Clone(std::string strObjName)
{
	return NULL;
}
std::string ScpObjCUnsignedShort::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjCUnsignedShort::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCUnsignedShort::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
void ScpObjCUnsignedShort::Release()
{
	delete this;
}
PADDRESS ScpObjCUnsignedShort::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCUnsignedShort::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObjCLong::ScpObjCLong()
{
	objecttype = ObjCLong;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCLong::~ScpObjCLong()
{
}
void ScpObjCLong::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%d", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjCLong::Clone(std::string strObjName)
{
	return NULL;
}
std::string ScpObjCLong::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjCLong::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCLong::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
void ScpObjCLong::Release()
{
	delete this;
}
PADDRESS ScpObjCLong::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCLong::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObjCUnsignedLong::ScpObjCUnsignedLong()
{
	objecttype = ObjCUnsignedLong;
	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);
}
ScpObjCUnsignedLong::~ScpObjCUnsignedLong()
{
}
void ScpObjCUnsignedLong::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%d", Value);
	engine->PrintError(text);
}

ScpObject * ScpObjCUnsignedLong::Clone(std::string strObjName)
{
	return NULL;
}
std::string ScpObjCUnsignedLong::ToString()
{
	std::string temp;
	return temp;
}
bool ScpObjCUnsignedLong::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpObjCUnsignedLong::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
void ScpObjCUnsignedLong::Release()
{
	delete this;
}
PADDRESS ScpObjCUnsignedLong::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObject* ScpObjCUnsignedLong::InnerFunction_Show(ScpObject* thisObject, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	thisObject->Show(engine);
	return thisObject;
}
