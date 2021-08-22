#ifndef _H_COMMONUTIL
#define _H_COMMONUTIL
#ifdef _WIN32
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <tchar.h>
#include <strsafe.h>
static std::wstring GetEnvironmentVariableStr(std::wstring name)
{
	DWORD dwErr;
	std::wstring temp ;
	#define BUFFER_SIZE (4096)
	wchar_t * Buffer = (wchar_t *) malloc(BUFFER_SIZE);
	if(Buffer)
	{
		memset(Buffer,0,BUFFER_SIZE);
		GetEnvironmentVariableW(name.c_str(),Buffer,BUFFER_SIZE);
		dwErr = GetLastError();
		temp = Buffer;
		free(Buffer);
	}
	return temp;
}
static std::wstring PathStripFileName(std::wstring pathname)
{
	std::wstring Temp;
	wchar_t Drv[MAX_PATH]={0};
	wchar_t Dir[MAX_PATH]={0};
	_tsplitpath_s(pathname.c_str(),Drv,MAX_PATH,Dir,MAX_PATH,NULL,0,NULL,0);
	_tcscat_s(Drv,MAX_PATH,Dir);
	Temp =Drv;
	return Temp;	
}
static std::wstring MyPathStripPath(const wchar_t * Path)
{
	std::wstring filename;
	if(Path)
	{
		wchar_t Name[MAX_PATH]={0};
		wchar_t Ext[MAX_PATH]={0};
		_tsplitpath_s(Path,NULL,0,NULL,0,Name,MAX_PATH,Ext,MAX_PATH);
		_tcscat_s(Name,MAX_PATH,Ext);
		filename=Name;
	}
	return filename;
}
static BOOL GetProcessPath(wchar_t * Path)
{
	if(Path==NULL)	
		return FALSE;
	wchar_t Temp[MAX_PATH];
	wchar_t Drv[MAX_PATH];
	wchar_t Dir[MAX_PATH];
	GetModuleFileNameW(NULL,Temp,MAX_PATH);
	_tsplitpath_s(Temp,Drv,MAX_PATH,Dir,MAX_PATH,NULL,0,NULL,0);
	_tcscat_s(Drv,MAX_PATH,Dir);
	_tcscpy_s(Path,MAX_PATH,Drv);
	return TRUE;	
}

static void CreateAndWaitProcess(const wchar_t * ProcessName,const wchar_t * Parameter)
{
	wchar_t CommandLine[512]={0};
	StringCbPrintfW(CommandLine,sizeof(CommandLine),L"%s \"%s\"",ProcessName,Parameter);
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	if( !CreateProcessW( NULL,   // No module name (use command line)
		(LPWSTR)CommandLine,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
		) 
	{
		return;
	}
	WaitForSingleObject( pi.hProcess, INFINITE );
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}
static HMODULE GetCurrentModule()
{
	HMODULE hModule = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCTSTR)GetCurrentModule,
		&hModule);

	return hModule;
}

static  LPCWSTR WINAPI GetCurrentModulePath ( LPWSTR lpModulePath, DWORD dwBufferSize)
{
	WCHAR	szFullName[MAX_PATH];

	HMODULE hModule = NULL; 
	if (!GetModuleHandleEx( 
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, 
		(LPCTSTR)GetCurrentModulePath, 
		&hModule))
	{
		return NULL;
	}

	if (GetModuleFileNameW(hModule,szFullName,MAX_PATH)==0)
	{
		return NULL;
	};
	LPWSTR lpSlashPos = wcsrchr(szFullName, '\\');
	if (lpSlashPos == NULL)
	{
		return NULL;
	}
	else
	{
		StringCchCopyNW(lpModulePath, dwBufferSize, szFullName, lpSlashPos - szFullName + 1);
		return lpModulePath;
	}

}
static  LPCWSTR WINAPI GetCurrentModuleName ( LPWSTR lpModuleName, DWORD dwBufferSize)
{
	WCHAR	szFullName[MAX_PATH];

	HMODULE hModule = NULL; 
	if (!GetModuleHandleEx( 
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, 
		(LPCTSTR)GetCurrentModulePath, 
		&hModule))
	{
		return NULL;
	}

	if (GetModuleFileNameW(hModule,szFullName,MAX_PATH)==0)
	{
		return NULL;
	};
	LPWSTR lpSlashPos = wcsrchr(szFullName, '\\');
	if (lpSlashPos == NULL)
	{
		return NULL;
	}
	else
	{
		StringCchCopyW(lpModuleName, dwBufferSize, lpSlashPos + 1);
		return lpModuleName;
	}
}
static HMODULE LoadModule(const wchar_t * ModuleName)
{
	HMODULE hModule = GetModuleHandleW(ModuleName);
	if(hModule==NULL)
	{
		wchar_t Path[MAX_PATH]={0};
		GetCurrentModulePath(Path,MAX_PATH);
		wcscat_s(Path,MAX_PATH,ModuleName);
		hModule=LoadLibraryW(Path);
	}
	return hModule;
}
static BOOL	IsWinXPSystem()
{
	BOOL	bResult = FALSE;
	OSVERSIONINFO info;
	ZeroMemory(&info, sizeof(OSVERSIONINFO));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if (GetVersionEx(&info))
	{
		bResult = (info.dwMajorVersion == 5 && info.dwMinorVersion == 1);
	}
	return  bResult;
}
static inline BOOL IsVistaOrLater()
{
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	if (osvi.dwMajorVersion >= 6)
		return TRUE;
	return FALSE;
}

