/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#include "ScpDirectoryObject.h"
#include "ScpStringObject.h"
#include "ScpRegExpObject.h"
#include "ScriptEngine.h"
#include "commanddefine_uni.h"
#include "../Common/commonutil.hpp"
#ifdef _WIN32
#include "../Common/IsValidFileName.h"
#else
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

bool is_dir(char * filename)
{
	struct stat buf;
	int ret = stat(filename, &buf);
	if (0 == ret)
	{
		if (buf.st_mode & S_IFDIR)
		{
			return true;
		}
	}
	return false;
}

int delete_dir(const char * dirname)
{
	char chBuf[4096];
	DIR * dir = NULL;
	struct dirent *ptr;
	int ret = 0;
	dir = opendir(dirname);
	if (NULL == dir)
	{
		return -1;
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
		snprintf(chBuf, 4096, "%s/%s", dirname, ptr->d_name);
		if (is_dir(chBuf))
		{
			ret = delete_dir(chBuf);
			if (0 != ret)
			{
				break;
			}
		}
		else
		{
			ret = remove(chBuf);
			if (0 != ret)
			{
				break;
			}
		}
	}
	(void)closedir(dir);
	ret = remove(dirname);
	if (0 != ret)
	{
		return -1;
	}
	return 0;
}
static int copyFile(const char* src, const char* des)
{
	int ret = -1;
	int fd, fd2;
	uint64_t buffersize = 4096;
	uint64_t size = 0;
	uint64_t size2 = 0;
	uint64_t filefullsize;
	filefullsize = GetFileLen(src);
	fd = open(src, O_RDONLY);
	fd2 = open(des, O_RDWR | O_CREAT, 00700);
	if (fd < 0 || fd2 < 0)
	{
		return ret;
	}
	ret = 0;
	unsigned char * buffer = (unsigned char *)malloc(buffersize);
	if (buffer)
	{
		while (filefullsize > 0)
		{
			size = read(fd, buffer, buffersize);
			size2 = write(fd2, buffer, size);
			if (size != size2)
			{
				ret = -1;
				break;
			}
			filefullsize -= size;
		}
		free(buffer);
	}

	close(fd);
	close(fd2);
	return ret;
}
bool copy_dir(const char * source,const char * dest)
{
    bool ret=false;

    DIR * p_dir;
    struct dirent * p_dirent;


    char read_buf[PATH_MAX];
    char write_buf[PATH_MAX];

    sprintf(read_buf,"%s/", source );
    sprintf(write_buf,"%s/",dest);
    if( is_dir(read_buf) )
    {
        if(mkdir(write_buf, 0755) < 0)
        {
            //printf("mkdir fall:%s\n", strerror(errno));
            return ret;
        }
        if((p_dir = opendir(read_buf)) == NULL )
        {
            return ret;
        }

        while((p_dirent=readdir(p_dir)) != NULL)
        {
            char read_buffer[PATH_MAX*2];
            char write_buffer[PATH_MAX*2];
            sprintf(read_buffer,"%s%s", read_buf, p_dirent->d_name);
            sprintf(write_buffer,"%s%s", write_buf, p_dirent->d_name);
            if( is_dir(read_buffer) && 0 != strcmp(p_dirent->d_name, ".") && 0 != strcmp(p_dirent->d_name, "..") )
            {

                copy_dir(read_buffer, write_buffer);
            }

            else if(0 != strcmp(p_dirent->d_name, ".") && 0 != strcmp(p_dirent->d_name, ".."))
            {
                //copy file
                if( copyFile(read_buffer, write_buffer) < 0 )
                {
                    ret=false;
                    break;
                }
                ret=true;
            }
        }
    }
    closedir(p_dir);
    return ret;
}
#endif

BOOL MyPathFileExist(const wchar_t* PathName)
{
	BOOL ret = FALSE;
#ifdef _WIN32
	if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(PathName))
	{
		ret = TRUE;
	}
#else

	DIR* dir;
	std::string dirpath = STDSTRINGEXT::W2UTF(PathName);
	dir = opendir(dirpath.c_str());
	if (dir != NULL)
	{
		ret = TRUE;
	}
	closedir(dir);
