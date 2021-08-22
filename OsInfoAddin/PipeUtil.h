#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
class CPipeUtil
{
public:
	CPipeUtil(void);
	~CPipeUtil(void);

	HANDLE CreateNamedPipeServer(const wchar_t * PipeName);
	void PipeWait(HANDLE hNamedPipe);
	HANDLE OpenNamedPipeClient(const wchar_t * PipeName);
	BOOL WritePipe(HANDLE hNamedPipe,const char * Content,DWORD Length); 
	BOOL ReadPipe(HANDLE hNamedPipe,char * Content,DWORD Length); 
	void ClosePipe(HANDLE hNamedPipe);
};
