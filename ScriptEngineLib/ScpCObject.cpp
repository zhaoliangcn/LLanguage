/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpCObject.h"
#include "ScriptEngine.h"

ScpObjCChar::ScpObjCChar()
{
	objecttype = ObjCChar;
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
ScpObject * ScpObjCChar::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpObjCChar::ToString()
{
	std::wstring temp;
	return temp;
}
void ScpObjCChar::Release()
{
	delete this;
}
bool ScpObjCChar::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCChar::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjCChar::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObjCUnsignedChar::ScpObjCUnsignedChar()
{
	objecttype = ObjCUnsignedChar;
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
ScpObject * ScpObjCUnsignedChar::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjCUnsignedChar::Release()
{
	delete this;
}
std::wstring ScpObjCUnsignedChar::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjCUnsignedChar::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCUnsignedChar::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjCUnsignedChar::GetValueAddress()
{
	return (PADDRESS)Value;
}


ScpObjCInt32::ScpObjCInt32()
{
	objecttype = ObjCInt32;
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

ScpObject * ScpObjCInt32::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjCInt32::Release()
{
	delete this;
}
std::wstring ScpObjCInt32::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjCInt32::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCInt32::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjCInt32::GetValueAddress()
{
	return (PADDRESS)Value;
}


ScpObjUnsignedInt32::ScpObjUnsignedInt32()
{
	objecttype = ObjUnsignedInt32;
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

ScpObject * ScpObjUnsignedInt32::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjUnsignedInt32::Release()
{
	delete this;
}
std::wstring ScpObjUnsignedInt32::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjUnsignedInt32::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjUnsignedInt32::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjUnsignedInt32::GetValueAddress()
{
	return (PADDRESS)Value;
}



ScpObjPointerofChar::ScpObjPointerofChar()
{
	objecttype = ObjPointerofChar;
}
ScpObjPointerofChar::~ScpObjPointerofChar()
{
}
void ScpObjPointerofChar::Show(CScriptEngine * engine)
{
	std::string text;
	text = STDSTRINGEXT::Format("%02X", Value);
	engine->PrintError(text);
}
ScpObject * ScpObjPointerofChar::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjPointerofChar::Release()
{
	delete this;
}
std::wstring ScpObjPointerofChar::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjPointerofChar::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjPointerofChar::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjPointerofChar::GetValueAddress()
{
	return (PADDRESS)Value;
}


ScpObjPointerofWchar::ScpObjPointerofWchar()
{
	objecttype = ObjPointerofWchar;
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
ScpObject * ScpObjPointerofWchar::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjPointerofWchar::Release()
{
	delete this;
}
std::wstring ScpObjPointerofWchar::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjPointerofWchar::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjPointerofWchar::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjPointerofWchar::GetValueAddress()
{
	return (PADDRESS)Value;
}



ScpObjHandle::ScpObjHandle()
{
	objecttype = ObjHandle;
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

ScpObject * ScpObjHandle::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjHandle::Release()
{
	delete this;
}
std::wstring ScpObjHandle::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjHandle::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjHandle::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjHandle::GetValueAddress()
{
	return (PADDRESS)Value;
}



ScpObjPointer::ScpObjPointer()
{
	objecttype = ObjPointer;
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

ScpObject * ScpObjPointer::Clone(std::wstring strObjName)
{
	return NULL;
}
void ScpObjPointer::Release()
{
	delete this;
}
std::wstring ScpObjPointer::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjPointer::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjPointer::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
PADDRESS ScpObjPointer::GetValueAddress()
{
	return (PADDRESS)&Value;
}


ScpObjStruct::ScpObjStruct()
{
	objecttype = ObjStruct;
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
ScpObject *  ScpObjStruct::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring  ScpObjStruct::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjStruct::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjStruct::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void  ScpObjStruct::Release()
{
	delete this;
}
PADDRESS  ScpObjStruct::GetValueAddress()
{
	return (PADDRESS)&Value;
}




ScpObjCShort::ScpObjCShort()
{
	objecttype = ObjCShort;
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
ScpObject *  ScpObjCShort::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring  ScpObjCShort::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjCShort::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCShort::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void  ScpObjCShort::Release()
{
	delete this;
}
PADDRESS  ScpObjCShort::GetValueAddress()
{
	return (PADDRESS)Value;
}


ScpObjCUnsignedShort::ScpObjCUnsignedShort()
{
	objecttype = ObjCUnsignedShort;
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

ScpObject * ScpObjCUnsignedShort::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpObjCUnsignedShort::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjCUnsignedShort::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCUnsignedShort::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void ScpObjCUnsignedShort::Release()
{
	delete this;
}
PADDRESS ScpObjCUnsignedShort::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObjCLong::ScpObjCLong()
{
	objecttype = ObjCLong;
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

ScpObject * ScpObjCLong::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpObjCLong::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjCLong::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCLong::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void ScpObjCLong::Release()
{
	delete this;
}
PADDRESS ScpObjCLong::GetValueAddress()
{
	return (PADDRESS)Value;
}

ScpObjCUnsignedLong::ScpObjCUnsignedLong()
{
	objecttype = ObjCUnsignedLong;
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

ScpObject * ScpObjCUnsignedLong::Clone(std::wstring strObjName)
{
	return NULL;
}
std::wstring ScpObjCUnsignedLong::ToString()
{
	std::wstring temp;
	return temp;
}
bool ScpObjCUnsignedLong::IsInnerFunction(std::wstring & functionname)
{
	return false;
}
ScpObject * ScpObjCUnsignedLong::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}
void ScpObjCUnsignedLong::Release()
{
	delete this;
}
PADDRESS ScpObjCUnsignedLong::GetValueAddress()
{
	return (PADDRESS)Value;
}
