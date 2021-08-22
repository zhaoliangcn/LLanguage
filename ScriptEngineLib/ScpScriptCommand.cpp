/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//������
//L�ű����Ե�һ�д������ȱ������������ú����ĵ��ã������ܽ���δ�ڲ��������ã��ٳ�����Ϊ������ʽ���н���
*/
#include "ScpScriptCommand.h"
#include "NumberHelp.h"
#include "../Common/commonutil.hpp"
#include "../Common/DebugUtil.hpp"
#include "ScpExtendObjectMgr.h"
#include "ScpCommonObject.h"
#include "ScpObjectDefine.h"
#include "ScriptEngine.h"
#include "ScpFunctionObject.h"
#include "ScpIfStatementObject.h"
#include "ScpWhileStatementObject.h"
#include "ScpCFunctionObject.h"
#include "ScpObjectNammes.h"
#include "commanddefine_uni.h"
CScriptCommand::CScriptCommand()
{
}
CScriptCommand::~CScriptCommand()
{
}

/*
�����롱����
�������󣺽ű����ļ�
*/
BOOL CScriptCommand::Do_Import_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::wstring &strobj = vtparameters->at(0);
		std::wstring libname = vtparameters->at(1);
		StringStripQuote(strobj);
		StringStripQuote(libname);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjLib == type)
		{
			ScpStringObject * strobj = (ScpStringObject*)currentObjectSpace->FindObject(libname);
			if (strobj)
			{
				libname = strobj->content;
				StringStripQuote(libname);
			}			
			if (0 != engine->ImportLib(libname))
			{
				engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorImportLibFailure);
				exit(0);
			}
		}