#endif
	return ret;
}

BOOL IsDirectory(const wchar_t* pDir)
{
#ifdef WIN32
	wchar_t szCurPath[MAX_PATH];
	ZeroMemory(szCurPath, MAX_PATH);
	_swprintf(szCurPath, L"%s//*", pDir);
	WIN32_FIND_DATAW FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAW));
	HANDLE hFile = FindFirstFileW(szCurPath, &FindFileData);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		FindClose(hFile);
		return FALSE;
	}
	else
	{
		FindClose(hFile);
		return TRUE;
	}
#else
	struct stat st;
	stat(STDSTRINGEXT::W2UTF(pDir).c_str(), &st);
	if (st.st_mode&S_IFDIR == S_IFDIR)
	{
		return TRUE;
	}
	return FALSE;
#endif
}

BOOL DeleteDirectory(const wchar_t* DirName)
{
#ifdef WIN32
	wchar_t szCurPath[MAX_PATH];
	_swprintf(szCurPath, L"%s//*.*", DirName);
	WIN32_FIND_DATAW FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAW));
	HANDLE hFile = FindFirstFileW(szCurPath, &FindFileData);
	BOOL IsFinded = TRUE;
	while (IsFinded)
	{
		IsFinded = FindNextFileW(hFile, &FindFileData);
		if (wcscmp(FindFileData.cFileName, L".") && wcscmp(FindFileData.cFileName, L".."))
		{
			std::wstring strFileName = L"";
			strFileName = strFileName + DirName + L"//" + FindFileData.cFileName;
			if (IsDirectory(strFileName.c_str()))
			{
				DeleteDirectory(strFileName.c_str());
			}
			else
			{
				DeleteFileW(strFileName.c_str());
			}
		}
	}
	FindClose(hFile);
	BOOL bRet = RemoveDirectoryW(DirName);
	return bRet;
#else
	return (0==delete_dir(STDSTRINGEXT::W2UTF(DirName).c_str()));
#endif
}

BOOL myFindAllFiles(std::wstring directory, std::wstring matchrule, VTSTRINGS& allfiles)
{
#ifdef _WIN32

	wchar_t szFind[MAX_PATH] = { L"\0" };
	WIN32_FIND_DATAW findFileData;
	BOOL bRet;

	wcscpy_s(szFind, MAX_PATH, directory.c_str());
	wcscat_s(szFind, L"\\*.*");

	HANDLE hFind = ::FindFirstFileW(szFind, &findFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}

	//遍历文件夹
	while (TRUE)
	{
		if (findFileData.cFileName[0] != L'.')
		{
			wchar_t pathname[MAX_PATH] = { 0 };
			if (directory.substr(directory.length() - 1, 1) == L"\\")
			{
				directory = directory.substr(0, directory.length() - 1);
			}
			swprintf(pathname, L"%s\\%s", directory.c_str(), findFileData.cFileName);
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				myFindAllFiles(pathname, matchrule, allfiles);
			}
			else
			{
				wregex wrgx;
				bool ret = false;
				try
				{
					wrgx = matchrule;
					ret = regex_search(pathname, wrgx);
				}
				catch (...)
				{
					ret = false;
				}
				if (ret)
				{
					allfiles.push_back(pathname);
				}
			}
		}
		bRet = ::FindNextFileW(hFind, &findFileData);
		if (!bRet)
		{
			break;
		}
	}
	::FindClose(hFind);
	return TRUE;
#else

	char chBuf[4096];
	DIR * dir = NULL;
	struct dirent *ptr;
	int ret = 0;
	dir = opendir(STDSTRINGEXT::W2UTF(directory).c_str());
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
		snprintf(chBuf, 4096, "%s/%s", STDSTRINGEXT::W2UTF(directory).c_str(), ptr->d_name);
		if (is_dir(chBuf))
		{
			myFindAllFiles(STDSTRINGEXT::UTF2W(chBuf).c_str(), matchrule, allfiles);
		}
		else
		{
			wregex wrgx;
			bool bret = false;
			try
			{
				wrgx = matchrule;
				bret = regex_search(STDSTRINGEXT::UTF2W(chBuf).c_str(), wrgx);
			}
			catch (...)
			{
				bret = false;
			}
			if (bret)
			{
				allfiles.push_back(STDSTRINGEXT::UTF2W(chBuf));
			}
		}
	}
	(void)closedir(dir);
	return TRUE;

