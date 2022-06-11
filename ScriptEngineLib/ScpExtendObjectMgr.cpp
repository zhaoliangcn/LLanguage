/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//��չ����Ĺ���ͨ������Ԥ����ĵ�����������֪��չ���������ID�����ơ����󹤳�����
*/
#include "ScpExtendObjectMgr.h"
#include "ScpOperationMgr.h"
#include "addin.h"

#include "../Common/commonutil.hpp"
#ifdef WIN32
#include <strsafe.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif


ScpExtendObjectMgr::ScpExtendObjectMgr(void)
{
}

ScpExtendObjectMgr::~ScpExtendObjectMgr(void)
{
}
BOOL ScpExtendObjectMgr::IsExtendObject(const wchar_t * objtypename)
{
	BOOL bRet = FALSE;
	ITExtendObject it = extendobjects.begin();
	while (it != extendobjects.end())
	{
		ExtendObjectItem &item = *it;
#ifdef WIN32
		if (_wcsicmp(item.objtypename_cn, objtypename) == 0
			|| _wcsicmp(item.objtypename_en, objtypename) == 0)
#else
		if (wcscasecmp(item.objtypename_cn, objtypename) == 0
			|| wcscasecmp(item.objtypename_en, objtypename) == 0)

#endif 
		{
			bRet = TRUE;
			break;
		}
		it++;
	}
	return bRet;
}
BOOL ScpExtendObjectMgr::IsExtendObject(ULONG UniqObjId)
{
	BOOL bRet = FALSE;
	ITExtendObject it = extendobjects.begin();
	while (it != extendobjects.end())
	{
		ExtendObjectItem &item = *it;
		if (item.uniqobjid == UniqObjId)
		{
			bRet = TRUE;
			break;
		}
		it++;
	}
	return bRet;
}
ULONG ScpExtendObjectMgr::GetExtendObjectId(const wchar_t * objtypename)
{
	ULONG id = -1;
	ITExtendObject it = extendobjects.begin();
	while (it != extendobjects.end())
	{
		ExtendObjectItem &item = *it;
#ifdef WIN32
		if (_wcsicmp(item.objtypename_cn, objtypename) == 0
			|| _wcsicmp(item.objtypename_en, objtypename) == 0)
#else
		if (wcscasecmp(item.objtypename_cn, objtypename) == 0
			|| wcscasecmp(item.objtypename_en, objtypename) == 0)

#endif 
		{
			id = item.uniqobjid;
			break;
		}
		it++;
	}
	return id;
}
ScpObject * ScpExtendObjectMgr::CreateExtendObject(const wchar_t * objtypename, VTPARAMETERS * paramters, CScriptEngine * engine)
{
	ScpObject* obj = NULL;
	ITExtendObject it = extendobjects.begin();
	while (it != extendobjects.end())
	{
		ExtendObjectItem &item = *it;
#ifdef WIN32
		if (_wcsicmp(item.objtypename_cn, objtypename) == 0
			|| _wcsicmp(item.objtypename_en, objtypename) == 0)
#else
		if (wcscasecmp(item.objtypename_cn, objtypename) == 0
			|| wcscasecmp(item.objtypename_en, objtypename) == 0)
#endif
		{
			obj = item.factory(paramters, engine);
			break;
		}
		it++;
	}
	return obj;
}
ScpObject * ScpExtendObjectMgr::CreateExtendObject(ULONG UniqObjId, VTPARAMETERS * paramters, CScriptEngine * engine)
{
	ScpObject* obj = NULL;
	ITExtendObject it = extendobjects.begin();
	while (it != extendobjects.end())
	{
		ExtendObjectItem &item = *it;
		if (item.uniqobjid == UniqObjId)
		{
			obj = item.factory(paramters, engine);
			break;
		}
		it++;
	}
	return obj;
}
std::wstring ScpExtendObjectMgr::GetExtendObjectName(ULONG UniqObjId)
{
	std::wstring temp;
	ScpObject* obj = NULL;
	ITExtendObject it = extendobjects.begin();
	while (it != extendobjects.end())
	{
		ExtendObjectItem &item = *it;
		if (item.uniqobjid == UniqObjId)
		{
			temp = item.objtypename_en;
			break;
		}
		it++;
	}
	return temp;

}
BOOL ScpExtendObjectMgr::RegistExtendObject(const wchar_t * objtypename_cn, const wchar_t * objtypename_en, ULONG UniqObjId, ExtObjCreateFactoryFunction factoryfunc)
{
	if (IsExtendObject(objtypename_cn) || IsExtendObject(objtypename_en) || IsExtendObject(UniqObjId))
	{
		return FALSE;
	}
	else
	{
		ExtendObjectItem item;
#ifdef WIN32
		StringCchCopy(item.objtypename_cn, _countof(item.objtypename_cn), objtypename_cn);
		StringCchCopy(item.objtypename_en, _countof(item.objtypename_en), objtypename_en);
#else 
		wcscpy(item.objtypename_cn, objtypename_cn);
		wcscpy(item.objtypename_en, objtypename_en);

#endif
		item.uniqobjid = UniqObjId;
		item.factory = factoryfunc;
		extendobjects.push_back(item);
		return FALSE;
	}
}