//		else if (ScpObjectNames::GetSingleInsatnce()->strObjPackage == strobj)
//		{
//			std::wstring packagename = vtparameters->at(1);
//			if (ScpFileObject::FileExist(packagename))
//			{
//#ifdef WIN32
//				VTUnzipedMemory unz;
//				CZipWrapper Zip;
//				Zip.UnZipToMem(packagename.c_str(), unz);
//				for (unsigned int i = 0;i < unz.size();i++)
//				{
//					UNZIPED_MEMORY * puzm = unz.at(i);
//					if (puzm)
//					{
//						if (0 != engine->ImportLibFromMemory(puzm->MemBuffer))
//						{
//							break;
//						}
//						Zip.FreeUnzipedMemory(puzm);
//					}
//				}
//#endif	
//			}
//		}
	}
	else
	{
		std::wstring libname = vtparameters->at(0);
		StringStripQuote(libname);
		ScpStringObject * strobj = (ScpStringObject*)currentObjectSpace->FindObject(libname);
		if (strobj)
		{
			libname = strobj->content;
			StringStripQuote(libname);
		}
		if (ScpFileObject::FileExist(libname))
		{
			if (STDSTRINGEXT::ToLowerW(ScpFileObject::GetFileExt(libname)) == L".scp")
			{
				if (0 != engine->ImportLib(libname))
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorImportLibFailure);
					exit(0);
				}

			}
			/*else if (STDSTRINGEXT::ToLowerW(ScpFileObject::GetFileExt(libname)) == L".zip")
			{
				std::wstring packagename = libname;
				if (ScpFileObject::FileExist(packagename))
				{
#ifdef WIN32
					VTUnzipedMemory unz;
					CZipWrapper Zip;
					Zip.UnZipToMem(packagename.c_str(), unz);
					for (unsigned int i = 0;i < unz.size();i++)
					{
						UNZIPED_MEMORY * puzm = unz.at(i);
						if (puzm)
						{
							if (0 != engine->ImportLibFromMemory(puzm->MemBuffer))
							{
								break;
							}
							Zip.FreeUnzipedMemory(puzm);
						}
					}
#endif
				}

			}*/
		}
	}
	return TRUE;
}
/*
��ִ�С�����
�������󣺽ű��ַ������ⲿ�ű��ļ���SQL���
*/
BOOL CScriptCommand::Do_Do_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 1)
	{
		std::wstring strobj = vtparameters->at(0);
		StringStripQuote(strobj);
		ScpStringObject *obj = (ScpStringObject*)currentObjectSpace->FindObject(strobj);
		if (obj && obj->GetType() == ObjString)
		{
			engine->DoString(obj->content);
		}
		else
		{
			if (ScpFileObject::FileExist(strobj))
			{
				CScriptEngine engine;
				engine.DoScript(strobj.c_str());
			}
			else
			{
				engine->SetLastErrorString(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidParameter);
			}
		}
	}
	else if (vtparameters->size() == 2)
	{
		std::wstring strobj = vtparameters->at(0);
		std::wstring pathname = vtparameters->at(1);
		StringStripQuote(strobj);
		StringStripQuote(pathname);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjScript == type)
		{
			ScpObject *obj = currentObjectSpace->FindObject(pathname);
			if (obj)
			{
				if (obj->GetType() == ObjString)
				{
					if (ScpFileObject::FileExist(pathname))
					{
						pathname = ((ScpStringObject*)obj)->content;
						StringStripQuote(pathname);
					}
					else
					{
						CScriptEngine engine;
						engine.DebugMemoryScript(((ScpStringObject*)obj)->content.c_str());
						
					}
				}					
				else if (obj->GetType() == ObjFile)
					pathname = ((ScpFileObject*)obj)->filename;
			}
			CScriptEngine engine;
			engine.DoScript(pathname.c_str());
		}
	}
	else
	{
		engine->SetLastErrorString(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidParameter);
	}
	return TRUE;
}
BOOL CScriptCommand::Do_Return_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	ScpObjectSpace * FuncObjectSpace = NULL;
	//��ǰ���ֿռ��п����Ǻ����ڲ�������������ѭ�����
	//�����ҵ����ڲ�ĺ������õ����ֿռ�
	if (currentObjectSpace->ObjectSpaceType != Space_Function)
	{
		if (currentObjectSpace->ObjectSpaceType == Space_While)
		{
			currentObjectSpace->breakingout = 1;
		}
		ScpObjectSpace * parentObjectSpace = currentObjectSpace->parentspace;
		while (parentObjectSpace && parentObjectSpace->ObjectSpaceType != Space_Global)
		{
			if (parentObjectSpace->ObjectSpaceType == Space_Function)
			{
				break;
			}
			if (parentObjectSpace->ObjectSpaceType == Space_While)
			{
				parentObjectSpace->breakingout = 1;
			}
			parentObjectSpace = parentObjectSpace->parentspace;
		}
		if (parentObjectSpace != NULL && parentObjectSpace->ObjectSpaceType == Space_Function)
			FuncObjectSpace = parentObjectSpace;
		else
			FuncObjectSpace = currentObjectSpace;

	}
	else
	{
		FuncObjectSpace = currentObjectSpace;
	}

	if (FuncObjectSpace->ObjectSpaceType == Space_Function)
	{
		if (vtparameters->size() == 1)
		{
			std::wstring expression = vtparameters->at(0);
			//ScpStringObject *strobjexpression = (ScpStringObject *)currentObjectSpace->FindObject(expression);
			//if (strobjexpression)
			//{
			//	if (strobjexpression->GetType() == ObjString)
			//	{
			//		expression = strobjexpression->content;
			//	}
			//}
			//if (expression.at(0) != L'(' && expression.at(expression.length() - 1) != L')')
			//{
			//	expression = L"(" + expression + L")";
			//}
			ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(expression);
			if (root)
			{
				ScpObject * retobj = root->CalculateEx(engine);
				if (retobj)
				{
					ScpFunctionObject * functionobj = (ScpFunctionObject *)FuncObjectSpace->belongto;
					retobj->AddRef();					
					functionobj->Result = retobj;
					DebugUtil::TraceW(L"Return From %s %s objtype %s ", functionobj->Name.c_str(), expression.c_str(), ScpGlobalObject::GetInstance()->GetTypeName(retobj->GetType()).c_str());

				}
				root->Destroy(engine->GetCurrentObjectSpace());
				engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
			}
		}
	}
	FuncObjectSpace->lastcommand = vl_return;
	currentObjectSpace->lastcommand = vl_return;
	return FALSE;
}

