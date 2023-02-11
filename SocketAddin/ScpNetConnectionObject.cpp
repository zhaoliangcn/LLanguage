#include "ScpNetConnectionObject.h"
#include "../Common/commonutil.hpp"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/ScpObjectFactory.h"
#include "../ScriptEngineLib/ScpObjectNammes.h"
#include "../ScriptEngineLib/commanddefine_uni.h"

const static char * scpConnectionTypeTCP = "TCP";
const static char * scpConnectionTypeUDP = "UDP";
#ifdef _WIN32
#pragma comment (lib,"ws2_32.lib")
#else
#define INVALID_SOCKET (-1)
#endif 
#include "../ScriptEngineLib/NumberHelp.h"


ScpObject *  __stdcall NetConnectionObjFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	if (paramters->size() == 3)
	{
		ScpObject * netcoon = new ScpNetConnectionObject();
		((ScpNetConnectionObject*)netcoon)->connectionType = paramters->at(2);
		return netcoon;
	}	
}
BOOL WINAPI NetConnection_Shutdown_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 1)
	{
		std::string text = vtparameters->at(0);

		ScpObject *obj = (ScpObject *)currentObjectSpace->FindObject(text);
		if (obj)
		{
			if (obj->GetType() == ObjNetConnection)
			{
				std::string func = scpcommand_en_shutdown;
				((ScpNetConnectionObject*)obj)->CallInnerFunction(func, NULL, engine);
				return TRUE;
			}
		}		
	}
	else if (vtparameters->size() == 2)
	{
		std::string strobj = vtparameters->at(0);
		std::string text = vtparameters->at(1);
		ScpObjectType type = ScpGlobalObject::GetInstance()->GetType(strobj.c_str());
		if (ObjNetConnection == type)
		{
			ScpNetConnectionObject *netconn = (ScpNetConnectionObject*)currentObjectSpace->FindObject(text);
			if (netconn)
			{
				std::string func = scpcommand_en_shutdown;
				((ScpNetConnectionObject*)netconn)->CallInnerFunction(func, NULL, engine);
				return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL WINAPI NetConnection_Connect_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string strobj1 = vtparameters->at(0);
		std::string strobj2 = vtparameters->at(1);
		ScpObject *obj1 = currentObjectSpace->FindObject(strobj1);
		if (obj1)
		{
			if (obj1->GetType() == ObjNetConnection)
			{
				ScpObject *addrobj = currentObjectSpace->FindObject(strobj2);
				if (addrobj->GetType() == ObjAddress)
				{
					std::string func = scpcommand_en_connect;
					VTPARAMETERS param;
					param.push_back(strobj2);
					((ScpNetConnectionObject *)obj1)->CallInnerFunction(func, &param, engine);
					return TRUE;
					//((ScpNetConnectionObject *)obj1)->Connect((ScpAddressObject*)addrobj);
				}
			}
		}
	}
	return FALSE;
}
BOOL WINAPI NetConnection_Send_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string conn = vtparameters->at(0);
		std::string content = vtparameters->at(1);
		ScpNetConnectionObject *connobj = (ScpNetConnectionObject *)currentObjectSpace->FindObject(conn);
		if (connobj)
		{
			//std::string func = scpcommand_en_send;
			//VTPARAMETERS param;
			//param.push_back(content);
			//connobj->CallInnerFunction(func, &param, engine);
			ScpObject  * obj = currentObjectSpace->FindObject(content);
			if(obj)
			{
			if(obj->GetType()==ObjString)
			{
			connobj->Send((ScpStringObject*)obj);
			}
			else if(obj->GetType()==ObjFile)
			{
			connobj->Send((ScpFileObject*)obj);
			}
			else if(obj->GetType()==ObjMemory)
			{
			connobj->Send((ScpMemoryObject*)obj);
			}
			return TRUE;
			}
		}
	}
	return FALSE;
}
BOOL WINAPI NetConnection_Receive_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string conn = vtparameters->at(0);
		std::string content = vtparameters->at(1);
		ScpNetConnectionObject *connobj = (ScpNetConnectionObject *)currentObjectSpace->FindObject(conn);
		if (connobj)
		{
			//std::string func = scpcommand_en_receive;
			//VTPARAMETERS param;
			//param.push_back(content);
			//connobj->CallInnerFunction(func, &param, engine);
			ScpObject  * obj = currentObjectSpace->FindObject(content);
			if(obj)
			{
			if(obj->GetType()==ObjString)
			{
			connobj->Receive((ScpStringObject*)obj);
			}
			else if(obj->GetType()==ObjFile)
			{
			connobj->Receive((ScpFileObject*)obj);
			}
			else if(obj->GetType()==ObjMemory)
			{
			connobj->Receive((ScpMemoryObject*)obj);
			}
			return TRUE;
			}

		}
	}
	return FALSE;
}
BOOL WINAPI NetConnection_Watch_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine)
{
	ScpObjectSpace * currentObjectSpace = engine->GetCurrentObjectSpace();
	if (vtparameters->size() == 2)
	{
		std::string conn = vtparameters->at(0);
		std::string content = vtparameters->at(1);
		ScpNetConnectionObject *connobj = (ScpNetConnectionObject *)currentObjectSpace->FindObject(conn);
		if (connobj)
		{
			//std::string func = scpcommand_en_watch;
			//VTPARAMETERS param;
			//param.push_back(content);
			//((ScpNetConnectionObject *)connobj)->CallInnerFunction(func, &param, engine);
			ScpAddressObject * addrobj=(ScpAddressObject*)currentObjectSpace->FindObject(content);
			if(addrobj)
			{
				connobj->Watch(addrobj);
				return TRUE;
			}			
		}
	}
	return FALSE;
}
ScpNetConnectionObject::ScpNetConnectionObject(void)
{

	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_send, InnerFunction_send);
	BindObjectInnerFuction(scpcommand_en_send, InnerFunction_send);

	BindObjectInnerFuction(scpcommand_cn_receive, InnerFunction_receive);
	BindObjectInnerFuction(scpcommand_en_receive, InnerFunction_receive);


	BindObjectInnerFuction(scpcommand_cn_receive, InnerFunction_watch);
	BindObjectInnerFuction(scpcommand_en_receive, InnerFunction_watch);

	BindObjectInnerFuction(scpcommand_cn_connect, InnerFunction_connect);
	BindObjectInnerFuction(scpcommand_en_connect, InnerFunction_connect);

	BindObjectInnerFuction(scpcommand_cn_shutdown, InnerFunction_shutdown);
	BindObjectInnerFuction(scpcommand_en_shutdown, InnerFunction_shutdown);