void ScpExtendObjectMgr::ClearExtendObject()
{
	extendobjects.clear();
}
BOOL  ScpExtendObjectMgr::LoadExtensions(const  wchar_t * ModulePathName, ScpGlobalCommandObject * scpglobalcommands)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	DWORD dwError;
	HMODULE hdll = GetModuleHandleW(ModulePathName);
	if (hdll)
	{
		//return TRUE;
	}		
	else
	{
		hdll = LoadLibraryW(ModulePathName);
	}
	if (hdll)
	{
		pGetObjectCount Func_GetObjectCount = (pGetObjectCount)GetProcAddress(hdll, "GetObjectCount");
		pGetObjectNameId Func_GetObjectNameId = (pGetObjectNameId)GetProcAddress(hdll, "GetObjectNameId");
		pGetUniqObjectIdEx Func_GetUniqObjectIdEx = (pGetUniqObjectIdEx)GetProcAddress(hdll, "GetUniqObjectIdEx");
		pGetObjFactoryEx Func_GetObjFactoryEx = (pGetObjFactoryEx)GetProcAddress(hdll, "GetObjFactoryEx");
		pExtObjCommandCount Func_ExtObjCommandCount = (pExtObjCommandCount)GetProcAddress(hdll, "ExtObjCommandCount");
		pExtObjCommandRegisterFunction Func_ExtObjCommandRegisterFunction = (pExtObjCommandRegisterFunction)GetProcAddress(hdll, "ExtObjCommandRegisterFunction");
		if (Func_GetObjectCount && Func_GetObjectNameId)
		{
			DWORD dwObjectCount = Func_GetObjectCount();
			for (DWORD index = 0;index < dwObjectCount;index++)
			{
				DWORD dwObjectId = -1;
				static const DWORD dwObjectTypeNameMax = 256;
				wchar_t ObjTypeNameCn[dwObjectTypeNameMax];
				wchar_t ObjTypeNameEn[dwObjectTypeNameMax];
				if (Func_GetObjectNameId(index, ObjTypeNameCn, dwObjectTypeNameMax, ObjTypeNameEn, dwObjectTypeNameMax, &dwObjectId))
				{
					if (!IsExtendObject(ObjTypeNameEn))//ȷ��δע��
					{
						if (Func_GetUniqObjectIdEx && Func_GetObjFactoryEx)
						{
							bRet = RegistExtendObject(ObjTypeNameCn, ObjTypeNameEn, Func_GetUniqObjectIdEx(ObjTypeNameEn), Func_GetObjFactoryEx(ObjTypeNameEn));
						}

						if (Func_ExtObjCommandCount && Func_ExtObjCommandRegisterFunction)
						{

							DWORD commandCount = Func_ExtObjCommandCount(ObjTypeNameEn);
							for (DWORD i = 0; i < commandCount; i++)
							{
								ExtObjectCommand extobjcmd;
								DWORD dwObjId;
								DWORD dwCommandId;
								ExtObjectCommandFunction commandfunc = NULL;
								wchar_t CommandNameCn[256] = { 0 };
								wchar_t CommandNameEn[256] = { 0 };
								Func_ExtObjCommandRegisterFunction(ObjTypeNameEn, i, &dwObjId, &dwCommandId, CommandNameCn, CommandNameEn, &commandfunc);
								extobjcmd.dwCommandId = dwCommandId;
								extobjcmd.dwObjectIdList.push_back(dwObjId);
								extobjcmd.CommandNames.push_back(CommandNameCn);
								extobjcmd.CommandNames.push_back(CommandNameEn);
								extobjcmd.ExtCommands.push_back(commandfunc);
								scpglobalcommands->RegistExtCommand(extobjcmd);
							}
						}
					}
					
				}
			}
		}
		pGetBinaryOperationCount Func_GetBinaryOperationCount = (pGetBinaryOperationCount)GetProcAddress(hdll, "GetBinaryOperationCount");
		pBinaryOperationRegister Func_BinaryOperationRegister = (pBinaryOperationRegister)GetProcAddress(hdll, "BinaryOperationRegister");
		if (Func_GetBinaryOperationCount && Func_BinaryOperationRegister)
		{
			DWORD dwOpCount = Func_GetBinaryOperationCount();
			for (int i = 0;i < dwOpCount;i++)
			{
				pBinaryOpertaion BinaryOpertaion_Func = NULL;
				wchar_t opName[256] = { 0 };
				ScpObjectType obj1Type;
				ScpObjectType obj2Type;
				Func_BinaryOperationRegister(i, opName, 256, obj1Type, obj2Type, &BinaryOpertaion_Func);
				ScpOperationMgr::GetInstance()->RegisterBinaryOperation(opName, obj1Type, obj2Type, BinaryOpertaion_Func);
			}
		}
		if (map_loadedExtension.find(ModulePathName) == map_loadedExtension.end())
		{
			map_loadedExtension[ModulePathName] = hdll;
		}
	}
	else
	{
		dwError = GetLastError();
	}
