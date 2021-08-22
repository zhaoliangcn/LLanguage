#include "ScpRangeObject.h"
#include "ScpIntObject.h"
#include "ScriptEngine.h"
#include "ScpStringObject.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"
ScpRangeObject::ScpRangeObject()
{
	objecttype = ObjRange;
	start = -1;
	end = -1;
	step = -1;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(str_CN_head, InnerFunction_head);
	BindObjectInnerFuction(str_EN_head, InnerFunction_head);

	BindObjectInnerFuction(str_CN_tail, InnerFunction_tail);
	BindObjectInnerFuction(str_EN_tail, InnerFunction_tail);

	BindObjectInnerFuction(str_CN_step, InnerFunction_step);
	BindObjectInnerFuction(str_EN_step, InnerFunction_step);

	BindObjectInnerFuction(str_CN_reset, InnerFunction_reset);
	BindObjectInnerFuction(str_EN_reset, InnerFunction_reset);

}

ScpRangeObject::~ScpRangeObject()
{
	std::vector<ScpObject *>::iterator it = Elements.begin();
	while (it != Elements.end())
	{
		ScpObject *temp = *it;
		if (temp)
		{
			temp->DelRef();
		}
		it = Elements.erase(it);
	}
}

void ScpRangeObject::Show(CScriptEngine * engine)
{
	for (int i = 0;i < Elements.size();i++)
	{
		Elements.at(i)->Show(engine);
	}
}

ScpObject * ScpRangeObject::Clone(std::wstring strObjName)
{
	return nullptr;
}

std::wstring ScpRangeObject::ToString()
{
	return std::wstring();
}

void ScpRangeObject::Release()
{
	delete this;
}

bool ScpRangeObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}

ScpObject * ScpRangeObject::CallInnerFunction(std::wstring & functionname, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

int ScpRangeObject::Init()
{
	std::vector<ScpObject *>::iterator it = Elements.begin();
	while (it!=Elements.end())
	{
		ScpObject *temp = *it;
		if (temp)
		{
			temp->DelRef();
		}
		it = Elements.erase(it);
	}
	int count = 0;
	for (int i = start;i <= end;i += step)
	{
		ScpIntObject * elem = new ScpIntObject;
		elem->value = i;
		elem->AddRef();
		Elements.push_back(elem);
		count++;
	}
	return count;
}

ScpObject * ScpRangeObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpRangeObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

ScpObject * ScpRangeObject::InnerFunction_head(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * head = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (head)
	{
		head->value = ((ScpRangeObject*)thisObject)->start;
		return head;
	}
	return nullptr;
}

ScpObject * ScpRangeObject::InnerFunction_tail(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{

	ScpIntObject * tail = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (tail)
	{
		tail->value = ((ScpRangeObject*)thisObject)->end;
		return tail;
	}
	return nullptr;
}

ScpObject * ScpRangeObject::InnerFunction_step(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * Istep = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	if (Istep)
	{
		Istep->value = ((ScpRangeObject*)thisObject)->step;
		return Istep;
	}
	return nullptr;
}

ScpObject * ScpRangeObject::InnerFunction_reset(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 3)
	{
		std::wstring wstart = parameters->at(0);
		std::wstring wend = parameters->at(1);
		std::wstring wstep = parameters->at(2);
		ScpObject * objstart = engine->GetCurrentObjectSpace()->FindObject(wstart);
		ScpObject * objend = engine->GetCurrentObjectSpace()->FindObject(wend);
		ScpObject * objstep = engine->GetCurrentObjectSpace()->FindObject(wend);
		if (objstart && objstart->GetType() == ObjInt)
		{
			((ScpRangeObject*)thisObject)->start = ((ScpIntObject*)objstart)->value;
		}
		else
		{
			if (IsStaticNumber(wstart))
			{
				((ScpRangeObject*)thisObject)->start = StringToInt(wstart);
			}
		}
		if (objend && objend->GetType() == ObjInt)
		{
			((ScpRangeObject*)thisObject)->end = ((ScpIntObject*)objend)->value;
		}
		else
		{
			if (IsStaticNumber(wend))
			{
				((ScpRangeObject*)thisObject)->end = StringToInt(wend);
			}
		}
		if (objstep && objstep->GetType() == ObjInt)
		{
			((ScpRangeObject*)thisObject)->end = ((ScpIntObject*)objstep)->value;
		}
		else
		{
			if (IsStaticNumber(wstep))
			{
				((ScpRangeObject*)thisObject)->step = StringToInt(wstep);
			}
		}
		((ScpRangeObject*)thisObject)->Init();
		return thisObject;
	}
	return nullptr;
}

ScpObject * __stdcall ScpRangeObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() == 5)
	{
		std::wstring wstart = paramters->at(2);
		std::wstring wend = paramters->at(3);
		std::wstring wstep = paramters->at(4);
		ScpRangeObject * range = new ScpRangeObject;
		if (range)
		{
			if (IsStaticNumber(wstart))
			{
				range->start = StringToInt(wstart);
			}
			if (IsStaticNumber(wend))
			{
				range->end = StringToInt(wend);
			}
			if (IsStaticNumber(wstep))
			{
				range->step = StringToInt(wstep);
			}
			range->Init();
			return range;
		}
	}
	return NULL;
}