#endif
}

#ifdef _WIN32
BOOL copy_dir(std::wstring source, std::wstring dest)
{
	BOOL re = FALSE;
	CreateDirectoryW(dest.c_str(), NULL); //创建目标文件夹
	std::wstring  stPath;

	stPath = STDSTRINGEXT::Format(L"%s\\*.*", source.c_str());
	WIN32_FIND_DATAW findFileData;
	HANDLE hFind = ::FindFirstFileW(stPath.c_str(), &findFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}
	do
	{
		if (findFileData.cFileName[0] != L'.')
		{
			wchar_t pathname[MAX_PATH] = { 0 };
			swprintf(pathname, L"%s\\%s", source.c_str(), findFileData.cFileName);
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//递归创建文件夹+"/"+finder.GetFileName()
				copy_dir(pathname, dest + L"\\" + findFileData.cFileName);
			}
			else
			{

				BOOL result = (GetFileAttributes(pathname) & FILE_ATTRIBUTE_DIRECTORY);
				if (!result)
				{
					re = CopyFileW(pathname, (dest + L"\\" + findFileData.cFileName).c_str(), FALSE);
				}
			}
		}
	} while (::FindNextFileW(hFind, &findFileData));
	::FindClose(hFind);
	return re;
}
#endif 
ScpDirectoryObject::ScpDirectoryObject(void)
{
	objecttype = ObjDirectory;

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_delete, InnerFunction_delete);
	BindObjectInnerFuction(scpcommand_en_delete, InnerFunction_delete);


	BindObjectInnerFuction(scpcommand_cn_open, InnerFunction_open);
	BindObjectInnerFuction(scpcommand_en_open, InnerFunction_open);

	BindObjectInnerFuction(scpcommand_cn_create, InnerFunction_create);
	BindObjectInnerFuction(scpcommand_en_create, InnerFunction_create);


	BindObjectInnerFuction(scpcommand_cn_move, InnerFunction_move);
	BindObjectInnerFuction(scpcommand_en_move, InnerFunction_move);


	BindObjectInnerFuction(scpcommand_cn_copy, InnerFunction_copy);
	BindObjectInnerFuction(scpcommand_en_copy, InnerFunction_copy);

	BindObjectInnerFuction(scpcommand_cn_find, InnerFunction_find);
	BindObjectInnerFuction(scpcommand_en_find, InnerFunction_find);

	BindObjectInnerFuction(scpcommand_cn_enum, InnerFunction_enum);
	BindObjectInnerFuction(scpcommand_en_enum, InnerFunction_enum);
}


ScpDirectoryObject::~ScpDirectoryObject(void)
{
}