BOOL CScriptCommand::Do_Loop_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	BOOL bRet = FALSE;
	ScpObjectSpace * currentObjectSpace = engine->currentObjectSpace;
	if (vtparameters->size() >= 2)
	{
		int loopcount = 0;
		std::wstring elementname = vtparameters->at(0);
		std::wstring functionname = vtparameters->at(1);
		StringStripQuote(elementname);
		StringStripQuote(functionname);
		if (IsStaticNumber(elementname))
		{
			loopcount = StringToInt(elementname);
		}
		else
		{
			ScpObject * obj1 = currentObjectSpace->FindObject(elementname);
			if (obj1)
			{
				if (obj1->GetType() == ObjInt)
				{
					loopcount = ((ScpIntObject*)obj1)->value;
				}
			}
		}
		ScpObject * obj2 = currentObjectSpace->FindObject(functionname);
		if (obj2)
		{
			if (obj2->GetType() == ObjFunction)
			{

				VTPARAMETERS vtFuncparameters;
				for (ULONG i = 1;i < vtparameters->size();i++)
				{
					vtFuncparameters.push_back(vtparameters->at(i));
				}
				while (loopcount > 0)
				{
					engine->scriptcommand->Do_Call_Command(&vtFuncparameters, engine);
					loopcount -= 1;
				}
			}
		}
		else
		{
			std::wstring command;
			for (ULONG i = 1;i < vtparameters->size();i++)
			{
				command += vtparameters->at(i);
				command += L",";
			}
			command = command.substr(0, command.length() - 1);
			while (loopcount > 0)
			{
				engine->DoString(command);
				loopcount -= 1;
			}
		}
	}
	return bRet;

}
BOOL CScriptCommand::Do_Public_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpClassObject * classobj = (ScpClassObject *)engine->GetCurrentObjectSpace()->belongto;
	if (classobj)
	{
		classobj->MemberVariableAttribute = ScpClassObject::Attr_Public;
	}
	return TRUE;
}
BOOL CScriptCommand::Do_Private_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpClassObject * classobj = (ScpClassObject *)engine->GetCurrentObjectSpace()->belongto;
	if (classobj)
	{
		classobj->MemberVariableAttribute = ScpClassObject::Attr_Private;
	}
	return TRUE;
}
/*
������������
��������ѭ����价����
�ҵ�������ǰ�������һ��ѭ�����������ѭ���ĵ�һ����俪ʼִ��
*/
BOOL CScriptCommand::Do_Continue_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->currentObjectSpace;
	while (currentObjectSpace != NULL)
	{
		if (currentObjectSpace->ObjectSpaceType == Space_Function)
		{
			break;
		}
		if (currentObjectSpace->ObjectSpaceType == Space_While)
		{
			currentObjectSpace->continuewhile = 1;
			break;
		}
		currentObjectSpace = currentObjectSpace->parentspace;
	}
	return TRUE;
}
/*
������������
��������ѭ����价����
�ҵ�������ǰ�������һ��ѭ�����������ѭ������ѭ����ĵ�һ�����ִ��
*/
BOOL CScriptCommand::Do_Break_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->currentObjectSpace;
	while (currentObjectSpace != NULL)
	{
		if (currentObjectSpace->ObjectSpaceType == Space_Function)
		{
			break;
		}
		if (currentObjectSpace->ObjectSpaceType == Space_While)
		{
			currentObjectSpace->breakingout = 1;
			break;
		}
		currentObjectSpace = currentObjectSpace->parentspace;
	}
	return TRUE;
}

/*
�����ء�����
��������
*/
BOOL CScriptCommand::Do_Load_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpGlobalObject::GetInstance()->SelectLanguage(engine->GetLanguge());
	ScpObjectNames::GetSingleInsatnce()->SelectLanguage(engine->GetLanguge());
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::wstring strobj = vtparameters->at(0);
		std::wstring content = vtparameters->at(1);
		StringStripQuote(strobj);
		StringStripQuote(content);
		ScpObject * obj = currentObjectSpace->FindObject(strobj);
		ScpObject * userobj = currentObjectSpace->FindObject(content);
		if (userobj)
		{
			if (userobj->GetType() == ObjString)
			{
				content = ((ScpStringObject*)userobj)->content;
				StringStripQuote(content);
			}
		}
		
		if (obj)
		{
			if (obj->GetType() == ObjJson)
			{
				((ScpJsonObject *)obj)->Load(content);
			}
		}
		else
		{
			if (strobj == ScpObjectNames::GetSingleInsatnce()->strObjDll)
			{
#ifdef WIN32
				LoadLibraryW(content.c_str());
#else
				dlopen(STDSTRINGEXT::W2UTF(content).c_str(), RTLD_NOW);
#endif
			}
#ifdef WIN32
			else if (_wcsicmp(strobj.c_str(), ScpObjectNames::GetSingleInsatnce()->strObjExtObj.c_str()) == 0)
#else 

            else if (wcscasecmp(strobj.c_str(),ScpObjectNames::GetSingleInsatnce()->strObjExtObj.c_str()) == 0)
#endif
			{

				engine->extend_obj_mgr.LoadExtension(content.c_str(), &engine->globalcommand);

			}
			else
			{
				std::wstring Message = STDSTRINGEXT::Format(L" at line(%d)", engine->GetCurrentCommandLine());
				engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidLoadCommand + Message);
			}
		}
	}
	else
	{
		std::wstring Message = STDSTRINGEXT::Format(L" at line(%d)", engine->GetCurrentCommandLine());
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidParameter + Message);

	}
	return TRUE;
}
/*
���̳С�����
����������
���๲����ĳ�Ա���󣬳�Ա��������Ա��˽�л򹫿�����
�������¶���ĳ�Ա��Ҫ����ָ��˽�л򹫿����� 
*/
BOOL CScriptCommand::Do_Inherit_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	BOOL ret = FALSE;
	if (Space_Class == currentObjectSpace->ObjectSpaceType)
	{
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorNestClassDefine);
		return ret;
	}
	if (vtparameters->size() == 3)
	{
		std::wstring &objtype = vtparameters->at(0);
		std::wstring &userobjname = vtparameters->at(1);
		std::wstring &userobjname2 = vtparameters->at(2);
		StringStripQuote(objtype);
		StringStripQuote(userobjname);
		StringStripQuote(userobjname2);
		ScpObject * obj = currentObjectSpace->FindObject(userobjname2);
		if (obj)
		{
			engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorObjExist);
		}
		else
		{
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(objtype.c_str());
			if (ObjClass == type)
			{
				ScpObject * obj = (ScpObject *)currentObjectSpace->FindObject(userobjname);
				if (obj)
				{
					if (obj->GetType() == ObjClass)
					{
						ScpClassObject *classobj = new ScpClassObject;
						*classobj = *(ScpClassObject*)obj;
						classobj->ClassDefine(userobjname2);
						currentObjectSpace->AddObject(userobjname2, classobj);
						classobj->UserClassObjectSpace.parentspace = engine->GetCurrentObjectSpace();
						//����UserClassObjectSpace������ָ��
						classobj->UserClassObjectSpace.belongto = classobj;
						engine->SetCurrentObjectSpace(&classobj->UserClassObjectSpace);
						ret = TRUE;
					}
				}
			}
			else
			{
				engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidClassDefine);
			}
		}
	}
	else
	{
		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidClassDefine);		
	}
	return ret;
}


