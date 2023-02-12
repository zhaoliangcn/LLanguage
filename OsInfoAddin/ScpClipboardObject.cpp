#include "ScpClipboardObject.h"
#ifdef _WIN32
#include "Clipboard.h"
#endif 
#include "../Common/commonutil.hpp"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/commanddefine_uni.h"

ScpClipboardObject::ScpClipboardObject()
{
	objecttype = ObjClipboard;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_copy, InnerFunction_copy);
	BindObjectInnerFuction(scpcommand_en_copy, InnerFunction_copy);

	BindObjectInnerFuction(scpcommand_cn_paste, InnerFunction_paste);
	BindObjectInnerFuction(scpcommand_en_paste, InnerFunction_paste);

	BindObjectInnerFuction(scpcommand_cn_clear, InnerFunction_clear);
	BindObjectInnerFuction(scpcommand_en_clear, InnerFunction_clear);
}


ScpClipboardObject::~ScpClipboardObject()
{
}



void ScpClipboardObject::Show(CScriptEngine * engine)
{
}

ScpObject * ScpClipboardObject::Clone(std::string strObjName)
{
	ScpClipboardObject * obj = new ScpClipboardObject;
	return obj;
}

std::string ScpClipboardObject::ToString()
{
	return std::string();
}

void ScpClipboardObject::Release()
{
}

bool ScpClipboardObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}

ScpObject * ScpClipboardObject::CallInnerFunction(std::string & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * ScpClipboardObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	return nullptr;
}

ScpObject * ScpClipboardObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
	}
	return nullptr;
}

ScpObject * ScpClipboardObject::InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters && parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (obj &&obj->GetType() == ObjString)
		{
			ScpStringObject * strobj = (ScpStringObject *)obj;
#ifdef _WIN32
			CClipboard clipboard;
			clipboard.SetString(NULL, strobj->content);
#endif
			return obj;
		}
	}
	return nullptr;
}

ScpObject * ScpClipboardObject::InnerFunction_paste(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters && parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (obj &&obj->GetType() == ObjString)
		{
			ScpStringObject * strobj = (ScpStringObject *)obj;
#ifdef _WIN32
			CClipboard clipboard;
			strobj->content = clipboard.GetString(NULL);
#endif
			return obj;
		}
	}
	return nullptr;
}

ScpObject * ScpClipboardObject::InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
#ifdef _WIN32
	CClipboard clipboard;
	clipboard.Clear(NULL);
#endif
	return nullptr;
}

ScpObject * __stdcall ScpClipboardObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	return new ScpClipboardObject();
}