static void RecurseCreateDir(const wchar_t * Path)
{
	if (Path)
	{
		std::wstring PathName=Path;
		size_t pos=PathName.rfind(L"\\");
		if(pos!=std::wstring::npos)
		{
			std::wstring sub=PathName.substr(0,pos);
			RecurseCreateDir(sub.c_str());
		}
		CreateDirectoryW(Path,NULL);
	}
}
static BOOL RecurseDeleteDirectoryW(const wchar_t* szFileDir)
{
	BOOL bRet = FALSE;
	std::wstring strDir = szFileDir;
	if (strDir.at(strDir.length()-1) != L'\\')
		strDir += L'\\';
	WIN32_FIND_DATAW wfd;
	HANDLE hFind = FindFirstFileW((strDir + L"*.*").c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return bRet;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (_wcsicmp(wfd.cFileName,L".") != 0 &&
				_wcsicmp(wfd.cFileName,L"..") != 0)
				RecurseDeleteDirectoryW( (strDir + wfd.cFileName).c_str());
		}
		else
		{
			DeleteFileW((strDir + wfd.cFileName).c_str());			
		}
	}
	while (FindNextFileW(hFind,&wfd));
	FindClose(hFind);
	RemoveDirectoryW(szFileDir);		
	bRet = TRUE;
	return bRet;
}
static BOOL DeleteDirectoryExW(const wchar_t* szFileDir)
{
	BOOL bRet = FALSE;
	std::wstring strDir = szFileDir;
	if (strDir.at(strDir.length()-1) != L'\\')
		strDir += L'\\';
	WIN32_FIND_DATAW wfd;
	HANDLE hFind = FindFirstFileW((strDir + L"*.*").c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return bRet;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (_wcsicmp(wfd.cFileName,L".") != 0 &&
				_wcsicmp(wfd.cFileName,L"..") != 0)
				DeleteDirectoryExW( (strDir + wfd.cFileName).c_str());
		}
		else
		{
			MoveFileExW((strDir + wfd.cFileName).c_str(),NULL,MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);			
		}
	}
	while (FindNextFileW(hFind,&wfd));
	FindClose(hFind);
	MoveFileExW(szFileDir,NULL,MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);		
	bRet = TRUE;
	return bRet;
}
static BOOL DeletePathFileOnRebootW(LPCWSTR lpszFullPath)
{
	return MoveFileExW(lpszFullPath,NULL,MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
}
static BOOL DeletePathFileOnRebootA(LPCSTR lpszFullPath)
{
	return MoveFileExA(lpszFullPath,NULL,MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
}
static ULONGLONG GetFileSizeA(LPCSTR	lpszFullPath)
{
	WIN32_FILE_ATTRIBUTE_DATA attr;
	LARGE_INTEGER result;
	result.QuadPart = 0;
	if (GetFileAttributesExA(lpszFullPath,GetFileExInfoStandard,&attr))
	{
		result.LowPart = attr.nFileSizeLow ;
		result.HighPart = attr.nFileSizeHigh ;
	}
	return result.QuadPart;
}

static ULONGLONG GetFileSizeW(LPCWSTR	lpszFullPath)
{
	WIN32_FILE_ATTRIBUTE_DATA attr;
	LARGE_INTEGER result;
	result.QuadPart = 0;
	if (GetFileAttributesExW(lpszFullPath,GetFileExInfoStandard,&attr))
	{
		result.LowPart = attr.nFileSizeLow ;
		result.HighPart = attr.nFileSizeHigh ;
	}
	return result.QuadPart;
}

static inline BOOL EnableDebugPrivilege()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return(FALSE);
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}
static inline BOOL GetProcessIdByName(LPWSTR szProcessName, LPDWORD lpPID)
{

	STARTUPINFO st;
	PROCESS_INFORMATION pi;
	PROCESSENTRY32W ps;
	HANDLE hSnapshot;
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	st.cb = sizeof(STARTUPINFO);
	ZeroMemory(&ps, sizeof(PROCESSENTRY32));
	ps.dwSize = sizeof(PROCESSENTRY32);

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!Process32FirstW(hSnapshot, &ps))
		return FALSE;

	do
	{
		if (lstrcmpiW(ps.szExeFile, szProcessName) == 0)
		{
			*lpPID = ps.th32ProcessID;
			CloseHandle(hSnapshot);
			return TRUE;
		}
	} while (Process32NextW(hSnapshot, &ps));
	CloseHandle(hSnapshot);
	return FALSE;
}
static inline BOOL LaunchProcess(LPCWSTR	lpProcessFullPath, LPCWSTR lpCmdArgs)
{
	BOOL bRet = FALSE;
	WCHAR szCmdLine[2048] = { 0 };
	std::wstring sCmdLine;
	sCmdLine.append(L"\"");
	sCmdLine.append(lpProcessFullPath);
	sCmdLine.append(L"\"");
	if (lpCmdArgs != NULL && 0 != lpCmdArgs[0])
	{
		sCmdLine.append(L" ");
		sCmdLine.append(lpCmdArgs);
	}
	wcscpy_s(szCmdLine, sCmdLine.c_str());

	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (CreateProcessW(lpProcessFullPath,   // No module name (use command line)
		szCmdLine,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi))
	{
		CloseHandle( pi.hThread );
		CloseHandle(pi.hProcess);
		bRet = TRUE;
	}
	else
	{
		
	}
	return bRet;
}
static inline BOOL  RegExistEx(HKEY hKeyRoot, LPCWSTR lpSubKey, BOOL m_bIsWow64)
{
	HKEY hKey;
	LONG lResult;
	REGSAM wow64 = (m_bIsWow64) ? KEY_WOW64_64KEY : 0;
	lResult = RegOpenKeyExW(hKeyRoot, lpSubKey, 0, KEY_READ | wow64, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		if (lResult == ERROR_FILE_NOT_FOUND) {
			//printf("Key not found.\n");
			return FALSE;
		}
		else {
			//printf("Error opening key.\n");			
			return TRUE;
		}
	}
	RegCloseKey(hKey);
	return TRUE;
}
static inline BOOL IsWow64()
{
	typedef BOOL(WINAPI *LPFN_IsWow64Process) (HANDLE, PBOOL);

	LPFN_IsWow64Process fpIsWow64Process;
	BOOL bResult = FALSE;

	fpIsWow64Process = (LPFN_IsWow64Process)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fpIsWow64Process)
	{
		if (!fpIsWow64Process(GetCurrentProcess(), &bResult))
		{
			// handle error
		}
	}
	return bResult;
}
#else
#include <unistd.h>
static size_t get_executable_path(char* processdir, char* processname, size_t len)
{

	char* path_end;
	if (processdir)
	{
		if (readlink("/proc/self/exe", processdir, len) <= 0)

			return -1;

		path_end = strrchr(processdir, '/');

		if (path_end == NULL)

			return -1;

		++path_end;
		if (processname)
			strcpy(processname, path_end);

		*path_end = '\0';

		return (size_t)(path_end - processdir);
	}
	return 0;
}
static uint64_t GetFileLen(const char *fileName)
{
	struct stat st;
	stat(fileName, &st);
	return st.st_size;
}

