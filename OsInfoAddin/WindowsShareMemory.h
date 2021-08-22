#include <windows.h>
#include <string>

class WindowsShareMemory
{
public:
	explicit WindowsShareMemory(size_t BufferSize);
	~WindowsShareMemory();
	int OpenShareMemory(const wchar_t * szName);
	int CreateShareMemory(const wchar_t * szName);
	void * GetShareMemoryAddress();
	int ReadShareMemory(void * pBuffer,DWORD dwReadPos,DWORD dwReadCount);
	int WriteShareMemory(void * pBuffer,DWORD dwWritePos,DWORD dwWriteCount);
	void Lock();
	void UnLock();
private:
	void * pShareMemoryAddress;
	HANDLE hMapFile;
	size_t BUF_SIZE;
	HANDLE ghMutex; 
	SECURITY_ATTRIBUTES SecAttr;
	SECURITY_DESCRIPTOR SecDesc;	

};

class WindowsFileShareMemory
{
public:
	explicit WindowsFileShareMemory(size_t BufferSize);  
	~WindowsFileShareMemory();
	int OpenFileShareMemory(const wchar_t * szFilePathName);
	int CreateFileShareMemory(const wchar_t * szFilePathName);
	int ReadFileShareMemory(void * pBuffer,DWORD dwReadPos,DWORD dwReadCount);
	int WriteFileShareMemrory(void * pBuffer,DWORD dwWritePos,DWORD dwWriteCount);
	void * GetFileShareMemoryAddress();	
	void Lock();
	void UnLock();
private:
	void * pFileShareMemoryAddress;
	HANDLE hFile;
	HANDLE hMapFile;
	HANDLE ghMutex; 
	std::wstring wsMutex;
	SECURITY_ATTRIBUTES SecAttr;
	SECURITY_DESCRIPTOR SecDesc;
	size_t BUF_SIZE;
};