/*
��ע�ᡱ����
�������󣺺��������û����庯������ȫ�ֺ���
*/
BOOL CScriptCommand::Do_Register_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::wstring strobj = vtparameters->at(0);
		std::wstring name1 = vtparameters->at(1);
		StringStripQuote(strobj);
		StringStripQuote(name1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjFunction == type)
		{
			ScpFunctionObject * funcobj = (ScpFunctionObject*)currentObjectSpace->FindObject(name1);
			if (funcobj)
			{
				if (funcobj->GetType() == ObjFunction)
				{
					engine->globalcommand.RegisterCommand(engine->language, name1, engine->vl_usercommand);
					engine->vl_usercommand++;
				}
			}
		}
	}
	if (vtparameters->size() == 3)
	{
		std::wstring strobj = vtparameters->at(0);
		std::wstring name1 = vtparameters->at(1);
		std::wstring strcommandvalue = vtparameters->at(2);
		StringStripQuote(strobj);
		StringStripQuote(name1);
		StringStripQuote(strcommandvalue);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjFunction == type)
		{
			ScpFunctionObject * funcobj = (ScpFunctionObject*)currentObjectSpace->FindObject(name1);
			if (funcobj)
			{
				if (funcobj->GetType() == ObjFunction)
					engine->globalcommand.RegisterCommand(engine->language, name1, StringToInt(strcommandvalue.c_str()));
			}
		}
	}
	return TRUE;
}

/*
����������
��������ѭ�������󣬹���ѭ�����������
*/
BOOL CScriptCommand::Do_While_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 1)
	{
		std::wstring expression = vtparameters->at(0);
		StringStripQuote(expression);
		ScpWhileStatementObject * whileobj = new ScpWhileStatementObject(engine);
		if (whileobj)
		{
			std::wstring userobjname = ScpObjectNames::GetSingleInsatnce()->strObjWhileStatement + expression;
			ScpWhileStatementObject * temp = (ScpWhileStatementObject *)currentObjectSpace->FindObject(userobjname);
			while (temp)
			{
				userobjname += L"@";
				temp = (ScpWhileStatementObject *)currentObjectSpace->FindObject(userobjname);
			}
			whileobj->Name = userobjname;
			whileobj->WhileStatementObjectSpace.spacename = userobjname;
			whileobj->SetCondition(expression);
			currentObjectSpace->AddObject(userobjname, whileobj);
			whileobj->WhileStatementObjectSpace.parentspace = currentObjectSpace;
			engine->SetCurrentObjectSpace(&whileobj->WhileStatementObjectSpace);
		}

	}
	else if (vtparameters->size() >= 2)
	{
		ScpIntObject ret;
		std::wstring command;
		for (ULONG i = 1;i < vtparameters->size();i++)
		{
			command += vtparameters->at(i);
			command += L",";
		}
		command = command.substr(0, command.length() - 1);
		std::wstring expression = vtparameters->at(0);
		ScpStringObject *strobj2 = (ScpStringObject *)currentObjectSpace->FindObject(expression);
		if (strobj2)
		{
			expression = strobj2->content;
		}
		BOOL bRet = FALSE;
		do
		{
			ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(expression);
			if (root)
			{
				ScpObject * retobj = root->CalculateEx(engine);
				if (retobj)
				{
					ret = *(ScpIntObject*)retobj;
				}
				if (ret.value == 1)
				{
					bRet = TRUE;
					engine->DoString(command);
				}
				else
				{
					bRet = FALSE;
				}
				root->Destroy(engine->GetCurrentObjectSpace());
				engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
			}
			
		} while (bRet);
	}
	return TRUE;
}
/*
�����塱����
�����������ж���������ͳ�ʼ��
*/
BOOL CScriptCommand::Do_Define_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	return ScpObjectDefine(vtparameters, engine);
}