void ScpDirectoryObject::Show(CScriptEngine* engine)
{
#ifdef _WIN32
	std::wstring text;
	text = STDSTRINGEXT::Format(L"%s", directory.c_str());
#else
	std::string text;
	text = STDSTRINGEXT::Format("%s", STDSTRINGEXT::W2UTF(directory).c_str());
#endif
	engine->PrintError(text);
}
ScpObject* ScpDirectoryObject::Clone(std::wstring strObjName)
{
	ScpDirectoryObject *obj = new ScpDirectoryObject;
	if (obj)
	{
		obj->directory = directory;
		obj->all = all;
		obj->allfiles = allfiles;
		obj->allsubdir = allsubdir;
		return obj;
	}
	return NULL;
}
std::wstring ScpDirectoryObject::ToString()
{
	std::wstring temp;
	temp = directory;
	return temp;
}
void ScpDirectoryObject::Release()
{
	delete this;
}
BOOL ScpDirectoryObject::Open(std::wstring dir)
{
	directory = dir;
	if (!MyPathFileExist(dir.c_str()))
	{
#ifdef _WIN32
		CreateDirectory(dir.c_str(), NULL);
#else
		std::string dirpath = STDSTRINGEXT::W2UTF(dir);
		mkdir(dirpath.c_str(), 0744);
#endif
	}
	return TRUE;
}
void ScpDirectoryObject::ShowAllFiles(CScriptEngine* engine)
{
	for (ITSTRINGS it = allfiles.begin();it != allfiles.end();it++)
	{
		engine->PrintError(*it, FALSE);
	}
}
void ScpDirectoryObject::ShowAllSubdir(CScriptEngine* engine)
{
	for (ITSTRINGS it = allsubdir.begin();it != allsubdir.end();it++)
	{
		engine->PrintError(*it, FALSE);
	}
}
void ScpDirectoryObject::ShowAll(CScriptEngine* engine)
{
	for (ITSTRINGS it = all.begin();it != all.end();it++)
	{
		engine->PrintError(*it, FALSE);
	}
}
void ScpDirectoryObject::EnumAll()
{
	all.clear();
	allfiles.clear();
	allsubdir.clear();
	if (directory.length() == 0)
		return;
#ifdef _WIN32
	wchar_t szFind[MAX_PATH] = { L"\0" };
	WIN32_FIND_DATAW findFileData;
	BOOL bRet;

	wcscpy_s(szFind, MAX_PATH, directory.c_str());
	wcscat_s(szFind, L"\\*.*");

	HANDLE hFind = ::FindFirstFileW(szFind, &findFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	//遍历文件夹
	while (TRUE)
	{
		if (findFileData.cFileName[0] != L'.')
		{
			wchar_t pathname[MAX_PATH] = { 0 };
			if (directory.substr(directory.length() - 1, 1) == L"\\")
			{
				directory = directory.substr(0, directory.length() - 1);
			}
			swprintf(pathname, L"%s\\%s", directory.c_str(), findFileData.cFileName);
			all.push_back(pathname);
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				allsubdir.push_back(pathname);
			}
			else
			{
				allfiles.push_back(pathname);
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
	char chBuf[4096];
	DIR * dir = NULL;
	struct dirent *ptr;
	int ret = 0;
	dir = opendir(STDSTRINGEXT::W2UTF(directory).c_str());
	if (NULL == dir)
	{
		return ;
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
		snprintf(chBuf, 4096, "%s/%s", STDSTRINGEXT::W2UTF(directory).c_str(), ptr->d_name);
		if (is_dir(chBuf))
		{
			allsubdir.push_back(STDSTRINGEXT::UTF2W(chBuf));
		}
		else
		{
			allfiles.push_back(STDSTRINGEXT::UTF2W(chBuf));
		}
	}
	(void)closedir(dir);
	return ;
#endif
}
BOOL ScpDirectoryObject::Copy(std::wstring source, std::wstring dest)
{
	BOOL re = FALSE;
#ifdef _WIN32
	re = copy_dir(source, dest);
#else
    re=copy_dir(STDSTRINGEXT::W2UTF(source).c_str(),STDSTRINGEXT::W2UTF(dest).c_str());
#endif
	return re;
}
BOOL ScpDirectoryObject::Move(std::wstring source, std::wstring dest)
{
#ifdef WIN32
	return MoveFileW(source.c_str(), dest.c_str());
#else
	return (rename(STDSTRINGEXT::W2UTF(source).c_str(), STDSTRINGEXT::W2UTF(dest).c_str()) != -1);
#endif
}
BOOL ScpDirectoryObject::FindAllFiles(ScpObjectSpace* currentObjectSpace, ScpTableObject* tableobj, std::wstring driectory, std::wstring matchrule)
{
	VTSTRINGS allmyfile;
	myFindAllFiles(driectory, matchrule, allmyfile);
	int count = allmyfile.size();
	for (int i = 0;i < count;i++)
	{
		ScpStringObject* string1 = new ScpStringObject();
		string1->objname = allmyfile.at(i);
		string1->content = allmyfile.at(i);
		tableobj->AddElement(string1->objname, string1);
		currentObjectSpace->AddObject(string1->objname, string1);
	}
	return TRUE;
}
ScpTableObject* ScpDirectoryObject::EnumAllFiles(ScpObjectSpace* currentObjectSpace, ScpObject* reobj)
{
	ScpTableObject* tableobj = new ScpTableObject();
	int dircount = allfiles.size();
	if (dircount == 0)
	{
		EnumAll();
		dircount = allfiles.size();
	}
	for (int i = 0;i < dircount;i++)
	{
		if (((ScpRegExpObject*)reobj)->Find(allfiles.at(i)))
		{

			ScpStringObject* string1 = new ScpStringObject();

			string1->objname = STDSTRINGEXT::Format(L"%s%s%d", directory.c_str(), str_EN_ObjFile, i);

			string1->content = allfiles.at(i);
			tableobj->AddElement(string1->objname, string1);
			if (currentObjectSpace->FindLocalObject(string1->objname))
			{
				currentObjectSpace->EraseObject(string1->objname);
			}
			currentObjectSpace->AddObject(string1->objname, string1);
		}
	}
	return tableobj;
}
ScpTableObject* ScpDirectoryObject::EnumAllFiles(ScpObjectSpace* currentObjectSpace)
{

	ScpTableObject* tableobj = new ScpTableObject();
	int dircount = allfiles.size();
	if (dircount == 0)
	{
		EnumAll();
		dircount = allfiles.size();
	}
	for (int i = 0;i < dircount;i++)
	{
		ScpStringObject* string1 = new ScpStringObject();

		string1->objname = STDSTRINGEXT::Format(L"%s%s%d", directory.c_str(), str_EN_ObjFile, i);

		string1->content = allfiles.at(i);
		tableobj->AddElement(string1->objname, string1);
		if (currentObjectSpace->FindLocalObject(string1->objname))
		{
			currentObjectSpace->EraseObject(string1->objname);
		}
		currentObjectSpace->AddObject(string1->objname, string1);
	}
	return tableobj;
}
ScpTableObject* ScpDirectoryObject::EnumAllSubDir(ScpObjectSpace* currentObjectSpace)
{

	ScpTableObject* tableobj = new ScpTableObject();
	int dircount = allsubdir.size();
	if (dircount == 0)
	{
		EnumAll();
		dircount = allfiles.size();
	}
	for (int i = 0;i < dircount;i++)
	{
		ScpStringObject* string1 = new ScpStringObject();

		string1->objname = STDSTRINGEXT::Format(L"%s%s%d", directory.c_str(), str_EN_ObjSubDir, i);


		string1->content = allsubdir.at(i);
		tableobj->AddElement(string1->objname, string1);
		if (currentObjectSpace->FindLocalObject(string1->objname))
		{
			currentObjectSpace->EraseObject(string1->objname);
		}
		currentObjectSpace->AddObject(string1->objname, string1);
	}
	return tableobj;
}
BOOL ScpDirectoryObject::Delete()
{
#ifdef _WIN32
	return DeleteDirectory(directory.c_str());
#else
	return delete_dir(STDSTRINGEXT::W2UTF(directory).c_str());
#endif
}
BOOL ScpDirectoryObject::Delete(std::wstring dir)
{
#ifdef _WIN32
	return DeleteDirectory(dir.c_str());
#else
	return delete_dir(STDSTRINGEXT::W2UTF(dir).c_str());
#endif
}
BOOL  ScpDirectoryObject::PathOrFileExist(std::wstring dir)
{
	BOOL ret = FALSE;
#ifdef _WIN32
	DWORD dwAttribute = INVALID_FILE_ATTRIBUTES;
	dwAttribute = GetFileAttributesW(dir.c_str());
	if (dwAttribute == INVALID_FILE_ATTRIBUTES)
	{
		ret = FALSE;
	}
	ret = TRUE;
#else
	DIR* d_dir;
	std::string dirpath = STDSTRINGEXT::W2UTF(dir);
	d_dir = opendir(dirpath.c_str());
	if (d_dir != NULL)
	{
		ret = TRUE;
	}
	closedir(d_dir);
#endif
	return ret;
}
BOOL ScpDirectoryObject::IsDir(std::wstring dir)
{
#ifdef _WIN32
	DWORD dwAttribute = INVALID_FILE_ATTRIBUTES;
	dwAttribute = GetFileAttributesW(dir.c_str());
	if ((dwAttribute & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		return TRUE;
	}
	return FALSE;
#else
	struct stat st;
	stat(STDSTRINGEXT::W2UTF(dir).c_str(), &st);
	if (st.st_mode&S_IFDIR == S_IFDIR)
	{
		return TRUE;
	}
	return FALSE;
#endif
}
BOOL ScpDirectoryObject::Create(std::wstring dir)
{
#ifdef _WIN32
	return CreateDirectoryW(dir.c_str(), NULL);
#else
	return (mkdir(STDSTRINGEXT::W2UTF(dir).c_str(), S_IRWXU) == 0);
#endif
}
ScpObject * ScpDirectoryObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}
ScpObject * ScpDirectoryObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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
			ScpStringObject* tname = new ScpStringObject;
			tname->content = ScpGlobalObject::GetInstance()->GetTypeName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{

	((ScpDirectoryObject*)thisObject)->Delete(((ScpDirectoryObject*)thisObject)->directory);
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_enum(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			param0 = ((ScpStringObject *)objparam0)->content;
		}
		if (param0 == str_CN_ObjSubDir ||
			param0 == str_EN_ObjSubDir)
		{
			ScpTableObject* tableobj = ((ScpDirectoryObject*)thisObject)->EnumAllSubDir(currentObjectSpace);
			return tableobj;
		}
		else if (param0 == str_CN_ObjFile ||
			param0 == str_EN_ObjFile)
		{
			ScpTableObject* tableobj = ((ScpDirectoryObject*)thisObject)->EnumAllFiles(currentObjectSpace);
			return tableobj;
		}
	}
	else if (parameters->size() == 2)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring name2 = parameters->at(1);
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		StringStripQuote(name2);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			param0 = ((ScpStringObject *)objparam0)->content;
		}
		if (param0 == str_CN_ObjSubDir ||
			param0 == str_EN_ObjSubDir)
		{
			ScpTableObject* tableobj = ((ScpDirectoryObject*)thisObject)->EnumAllSubDir(currentObjectSpace);
			if (currentObjectSpace->FindLocalObject(name2))
			{
				currentObjectSpace->EraseObject(name2);
			}
			currentObjectSpace->AddObject(name2, tableobj);
		}
		else if (param0 == str_CN_ObjFile ||
			param0 == str_EN_ObjFile)
		{
			ScpTableObject* tableobj = ((ScpDirectoryObject*)thisObject)->EnumAllFiles(currentObjectSpace);
			if (currentObjectSpace->FindLocalObject(name2))
			{
				currentObjectSpace->EraseObject(name2);
			}
			currentObjectSpace->AddObject(name2, tableobj);
		}
	}
	if (parameters->size() == 3)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring & name2 = parameters->at(1);
		std::wstring & name3 = parameters->at(2);
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		StringStripQuote(name2);
		StringStripQuote(name3);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			param0 = ((ScpStringObject *)objparam0)->content;
		}
		if (param0 == str_EN_ObjFile ||
			param0 == str_CN_ObjFile)
		{
			ScpObject* reobj = currentObjectSpace->FindLocalObject(name3);
			if (reobj && reobj->GetType() == ObjRegExp)
			{
				ScpTableObject* tableobj = ((ScpDirectoryObject*)thisObject)->EnumAllFiles(currentObjectSpace, reobj);
				if (currentObjectSpace->FindLocalObject(name2))
				{
					currentObjectSpace->EraseObject(name2);
				}
				currentObjectSpace->AddObject(name2, tableobj);
			}

		}
	}
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		std::wstring findtype = parameters->at(0);
		std::wstring matchrule = parameters->at(1);
		StringStripQuote(findtype);
		StringStripQuote(matchrule);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(findtype);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			findtype = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objmatchrule = engine->GetCurrentObjectSpace()->FindObject(matchrule);
		if (objmatchrule && objmatchrule->GetType() == ObjString)
		{
			matchrule = ((ScpStringObject *)objmatchrule)->content;
		}
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(findtype.c_str());
		if (ObjFile == type)
		{
			ScpTableObject* tableobj = new ScpTableObject;
			((ScpDirectoryObject*)thisObject)->FindAllFiles(engine->GetCurrentObjectSpace(), tableobj, ((ScpDirectoryObject*)thisObject)->directory, matchrule);
			return tableobj;
		}
	}
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring name = parameters->at(0);
		StringStripQuote(name);
		ScpObject* obj = currentObjectSpace->FindLocalObject(name);

		if (obj && obj->GetType() == ObjDirectory)
		{
			ScpDirectoryObject::Copy(((ScpDirectoryObject*)thisObject)->directory, ((ScpDirectoryObject*)obj)->directory);
		}
		else if (obj && obj->GetType() == ObjString)
		{
			name = ((ScpStringObject*)obj)->content;
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				ScpDirectoryObject::Copy(((ScpDirectoryObject*)thisObject)->directory, name);
		}
		else
		{
			//StringStripQuote(name);
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				ScpDirectoryObject::Copy(((ScpDirectoryObject*)thisObject)->directory, name);
		}
		return thisObject;
	}
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_move(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring name = parameters->at(0);
		StringStripQuote(name);
		ScpObject* obj = currentObjectSpace->FindLocalObject(name);
		if (obj && obj->GetType() == ObjString)
		{
			name = ((ScpStringObject*)obj)->content;
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				ScpDirectoryObject::Move(((ScpDirectoryObject*)thisObject)->directory, name);
		}
		else
		{
			//StringStripQuote(name);
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				ScpDirectoryObject::Move(((ScpDirectoryObject*)thisObject)->directory, name);
		}
		return thisObject;

	}
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_create(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring name = parameters->at(0);
		StringStripQuote(name);
		ScpObject* obj = currentObjectSpace->FindLocalObject(name);
		if (obj && obj->GetType() == ObjString)
		{
			name = ((ScpStringObject*)obj)->content;
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				((ScpDirectoryObject*)thisObject)->Open(name);
		}
		else
		{
			//StringStripQuote(name);
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				((ScpDirectoryObject*)thisObject)->Open(name);
		}
		return thisObject;

	}
	else if (parameters->size() == 0)
	{
		((ScpDirectoryObject*)thisObject)->Open(((ScpDirectoryObject*)thisObject)->directory);
	}
	return nullptr;
}
ScpObject * ScpDirectoryObject::InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		ScpObjectSpace* currentObjectSpace = engine->GetCurrentObjectSpace();
		std::wstring name = parameters->at(0);
		StringStripQuote(name);
		ScpObject* obj = currentObjectSpace->FindLocalObject(name);
		if (obj && obj->GetType() == ObjString)
		{
			name = ((ScpStringObject*)obj)->content;
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				((ScpDirectoryObject*)thisObject)->Open(name);
		}
		else
		{
			//StringStripQuote(name);
#ifdef _WIN32
			if (IsValidFileName(name.c_str()))
#endif
				((ScpDirectoryObject*)thisObject)->Open(name);
		}
		return thisObject;

	}
	else if (parameters->size() == 0)
	{
		((ScpDirectoryObject*)thisObject)->Open(((ScpDirectoryObject*)thisObject)->directory);
	}
	return nullptr;
}
bool ScpDirectoryObject::IsInnerFunction(std::wstring& functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;

}
ScpObject* ScpDirectoryObject::CallInnerFunction(std::wstring& functionname, VTPARAMETERS* parameters, CScriptEngine* engine)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}

ScpObject * __stdcall ScpDirectoryObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() >= 2)
	{
		std::wstring &strobj = paramters->at(0);
		std::wstring &userobjname = paramters->at(1);
		std::wstring content;
		if (paramters->size() == 3)
			content = paramters->at(2);
		StringStripQuote(content);
		ScpDirectoryObject *dirobj = new ScpDirectoryObject;
		if (dirobj)
		{
			ScpStringObject * obj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(userobjname);
			if (obj)
			{
				ScpObjectType type = obj->GetType();
				if (ObjString == type)
				{
					userobjname = obj->content;
				}
			}
			dirobj->directory = content;
			return dirobj;

		}
	}
	return NULL;
}
