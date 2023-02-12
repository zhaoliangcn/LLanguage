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


	//首先需要创建命名管道
	//这里创建的是双向模式且使用重叠模式的命名管道
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
	//添加事件以等待客户端连接命名管道
	//该事件为手动重置事件，且初始化状态为无信号状态
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(!hEvent)
	{
		return  ;
	}

	memset(&ovlpd, 0, sizeof(OVERLAPPED));

	//将手动重置事件传递给 ovlap 参数
	ovlpd.hEvent = hEvent;

	//等待客户端连接
	if(!ConnectNamedPipe(hNamedPipe, &ovlpd))
	{
		if(ERROR_IO_PENDING != GetLastError())
		{
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);

			return ;
		}
	}

	//等待事件 hEvent 失败
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
	    //等待连接命名管道
    if(!WaitNamedPipe(PipeName, NMPWAIT_WAIT_FOREVER))
    {       
        return NULL;
    }
 
    //打开命名管道
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
 
    //从命名管道中读取数据
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
