/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//基本对象的工厂函数
*/
#include "ScpObjectFactory.h"
#include "ScpCommonObject.h"
#include "ScpExpressionBlock.h"
#include "ScpExpressionAnalyser.h"

ScpObject * BaseObjectFactory(ScpObjectType type)
{
	if (type == ObjString)
	{
		return new ScpStringObject();
	}
	else if (type == ObjInt)
	{
		return new ScpIntObject();
	}
	else if (type ==ObjBigInt)
	{
		return  new ScpBigIntObject();
	}
	else if (ObjDouble == type)
	{
		return new ScpDoubleObject();
	}
	else if (ObjTable == type)
	{
		return  new ScpTableObject();
	}
	else if (ObjList == type)
	{
		return  new ScpListObject();
	}
	else if (ObjRange == type)
	{
		return  new ScpRangeObject();
	}
	else if (ObjMemory == type)
	{
		return new ScpMemoryObject();
	}
	else if (ObjDirectory == type)
	{
		return new ScpDirectoryObject();
	}
	else if (ObjFile == type)
	{
		return new ScpFileObject();
	}
	else if (ObjJson == type)
	{
		return new ScpJsonObject();
	}
	else if (ObjArray == type)
	{
		//fix
		return new ScpArrayObject();
	}
	else if (ObjNull == type)
	{
		return new ScpNullObject();
	}
	else if (ObjStruct == type)
	{
		return new ScpStructObject();
	}
	else if (ObjTime == type)
	{
		return  new ScpTimeObject();
	}
	else if (ObjRegExp == type)
	{
		return new ScpRegExpObject();
	}
	else if (ObjStack == type)
	{
		return new ScpStackObject();
	}
	else if (ObjQueue == type)
	{
		return new ScpQueueObject();
	}
	else if (ObjMap == type)
	{
		return new ScpMapObject();
	}
	else if (ObjExpressionNode == type)
	{
		return new ScpExpressionTreeNode();
	}
	return NULL;
}