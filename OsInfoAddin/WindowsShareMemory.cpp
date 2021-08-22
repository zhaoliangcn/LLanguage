
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "windowsSharememory.h"

LPCWSTR	ParseNameW(LPCWSTR	lpszFullPath)
{
	if (NULL == lpszFullPath) return NULL;

	LPCWSTR	lpBackSlashPos = wcsrchr(lpszFullPath,'\\');
	LPCWSTR	lpSlashPos = wcsrchr(lpszFullPath,'/');

	if (NULL == lpBackSlashPos && NULL ==lpSlashPos) return lpszFullPath;

	if (NULL != lpBackSlashPos)		lpBackSlashPos++;
	if (NULL != lpSlashPos)		lpSlashPos++;
	return (lpBackSlashPos > lpSlashPos)?lpBackSlashPos:lpSlashPos;
}
WindowsShareMemory::WindowsShareMemory(size_t BufferSize):BUF_SIZE(BufferSize)
{
	hMapFile = NULL;
	pShareMemoryAddress = NULL;

	SecAttr.nLength = sizeof(SecAttr);
	SecAttr.bInheritHandle = FALSE;
	SecAttr.lpSecurityDescriptor = &SecDesc;

	InitializeSecurityDescriptor(&SecDesc, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&SecDesc, TRUE, 0, FALSE);
	ghMutex = CreateMutex( 
		&SecAttr,  
		FALSE, 
		L"Global\\BasicMutex"); 

	if (ghMutex == NULL) 
	{
		//printf("CreateMutex error: %d\n", GetLastError());
		return;
	}

}
WindowsShareMemory::~WindowsShareMemory()
{
	if(pShareMemoryAddress)
	{
		UnmapViewOfFile(pShareMemoryAddress);
	}
	if(hMapFile!=NULL && hMapFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hMapFile);
	}	
}
int WindowsShareMemory::OpenShareMemory(const wchar_t *szName)
{	
	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		szName);
	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not open file mapping object (%d).\n"),	GetLastError());
		return 1;
	}
	pShareMemoryAddress = MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);
	if (pShareMemoryAddress == NULL)
	{
		//_tprintf(TEXT("Could not map view of file (%d).\n"),GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}	
	return 0;
}
int WindowsShareMemory::CreateShareMemory(const wchar_t *szName)
{
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		&SecAttr,  
		PAGE_READWRITE, 
		0,  
		BUF_SIZE, 
		szName);

	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not create file mapping object (%d).\n"),GetLastError());
		return 1;
	}
	pShareMemoryAddress = MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS, 
		0,
		0,
		BUF_SIZE);
	if (pShareMemoryAddress == NULL)
	{
		//_tprintf(TEXT("Could not map view of file (%d).\n"),GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}
	return 0;
}
void * WindowsShareMemory::GetShareMemoryAddress()
{
	if(hMapFile!=NULL && 
		hMapFile!=INVALID_HANDLE_VALUE &&
		pShareMemoryAddress!=NULL)
	{
		return pShareMemoryAddress;
	}
	return NULL;
}
void WindowsShareMemory::Lock()
{
	WaitForSingleObject( 
		ghMutex,
		INFINITE);
}
void WindowsShareMemory::UnLock()
{
	ReleaseMutex(ghMutex);
}
int WindowsShareMemory::ReadShareMemory(void * pBuffer,DWORD dwReadPos,DWORD dwReadCount)
{
	if((dwReadPos+dwReadCount)>=BUF_SIZE)
	{
		return 1;
	}
	Lock();
	void * pAddr = GetShareMemoryAddress();
	if(pAddr)
	{
		memcpy(pBuffer,(unsigned char *)pAddr+dwReadPos,dwReadCount);
	}
	UnLock();
	return 0;
}
int WindowsShareMemory::WriteShareMemory(void * pBuffer,DWORD dwWritePos,DWORD dwWriteCount)
{
	if((dwWritePos+dwWriteCount)>=BUF_SIZE)
	{
		return 1;
	}
	Lock();
	void * pAddr = GetShareMemoryAddress();
	if(pAddr)
	{
		memcpy((unsigned char *)pAddr+dwWritePos,pBuffer,dwWriteCount);
	}
	UnLock();
	return 0;
}