/*
�����㡱����
�������󣺱��ʽ
*/
BOOL CScriptCommand::Do_Compute_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{	
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();	
	if (vtparameters->size() == 3)
	{
		std::wstring &expobj = vtparameters->at(0);
		std::wstring &expname = vtparameters->at(1);
		std::wstring exp = vtparameters->at(2);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(expobj.c_str());
		if (ObjExpression == type)
		{
			ScpStringObject *strobj2 = (ScpStringObject *)currentObjectSpace->FindObject(exp);

			if (strobj2)
			{
				exp = strobj2->content;
			}			
			DebugUtil::TraceW(L"Compute Enter expression %s", exp.c_str());
			ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(exp);
			if (root)
			{
				ScpObject * retobj = root->CalculateEx(engine);
				if (retobj)
				{
					ScpObject * objret = currentObjectSpace->FindLocalObject(expname);
					if (objret)
					{
						currentObjectSpace->EraseObject(expname);
					}
					currentObjectSpace->AddObject(expname, retobj);
				}
				root->Destroy(currentObjectSpace);
				engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
			}			
		}
		else
		{			
			for (unsigned int i = 0;i < vtparameters->size();i++)
			{
				std::wstring expression = vtparameters->at(i);
				ScpStringObject *strobj1 = (ScpStringObject *)currentObjectSpace->FindObject(expression);
				if (strobj1)
				{
					expression = strobj1->content;
				}
				DebugUtil::TraceW(L"Compute Enter expression %s", expression.c_str());
				ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(expression);
				if (root)
				{
					ScpObject * retobj = root->CalculateEx(engine);
					if (retobj)
					{
						//delete retobj;
						if (retobj->istemp)
						{
							currentObjectSpace->ReleaseTempObject(retobj);
						}
					}
					root->Destroy(currentObjectSpace);
					engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
				}
			}			
		}
	}
	else
	{		
		for (unsigned int i = 0;i < vtparameters->size();i++)
		{
			std::wstring expression = vtparameters->at(i);
			ScpStringObject *strobj1 = (ScpStringObject *)currentObjectSpace->FindObject(expression);
			if (strobj1)
			{
				expression = strobj1->content;
			}
			//DebugUtil::TraceW(L"Compute Enter expression %s", expression.c_str());
			ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(expression);
			if (root)
			{
				ScpObject * retobj = root->CalculateEx(engine);
				if (retobj)
				{
					//delete retobj;
					if (retobj->istemp)
					{
						currentObjectSpace->ReleaseTempObject(retobj);
					}
				}
				root->Destroy(currentObjectSpace);
				engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
			}
		}		
	}
	return TRUE;
}
/*
�����á�����
�������󣺺�����C���Ժ������̺߳����塢python������ʵ���ĳ�Ա����
*/
BOOL CScriptCommand::Do_Call_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() < 1)
	{
		return FALSE;
	}
	std::wstring objname = vtparameters->at(0);
	std::wstring name;
	if (vtparameters->size() >= 2)
		name = vtparameters->at(1);
	ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(objname.c_str());
	if (ObjFunction == type)
	{
		BOOL Clone = FALSE;
		ScpFunctionObject* func = (ScpFunctionObject*)currentObjectSpace->FindObject(name);
		if (func)
		{
			if (currentObjectSpace->IsMyParentSpace(func->FunctionObjectSpace) || currentObjectSpace == func->FunctionObjectSpace)
			{
				//˵���ǵݹ�ĺ�������			
				Clone = TRUE;
			}
		}
		ScpObjectSpace * OldObjectSpace = NULL;
		VTPARAMETERS OldRealParameters;
		std::wstring OldName;
		if (func)
		{
			if (func->GetType() == ObjFunction)
			{
				if (Clone)
				{
					OldObjectSpace = func->FunctionObjectSpace;
					OldName = func->Name;
					func->FunctionObjectSpace = new ScpObjectSpace;
					func->FunctionObjectSpace->belongto = func;
					if (currentObjectSpace == OldObjectSpace)
					{
						func->FunctionObjectSpace->parentspace = currentObjectSpace;
					}
					else
					{
						func->FunctionObjectSpace->parentspace = currentObjectSpace;
						//func->FunctionObjectSpace->parentspace=OldObjectSpace->parentspace;
					}
					func->FunctionObjectSpace->ObjectSpaceType = Space_Function;
					OldRealParameters = func->RealParameters;
					func->RealParameters.clear();
					func->Name = func->GetCloneName();
				}
				if (func->RealParameters.size() == 0)
				{
					for (ULONG i = 2;i < vtparameters->size();i++)
					{
						ScpObject * obj = currentObjectSpace->FindObject(vtparameters->at(i));
						if (obj)
						{
							func->RealParameters.push_back(vtparameters->at(i));
						}
						else
						{
							func->RealParameters.push_back(vtparameters->at(i));
							//engine->PrintError(scpErrorInvalidFunctionParameter);
						}
					}
				}

				func->Do(engine);
			}
			if (Clone)
			{
				ScpObjectSpace * tempObjectSpace = func->FunctionObjectSpace;
				func->FunctionObjectSpace = OldObjectSpace;
				delete tempObjectSpace;
				func->RealParameters = OldRealParameters;
				func->Name = OldName;
				//currentObjectSpace->EraseObject(clonename);
			}
		}
	}
	else if (ObjCFunction == type)
	{
		ScpCFunctionObject* func;
		func = (ScpCFunctionObject*)currentObjectSpace->FindObject(name);
		if (func)
		{
			if (func->GetType() == ObjCFunction)
			{
				std::wstring retvalue = vtparameters->at(2);
				VTPARAMETERS Parameters;
				for (ULONG i = 3;i < vtparameters->size();i++)
				{
					std::wstring wparam = vtparameters->at(i);
					Parameters.push_back(wparam);
				}
				func->Call(retvalue, Parameters, currentObjectSpace);
			}
		}
	}
	else
	{
		size_t pos = objname.find(L":");
		if (pos == std::wstring::npos)
		{
			pos = objname.find(L".");
		}
		if (pos != std::wstring::npos)
		{
			std::wstring classname = objname.substr(0, pos);
			std::wstring functionname = objname.substr(pos + 1, objname.length() - pos - 1);
			ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(functionname.c_str());
			if (ObjFunction == type)
			{
				ScpClassInstanceObject *classobj = (ScpClassInstanceObject*)currentObjectSpace->FindObject(classname);
				if (classobj)
				{
					if (classobj->GetType() == ObjClassInstance)
					{
						ScpFunctionObject* func;
						func = (ScpFunctionObject*)classobj->UserClassObjectSpace.FindObject(name);
						if (func)
						{
							if (func->GetType() == ObjFunction)
							{

								VTPARAMETERS TempVtparameters;
								BOOL recurse = FALSE;
								if (currentObjectSpace->IsMyParentSpace(&classobj->UserClassObjectSpace))
								{
									recurse = TRUE;
								}
								if (!recurse)
								{
									classobj->UserClassObjectSpace.parentspace = currentObjectSpace;
									engine->SetCurrentObjectSpace(&classobj->UserClassObjectSpace);
								}
								else
								{
									TempVtparameters = func->RealParameters;
									func->RealParameters.clear();

								}
								for (ULONG i = 2; i < vtparameters->size(); i++)
								{
									ScpObject * obj = currentObjectSpace->FindObject(vtparameters->at(i));
									if (obj)
									{
										func->RealParameters.push_back(vtparameters->at(i));
									}
									else
									{
										func->RealParameters.push_back(vtparameters->at(i));
										//engine->PrintError(scpErrorInvalidFunctionParameter);
									}
								}
								func->Do(engine);
								if (!recurse)
								{
									engine->SetCurrentObjectSpace(classobj->UserClassObjectSpace.parentspace);
								}
								else
								{
									func->RealParameters = TempVtparameters;
								}


							}
						}
					}
				}
			}
			else
			{
				ScpClassInstanceObject *classobj = (ScpClassInstanceObject*)currentObjectSpace->FindObject(classname);
				if (classobj)
				{
					if (classobj->GetType() == ObjClassInstance)
					{
						ScpFunctionObject* func;
						func = (ScpFunctionObject*)classobj->UserClassObjectSpace.FindObject(functionname);
						if (func)
						{
							if (func->GetType() == ObjFunction)
							{
								VTPARAMETERS TempVtparameters;
								BOOL recurse = FALSE;
								if (currentObjectSpace->IsMyParentSpace(&classobj->UserClassObjectSpace))
								{
									recurse = TRUE;
								}
								if (!recurse)
								{
									classobj->UserClassObjectSpace.parentspace = currentObjectSpace;
									engine->SetCurrentObjectSpace(&classobj->UserClassObjectSpace);
								}
								else
								{
									TempVtparameters = func->RealParameters;
									func->RealParameters.clear();
								}
								for (ULONG i = 1; i < vtparameters->size(); i++)
								{
									ScpObject * obj = currentObjectSpace->FindObject(vtparameters->at(i));
									if (obj)
									{
										func->RealParameters.push_back(vtparameters->at(i));
									}
									else
									{
										func->RealParameters.push_back(vtparameters->at(i));
										//engine->PrintError(scpErrorInvalidFunctionParameter);
									}
								}
								func->Do(engine);
								if (!recurse)
								{
									engine->SetCurrentObjectSpace(classobj->UserClassObjectSpace.parentspace);
								}
								else
								{
									func->RealParameters = TempVtparameters;
								}


							}
						}
					}
				}
			}
		}
		else
		{
			DebugUtil::TraceW(L"Call Enter");

			ScpFunctionObject* func = (ScpFunctionObject*)currentObjectSpace->FindObject(objname);
			//ScpFunctionObject* realfunc = func;
			if (func)
			{
				std::wstring OldName;
				BOOL Clone = FALSE;
				//std::wstring clonename=name+L"clone";
				if (currentObjectSpace->IsMyParentSpace(func->FunctionObjectSpace) || currentObjectSpace == func->FunctionObjectSpace)
				{
					//˵���ǵݹ�ĺ�������	
					DebugUtil::TraceW(L"Clone Call Enter");
					Clone = TRUE;
				}
				ScpObjectSpace * OldObjectSpace = NULL;
				VTPARAMETERS OldRealParameters;
				if (func)
				{
					if (func->GetType() == ObjFunction)
					{
						if (Clone)
						{
							OldObjectSpace = func->FunctionObjectSpace;
							OldName = func->Name;
							func->FunctionObjectSpace = new ScpObjectSpace;
							func->FunctionObjectSpace->belongto = func;
							if (currentObjectSpace == OldObjectSpace)
							{
								func->FunctionObjectSpace->parentspace = currentObjectSpace;
							}
							else
							{
								func->FunctionObjectSpace->parentspace = currentObjectSpace;
								//func->FunctionObjectSpace->parentspace=OldObjectSpace->parentspace;
							}
							func->FunctionObjectSpace->ObjectSpaceType = Space_Function;
							OldRealParameters = func->RealParameters;
							func->RealParameters.clear();
							func->Name = func->GetCloneName();
						}
						if (func->RealParameters.size() == 0)
						{
							for (ULONG i = 1; i < vtparameters->size(); i++)
							{
								func->RealParameters.push_back(vtparameters->at(i));
							}
						}

						func->Do(engine);
					}
					if (Clone)
					{
						ScpObjectSpace * tempObjectSpace = func->FunctionObjectSpace;
						func->FunctionObjectSpace = OldObjectSpace;
						delete tempObjectSpace;
						func->RealParameters = OldRealParameters;
						func->Name = OldName;
						DebugUtil::TraceW(L"Clone Call Out");
						//currentObjectSpace->EraseObject(clonename);
					}
					DebugUtil::TraceW(L" Call Out");
				}

			}
		}
	}
	return TRUE;
}