#ifdef _WIN32
	_engine = NULL;
	WSADATA wsaData;
	int Ret;
	if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
	{
		std::string text;
		text=STDSTRINGEXT::Format("WSAStartup failed with error %d\n", Ret);
		if(_engine)
		_engine->PrintError(text);

	}	
	sock = NULL;
	nsock = NULL;

#else
    sock = -1;
    nsock = -1;
#endif
	objecttype = ObjNetConnection;
}

ScpNetConnectionObject::~ScpNetConnectionObject(void)
{
#ifdef _WIN32
	if (WSACleanup() == SOCKET_ERROR)
	{
		std::string text;
		text=STDSTRINGEXT::Format("WSACleanup failed with error %d\n", WSAGetLastError());
		if(_engine)
		_engine->PrintError(text);

	}
#endif
}

void ScpNetConnectionObject::Show(CScriptEngine * engine)
{
	LocalAddress.Show(engine);
	RemoteAddress.Show(engine);
	std::string text;
	text=STDSTRINGEXT::Format("%s",connectionType.c_str());
	engine->PrintError(text);
}

int ScpNetConnectionObject::Watch(ScpAddressObject *local)
{
#ifdef _WIN32
	if(sock)
		return -1;
#else 
	if(sock>0)
		return -1;
#endif
	int ret=-1;
	int error;
	
	do
	{
		if(scpConnectionTypeTCP==connectionType)
		{
			struct sockaddr_in salocaladdr;
			salocaladdr.sin_family = AF_INET;
			salocaladdr.sin_addr.s_addr = inet_addr(local->GetIp().c_str());
			salocaladdr.sin_port = htons(local->GetPort());
			struct sockaddr_in saremoteaddr;
#ifdef _WIN32
			int addrlen=sizeof saremoteaddr; 
#else
			socklen_t addrlen=sizeof saremoteaddr;
#endif
#ifdef _WIN32
			if(nsock)
#else
			if(nsock>0)
#endif
			{
				sock=accept(nsock,(struct sockaddr*)&saremoteaddr,&addrlen);
			}
			else
			{
				nsock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	
				if(nsock==INVALID_SOCKET)
				{
#ifdef _WIN32
					error = WSAGetLastError();
#endif

					break;
				}
				ret = bind(nsock,(struct sockaddr*)&salocaladdr,sizeof salocaladdr);
				if(ret==-1)
				{
#ifdef _WIN32
					error = WSAGetLastError();
#endif
					break;
				}
				LocalAddress = *local;
				ret = listen(nsock,0);
				if(ret==-1)
				{
#ifdef _WIN32
					error = WSAGetLastError();
#endif
					break;
				}
				sock=accept(nsock,(struct sockaddr*)&saremoteaddr,&addrlen);


			}
			if(sock==INVALID_SOCKET)
			{
				ret = -1;
			}
			else
			{
				RemoteAddress.ip = inet_ntoa(saremoteaddr.sin_addr);
				char wport[10]={0};
				//_itow_s(ntohs(saremoteaddr.sin_port),wport,10);
				sprintf(wport,"%d",ntohs(saremoteaddr.sin_port));
				RemoteAddress.port = wport;

				//windows 非阻塞
				//ULONG mode=1;
				//ioctlsocket(sock,FIONBIO,&mode);

			}

		}
		else if(scpConnectionTypeUDP==connectionType)
		{
			LocalAddress = *local;
			struct sockaddr_in salocaladdr;
			salocaladdr.sin_family = AF_INET;
			salocaladdr.sin_addr.s_addr = inet_addr(LocalAddress.ip.c_str());
			salocaladdr.sin_port = htons(StringToInt(LocalAddress.port.c_str()));
			sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			ret = bind(sock, (struct sockaddr *)&salocaladdr, sizeof(salocaladdr));
			if(ret==-1)
			{
#ifdef _WIN32
					error = WSAGetLastError();
#endif
				break;
			}
		}
	}
	while(0);
	if(ret==-1)
	{
		
		std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorCannotListening,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
		if(_engine)
		_engine->PrintError(errormessage);
		//engine->PrintError(scpErrorConnectionTimeOut);

	}
	return ret;

}
int ScpNetConnectionObject::Connect(ScpAddressObject * remote)
{

	int ret=0;
	RemoteAddress =  * remote;
	if(scpConnectionTypeTCP==connectionType)
	{
		sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		struct sockaddr_in saremoteaddr;
		saremoteaddr.sin_family = AF_INET;
		saremoteaddr.sin_addr.s_addr = inet_addr(RemoteAddress.GetIp().c_str());
		saremoteaddr.sin_port = htons(RemoteAddress.GetPort());
		ret = connect(sock,(struct sockaddr*)&saremoteaddr,sizeof saremoteaddr);
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	}
	if(ret==-1)
	{
		if(_engine)
			_engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionTimeOut);

	}
	return ret;
}
int ScpNetConnectionObject::Send(ScpStringObject * strsrc)
{
	int len;
	if(scpConnectionTypeTCP==connectionType)
	{
		if(sock)
		{
			std::string content=strsrc->content;
			len =send(sock,(const char * )content.c_str(),content.length(),0);
			if(len==-1)
			{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock,2);
#endif
				sock=NULL;
				
				std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorSendFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
				if (_engine)
					_engine->PrintError(errormessage);
				//engine->PrintError(scpErrorSendFail);

			}
		}
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		if(!sock)
		{
			sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		}
		struct sockaddr_in saremoteaddr;
		saremoteaddr.sin_family = AF_INET;
		saremoteaddr.sin_addr.s_addr = inet_addr(RemoteAddress.ip.c_str());
		saremoteaddr.sin_port = htons(StringToInt(RemoteAddress.port.c_str()));
		//字符串长度大于64K的时候需要分块传输
		std::string content=strsrc->content;
		len=sendto(sock,(const char *)content.c_str(),content.length(),0,(sockaddr*)&saremoteaddr,sizeof saremoteaddr);
	}

	return len;
}
int ScpNetConnectionObject::Send(ScpMemoryObject * memsrc)
{
	if(!memsrc)
	{
		return -1;
	}
	if(memsrc->GetSize()>32*1024)
	{
		return -1;
	}
	int len;
	if(scpConnectionTypeTCP==connectionType)
	{
		if(sock)
		{
			len =send(sock,(char *)memsrc->Address,memsrc->GetSize(),0);
			if(len==-1)
			{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock,2);
#endif
				sock=NULL;
				
				std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorSendFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
				if (_engine)
					_engine->PrintError(errormessage);
				//engine->PrintError(scpErrorSendFail);

			}
		}
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		if(!sock)
		{
			sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		}
		struct sockaddr_in saremoteaddr;
		saremoteaddr.sin_family = AF_INET;
		saremoteaddr.sin_addr.s_addr = inet_addr(RemoteAddress.ip.c_str());
		saremoteaddr.sin_port = htons(StringToInt(RemoteAddress.port.c_str()));
		len=sendto(sock,(char *)memsrc->Address,memsrc->GetSize(),0,(sockaddr*)&saremoteaddr,sizeof saremoteaddr);
	}

	return len;
}
int ScpNetConnectionObject::Receive(ScpMemoryObject * memdst)
{
	if(!memdst)
	{
		return -1;
	}
	int len;
	size_t BufferSize = 1024*32;
	if(scpConnectionTypeTCP==connectionType)
	{
		if(sock)
		{

			char * buffer = new char[BufferSize];
			memset(buffer,0,BufferSize);
			if(buffer)
			{
				if(memdst)
				{
					len =recv(sock,buffer,BufferSize,0);
					if(memdst->Acquare(len))
					{
						memcpy(memdst->Address,buffer,len);
					}										
				}
				delete[] buffer;
			}
			if(len==-1)
			{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock,2);
#endif
				sock=NULL;	
				
				std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorReceiveFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
				if(error==10054)
				{
					if (_engine)
						_engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionClosed);
				}
				else
				{
					if (_engine)
						_engine->PrintError(errormessage);
				}
				//engine->PrintError(scpErrorReceiveFail);

			}
		}
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		//UDP协议一次接收的数据必须小于65535字节
		struct sockaddr_in saremoteaddr;
		char * buffer = new char[BufferSize];
		memset(buffer,0,BufferSize);
