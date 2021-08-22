/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//L脚本语言运行时库，二元运算符、一元运算符的功能实现
*/
#include "ScpRuntime.h"
#include "ScpCommonObject.h"
#include "ScpOperationMgr.h"
#include "ScriptEngine.h"



ScpObject * Add(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	pBinaryOpertaion BinaryOpertaionFunc= ScpOperationMgr::GetInstance()->GetBinaryOperation(L"+", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret =  BinaryOpertaionFunc(x, y, objectSpace);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjInt);
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value + ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value + ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value + ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpIntObject *)x)->value + ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value + ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value + ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpBigIntObject *)x)->value + ((ScpDoubleObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = (__int64)((ScpIntObject *)x)->value + ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value + ((ScpBigIntObject*)y)->value;
		}
		else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
		{
			ret = objectSpace->AcquireTempObject(ObjTable);
			((ScpTableObject *)ret)->Combine(x);
			((ScpTableObject *)ret)->Combine(y);
		}
		else if (x->GetType() == ObjList && y->GetType() == ObjList)
		{
			ret = objectSpace->AcquireTempObject(ObjList);
			((ScpListObject *)ret)->Combine(x);
			((ScpListObject *)ret)->Combine(y);
		}
		else if (x->GetType() == ObjString && y->GetType() == ObjString)
		{
			ret = objectSpace->AcquireTempObject(ObjString);
			ret = (ScpObject *)Connect((ScpStringObject*)x, (ScpStringObject*)y, (ScpStringObject*)ret);
		}
		else
		{
			std::wstring error = L"Invalid Add Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}	
	if(ret)
	ret->istemp = true;
	return ret;
}
ScpObject * Sub(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"-", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjInt);
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value - ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value - ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value - ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpIntObject *)x)->value - ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value - ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value - ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpBigIntObject *)x)->value - ((ScpDoubleObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = (__int64)((ScpIntObject *)x)->value - ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value - ((ScpBigIntObject*)y)->value;
		}
		else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
		{
			ret = objectSpace->AcquireTempObject(ObjTable);
			((ScpTableObject *)ret)->Combine(x);
			((ScpTableObject *)ret)->Exclude(y);
		}
		else if (x->GetType() == ObjList && y->GetType() == ObjList)
		{
			ret = objectSpace->AcquireTempObject(ObjList);
			((ScpListObject *)ret)->Combine(x);
			((ScpListObject *)ret)->Exclude(y);
		}
		else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpTimeObject*)x)->value - ((ScpTimeObject*)y)->value;
		}
		else
		{
			std::wstring error = L"Invalid Sub Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	if (ret)
	ret->istemp = true;
	return ret;
}
ScpObject * Mul( ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"*", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjInt);
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value*((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value*((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value*((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpIntObject *)x)->value*((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value*((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value*((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpBigIntObject *)x)->value*((ScpDoubleObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjBigInt);
			((ScpBigIntObject*)ret)->value = (__int64)((ScpIntObject *)x)->value*((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			ret = objectSpace->AcquireTempObject(ObjDouble);
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value*((ScpBigIntObject*)y)->value;
		}
		else
		{
			std::wstring error = L"Invalid Mul Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	if (ret)
	ret->istemp=true;
	return ret;
}
ScpObject * Div(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (y->GetType() == ObjInt)
	{
		if (((ScpIntObject *)y)->value == 0)
		{
			//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidDividend);
			return ret;
		}
	}
	else if (y->GetType() == ObjDouble)
	{
		if (((ScpDoubleObject *)y)->value == 0)
		{
			//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidDividend);
			return ret;
		}
	}
	else if (y->GetType() == ObjBigInt)
	{
		if (((ScpBigIntObject *)y)->value == 0)
		{
			//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidDividend);
			return ret;
		}
	}
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value / ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		ret = objectSpace->AcquireTempObject(ObjDouble);
		((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value / ((ScpDoubleObject*)y)->value;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjDouble);
		((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value / ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		ret = objectSpace->AcquireTempObject(ObjDouble);
		((ScpDoubleObject*)ret)->value = ((ScpIntObject *)x)->value / ((ScpDoubleObject*)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value / ((ScpBigIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value / ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		ret = objectSpace->AcquireTempObject(ObjDouble);
		((ScpDoubleObject*)ret)->value = ((ScpBigIntObject *)x)->value / ((ScpDoubleObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject*)ret)->value = (__int64)((ScpIntObject *)x)->value / ((ScpBigIntObject *)y)->value;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjDouble);
		((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value / ((ScpBigIntObject*)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid Div Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	if (ret)
	ret->istemp = true;
	return ret;
}
ScpObject * Mod(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value % ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value % ((ScpBigIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value % ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value % ((ScpIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid Mod Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * Assign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"=", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			((ScpIntObject *)x)->value = ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			((ScpDoubleObject*)x)->value = ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			((ScpDoubleObject*)x)->value = ((ScpIntObject*)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			((ScpIntObject*)x)->value = (int)((ScpDoubleObject*)y)->value;
			//提示数据截断 
		}
		else if (x->GetType() == ObjPointerofWchar && y->GetType() == ObjString)
		{
			ScpObjPointerofWchar *obj = (ScpObjPointerofWchar *)x;
			ScpStringObject *strobj = (ScpStringObject *)y;
			obj->Value = (wchar_t *)strobj->content.c_str();
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			((ScpBigIntObject *)x)->value = ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			((ScpBigIntObject *)x)->value = ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			((ScpBigIntObject *)x)->value = (__int64)((ScpDoubleObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			((ScpIntObject *)x)->value = (int)((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			((ScpDoubleObject *)x)->value = (double)((ScpBigIntObject*)y)->value;
		}
		else if (x->GetType() == ObjString && y->GetType() == ObjString)
		{
			((ScpStringObject *)x)->content = ((ScpStringObject *)y)->content;
		}
		else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
		{
			((ScpTableObject *)x)->Assign(y);
		}
		else if (x->GetType() == ObjList && y->GetType() == ObjList)
		{
			((ScpListObject *)x)->Assign(y);
		}
		else if (x->GetType() == ObjFile && ((y->GetType() == ObjStaticString) || (y->GetType() == ObjString)))
		{
			if (ScpFileObject::FileExist(((ScpStringObject*)y)->content))
			{
				((ScpFileObject *)x)->filename = ((ScpStringObject*)y)->content;
			}
		}
		else if (x->GetType() == ObjString && y->GetType() == ObjTime)
		{
			((ScpStringObject *)x)->content = ((ScpTimeObject*)y)->ToString();
		}
		else if (x->GetType() == ObjMemory && y->GetType() == ObjMemory)
		{
			((ScpMemoryObject *)x)->ReleaseMem();
			*((ScpMemoryObject *)x) = *((ScpMemoryObject *)y);
		}
		else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
		{
			((ScpTimeObject *)x)->value = ((ScpTimeObject *)y)->value;
		}
		else if (x->GetType() == ObjRegExp && y->GetType() == ObjString)
		{
			((ScpRegExpObject *)x)->wstrregexp = ((ScpStringObject *)y)->content;
			((ScpRegExpObject *)x)->Compile(((ScpRegExpObject *)x)->wstrregexp);
		}
		else if (x->GetType() == ObjRegExp && y->GetType() == ObjRegExp)
		{
			((ScpRegExpObject *)x)->wstrregexp = ((ScpRegExpObject *)y)->wstrregexp;
			((ScpRegExpObject *)x)->Compile(((ScpRegExpObject *)x)->wstrregexp);
		}
		else if (x->GetType() == ObjClassInstance && y->GetType() == ObjClassInstance)
		{
			//确保是相同类的实例
			if (((ScpClassInstanceObject *)x)->instanceOf == ((ScpClassInstanceObject *)y)->instanceOf)
			{
				((ScpClassInstanceObject *)x)->UserClassObjectSpace.userobject.Destroy();
				((ScpClassInstanceObject *)x)->UserClassObjectSpace.userobject.DeepCopy(&((ScpClassInstanceObject *)y)->UserClassObjectSpace.userobject);
				//拷贝类成员的属性
				((ScpClassInstanceObject *)x)->memberattrmap = ((ScpClassInstanceObject *)y)->memberattrmap;
			}
		}
		else
		{
			std::wstring error = L"Invalid Assign Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
		
	}
	return ret;
}
ScpObject * Equal(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = objectSpace->AcquireTempObject(ObjInt);
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject *)x)->value == ((ScpIntObject *)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpDoubleObject*)x)->value == ((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((int)((ScpDoubleObject*)x)->value == ((ScpIntObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject*)x)->value == (int)((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjMemory && y->GetType() == ObjMemory)
	{
		((ScpIntObject *)ret)->value = memcmp(((ScpMemoryObject *)x)->Address, ((ScpMemoryObject *)y)->Address, ((ScpMemoryObject *)y)->Size) == 0 ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value == ((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value == ((ScpIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value == (__int64)((ScpDoubleObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value == (int)((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpDoubleObject *)x)->value == ((ScpBigIntObject*)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjString && y->GetType() == ObjString)
	{
		((ScpIntObject *)ret)->value = ((ScpStringObject *)x)->content == ((ScpStringObject *)y)->content ? 1 : 0;
	}
	else if (x->GetType() == ObjFile && y->GetType() == ObjFile)
	{
		ScpFileObject * f1 = (ScpFileObject*)x;
		ScpFileObject * f2 = (ScpFileObject*)y;
		if (ScpFileObject::Compare(f1->filename, f2->filename) == 0)
		{
			((ScpIntObject*)ret)->value = 1;
		}
		else
		{
			((ScpIntObject*)ret)->value = 0;
		}
	}
	else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
	{
		*((ScpIntObject*)ret) = ScpTimeObject::Equl((ScpTimeObject*)x, (ScpTimeObject*)y);
	}
	else
	{
		std::wstring error = L"Invalid Equal Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * Lessthan(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = objectSpace->AcquireTempObject(ObjInt);
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject *)x)->value<((ScpIntObject *)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpDoubleObject*)x)->value<((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((int)((ScpDoubleObject*)x)->value<((ScpIntObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject*)x)->value<(int)((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value<((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value<((ScpIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value<(__int64)((ScpDoubleObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value<(int)((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpDoubleObject *)x)->value<((ScpBigIntObject*)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjString && y->GetType() == ObjString)
	{
		((ScpIntObject *)ret)->value = ((ScpStringObject *)x)->content<((ScpStringObject *)y)->content ? 1 : 0;
	}
	else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
	{
		*((ScpIntObject*)ret) = ScpTimeObject::LessThan((ScpTimeObject*)x, (ScpTimeObject*)y);
	}
	else
	{
		std::wstring error = L"Invalid LessThan Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * LessorEqual(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = objectSpace->AcquireTempObject(ObjInt);
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject *)x)->value <= ((ScpIntObject *)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpDoubleObject*)x)->value <= ((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((int)((ScpDoubleObject*)x)->value <= ((ScpIntObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject*)x)->value <= (int)((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value <= ((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value <= ((ScpIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value <= (__int64)((ScpDoubleObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value <= (int)((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpDoubleObject *)x)->value <= ((ScpBigIntObject*)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjString && y->GetType() == ObjString)
	{
		((ScpIntObject *)ret)->value = ((ScpStringObject *)x)->content <= ((ScpStringObject *)y)->content ? 1 : 0;
	}
	else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
	{
		*((ScpIntObject*)ret) = ScpTimeObject::LessOrEqul((ScpTimeObject*)x, (ScpTimeObject*)y);
	}
	else
	{
		std::wstring error = L"Invalid LessOrEqual Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * Bigthan(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = objectSpace->AcquireTempObject(ObjInt);
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject *)x)->value>((ScpIntObject *)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpDoubleObject*)x)->value>((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((int)((ScpDoubleObject*)x)->value>((ScpIntObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject*)x)->value>(int)((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value>((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value>((ScpIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value>(__int64)((ScpDoubleObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value>(int)((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpDoubleObject *)x)->value>((ScpBigIntObject*)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjString && y->GetType() == ObjString)
	{
		((ScpIntObject *)ret)->value = ((ScpStringObject *)x)->content>((ScpStringObject *)y)->content ? 1 : 0;
	}
	else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
	{
		*((ScpIntObject*)ret) = ScpTimeObject::BigThan((ScpTimeObject*)x, (ScpTimeObject*)y);
	}
	else
	{
		std::wstring error = L"Invalid BigThan Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * BigorEqual(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = objectSpace->AcquireTempObject(ObjInt);
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject *)x)->value >= ((ScpIntObject *)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpDoubleObject*)x)->value >= ((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((int)((ScpDoubleObject*)x)->value >= ((ScpIntObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject*)x)->value >= (int)((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value >= ((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value >= ((ScpIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value >= (__int64)((ScpDoubleObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value >= (int)((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpDoubleObject *)x)->value >= ((ScpBigIntObject*)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjString && y->GetType() == ObjString)
	{
		((ScpIntObject *)ret)->value = ((ScpStringObject *)x)->content >= ((ScpStringObject *)y)->content ? 1 : 0;
	}
	else if (x->GetType() == ObjTime && y->GetType() == ObjTime)
	{
		*((ScpIntObject*)ret) = ScpTimeObject::BigorEqul((ScpTimeObject*)x, (ScpTimeObject*)y);
	}
	else
	{
		std::wstring error = L"Invalid BigOrEqual Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * Not(ScpObject * x, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret =NULL;
	if (x->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)x)->value = (((ScpIntObject *)x)->value == 1) ? 0 : 1;
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value;
	}
	if (x->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)x)->value = (((ScpBigIntObject *)x)->value == 1) ? 0 : 1;
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value;
	}
	return ret;
}
ScpObject * Minus(ScpObject * x, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if(x->GetType() ==ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value=-((ScpIntObject *)x)->value;
	}	
	else if(x->GetType()==ObjDouble)
	{
		ret= objectSpace->AcquireTempObject(ObjDouble);
		((ScpDoubleObject *)ret)->value=-((ScpDoubleObject *)x)->value;
	}
	else if(x->GetType()==ObjBigInt)
	{
		ret= objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value=-((ScpBigIntObject *)x)->value;
	}
	ret->istemp=true;
	return ret;
}
ScpObject * NotEqual(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = objectSpace->AcquireTempObject(ObjInt);
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject *)x)->value != ((ScpIntObject *)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpDoubleObject*)x)->value != ((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((int)((ScpDoubleObject*)x)->value != ((ScpIntObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = (((ScpIntObject*)x)->value != (int)((ScpDoubleObject*)y)->value) ? 1 : 0;
	}
	else if (x->GetType() == ObjMemory && y->GetType() == ObjMemory)
	{
		((ScpIntObject *)ret)->value = memcmp(((ScpMemoryObject *)x)->Address, ((ScpMemoryObject *)y)->Address, ((ScpMemoryObject *)y)->Size) == 0 ? 0 : 1;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value != ((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value != ((ScpIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
	{
		((ScpIntObject *)ret)->value = ((ScpBigIntObject *)x)->value != (__int64)((ScpDoubleObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value != (int)((ScpBigIntObject *)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpDoubleObject *)x)->value != ((ScpBigIntObject*)y)->value ? 1 : 0;
	}
	else if (x->GetType() == ObjString && y->GetType() == ObjString)
	{
		((ScpIntObject *)ret)->value = ((ScpStringObject *)x)->content != ((ScpStringObject *)y)->content ? 1 : 0;
	}
	else
	{
		std::wstring error = L"Invalid NotEqual Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitAnd(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value&((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value&((ScpBigIntObject *)y)->value;
	}
	else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
	{
		ret = objectSpace->AcquireTempObject(ObjTable);
		((ScpTableObject *)ret)->Combine(x);//一个空的表对象和另一个非空的表对象合并实际上就是复制
		((ScpTableObject *)ret)->Intersection(y);//求交集
	}
	else if (x->GetType() == ObjList && y->GetType() == ObjList)
	{
		ret = objectSpace->AcquireTempObject(ObjList);
		((ScpListObject *)ret)->Combine(x);//一个空的表对象和另一个非空的表对象合并实际上就是复制
		((ScpListObject *)ret)->Intersection(y);//求交集
	}
	else
	{
		std::wstring error = L"Invalid BitAnd Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * BitOr(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value | ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value | ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitOr Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * BitNot(ScpObject * x, CScriptEngine * engine)
{	
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ~((ScpIntObject *)x)->value;
	}
	else if (x->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ~((ScpBigIntObject *)x)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitNot Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;

}
ScpObject * BitXor(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value ^ ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value ^ ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitXor Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * LogicalAnd(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret =NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value && ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value && ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid LogicalAnd Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * LogicalOr(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value || ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value || ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid LogicalOr Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	ret->istemp = true;
	return ret;
}
ScpObject * BitShiftLeft(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value << ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value << ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value << ((ScpBigIntObject *)y)->value;
	}
	else if (x->GetType() == ObjFile && y->GetType() == ObjString)
	{
		ret = x;
		((ScpFileObject *)x)->append(((ScpStringObject *)y)->content);
	}
	else if (x->GetType() == ObjFile && y->GetType() == ObjMemory)
	{
		ret = x;
		((ScpFileObject *)x)->append( ((ScpMemoryObject *)y)->Size, ((ScpMemoryObject *)y)->Address);
	}
	else if (x->GetType() == ObjFile && y->GetType() == ObjInt)
	{
		ret = x;
		((ScpFileObject *)x)->append(sizeof(int), &((ScpIntObject *)y)->value);
	}
	else if (x->GetType() == ObjFile && y->GetType() == ObjDouble)
	{
		ret = x;
		((ScpFileObject *)x)->append(sizeof(double), &((ScpDoubleObject *)y)->value);
	}
	else if (x->GetType() == ObjFile && y->GetType() == ObjBigInt)
	{
		ret = x;
		((ScpFileObject *)x)->append(sizeof(long long), &((ScpBigIntObject *)y)->value);
	}
	else
	{
		std::wstring error = L"Invalid BitShiftLeft Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitShiftRight(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = NULL;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value >> ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		ret = objectSpace->AcquireTempObject(ObjBigInt);
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value >> ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		ret = objectSpace->AcquireTempObject(ObjInt);
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value >> ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitShiftRight Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * AddAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"+=", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value + ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value + ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value + ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			((ScpIntObject*)ret)->value = (int)(((ScpIntObject *)x)->value + ((ScpDoubleObject*)y)->value);
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value + ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value + ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			((ScpBigIntObject*)ret)->value = (__int64)(((ScpBigIntObject *)x)->value + ((ScpDoubleObject *)y)->value);
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			((ScpIntObject*)ret)->value = (int)(__int64)((ScpIntObject *)x)->value + ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value + ((ScpBigIntObject*)y)->value;
		}
		else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
		{
			((ScpTableObject *)ret)->Combine(x);
			((ScpTableObject *)ret)->Combine(y);
		}
		else if (x->GetType() == ObjList && y->GetType() == ObjList)
		{
			((ScpListObject *)ret)->Combine(x);
			((ScpListObject *)ret)->Combine(y);
		}
		else if (x->GetType() == ObjString && y->GetType() == ObjString)
		{
			((ScpStringObject *)x)->content = ((ScpStringObject *)x)->content + ((ScpStringObject *)y)->content;
		}
		else if (x->GetType() == ObjClassInstance)
		{
			ScpObjectType  type = y->GetType();
			if (type != ObjClass
				&& type != ObjClassInstance
				&& type != ObjIfStatement
				&& type != ObjWhileStatement
				)
			{				
				std::wstring name = engine->GetCurrentObjectSpace()->GetObjectNameR(y);
				if (type == ObjFunction) 
				{
					((ScpClassInstanceObject *)x)->MemberVariableAttribute = ScpClassObject::Attr_Public;
					((ScpClassInstanceObject *)x)->AddMemberFunction(name, y);
					((ScpClassInstanceObject *)x)->MemberVariableAttribute = ScpClassObject::Attr_Private;
				}					
				else
				{
					((ScpClassInstanceObject *)x)->MemberVariableAttribute = ScpClassObject::Attr_Public;
					((ScpClassInstanceObject *)x)->AddMemberVariable(name, y);
					((ScpClassInstanceObject *)x)->MemberVariableAttribute = ScpClassObject::Attr_Private;
				}
					
			}
		}
		else
		{
			std::wstring error = L"Invalid AddAndAssign Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	return ret;
}
ScpObject * SubAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"-=", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value - ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value - ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value - ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			((ScpIntObject*)ret)->value = (int)(((ScpIntObject *)x)->value - ((ScpDoubleObject*)y)->value);
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value - ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value - ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			((ScpBigIntObject*)ret)->value = (__int64)(((ScpBigIntObject *)x)->value - ((ScpDoubleObject *)y)->value);
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			((ScpIntObject*)ret)->value = (int)((__int64)((ScpIntObject *)x)->value - ((ScpBigIntObject *)y)->value);
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value - ((ScpBigIntObject*)y)->value;
		}
		else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
		{
			((ScpTableObject *)ret)->Combine(x);
			((ScpTableObject *)ret)->Exclude(y);
		}
		else if (x->GetType() == ObjList && y->GetType() == ObjList)
		{
			((ScpListObject *)ret)->Combine(x);
			((ScpListObject *)ret)->Exclude(y);
		}
		else
		{
			std::wstring error = L"Invalid SubAndAssign Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	return ret;
}
ScpObject * MulAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"*=", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value*((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value*((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value*((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			((ScpIntObject*)ret)->value = (int)(((ScpIntObject *)x)->value*((ScpDoubleObject*)y)->value);
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value*((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value*((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			((ScpBigIntObject*)ret)->value = (__int64)(((ScpBigIntObject *)x)->value*((ScpDoubleObject *)y)->value);
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			((ScpIntObject*)ret)->value = (int)((__int64)((ScpIntObject *)x)->value*((ScpBigIntObject *)y)->value);
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value*((ScpBigIntObject*)y)->value;
		}
		else
		{
			std::wstring error = L"Invalid MulAndAssign Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	return ret;
}
ScpObject * DivAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (y->GetType() == ObjInt)
	{
		if (((ScpIntObject *)y)->value == 0)
		{
			//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidDividend);
			return ret;
		}
	}
	else if (y->GetType() == ObjDouble)
	{
		if (((ScpDoubleObject *)y)->value == 0)
		{
			//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidDividend);
			return ret;
		}
	}
	else if (y->GetType() == ObjBigInt)
	{
		if (((ScpBigIntObject *)y)->value == 0)
		{
			//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidDividend);
			return ret;
		}
	}
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"/=", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value / ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjDouble)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value / ((ScpDoubleObject*)y)->value;
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject*)x)->value / ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjDouble)
		{
			((ScpIntObject*)ret)->value = (int)(((ScpIntObject *)x)->value / ((ScpDoubleObject*)y)->value);
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value / ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			((ScpBigIntObject*)ret)->value = ((ScpBigIntObject *)x)->value / ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjDouble)
		{
			((ScpBigIntObject*)ret)->value = (__int64)(((ScpBigIntObject *)x)->value / ((ScpDoubleObject *)y)->value);
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			((ScpIntObject*)ret)->value = (int)((__int64)((ScpIntObject *)x)->value / ((ScpBigIntObject *)y)->value);
		}
		else if (x->GetType() == ObjDouble && y->GetType() == ObjBigInt)
		{
			((ScpDoubleObject*)ret)->value = ((ScpDoubleObject *)x)->value / ((ScpBigIntObject*)y)->value;
		}
		else
		{
			std::wstring error = L"Invalid DivAndAssign Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	return ret;
}
ScpObject * ModAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (y->GetType() == ObjInt)
	{
		if (((ScpIntObject *)y)->value == 0)
		{
			return ret;
		}
	}
	else if (y->GetType() == ObjDouble)
	{
		if (((ScpDoubleObject *)y)->value == 0)
		{
			return ret;
		}
	}
	else if (y->GetType() == ObjBigInt)
	{
		if (((ScpBigIntObject *)y)->value == 0)
		{
			return ret;
		}
	}
	pBinaryOpertaion BinaryOpertaionFunc = ScpOperationMgr::GetInstance()->GetBinaryOperation(L"/=", x->GetType(), y->GetType());
	if (BinaryOpertaionFunc)
	{
		ret = BinaryOpertaionFunc(x, y, NULL);
	}
	else
	{
		if (x->GetType() == ObjInt && y->GetType() == ObjInt)
		{
			((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value % ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
		{
			((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value % ((ScpBigIntObject *)y)->value;
		}
		else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
		{
			((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value % ((ScpIntObject *)y)->value;
		}
		else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
		{
			((ScpIntObject *)ret)->value = (int)(((ScpBigIntObject *)x)->value % ((ScpIntObject *)y)->value);
		}
		else
		{
			std::wstring error = L"Invalid ModAndAssign Operation ";
			error += engine->GetCurrentSourceLine();
			engine->PrintError(error);
		}
	}
	return ret;
}
ScpObject * BitAndAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value&((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value&((ScpBigIntObject *)y)->value;
	}
	else if (x->GetType() == ObjTable && y->GetType() == ObjTable)
	{
		((ScpTableObject *)ret)->Intersection(y);//求交集
	}
	else if (x->GetType() == ObjList && y->GetType() == ObjList)
	{
		((ScpListObject *)ret)->Intersection(y);//求交集
	}
	else
	{
		std::wstring error = L"Invalid BitAndAndAssign Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitOrAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value | ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value | ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitOrAndAssign Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitNotAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (x->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ~((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt)
	{
		((ScpBigIntObject *)ret)->value = ~((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitNotAndAssign Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitXorAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value ^ ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjBigInt)
	{
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value ^ ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitXorAndAssign Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitShiftLeftAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value << ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value << ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value << ((ScpBigIntObject *)y)->value;
	}	
	else
	{
		std::wstring error = L"Invalid BitShiftLeftAndAssign Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * BitShiftRightAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine)
{
	ScpObjectSpace * objectSpace = engine->GetCurrentObjectSpace();
	ScpObject * ret = x;
	if (x->GetType() == ObjInt && y->GetType() == ObjInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value >> ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjBigInt && y->GetType() == ObjInt)
	{
		((ScpBigIntObject *)ret)->value = ((ScpBigIntObject *)x)->value >> ((ScpIntObject *)y)->value;
	}
	else if (x->GetType() == ObjInt && y->GetType() == ObjBigInt)
	{
		((ScpIntObject *)ret)->value = ((ScpIntObject *)x)->value >> ((ScpBigIntObject *)y)->value;
	}
	else
	{
		std::wstring error = L"Invalid BitShiftRightAndAssign Operation ";
		error += engine->GetCurrentSourceLine();
		engine->PrintError(error);
	}
	return ret;
}
ScpObject * PreSelfAdd(ScpObject * x, CScriptEngine * engine)
{
	ScpObject * ret=x;
	if(x->GetType() ==ObjInt)
	{
		++((ScpIntObject *)x)->value;
	}	
	else if(x->GetType()==ObjDouble)
	{
		++((ScpDoubleObject *)x)->value;
	}
	else if(x->GetType()==ObjBigInt)
	{
		++((ScpBigIntObject *)x)->value;
	}
	return ret;
}
ScpObject * PostSelfAdd(ScpObject * x, CScriptEngine * engine)
{
	ScpObject * ret=x;
	if(x->GetType() ==ObjInt)
	{
		((ScpIntObject *)x)->value++;
	}	
	else if(x->GetType()==ObjDouble)
	{
		((ScpDoubleObject *)x)->value++;
	}
	else if(x->GetType()==ObjBigInt)
	{
		((ScpBigIntObject *)x)->value++;
	}
	return ret;
}
ScpObject * PreSelfSub(ScpObject * x, CScriptEngine * engine)
{
	ScpObject * ret = x;
	if (x->GetType() == ObjInt)
	{
		 --((ScpIntObject *)x)->value;
	}
	else if (x->GetType() == ObjDouble)
	{
		--((ScpDoubleObject *)x)->value;
	}
	else if (x->GetType() == ObjBigInt)
	{
		--((ScpBigIntObject *)x)->value;
	}
	return ret;
}
ScpObject * PostSelfSub(ScpObject * x, CScriptEngine * engine)
{
	ScpObject * ret = x;
	if (x->GetType() == ObjInt)
	{
		 ((ScpIntObject *)x)->value--;
	}
	else if (x->GetType() == ObjDouble)
	{
		 ((ScpDoubleObject *)x)->value--;
	}
	else if (x->GetType() == ObjBigInt)
	{
		 ((ScpBigIntObject *)x)->value--;
	}
	return ret;
}