/*
���˳�������
��������
*/
BOOL CScriptCommand::Do_Exit_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 0)
	{
		exit(0);
	}
	else if (vtparameters->size() == 1)
	{

	}
	return TRUE;
}
/*
�����������
�����������������ʽ����������������л���
*/
BOOL  CScriptCommand::Do_Test_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{

	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 1)
	{
		std::wstring expression = vtparameters->at(0);
		DebugUtil::TraceW(L"Test Enter expression %s", expression.c_str());
		std::wstring userobjname = ScpObjectNames::GetSingleInsatnce()->strObjIfStatement;
		{
			ScpStringObject *strobj2 = (ScpStringObject *)currentObjectSpace->FindObject(expression);
			if (strobj2)
			{
				if (strobj2->GetType() == ObjString)
				{
					expression = strobj2->content;
				}
			}
			userobjname = ScpObjectNames::GetSingleInsatnce()->strObjIfStatement + expression;
			ScpIfStatementObject * ifstmtObj = new ScpIfStatementObject(engine);
			if (ifstmtObj)
			{
				ifstmtObj->ConditionExpression = expression;
				while (currentObjectSpace->FindObject(userobjname))
				{
					userobjname += L"@";
				}
				ifstmtObj->Name = userobjname;
				ifstmtObj->IfStatementObjectSpace.spacename = userobjname;
				currentObjectSpace->AddObject(userobjname, ifstmtObj);
				ifstmtObj->IfStatementObjectSpace.parentspace = currentObjectSpace;
				engine->SetCurrentObjectSpace(&ifstmtObj->IfStatementObjectSpace);
			}
			//ifstmtObj->ReComputeCondition();
			DebugUtil::TraceW(L"Test Out expression %s", expression.c_str());
		}
	}
	else if (vtparameters->size() >= 2)
	{
		std::wstring command;
		for (ULONG i = 1;i < vtparameters->size();i++)
		{
			command += vtparameters->at(i);
			command += L",";
		}
		command = command.substr(0, command.length() - 1);
		std::wstring expression = vtparameters->at(0);
		ScpStringObject *strobjexpression = (ScpStringObject *)currentObjectSpace->FindObject(expression);
		if (strobjexpression)
		{
			if (strobjexpression->GetType() == ObjString)
			{
				expression = strobjexpression->content;
			}
		}
		ScpExpressionTreeNode *root = engine->ana.BuildExressionTreeEx(expression);
		if (root)
		{
			ScpObject * retobj = root->CalculateEx(engine);
			if (retobj)
			{
				currentObjectSpace->lastTestResult = ((ScpIntObject*)retobj)->value;
				if (((ScpIntObject*)retobj)->value == 1)
				{
					engine->DoString(command);
				}
				if (retobj->istemp)
				{
					currentObjectSpace->ReleaseTempObject(retobj);
				}
			}
			root->Destroy(engine->GetCurrentObjectSpace());
			engine->GetCurrentObjectSpace()->ReleaseTempObject(root);
		}
	}
	return TRUE;
}
/*
����������
��������������价����
*/
BOOL CScriptCommand::Do_Otherwise_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() >= 1)
	{
		if (engine->GetCurrentObjectSpace()->lastcommand == vl_test)
		{
			std::wstring command;
			for (ULONG i = 0;i < vtparameters->size();i++)
			{
				command += vtparameters->at(i);
				command += L",";
			}
			command = command.substr(0, command.length() - 1);
			if (engine->GetCurrentObjectSpace()->lastTestResult == 0)
			{
				engine->DoString(command);
			}
		}

	}
	return TRUE;
}