#ifdef _WIN32
		int addrlen=sizeof saremoteaddr;
#else
		socklen_t addrlen=sizeof saremoteaddr;
#endif
		if(buffer)
		{
			if(!sock)
			{
				sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			}
			len=recvfrom(sock,buffer,BufferSize,0,(sockaddr*)&saremoteaddr,&addrlen);			
			if(memdst)
			{
				if(memdst->Acquare(len))
				{
					memcpy(memdst->Address,buffer,len);
				}				
			}
			RemoteAddress.ip =inet_ntoa(saremoteaddr.sin_addr);
			char wport[10]={0};
			//_itow_s(ntohs(saremoteaddr.sin_port),wport,10);
			sprintf(wport,"%d",ntohs(saremoteaddr.sin_port));
			RemoteAddress.port = wport;
			delete[] buffer;

		}
	}
	return len;
}
int ScpNetConnectionObject::Receive(ScpStringObject * strdst)
{
	int len;
	size_t BufferSize = 1024*32;
	if(scpConnectionTypeTCP==connectionType)
	{
		if(sock)
		{

			char * buffer = new char[BufferSize+1];
			memset(buffer,0,BufferSize+1);
			if(buffer)
			{
				if(strdst && strdst->GetType()==ObjString)
				{
					len =recv(sock,( char *)buffer,BufferSize,0);
					if(len>0)
					{
						buffer[len]=0;
						strdst->content=std::string(buffer);
					}	
					else
					{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
#endif
					}
				}
				delete[] buffer;
			}
			if(len==-1)
			{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock,2);
#endif
				sock=NULL;
				if(strdst && strdst->GetType()==ObjString)
					strdst->content="";
				
				std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorReceiveFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
				if(error==10054)
				{
					if (_engine)
						_engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionClosed);
				}
				else
				{
					if (_engine)
						_engine->PrintError(errormessage);
				}
				//engine->PrintError(scpErrorReceiveFail);

			}
		}
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		
		struct sockaddr_in saremoteaddr;
		char * buffer = new char[BufferSize+1];
		memset(buffer,0,BufferSize+1);