static void _split_whole_name(const char *whole_name, char *fname, char *ext)
{
	const char *p_ext;

	p_ext = strrchr(whole_name, '.');
	if (NULL != p_ext)
	{
		strcpy(ext, p_ext);
		snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		ext[0] = '\0';
		strcpy(fname, whole_name);
	}
}
static void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	const char *p_whole_name;

	drive[0] = '\0';
	if (NULL == path)
	{
		dir[0] = '\0';
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	if ('/' == path[strlen(path)])
	{
		strcpy(dir, path);
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	p_whole_name = strrchr(path, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		_split_whole_name(p_whole_name, fname, ext);

		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		_split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}
static std::string PathStripFileName(std::string pathname)
{
	std::string Temp;
	char Drv[4096] = { 0 };
	char Dir[4096] = { 0 };
	char FName[4096] = { 0 };
	char Ext[4096] = { 0 };
	_splitpath(pathname.c_str(), Drv, Dir, FName, Ext);
	strcat(Drv, Dir);
	Temp = Drv;
	return Temp;
}
#endif

static inline void StringStripQuote(std::wstring & quotedstring)
{
	if (!quotedstring.empty())
	{
		if (quotedstring.at(0) == L'\"' && quotedstring.at(quotedstring.length() - 1) == L'\"')
		{
			quotedstring = quotedstring.substr(1, quotedstring.length() - 2);
		}
	}
}

#endif //_H_COMMONUTIL