#else
	void *hdll;
	hdll = dlopen(STDSTRINGEXT::W2UTF(ModulePathName).c_str(), RTLD_LAZY);
	if (hdll) {
		pGetObjectCount Func_GetObjectCount = (pGetObjectCount)dlsym(hdll, "GetObjectCount");
		pGetObjectNameId Func_GetObjectNameId = (pGetObjectNameId)dlsym(hdll, "GetObjectNameId");
		pGetUniqObjectIdEx Func_GetUniqObjectIdEx = (pGetUniqObjectIdEx)dlsym(hdll, "GetUniqObjectIdEx");
		pGetObjFactoryEx Func_GetObjFactoryEx = (pGetObjFactoryEx)dlsym(hdll, "GetObjFactoryEx");
		pExtObjCommandCount Func_ExtObjCommandCount = (pExtObjCommandCount)dlsym(hdll, "ExtObjCommandCount");
		pExtObjCommandRegisterFunction Func_ExtObjCommandRegisterFunction = (pExtObjCommandRegisterFunction)dlsym(hdll, "ExtObjCommandRegisterFunction");
		if (Func_GetObjectCount && Func_GetObjectNameId)
		{
			DWORD dwObjectCount = Func_GetObjectCount();
			for (DWORD index = 0;index < dwObjectCount;index++)
			{
				DWORD dwObjectId = -1;
				static const DWORD dwObjectTypeNameMax = 256;
				wchar_t ObjTypeNameCn[dwObjectTypeNameMax];
				wchar_t ObjTypeNameEn[dwObjectTypeNameMax];
				if (Func_GetObjectNameId(index, ObjTypeNameCn, dwObjectTypeNameMax, ObjTypeNameEn, dwObjectTypeNameMax, &dwObjectId))
				{
					if (Func_GetUniqObjectIdEx && Func_GetObjFactoryEx)
					{
						bRet = RegistExtendObject(ObjTypeNameCn, ObjTypeNameEn, Func_GetUniqObjectIdEx(ObjTypeNameEn), Func_GetObjFactoryEx(ObjTypeNameEn));
					}

					if (Func_ExtObjCommandCount && Func_ExtObjCommandRegisterFunction)
					{

						DWORD commandCount = Func_ExtObjCommandCount(ObjTypeNameEn);
						for (DWORD i = 0; i < commandCount; i++)
						{
							ExtObjectCommand extobjcmd;
							DWORD dwObjId;
							DWORD dwCommandId;
							ExtObjectCommandFunction commandfunc = NULL;
							wchar_t CommandNameCn[256] = { 0 };
							wchar_t CommandNameEn[256] = { 0 };
							Func_ExtObjCommandRegisterFunction(ObjTypeNameEn, i, &dwObjId, &dwCommandId, CommandNameCn, CommandNameEn, &commandfunc);
							extobjcmd.dwCommandId = dwCommandId;
							extobjcmd.dwObjectIdList.push_back(dwObjId);
							extobjcmd.CommandNames.push_back(CommandNameCn);
							extobjcmd.CommandNames.push_back(CommandNameEn);
							extobjcmd.ExtCommands.push_back(commandfunc);
							scpglobalcommands->RegistExtCommand(extobjcmd);
						}
					}
				}
			}
		}
		pGetBinaryOperationCount Func_GetBinaryOperationCount = (pGetBinaryOperationCount)dlsym(hdll, "GetBinaryOperationCount");
		pBinaryOperationRegister Func_BinaryOperationRegister = (pBinaryOperationRegister)dlsym(hdll, "BinaryOperationRegister");
		if (Func_GetBinaryOperationCount && Func_BinaryOperationRegister)
		{
			DWORD dwOpCount = Func_GetBinaryOperationCount();
			for (int i = 0;i < dwOpCount;i++)
			{
				pBinaryOpertaion BinaryOpertaion_Func = NULL;
				wchar_t opName[256] = { 0 };
				ScpObjectType obj1Type;
				ScpObjectType obj2Type;
				Func_BinaryOperationRegister(i, opName, 256, obj1Type, obj2Type, &BinaryOpertaion_Func);
				ScpOperationMgr::GetInstance()->RegisterBinaryOperation(opName, obj1Type, obj2Type, BinaryOpertaion_Func);
			}
		}
		if (map_loadedExtension.find(ModulePathName) == map_loadedExtension.end())
		{
			map_loadedExtension[ModulePathName] = hdll;
			bRet = TRUE;
		}
		//dlclose(hdll);
	}
