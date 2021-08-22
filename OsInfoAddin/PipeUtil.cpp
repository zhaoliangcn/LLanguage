#include "PipeUtil.h"

CPipeUtil::CPipeUtil(void)
{
}

CPipeUtil::~CPipeUtil(void)
{
}

HANDLE CPipeUtil::CreateNamedPipeServer(const wchar_t * PipeName)
{
	HANDLE            hNamedPipe;



	hNamedPipe = CreateNamedPipe(PipeName, 
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, 
		0, 1, 1024, 1024, 0, NULL);

	if(INVALID_HANDLE_VALUE == hNamedPipe)
	{
		hNamedPipe = NULL;
		return NULL;
	}
	return hNamedPipe;
}
void CPipeUtil::PipeWait(HANDLE hNamedPipe)
{
		HANDLE                    hEvent;
	OVERLAPPED                ovlpd;

	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(!hEvent)
	{
		return  ;
	}

	memset(&ovlpd, 0, sizeof(OVERLAPPED));


	ovlpd.hEvent = hEvent;


	if(!ConnectNamedPipe(hNamedPipe, &ovlpd))
	{
		if(ERROR_IO_PENDING != GetLastError())
		{
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);

			return ;
		}
	}


	if(WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE))
	{
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);

		return;
	}

	CloseHandle(hEvent);
}
HANDLE CPipeUtil::OpenNamedPipeClient(const wchar_t * PipeName)
{
	HANDLE            hNamedPipe;

    if(!WaitNamedPipe(PipeName, NMPWAIT_WAIT_FOREVER))
    {       
        return NULL;
    }
 

    hNamedPipe = CreateFile(PipeName, GENERIC_READ | GENERIC_WRITE, 
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(INVALID_HANDLE_VALUE == hNamedPipe)
    {       
        return NULL;
    }
	return hNamedPipe;
}
BOOL CPipeUtil::WritePipe(HANDLE hNamedPipe,const char * Content,DWORD Length)
{
	BOOL ret = TRUE;
	DWORD            dwWrite;
    if(!WriteFile(hNamedPipe, Content, Length, &dwWrite, NULL))
    {
        ret = FALSE;
    }
	return ret;
}
BOOL CPipeUtil::ReadPipe(HANDLE hNamedPipe,char * Content,DWORD Length)
{

	BOOL ret = TRUE;
	DWORD            dwRead;
    memset((void *)Content, 0, Length);
 

    if(!ReadFile(hNamedPipe, (LPVOID)Content, Length, &dwRead, NULL))
    {
        ret = FALSE;
    }
	return ret;
}
void CPipeUtil::ClosePipe(HANDLE hNamedPipe)
{
	CloseHandle(hNamedPipe);
}
