/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//全局对象名称管理，建立对象名称和对象类型ID之间的映射关系
*/
#include "ScpGlobalObject.h"
#include "../Common/MapFindKeyByValue.hpp"
#include "../Common/stdstringext.hpp"

ScpGlobalObject ScpGlobalObject::singleton;

ScpGlobalObject::ScpGlobalObject(void)
{
	Init();
}


ScpGlobalObject::~ScpGlobalObject(void)
{
	chsobjectmap.clear();
	engobjectmap.clear();
}
BOOL ScpGlobalObject::Register(const char * objname_cn,const char * objname_en,ULONG TypeID)
{
	if(chsobjectmap.find(objname_cn)==chsobjectmap.end() 
		&& engobjectmap.find(objname_en)==engobjectmap.end())
	{
		chsobjectmap[objname_cn]=TypeID;
		engobjectmap[objname_en]=TypeID;
		return TRUE;
	}
	return FALSE;
}
void ScpGlobalObject::Init()
{
#ifdef USE_GOOGLE_HASHMAP
	chsobjectmap.set_empty_key(L"");
	chsobjectmap.set_deleted_key(L"");
#endif

	chsobjectmap[str_CN_ObjFile]=ObjFile;
	chsobjectmap[str_CN_ObjCode]=ObjCode;
	chsobjectmap[str_CN_ObjMsgBox]=ObjMsgBox;
	chsobjectmap[str_CN_ObjProc]=ObjProc;	
	chsobjectmap[str_CN_ObjProc1]=ObjProc;	
	chsobjectmap[str_CN_ObjScript]=ObjScript;
	chsobjectmap[str_CN_ObjString]=ObjString;
	chsobjectmap[str_CN_ObjNumber]=ObjNumber;
	chsobjectmap[str_CN_ObjMemory]=ObjMemory;
	chsobjectmap[str_CN_ObjObjState]=ObjState;
	chsobjectmap[str_CN_ObjResult]=ObjResult;
	chsobjectmap[str_CN_ObjFunction]=ObjFunction;
	chsobjectmap[str_CN_ObjInt]=ObjInt;
	chsobjectmap[str_CN_ObjDouble] =ObjDouble;
	chsobjectmap[str_CN_ObjExpression] =ObjExpression;
	chsobjectmap[str_CN_ObjTable] = ObjTable;
	chsobjectmap[str_CN_ObjStack] = ObjStack;
	chsobjectmap[str_CN_ObjQueue] = ObjQueue;
	chsobjectmap[str_CN_ObjElement] = ObjElement;
	chsobjectmap[str_CN_ObjRegExp]=ObjRegExp;
	chsobjectmap[str_CN_ObjClass]=ObjClass;
	chsobjectmap[str_CN_ObjClassInstance]=ObjClassInstance;
	chsobjectmap[str_CN_ObjClassMember]=ObjClassMember;
	chsobjectmap[str_CN_ObjLib]=ObjLib;
	chsobjectmap[str_CN_ObjMap]=ObjMap;
	chsobjectmap[str_CN_ObjThreeElementMap]=ObjThreeElementMap;
	chsobjectmap[str_CN_ObjNull]=ObjNull;
	chsobjectmap[str_CN_ObjEnum]=ObjEnum;
	chsobjectmap[str_CN_ObjPointer]=ObjPointer;
	chsobjectmap[str_CN_ObjHandle]=ObjHandle;
	chsobjectmap[str_CN_ObjCInt32]=ObjCInt32;
	chsobjectmap[str_CN_ObjPointerofChar]=ObjPointerofChar;
	chsobjectmap[str_CN_ObjPointerofWchar]=ObjPointerofWchar;
	chsobjectmap[str_CN_ObjUnsignedInt32]=ObjUnsignedInt32;
	chsobjectmap[str_CN_ObjCFunction]=ObjCFunction;
	chsobjectmap[str_CN_ObjGlobalCommand]=ObjGlobalCommand;	
	chsobjectmap[str_CN_ObjTime]=ObjTime;	
	chsobjectmap[str_CN_ObjCurrentTime]=ObjCurrentTime;
	chsobjectmap[str_CN_ObjPicture]=ObjPicture;	
	chsobjectmap[str_CN_ObjVideo]=ObjVideo;	
	chsobjectmap[str_CN_ObjDirectory]=ObjDirectory;	
	chsobjectmap[str_CN_ObjUserinput]=ObjUserinput;	
	chsobjectmap[str_CN_ObjSubDir]=ObjSubDir;	
	chsobjectmap[str_CN_ObjStringArray]=ObjStringArray;	
	chsobjectmap[str_CN_ObjRandomNumber]=ObjRandomNumber;
	chsobjectmap[str_CN_ObjEnvironmentVariable]=ObjEnvironmentVariable;
	chsobjectmap[str_CN_ObjJson]=ObjJson ;
	chsobjectmap[str_CN_ObjVoid]=ObjVoid;
	chsobjectmap[str_CN_ObjExtensionModule]=ObjExtensionModule;
	chsobjectmap[str_CN_ObjStruct]=ObjStruct;
	chsobjectmap[str_CN_ObjCShort]=ObjCShort;
	chsobjectmap[str_CN_ObjCUnsignedShort]=ObjCUnsignedShort;
	chsobjectmap[str_CN_ObjExpressions]=ObjExpressions;
	chsobjectmap[str_CN_ObjArray]=ObjArray;
	chsobjectmap[str_CN_ObjStaticInt]=ObjStaticInt;
	chsobjectmap[str_CN_ObjStaticDouble]=ObjStaticDouble;
	chsobjectmap[str_CN_ObjStaticString]=ObjStaticString;
	chsobjectmap[str_CN_ObjWhileStatement]=ObjWhileStatement;
	chsobjectmap[str_CN_ObjIfStatement]=ObjIfStatement;
	chsobjectmap[str_CN_ObjCChar]=ObjCChar;
	chsobjectmap[str_CN_ObjCUnsignedChar]=ObjCUnsignedChar;
	chsobjectmap[str_CN_ObjCShort]=ObjCShort;
	chsobjectmap[str_CN_ObjCUnsignedShort]=ObjCUnsignedShort;
	chsobjectmap[str_CN_ObjCLong]=ObjCLong;
	chsobjectmap[str_CN_ObjCUnsignedLong]=ObjCUnsignedLong;
	chsobjectmap[str_CN_ObjStructInstance]=ObjStructInstance;
	chsobjectmap[str_CN_ObjBigInt]=ObjBigInt;
	chsobjectmap[str_CN_ObjList] = ObjList;
	chsobjectmap[str_CN_ObjRange] = ObjRange;



	engobjectmap[str_EN_ObjFile]=ObjFile;
	engobjectmap[str_EN_ObjCode]=ObjCode;
	engobjectmap[str_EN_ObjMsgBox]=ObjMsgBox;
	engobjectmap[str_EN_ObjProc]=ObjProc;	
	engobjectmap[str_EN_ObjProc1]=ObjProc;	
	engobjectmap[str_EN_ObjScript]=ObjScript;
	engobjectmap[str_EN_ObjString]=ObjString;
	engobjectmap[str_EN_ObjNumber]=ObjNumber;
	engobjectmap[str_EN_ObjMemory]=ObjMemory;
	engobjectmap[str_EN_ObjObjState]=ObjState;
	engobjectmap[str_EN_ObjResult]=ObjResult;
	engobjectmap[str_EN_ObjFunction]=ObjFunction;
	engobjectmap[str_EN_ObjInt]=ObjInt;
	engobjectmap[str_EN_ObjDouble] =ObjDouble;
	engobjectmap[str_EN_ObjExpression] =ObjExpression;
	engobjectmap[str_EN_ObjTable] = ObjTable;
	engobjectmap[str_EN_ObjStack] = ObjStack;
	engobjectmap[str_EN_ObjQueue] = ObjQueue;
	engobjectmap[str_EN_ObjElement] = ObjElement;
	engobjectmap[str_EN_ObjRegExp]=ObjRegExp;
	engobjectmap[str_EN_ObjClass]=ObjClass;
	engobjectmap[str_EN_ObjClassInstance]=ObjClassInstance;
	engobjectmap[str_EN_ObjClassMember]=ObjClassMember;
	engobjectmap[str_EN_ObjLib]=ObjLib;
	engobjectmap[str_EN_ObjMap]=ObjMap;
	engobjectmap[str_EN_ObjThreeElementMap]=ObjThreeElementMap;
	engobjectmap[str_EN_ObjNull]=ObjNull;
	engobjectmap[str_EN_ObjEnum]=ObjEnum;
	engobjectmap[str_EN_ObjPointer]=ObjPointer;
	engobjectmap[str_EN_ObjHandle]=ObjHandle;
	engobjectmap[str_EN_ObjCInt32]=ObjCInt32;
	engobjectmap[str_EN_ObjPointerofChar]=ObjPointerofChar;
	engobjectmap[str_EN_ObjPointerofWchar]=ObjPointerofWchar;
	engobjectmap[str_EN_ObjUnsignedInt32]=ObjUnsignedInt32;
	engobjectmap[str_EN_ObjCFunction]=ObjCFunction;
	engobjectmap[str_EN_ObjGlobalCommand]=ObjGlobalCommand;	
	engobjectmap[str_EN_ObjTime]=ObjTime;	
	engobjectmap[str_EN_ObjCurrentTime]=ObjCurrentTime;
	engobjectmap[str_EN_ObjPicture]=ObjPicture;	
	engobjectmap[str_EN_ObjVideo]=ObjVideo;	
	engobjectmap[str_EN_ObjDirectory]=ObjDirectory;	
	engobjectmap[str_EN_ObjUserinput]=ObjUserinput;
	engobjectmap[str_EN_ObjSubDir]=ObjSubDir;	
	engobjectmap[str_EN_ObjStringArray]=ObjStringArray;	
	engobjectmap[str_EN_ObjRandomNumber]=ObjRandomNumber;
	engobjectmap[str_EN_ObjEnvironmentVariable]=ObjEnvironmentVariable;
	engobjectmap[str_EN_ObjJson]=ObjJson ;
	engobjectmap[str_EN_ObjVoid]=ObjVoid;
	engobjectmap[str_EN_ObjExtensionModule]=ObjExtensionModule;
	engobjectmap[str_EN_ObjStruct]=ObjStruct;
	engobjectmap[str_EN_ObjCShort]=ObjCShort;
	engobjectmap[str_EN_ObjCUnsignedShort]=ObjCUnsignedShort;
	engobjectmap[str_EN_ObjExpressions]=ObjExpressions;
	engobjectmap[str_EN_ObjArray]=ObjArray;
	engobjectmap[str_EN_ObjStaticInt]=ObjStaticInt;
	engobjectmap[str_EN_ObjStaticDouble]=ObjStaticDouble;
	engobjectmap[str_EN_ObjStaticString]=ObjStaticString;
	engobjectmap[str_EN_ObjWhileStatement]=ObjWhileStatement;
	engobjectmap[str_EN_ObjIfStatement]=ObjIfStatement;
	engobjectmap[str_EN_ObjCChar]=ObjCChar;
	engobjectmap[str_EN_ObjCUnsignedChar]=ObjCUnsignedChar;
	engobjectmap[str_EN_ObjCShort]=ObjCShort;
	engobjectmap[str_EN_ObjCUnsignedShort]=ObjCUnsignedShort;
	engobjectmap[str_EN_ObjCLong]=ObjCLong;
	engobjectmap[str_EN_ObjCUnsignedLong]=ObjCUnsignedLong;
	engobjectmap[str_EN_ObjStructInstance]=ObjStructInstance;
	engobjectmap[str_EN_ObjBigInt]=ObjBigInt;
	engobjectmap[str_EN_ObjList] = ObjList;
	engobjectmap[str_EN_ObjRange] = ObjRange;
}
ScpObjectType ScpGlobalObject::GetType(const char * strObj)
{
	ScpObjectType type=ObjUnknown;
	if(language==0)
	{
		ITCHSOBJECTMAP it =chsobjectmap.find(strObj); 
		if(it!=chsobjectmap.end())
		{
			type=(ScpObjectType)it->second;
		}
		else
		{
			ITCHSOBJECTMAP it = engobjectmap.find(strObj);
			if (it != engobjectmap.end())
			{
				type = (ScpObjectType)it->second;
			}
		}
	}
	else if(language==1)
	{
		ITCHSOBJECTMAP it =engobjectmap.find(strObj); 
		if(it!=engobjectmap.end())
		{
			type=(ScpObjectType)it->second;
		}
		else
		{
			ITCHSOBJECTMAP it = chsobjectmap.find(strObj);
			if (it != chsobjectmap.end())
			{
				type = (ScpObjectType)it->second;
			}
		}
	}

	return type;
}
std::string ScpGlobalObject::GetTypeName(ScpObjectType type)
{
	std::string temp;
	if(language==0)
	{
		temp=FindKeyByValue(chsobjectmap,type,temp);
		if (temp.empty())
		{
			temp = FindKeyByValue(engobjectmap, type, temp);
		}
	}
	else if(language==1)
	{
		temp=FindKeyByValue(engobjectmap,type,temp);
		if (temp.empty())
		{
			temp = FindKeyByValue(chsobjectmap, type, temp);
		}
	}
	return temp;
}
void ScpGlobalObject::Show(CScriptEngine * engine)
{

}
void ScpGlobalObject::SelectLanguage(int lang)
{
	language=lang;

}