#endif
	return bRet;
}
BOOL ScpExtendObjectMgr::LoadExtension(const wchar_t * ModuleName, ScpGlobalCommandObject * scpglobalcommands)
{
	BOOL bRet = FALSE;
#ifdef _WIN32
	wchar_t ExtensionPath[MAX_PATH] = { 0 };
	wchar_t szFind[MAX_PATH] = { L"\0" };
	wchar_t szModuleFullName[MAX_PATH] = { L"\0" };
	wcscpy_s(szModuleFullName, ModuleName);
	wcscat_s(szModuleFullName, L"Addin.dll");

	if (GetModuleHandleW(szModuleFullName))
	{
		//���������ܻ����ڴ��м��ض�����������ʵ�������Բ��ö�̬������ü����ж��Ƿ���ע����չ
		//return TRUE;
	}

	GetCurrentModulePath(ExtensionPath, MAX_PATH);
	if(!wcsstr(ExtensionPath, L"Addin\\"))
	wcscat_s(ExtensionPath, MAX_PATH, L"Addin\\");
	wcscpy_s(szFind, MAX_PATH, ExtensionPath);
	wcscat_s(szFind, szModuleFullName);

	WIN32_FIND_DATAW findFileData;
	HANDLE hFind = ::FindFirstFileW(szFind, &findFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return bRet;
	}

	//�����ļ���
	while (TRUE)
	{
		if (findFileData.cFileName[0] != L'.')
		{
			wchar_t pathname[MAX_PATH] = { 0 };
			swprintf(pathname, L"%s\\%s", ExtensionPath, findFileData.cFileName);
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
			}
			else
			{
				LoadExtensions(pathname, scpglobalcommands);
			}
		}
		bRet = ::FindNextFileW(hFind, &findFileData);
		if (!bRet)
		{
			break;
		}
	}
	::FindClose(hFind);
#else
	char ExtensionPath[4096] = { 0 };
	wchar_t szModuleFullName[MAX_PATH] = { L"\0" };
	wcscpy(szModuleFullName, L"lib");
	wcscat(szModuleFullName, ModuleName);
	wcscat(szModuleFullName, L"Addin.so");

	get_executable_path(ExtensionPath, NULL, 4096);
	strcat(ExtensionPath, "Addin/");
	char chBuf[PATH_MAX*2];
	DIR * dir = NULL;
	struct dirent *ptr;
	int ret = 0;
	dir = opendir(ExtensionPath);
	if (NULL == dir)
	{
		return FALSE;
	}
	while ((ptr = readdir(dir)) != NULL)
	{
		ret = strcmp(ptr->d_name, ".");
		if (0 == ret)
		{
			continue;
		}
		ret = strcmp(ptr->d_name, "..");
		if (0 == ret)
		{
			continue;
		}
		if (strcasecmp(ptr->d_name, STDSTRINGEXT::W2UTF(szModuleFullName).c_str()) == 0)
		{
			snprintf(chBuf, PATH_MAX*2, "%s/%s", ExtensionPath, ptr->d_name);
			bRet = LoadExtensions(STDSTRINGEXT::UTF2W(chBuf).c_str(), scpglobalcommands);
		}
	}
	(void)closedir(dir);
#endif
	return bRet;
}

void ScpExtendObjectMgr::FreeAllExtensions()
{
#ifdef _WIN32
	if (map_loadedExtension.size() > 0)
	{
		ITHANDLESMAP it = map_loadedExtension.begin();
		while (it != map_loadedExtension.end())
		{
			HMODULE h = (HMODULE)it->second;
			if (h)
			{
				FreeLibrary(h);
			}
			it = map_loadedExtension.erase(it);
		}
	}
#else
	if (map_loadedExtension.size() > 0)
	{
		ITHANDLESMAP it = map_loadedExtension.begin();
		while (it != map_loadedExtension.end())
		{
			void* h = (void*)it->second;
			if (h)
			{
				dlclose(h);
			}
			it = map_loadedExtension.erase(it);
		}
	}
#endif // _WIN32
}