#ifdef _WIN32
		int addrlen=sizeof saremoteaddr;
#else
		socklen_t addrlen=sizeof saremoteaddr;
#endif
		if(buffer)
		{
			if(!sock)
			{
				sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			}
			len=recvfrom(sock,(char *)buffer,BufferSize,0,(sockaddr*)&saremoteaddr,&addrlen);
			if(strdst && strdst->GetType()==ObjString)
			{
				if(len>0)
				{
					buffer[len]=0;
					strdst->content=buffer;	
				}
				else
				{
					int error ;
#ifdef _WIN32
					error = WSAGetLastError();
#endif
					if(strdst && strdst->GetType()==ObjString)
						strdst->content="";	
					
					std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorReceiveFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
					if(error==10054)
					{
						if (_engine)
							_engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionClosed);
					}
					else
					{
						if (_engine)
							_engine->PrintError(errormessage);
					}
				}
			}
			RemoteAddress.ip = inet_ntoa(saremoteaddr.sin_addr);
			char wport[10]={0};
			//_itow_s(ntohs(saremoteaddr.sin_port),wport,10);
			sprintf(wport,"%d",ntohs(saremoteaddr.sin_port));
			RemoteAddress.port = wport;
			delete[] buffer;

		}
	}
	return len;
}
int ScpNetConnectionObject::Send(ScpFileObject * srcFile)
{
	return Send((ScpObject*)srcFile);
}
int ScpNetConnectionObject::Receive(ScpFileObject *destFile)
{
	return Receive((ScpObject*)destFile);
}
int  ScpNetConnectionObject::Send(ScpObject * srcObj)
{
	if(!srcObj)
	{
		return -1;
	}
	int len;
	if(scpConnectionTypeTCP==connectionType)
	{
		if(sock)
		{
			if(srcObj->GetType()==ObjFile)
			{
				ScpFileObject * FileObj = (ScpFileObject *)srcObj;
				if(FileObj->readall())
				{
					len =send(sock,(const char *)FileObj->content,FileObj->filesize,0);
				}
			}
			if(len==-1)
			{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock,2);
#endif
				sock=NULL;
				
				std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorSendFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
				if (_engine)
					_engine->PrintError(errormessage);
				//engine->PrintError(scpErrorSendFail);

			}
		}
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		if(!sock)
		{
			sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		}
		struct sockaddr_in saremoteaddr;
		saremoteaddr.sin_family = AF_INET;
		saremoteaddr.sin_addr.s_addr = inet_addr(RemoteAddress.ip.c_str());
		saremoteaddr.sin_port = htons(StringToInt(RemoteAddress.port.c_str()));
		if(srcObj->GetType()==ObjFile)
		{
			ScpFileObject * FileObj = (ScpFileObject *)srcObj;
			if(FileObj->readall())
			{
				len=sendto(sock,(const char *)FileObj->content,FileObj->filesize,0,(sockaddr*)&saremoteaddr,sizeof saremoteaddr);
			}
			
		}
		
	}

	return len;
}
int  ScpNetConnectionObject::Receive(ScpObject * destObj)
{
	if(!destObj)
	{
		return -1;
	}
	int len;
	size_t BufferSize = 1024*32;
	if(scpConnectionTypeTCP==connectionType)
	{
		if(sock)
		{

			char * buffer = new char[BufferSize];
			memset(buffer,0,BufferSize);
			if(buffer)
			{				
				len =recv(sock,buffer,BufferSize,0);
				if(len>0)
				{
					if(destObj->GetType()==ObjFile)
					{
						ScpFileObject * FileObj = (ScpFileObject *)destObj;
						FileObj->write(0,len,buffer);
					}	
				}				
				delete[] buffer;
			}
			if(len==-1)
			{
				int error ;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock,2);
#endif
				sock=NULL;		
				
				std::string errormessage = STDSTRINGEXT::Format("%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorReceiveFail,ScpObjectNames::GetSingleInsatnce()->scpErrorCode,error);
				if(error==10054)
				{
					if (_engine)
						_engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionClosed);
				}
				else
				{
					if (_engine)
						_engine->PrintError(errormessage);
				}
				//engine->PrintError(scpErrorReceiveFail);

			}
		}
	}
	else if(scpConnectionTypeUDP==connectionType)
	{
		struct sockaddr_in saremoteaddr;
		char * buffer = new char[BufferSize];
		memset(buffer,0,BufferSize);
#ifdef _WIN32
		int addrlen=sizeof saremoteaddr;
#else
		socklen_t addrlen=sizeof saremoteaddr;
#endif
		if(buffer)
		{
			if(!sock)
			{
				sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			}
			len=recvfrom(sock,buffer,BufferSize,0,(sockaddr*)&saremoteaddr,&addrlen);
			if(destObj->GetType()==ObjFile)
			{
				ScpFileObject * FileObj = (ScpFileObject *)destObj;
				FileObj->write(0, len,FileObj->content);
			}			
			RemoteAddress.ip = inet_ntoa(saremoteaddr.sin_addr);
			char wport[10]={0};
			//_itow_s(ntohs(saremoteaddr.sin_port),wport,10);
			sprintf(wport,"%d",ntohs(saremoteaddr.sin_port));
			RemoteAddress.port = wport;
			delete[] buffer;

		}
	}
	return len;
}
ScpObject * ScpNetConnectionObject::Clone(std::string strObjName)
{
	ScpNetConnectionObject * obj = new ScpNetConnectionObject;
	if (obj)
	{
		obj->LocalAddress = LocalAddress;
		obj->RemoteAddress = RemoteAddress;
		obj->connectionType = connectionType;
		return obj;
	}
	return NULL;
}	
std::string ScpNetConnectionObject::ToString()
{
	std::string temp;

	temp = LocalAddress.ToString();
	temp +=RemoteAddress.ToString();
	temp +=connectionType;

	return temp;
}
void ScpNetConnectionObject::Release() 
{
	delete this;
}
bool ScpNetConnectionObject::IsInnerFunction(std::string & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpNetConnectionObject::CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	ScpObjectNames::GetSingleInsatnce()->SelectLanguage(engine->GetLanguge());

	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}	
	return NULL;
}
int ScpNetConnectionObject::DisConnect()
{
	
	int ret =0;
	if(sock)
	{
#ifdef WIN32
		ret =  closesocket(sock);
		#else
		ret = close(sock);
		#endif
		sock=NULL;
	}	
	if(nsock)
	{
		ret = shutdown(nsock,2);
		#ifdef WIN32
		ret =  closesocket(nsock);
		#else
		ret = close(nsock);
		#endif
		nsock=NULL;
	}
	return ret;
}