/*
���ȴ�������
���������û�����������ַ������߳�
*/
BOOL CScriptCommand::Do_Wait_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::wstring userinputobj = vtparameters->at(0);
		std::wstring strname = vtparameters->at(1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(userinputobj.c_str());
		if (ObjUserinput == type)
		{
			ScpStringObject *strobj = (ScpStringObject *)currentObjectSpace->FindObject(strname);
			if (strobj)
			{
				char buffer[1024] = { 0 };
#ifdef _WIN32
				gets_s(buffer, sizeof buffer);
#else
				fgets(buffer, sizeof(buffer), stdin);
#endif
				strobj->content = STDSTRINGEXT::AToW(buffer);
				//strobj->Show(engine);
			}
		}
	}
	return TRUE;
}
/*
������������
�������󣺺������ࡢѭ����䡢������䣬�˳����������
*/
BOOL CScriptCommand::Do_End_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	BOOL ret = FALSE;
	if (!currentObjectSpace)
	{
		return ret;
	}
	if (vtparameters->size() == 0)
	{
		if (currentObjectSpace->ObjectSpaceType == Space_Function || currentObjectSpace->ObjectSpaceType == Space_While)
		{
			if (currentObjectSpace->belongto)
			{
				if (currentObjectSpace->belongto->GetType() == ObjFunction)
				{
					ScpFunctionObject * funcobj = (ScpFunctionObject *)currentObjectSpace->belongto;
					engine->SetCurrentObjectSpace(funcobj->FunctionObjectSpace->parentspace);
					ret = TRUE;
				}
				else if (currentObjectSpace->belongto->GetType() == ObjWhileStatement)
				{
					ScpWhileStatementObject * whileobj = (ScpWhileStatementObject *)currentObjectSpace->belongto;
					engine->SetCurrentObjectSpace(whileobj->WhileStatementObjectSpace.parentspace);
					whileobj->Do(engine);
					engine->currentObjectSpace->EraseObject(whileobj->Name);
					ret = TRUE;
				}
				else
				{
					engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidScript);
				}
			}
		}
		else if (currentObjectSpace->ObjectSpaceType == Space_Class)
		{
			ScpClassObject *classobj = (ScpClassObject *)currentObjectSpace->belongto;
			engine->SetCurrentObjectSpace(classobj->UserClassObjectSpace.parentspace);
			//classobj->ClassBody.pop_back();//ɾ�����һ��"����"				
			ret = TRUE;
		}
		else if (currentObjectSpace->ObjectSpaceType == Space_If)
		{
			ScpIfStatementObject * ifstmtobj = (ScpIfStatementObject *)currentObjectSpace->belongto;
			if (ifstmtobj->GetType() == ObjIfStatement)
			{
				DebugUtil::TraceW(L"End Enter");				
				ifstmtobj->Do(engine);					
				engine->SetCurrentObjectSpace(ifstmtobj->IfStatementObjectSpace.parentspace);				
				engine->currentObjectSpace->EraseObject(ifstmtobj->Name);
			}
		}
		else if (currentObjectSpace->ObjectSpaceType == Space_Struct)
		{
			ScpStructObject * structobj = (ScpStructObject*)currentObjectSpace->belongto;
			if (structobj->GetType() == ObjStruct)
			{
				structobj->GetStructMemorySize();
				engine->SetCurrentObjectSpace(structobj->StructObjectSpace.parentspace);
				structobj->Boday.pop_back();
				ret = TRUE;
			}
		}
	}
	else
	{
		//engine->PrintError(scpErrorInvalidClassOrFunctionDefine);		
	}
	return ret;
}