WindowsFileShareMemory::WindowsFileShareMemory(size_t BufferSize):BUF_SIZE(BufferSize)
{
	hFile = NULL;
	hMapFile = NULL;
	pFileShareMemoryAddress = NULL;
	SecAttr.nLength = sizeof(SecAttr);
	SecAttr.bInheritHandle = FALSE;
	SecAttr.lpSecurityDescriptor = &SecDesc;

	InitializeSecurityDescriptor(&SecDesc, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&SecDesc, TRUE, 0, FALSE);
}
WindowsFileShareMemory::~WindowsFileShareMemory()
{
	if(pFileShareMemoryAddress)
	{
		UnmapViewOfFile(pFileShareMemoryAddress);
	}
	if(hMapFile!=NULL && hMapFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hMapFile);
	}	
	if(hFile!=NULL && hFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}	
}
int WindowsFileShareMemory::OpenFileShareMemory(const wchar_t *szFilePathName)
{	
	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		ParseNameW(szFilePathName));
	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not open file mapping object (%d).\n"),GetLastError());
		return 1;
	}
	pFileShareMemoryAddress = MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);
	if (pFileShareMemoryAddress == NULL)
	{
		//_tprintf(TEXT("Could not map view of file (%d).\n"),	GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}
	std::wstring wsGlobalMutexName=L"Global\\";
	wsGlobalMutexName+=ParseNameW(szFilePathName);
	ghMutex = CreateMutex( 
		&SecAttr,
		FALSE,
		wsGlobalMutexName.c_str());

	if (ghMutex == NULL) 
	{
		//printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}
	return 0;
}
int WindowsFileShareMemory::CreateFileShareMemory(const wchar_t *szFilePathName)
{
	hFile = CreateFile(szFilePathName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, 
		NULL,
		OPEN_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	if(INVALID_HANDLE_VALUE==hFile)
	{
		return 1;
	}
	void * pBuffer=malloc(BUF_SIZE);
	if(!pBuffer)
	{
		return 1;
	}
	memset(pBuffer,0,BUF_SIZE);	
	DWORD dwWriteCount=0;
	WriteFile(hFile,pBuffer,BUF_SIZE,&dwWriteCount,NULL);
	free(pBuffer);
	hMapFile = CreateFileMapping(
		hFile,
		&SecAttr,
		PAGE_READWRITE,
		0,
		0,
		ParseNameW(szFilePathName));

	if (hMapFile == NULL)
	{
		//_tprintf(TEXT("Could not create file mapping object (%d).\n"),GetLastError());
		return 1;
	}
	pFileShareMemoryAddress = MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);
	if (pFileShareMemoryAddress == NULL)
	{
		//_tprintf(TEXT("Could not map view of file (%d).\n"),	GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}
	std::wstring wsGlobalMutexName=L"Global\\";
	wsGlobalMutexName+=ParseNameW(szFilePathName);
	ghMutex = CreateMutex( 
		&SecAttr, 
		FALSE, 
		wsGlobalMutexName.c_str());

	if (ghMutex == NULL) 
	{
		//printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}
	return 0;
}
void * WindowsFileShareMemory::GetFileShareMemoryAddress()
{
	if(hMapFile!=NULL && 
		hMapFile!=INVALID_HANDLE_VALUE &&
		pFileShareMemoryAddress!=NULL)
	{
		return pFileShareMemoryAddress;
	}
	return NULL;
}
void WindowsFileShareMemory::Lock()
{
	WaitForSingleObject( 
		ghMutex,
		INFINITE);
}
void WindowsFileShareMemory::UnLock()
{
	ReleaseMutex(ghMutex);
}
int WindowsFileShareMemory::ReadFileShareMemory(void * pBuffer,DWORD dwReadPos,DWORD dwReadCount)
{
	if((dwReadPos+dwReadCount)>=BUF_SIZE)
	{
		return 1;
	}
	Lock();
	void * pAddr = GetFileShareMemoryAddress();
	if(pAddr)
	{
		memcpy(pBuffer,(unsigned char *)pAddr+dwReadPos,dwReadCount);
	}
	UnLock();
	return 0;
}
int WindowsFileShareMemory::WriteFileShareMemrory(void * pBuffer,DWORD dwWritePos,DWORD dwWriteCount)
{
	if((dwWritePos+dwWriteCount)>=BUF_SIZE)
	{
		return 1;
	}
	Lock();
	void * pAddr = GetFileShareMemoryAddress();
	if(pAddr)
	{
		memcpy((unsigned char *)pAddr+dwWritePos,pBuffer,dwWriteCount);
	}
	UnLock();
	return 0;
}