ScpObject * ScpNetConnectionObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpNetConnectionObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string param0 = parameters->at(0);
		StringStripQuote(param0);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(param0);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			if (((ScpStringObject *)objparam0)->content == str_EN_ObjType ||
				((ScpStringObject *)objparam0)->content == str_CN_ObjType)
			{
				ScpStringObject * tname = (ScpStringObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjString);
				tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
				tname->istemp = true;
				return tname;
			}
		}
		if (parameters->at(0) == str_EN_ObjType || parameters->at(0) == str_CN_ObjType)
		{
			ScpStringObject * tname = new ScpStringObject;
			tname->content = engine->extend_obj_mgr.GetExtendObjectName(thisObject->GetType());
			tname->istemp = true;
			return tname;
		}
	}
	return nullptr;
}

ScpObject * ScpNetConnectionObject::InnerFunction_send(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpObject * addrobj = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (addrobj && addrobj->GetType() == ObjString)
		{
			ScpIntObject * obj = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Send((ScpStringObject *)addrobj);
			return obj;
		}
		else if (addrobj && addrobj->GetType() == ObjMemory)
		{
			ScpIntObject * obj = (ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Send((ScpMemoryObject *)addrobj);
			return obj;
		}
		else if (addrobj && addrobj->GetType() == ObjFile)
		{
			ScpIntObject * obj = (ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Send((ScpFileObject *)addrobj);
			return obj;
		}
	}
	return nullptr;
}

ScpObject * ScpNetConnectionObject::InnerFunction_receive(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpStringObject * addrobj = (ScpStringObject *)engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (addrobj && addrobj->GetType() == ObjString)
		{
			ScpIntObject * obj = (ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Receive((ScpStringObject *)addrobj);
			return obj;
		}
		else if (addrobj && addrobj->GetType() == ObjMemory)
		{
			ScpIntObject * obj = (ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Receive((ScpMemoryObject *)addrobj);
			return obj;
		}
		else if (addrobj && addrobj->GetType() == ObjFile)
		{
			ScpIntObject * obj = (ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Receive((ScpFileObject *)addrobj);
			return obj;
		}
	}
	return nullptr;
}

ScpObject * ScpNetConnectionObject::InnerFunction_watch(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpAddressObject * addrobj = (ScpAddressObject *)engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (addrobj && addrobj->GetType() == ObjAddress)
		{
			ScpIntObject * obj = (ScpIntObject *)(ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Watch(addrobj);
			return obj;
		}
	}
	return nullptr;
}

ScpObject * ScpNetConnectionObject::InnerFunction_connect(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::string wsparam = parameters->at(0);
		StringStripQuote(wsparam);
		ScpAddressObject * addrobj = (ScpAddressObject *)engine->GetCurrentObjectSpace()->FindObject(wsparam);
		if (addrobj && addrobj->GetType() == ObjAddress)
		{
			ScpIntObject * obj = (ScpIntObject *)(ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
			obj->value = ((ScpNetConnectionObject*)thisObject)->Connect(addrobj);
			return obj;
		}
	}
	return nullptr;
}

ScpObject * ScpNetConnectionObject::InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	ScpIntObject * obj = (ScpIntObject *)(ScpIntObject*)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
	obj->value = ((ScpNetConnectionObject*)thisObject)->DisConnect();
	return obj;

}
