/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//基本对象的构建，参数检测和对象初始化
//调用扩展对象的工厂函数
*/
#include "ScpObjectDefine.h"
#include "NumberHelp.h"
#include "../Common/commonutil.hpp"
#include "../Common/DebugUtil.hpp"
#include "ScpExtendObjectMgr.h"
#include "ScpCommonObject.h"
#include "ScriptEngine.h"
#include "ScpFunctionObject.h"
#include "ScpCFunctionObject.h"
#include "ScpObjectNammes.h"

BOOL ScpObjectDefine(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	BOOL Ret = FALSE;
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() >= 2)
	{
		std::wstring strobj = vtparameters->at(0);
		std::wstring userobjname = vtparameters->at(1);

		ScpObject * obj = NULL;
		if (currentObjectSpace->ObjectSpaceType == Space_While)
		{
			obj = currentObjectSpace->FindLocalObject(userobjname);
			if (obj)
			{
				return TRUE;
			}
		}
		else if (currentObjectSpace->ObjectSpaceType == Space_Function)
		{
			obj = currentObjectSpace->FindLocalObject(userobjname);
			if (obj)
			{
				currentObjectSpace->EraseObject(userobjname);
			}
		}
		else
		{
			obj = currentObjectSpace->FindLocalObject(userobjname);
			if (obj)
			{
				return TRUE;
				//engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjExist);
			}
		}
		//else
		{
			std::wstring content;
			if (vtparameters->size() == 3)
				content = vtparameters->at(2);
			if (engine->extend_obj_mgr.IsExtendObject(strobj.c_str()))
			{
				ScpObject * obj = engine->extend_obj_mgr.CreateExtendObject(strobj.c_str(), vtparameters,engine);
				if (obj)
				{
					currentObjectSpace->AddObject(userobjname, obj);
					return TRUE;
				}
			}
			ScpGlobalObject::GetInstance()->SelectLanguage(engine->GetLanguge());
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
			
			if (ObjString == type)
			{
				ScpStringObject *strobj = (ScpStringObject*)ScpStringObjectFactory(vtparameters, engine);
				if (strobj)
				{
					currentObjectSpace->AddObject(userobjname, strobj);
				}
			}
			else if (ObjInt == type)
			{
				ScpIntObject *obj =(ScpIntObject *)ScpIntObjectFactory(vtparameters, engine);
				if (obj)
				{
					currentObjectSpace->AddObject(userobjname, obj);
				}
			}
			else if (ObjBigInt == type)
			{
				ScpBigIntObject * obj =(ScpBigIntObject*)ScpBigIntObjectFactory(vtparameters, engine);
				if (obj)
				{
					currentObjectSpace->AddObject(userobjname, obj);
				}
			}
			else if (ObjDouble == type)
			{
				ScpDoubleObject *obj = (ScpDoubleObject*)ScpDoubleObjectFactory(vtparameters, engine);
				if (obj)
				{
					currentObjectSpace->AddObject(userobjname, obj);
				}
				
			}
			else if (ObjTable == type)
			{
				ScpTableObject * tableobj =(ScpTableObject*)ScpTableObjectFactory(vtparameters, engine);
				if (tableobj)
					currentObjectSpace->AddObject(userobjname, tableobj);
			}
			else if (ObjList == type)
			{
				ScpListObject * listobj = (ScpListObject*)ScpListObjectFactory(vtparameters, engine);
				if(listobj)
					currentObjectSpace->AddObject(userobjname, listobj);
			}
			else if (ObjRange == type)
			{
				ScpRangeObject * range = (ScpRangeObject*)ScpRangeObjectFactory(vtparameters, engine);
				if (range)
				{
					currentObjectSpace->AddObject(userobjname, range);
				}
			}
			else if (ObjStack == type)
			{
				ScpStackObject * stackobj =( ScpStackObject*)ScpStackObjectFactory(vtparameters, engine);
				if (stackobj)
					currentObjectSpace->AddObject(userobjname, stackobj);
			}
			else if (ObjQueue == type)
			{
				ScpQueueObject * queueobj = (ScpQueueObject*)ScpQueueObjectFactory(vtparameters, engine);
				if(queueobj)
					currentObjectSpace->AddObject(userobjname, queueobj);
			}
			else if (ObjMap == type)
			{
				ScpMapObject * mapobj = (ScpMapObject*)ScpMapObjectFactory(vtparameters, engine);
				if (mapobj)
					currentObjectSpace->AddObject(userobjname, mapobj);
			}
			else if (ObjRegExp == type)
			{
				ScpRegExpObject * regexpobj =(ScpRegExpObject*)ScpRegExpObjectFactory(vtparameters, engine);
				if (regexpobj)
				{
					currentObjectSpace->AddObject(userobjname, regexpobj);
				}
			}
			else if (ObjTime == type)
			{
				ScpTimeObject *timeobj = (ScpTimeObject*)ScpTimeObjectFactory(vtparameters, engine);
				if (timeobj)
					currentObjectSpace->AddObject(userobjname, timeobj);
			}
			else if (ObjFunction == type)
			{
				//在函数的内部不允许定义函数
				if (Space_Function == currentObjectSpace->ObjectSpaceType)
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidFunctionDefine);
					return Ret;
				}
				ScpFunctionObject * funcobj = new ScpFunctionObject;
				if (funcobj)
				{
					funcobj->Name = userobjname;
					for (ULONG i = 2;i < vtparameters->size();i++)
					{
						std::wstring & wparam = vtparameters->at(i);
						funcobj->FormalParameters.push_back(wparam);
					}
					funcobj->FunctionObjectSpace->spacename = ScpGlobalObject::GetInstance()->GetTypeName(ObjFunction) + userobjname;
					currentObjectSpace->AddObject(userobjname, funcobj);
					funcobj->FunctionObjectSpace->parentspace = currentObjectSpace;
					engine->SetCurrentObjectSpace(funcobj->FunctionObjectSpace);
				}

			}
			else if (ObjCFunction == type)
			{

				if (vtparameters->size() >= 5)
				{
					std::wstring strdll = vtparameters->at(2);
					ScpStringObject * objdll = (ScpStringObject*)currentObjectSpace->FindObject(strdll);
					if (objdll)
					{
						if (objdll->GetType() == ObjString)
						{
							strdll = ((ScpStringObject *)objdll)->content;
						}
					}
					std::wstring strcfunction = vtparameters->at(3);
					ScpStringObject * objfunction = (ScpStringObject*)currentObjectSpace->FindObject(strcfunction);
					if (objfunction)
					{
						if (objfunction->GetType() == ObjString)
						{
							strcfunction = ((ScpStringObject *)objfunction)->content;
						}
					}
					std::wstring returntype = vtparameters->at(4);
					ScpCFunctionObject * funcobj = new ScpCFunctionObject;
					VTPARAMETERS Parameters;
					for (ULONG i = 5;i<vtparameters->size();i++)
					{
						std::wstring wparam = vtparameters->at(i);
						Parameters.push_back(wparam);
					}
					funcobj->MakeCFunctionInterface(userobjname, strdll, strcfunction, returntype, Parameters);

					currentObjectSpace->AddObject(userobjname, funcobj);
				}
			}
			else if (ObjCInt32 == type)
			{
				ScpObjCInt32 *obj = new ScpObjCInt32;
				ScpIntObject * intobj = (ScpIntObject *)currentObjectSpace->FindObject(content);
				if (intobj)
				{
					if (obj->GetType() == ObjInt)
					{
						obj->Value = intobj->value;
					}
				}
				else
				{
					if (IsStaticNumber(content))
					{
						obj->Value = StringToInt(content);
					}
					else
					{
						obj->Value = 0;
						if(!content.empty())
							engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjectInitializeFault);
					}
				}
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjHandle == type)
			{
				ScpObjHandle *obj = new ScpObjHandle;
#ifdef Linux64
				obj->Value = (HANDLE)StringToInt64(content);
#else
				obj->Value = (HANDLE)StringToInt(content);
#endif
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjPointerofChar == type)
			{
				ScpObjPointerofChar *obj = new ScpObjPointerofChar;
				ScpStringObject *strobj = (ScpStringObject *)currentObjectSpace->FindObject(content);
				obj->Value = (char *)strobj->content.c_str();
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjPointerofWchar == type)
			{
				ScpObjPointerofWchar *obj = new ScpObjPointerofWchar;
				ScpStringObject *strobj = (ScpStringObject *)currentObjectSpace->FindObject(content);
				if (strobj)
					if (strobj->GetType() == ObjString)
						obj->Value = (wchar_t *)strobj->content.c_str();

				ScpMemoryObject *memobj = (ScpMemoryObject *)currentObjectSpace->FindObject(content);
				if (memobj)
					if (memobj->GetType() == ObjMemory)
					{
						obj->Value = (wchar_t *)memobj->Address;
					}
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjUnsignedInt32 == type)
			{
				ScpObjUnsignedInt32 *obj = new ScpObjUnsignedInt32;
				if (IsStaticNumber(content))
				{
					obj->Value = (unsigned int)StringToInt(content);
				}
				else
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjectInitializeFault);
				}
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjPointer == type)
			{
				ScpObjPointer *obj = new ScpObjPointer;
#ifdef Linux64
				obj->Value = (void *)StringToInt64(content);
#else
				obj->Value = (void *)StringToInt(content);
#endif
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjCChar == type)
			{
				ScpObjCChar * obj = new ScpObjCChar;
				obj->Value = (unsigned char)STDSTRINGEXT::WToA(content).at(0);
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjCUnsignedChar == type)
			{
				ScpObjCUnsignedChar * obj = new ScpObjCUnsignedChar;
				obj->Value = STDSTRINGEXT::WToA(content).at(0);
				currentObjectSpace->AddObject(userobjname, obj);
			}
			else if (ObjCShort == type)
			{
				ScpObjCShort * obj = new ScpObjCShort;
				ScpIntObject * intobj = (ScpIntObject *)currentObjectSpace->FindObject(content);
				if (intobj)
				{
					if (obj->GetType() == ObjInt)
					{
						obj->Value = (short)intobj->value;
					}
				}
				else
				{
					if (IsStaticNumber(content))
					{
						obj->Value = (short)StringToInt(content);
					}
					else
					{
						engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjectInitializeFault);
					}
				}
				currentObjectSpace->AddObject(userobjname, obj);

			}
			else if (ObjCUnsignedShort == type)
			{
				ScpObjCUnsignedShort * obj = new ScpObjCUnsignedShort;
				ScpIntObject * intobj = (ScpIntObject *)currentObjectSpace->FindObject(content);
				if (intobj)
				{
					if (obj->GetType() == ObjInt)
					{
						obj->Value = (unsigned short)intobj->value;
					}
				}
				else
				{
					if (IsStaticNumber(content))
					{
						obj->Value = (unsigned short)StringToInt(content);
					}
					else
					{
						engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjectInitializeFault);
					}
				}
				currentObjectSpace->AddObject(userobjname, obj);


			}
			else if (ObjCLong == type)
			{

				ScpObjCLong * obj = new ScpObjCLong;
				ScpIntObject * intobj = (ScpIntObject *)currentObjectSpace->FindObject(content);
				if (intobj)
				{
					if (obj->GetType() == ObjInt)
					{
						obj->Value = (long)intobj->value;
					}
				}
				else
				{
					if (IsStaticNumber(content))
					{
						obj->Value = (long)StringToInt(content);
					}
					else
					{
						engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjectInitializeFault);
					}
				}
				currentObjectSpace->AddObject(userobjname, obj);

			}
			else if (ObjCUnsignedLong == type)
			{

				ScpObjCUnsignedLong * obj = new ScpObjCUnsignedLong;
				ScpIntObject * intobj = (ScpIntObject *)currentObjectSpace->FindObject(content);
				if (intobj)
				{
					if (obj->GetType() == ObjInt)
					{
						obj->Value = (unsigned long)intobj->value;
					}
				}
				else
				{
					if (IsStaticNumber(content))
					{
						obj->Value = (unsigned long)StringToInt(content);
					}
					else
					{
						engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjectInitializeFault);
					}
				}
				currentObjectSpace->AddObject(userobjname, obj);
			}			
			else if (ObjClass == type)
			{
				//在类的内部和函数的内部不允许定义类
				if (Space_Global != currentObjectSpace->ObjectSpaceType)
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorNestClassDefine);
					return Ret;
				}
				if (vtparameters->size() == 2)
				{
					ScpClassObject *classobj = new ScpClassObject;
					if (classobj)
					{
						classobj->ClassDefine(userobjname);
						currentObjectSpace->AddObject(userobjname, classobj);
						classobj->UserClassObjectSpace.parentspace = engine->GetCurrentObjectSpace();
						engine->SetCurrentObjectSpace(&classobj->UserClassObjectSpace);
					}					
				}
			}
			else if (ObjStruct == type)
			{
				if (vtparameters->size() == 2)
				{
					ScpStructObject * structobj = new ScpStructObject;
					if (structobj)
					{
						structobj->Name = (userobjname);
						currentObjectSpace->AddObject(userobjname, structobj);
						structobj->StructObjectSpace.parentspace = engine->GetCurrentObjectSpace();
						engine->SetCurrentObjectSpace(&structobj->StructObjectSpace);
					}
				}
			}
			else if (ObjArray == type)
			{
				ScpArrayObject * obj =(ScpArrayObject *) ScpArrayObjectFactory(vtparameters, engine);
				if (obj)
				{
					currentObjectSpace->AddObject(obj->arrayname, obj);
				}
			}
			else if (ObjJson == type)
			{
				if (vtparameters->size() == 2)
				{
					std::wstring jsonname = vtparameters->at(1);
					ScpObject * obj = currentObjectSpace->FindObject(jsonname);
					if (obj)
					{
						if (obj->GetType() == ObjString)
						{
							jsonname = ((ScpStringObject *)obj)->content;
						}
					}
					ScpJsonObject * jsonobj = (ScpJsonObject*)ScpJsonObjectFactory(vtparameters, engine);
					if (jsonobj)
					{
						currentObjectSpace->AddObject(jsonname, jsonobj);
					}					
				}
			}
			else if (ObjFile == type)
			{
				ScpFileObject* fileobj = (ScpFileObject*)ScpFileObjectFactory(vtparameters, engine);
				if (fileobj)
				{
					currentObjectSpace->AddObject(userobjname, fileobj);
				}
			}
			else if (ObjDirectory == type)
			{
				ScpDirectoryObject *dirobj = (ScpDirectoryObject*)ScpDirectoryObjectFactory(vtparameters, engine);
				if (dirobj)
				{
					currentObjectSpace->AddObject(userobjname, dirobj);
				}
			}
			else if (ObjMemory == type)
			{
				ScpMemoryObject * mem =(ScpMemoryObject*)ScpMemoryObjectFactory(vtparameters, engine);;
				if (mem)
				{
					currentObjectSpace->AddObject(userobjname, mem);
				}
			}
			else if (ObjRandomNumber == type)
			{
				ScpRandomNumberObject * obj = (ScpRandomNumberObject*)ScpRandomNumberObjectFactory(vtparameters, engine);;
				if (obj)
				{
					currentObjectSpace->AddObject(userobjname, obj);
				}
			}
			else
			{
				//看看是否是定义类的实例
				ScpObject * obj = currentObjectSpace->FindObject(strobj);
				if (obj)
				{
					if (obj->GetType() == ObjClass)
					{
						if (vtparameters->size() == 2)
						{
							ScpClassInstanceObject *classobj = new ScpClassInstanceObject;
							if(classobj)
							{
								//类成员变量需要进行深拷贝，类成员函数仅拷贝函数地址
								classobj->UserClassObjectSpace.userobject.DeepCopy(&((ScpClassObject *)obj)->UserClassObjectSpace.userobject);
								//classobj->UserClassObjectSpace = ((ScpClassObject *)obj)->UserClassObjectSpace;		
								/*for (int i = 0;i < classobj->UserClassObjectSpace.userobject.GetSize();i++)
								{
									ScpObject * obj =classobj->UserClassObjectSpace.userobject.GetObject(i);
									if (obj)
									{
										obj->AddRef();
									}
								}*/
								//拷贝类成员的属性
								classobj->memberattrmap = ((ScpClassObject *)obj)->memberattrmap;
								//重新修改当前类实例的名字空间的属主
								classobj->UserClassObjectSpace.belongto = classobj;
								//
								classobj->ClassBody = ((ScpClassObject *)obj)->ClassBody;
								classobj->ClassDefine(userobjname);
								classobj->objecttype = ObjClassInstance;
								classobj->classname = strobj;
								classobj->instanceOf = (ScpClassObject *)obj;
								currentObjectSpace->AddObject(userobjname, classobj);
							}
						}
					}
					else if (obj->GetType() == ObjStruct)
					{
						if (vtparameters->size() == 2)
						{
							ScpStructInstanceObject * structobj = new ScpStructInstanceObject;
							if (structobj)
							{
								*structobj = *(ScpStructInstanceObject*)obj;
								structobj->Name = userobjname;
								structobj->AllocStructMemory();
								currentObjectSpace->AddObject(userobjname, structobj);
							}
						}
					}
				}
				else if (ObjUnknown == type)
				{
					std::wstring Message = STDSTRINGEXT::Format(L" at line(%d)", engine->GetCurrentCommandLine());
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidObjectDefine + Message);
				}
			}
		}
	}
	else
	{
		std::wstring Message = STDSTRINGEXT::Format(L" at line(%d)", engine->GetCurrentCommandLine());
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidObjectDefine+ Message);
	}
	return TRUE;
}
