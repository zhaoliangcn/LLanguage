#include "ScpSocketObject.h"
#include "../ScriptEngineLib/ScriptEngine.h"
#include "../ScriptEngineLib/ScpStringObject.h"
#include "../ScriptEngineLib/ScpMemoryObject.h"
#include "../ScriptEngineLib/ScpFileObject.h"
#include "../ScriptEngineLib/ScpObjectNammes.h"
#include "../ScriptEngineLib/commanddefine_uni.h"
#include "../Common/commonutil.hpp"

#ifdef _WIN32
#pragma comment (lib,"ws2_32.lib")
#else
#define INVALID_SOCKET (-1)
#define wcsicmp wcscasecmp
#endif
ScpObject *  __stdcall SocketObjFactory(VTPARAMETERS * paramters, CScriptEngine * engine)
{
	ScpObject * obj = new ScpSocketObject();
	return obj;
}
ScpSocketObject::ScpSocketObject(void):sock(0),_engine(NULL)
{
	objecttype = ObjSocket;




	BindObjectInnerFuction(scpcommand_en_show, InnerFunction_Show);
	BindObjectInnerFuction(scpcommand_cn_show, InnerFunction_Show);

	BindObjectInnerFuction(scpcommand_cn_get, InnerFunction_Get);
	BindObjectInnerFuction(scpcommand_en_get, InnerFunction_Get);

	BindObjectInnerFuction(scpcommand_cn_set, InnerFunction_set);
	BindObjectInnerFuction(scpcommand_cn_set, InnerFunction_set);

	BindObjectInnerFuction(scpcommand_cn_send, InnerFunction_send);
	BindObjectInnerFuction(scpcommand_en_send, InnerFunction_send);

	BindObjectInnerFuction(scpcommand_cn_watch, InnerFunction_watch);
	BindObjectInnerFuction(scpcommand_en_watch, InnerFunction_watch);

	BindObjectInnerFuction(scpcommand_cn_receive, InnerFunction_receive);
	BindObjectInnerFuction(scpcommand_en_receive, InnerFunction_receive);

	BindObjectInnerFuction(scpcommand_cn_bind, InnerFunction_bind);
	BindObjectInnerFuction(scpcommand_en_bind, InnerFunction_bind);

	BindObjectInnerFuction(scpcommand_cn_connect, InnerFunction_connect);
	BindObjectInnerFuction(scpcommand_en_connect, InnerFunction_connect);

	BindObjectInnerFuction(scpcommand_cn_create, InnerFunction_create);
	BindObjectInnerFuction(scpcommand_en_create, InnerFunction_create);

	BindObjectInnerFuction(scpcommand_cn_shutdown, InnerFunction_shutdown);
	BindObjectInnerFuction(scpcommand_en_shutdown, InnerFunction_shutdown);
	
	BindObjectInnerFuction(scpcommand_cn_listen, InnerFunction_listen);
	BindObjectInnerFuction(scpcommand_en_listen, InnerFunction_listen);

	BindObjectInnerFuction(scpcommand_cn_accept, InnerFunction_accept);
	BindObjectInnerFuction(scpcommand_en_accept, InnerFunction_accept);


#ifdef _WIN32
	WSADATA wsaData;
	int Ret;
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		std::wstring text;
		text = STDSTRINGEXT::Format(L"WSAStartup failed with error %d\n", Ret);
		if(_engine)
			_engine->PrintError(text);

	}
	sock = NULL;
#else
	sock = -1;
#endif
}

ScpSocketObject::~ScpSocketObject(void)
{
	int error=0;
#ifdef _WIN32
	error = WSAGetLastError();
	if(sock)
	{
		closesocket(sock);
	}
	if (WSACleanup() == SOCKET_ERROR)
	{
		std::wstring text;
		text = STDSTRINGEXT::Format(L"WSACleanup failed with error %d\n", WSAGetLastError());
		if(_engine)
			_engine->PrintError(text);
	}
#else
	if(sock)
	{
		shutdown(sock,2);
	}
#endif
}


void ScpSocketObject::Show(CScriptEngine * engine)  
{
	engine->PrintError(L"SOCKET OBJECT EXT");
}
ScpObject * ScpSocketObject::Clone(std::wstring strObjName)
{
	ScpSocketObject * obj = new ScpSocketObject;
	if (obj)
	{
		obj->address = address;
		obj->remoteAddress = remoteAddress;
		obj->connectionType = connectionType;
		return obj;
	}
	return NULL;
}
std::wstring ScpSocketObject::ToString()
{
	return std::wstring();
}
void ScpSocketObject::Release() 
{
	delete this;
}
bool ScpSocketObject::IsInnerFunction(std::wstring & functionname)
{
	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		return true;
	}
	return false;
}
ScpObject * ScpSocketObject::CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine)
{
	_engine = engine;
	ScpObjectNames::GetSingleInsatnce()->SelectLanguage(engine->GetLanguge());

	if (ObjectInnerFunctions.find(functionname) != ObjectInnerFunctions.end())
	{
		ObjectInnerFunction func = ObjectInnerFunctions[functionname];
		return func(this, parameters, engine);
	}
	return NULL;
}
int ScpSocketObject::Send(std::string & content,CScriptEngine * engine)
{
	int len=-1;
	if(sock && sock!=INVALID_SOCKET)
	{
		if (scpConnectionTypeTCP == connectionType)
		{
			len = send(sock, (const char *)content.c_str(), content.length(), 0);
		}
		else if (scpConnectionTypeUDP == connectionType)
		{
			struct sockaddr_in saremoteaddr;
			saremoteaddr.sin_family = AF_INET;
			saremoteaddr.sin_addr.s_addr = inet_addr(STDSTRINGEXT::WToA(remoteAddress.GetIp()).c_str());
			saremoteaddr.sin_port = htons(remoteAddress.GetPort());
			//�ַ������ȴ���64K��ʱ����Ҫ�ֿ鴫��
			len = sendto(sock, (const char *)content.c_str(), content.length(), 0, (sockaddr*)&saremoteaddr, sizeof saremoteaddr);
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
			sock = 0;
			
			std::wstring errormessage = STDSTRINGEXT::Format(L"%s%s%d",ScpObjectNames::GetSingleInsatnce()->scpErrorSendFail.c_str(),ScpObjectNames::GetSingleInsatnce()->scpErrorCode.c_str(),error);
			engine->PrintError(errormessage);
			//engine->PrintError(scpErrorSendFail);

		}
	}	
	return len;
}
int ScpSocketObject::Send(ScpObject * contentobj, CScriptEngine * engine)
{
	int len = -1;
	if (sock && sock != INVALID_SOCKET)
	{
		if (contentobj && contentobj->GetType() == ObjMemory)
		{
			ScpMemoryObject * mem = (ScpMemoryObject *)contentobj;

			if (scpConnectionTypeTCP == connectionType)
			{
				len = send(sock, (const char *)mem->Address, mem->GetSize(), 0);
			}
			else if (scpConnectionTypeUDP == connectionType)
			{
				struct sockaddr_in saremoteaddr;
				saremoteaddr.sin_family = AF_INET;
				saremoteaddr.sin_addr.s_addr = inet_addr(STDSTRINGEXT::WToA(remoteAddress.GetIp()).c_str());
				saremoteaddr.sin_port = htons(remoteAddress.GetPort());
				//�ַ������ȴ���64K��ʱ����Ҫ�ֿ鴫��
				len = sendto(sock, (const char *)mem->Address, mem->GetSize(), 0, (sockaddr*)&saremoteaddr, sizeof saremoteaddr);
			}
			if (len == -1)
			{
				int error;
#ifdef _WIN32
				error = WSAGetLastError();
				closesocket(sock);
#else
				shutdown(sock, 2);
#endif
				sock = 0;

				std::wstring errormessage = STDSTRINGEXT::Format(L"%s%s%d", ScpObjectNames::GetSingleInsatnce()->scpErrorSendFail.c_str(), ScpObjectNames::GetSingleInsatnce()->scpErrorCode.c_str(), error);
				engine->PrintError(errormessage);
				//engine->PrintError(scpErrorSendFail);

			}

		}
		
	}
	return len;
}
int ScpSocketObject::Send(std::wstring & content,CScriptEngine * engine)
{
	int len=-1;
	std::wstring text = STDSTRINGEXT::Format(L"SOCKET OBJECT SEND CONTENT %s",content.c_str());
	engine->PrintError(text);
	std::string realcontent;
	ScpObject * obj =engine->GetCurrentObjectSpace()->FindObject(content);
	if(obj)
	{
		realcontent=STDSTRINGEXT::WToA(((ScpStringObject*)obj)->content);
	}
	else
	{
		realcontent = STDSTRINGEXT::WToA(content);
	}	
	len=Send(realcontent,engine);
	return len;
}
int ScpSocketObject::Bind(ScpObject *  addrobj,CScriptEngine * engine)
{
	ScpAddressObject * local = (ScpAddressObject *) addrobj;
	int ret = -1;
	if (scpConnectionTypeTCP == connectionType)
	{
		struct sockaddr_in salocaladdr;
		salocaladdr.sin_family = AF_INET;
		salocaladdr.sin_addr.s_addr = inet_addr(STDSTRINGEXT::WToA(local->GetIp()).c_str());
		salocaladdr.sin_port = htons(local->GetPort());

		ret = bind(sock, (struct sockaddr*)&salocaladdr, sizeof salocaladdr);
	}
	else
	{
		struct sockaddr_in salocaladdr;
		salocaladdr.sin_family = AF_INET;
		salocaladdr.sin_addr.s_addr = inet_addr(STDSTRINGEXT::WToA(local->GetIp()).c_str());
		salocaladdr.sin_port = htons(local->GetPort());
		ret = bind(sock, (struct sockaddr *)&salocaladdr, sizeof(salocaladdr));
	}
	if(ret==-1)
	{
#ifdef _WIN32
		int error = WSAGetLastError();
		std::wstring errormessage = STDSTRINGEXT::Format(L"Error of bind %d", error);
		engine->PrintError(errormessage);
#endif
	}


	address = *local;	
	return ret;
}
int ScpSocketObject::Bind(std::wstring addrobjname,CScriptEngine * engine)
{
	int ret = -1;
	ScpObject * obj=engine->GetCurrentObjectSpace()->FindObject(addrobjname);
	if(obj && obj->GetType()==ObjAddress)
	{
		ret =Bind(obj,engine);
	}
	return ret;

}
int ScpSocketObject::Receive(ScpObject * contentobj,CScriptEngine *engine)
{
	int len=-1;
	ScpStringObject * contentstr=(ScpStringObject * )contentobj;
	ScpMemoryObject * contentmemory = (ScpMemoryObject*)contentobj;
	if(contentobj && contentobj->GetType()==ObjString)
	{
		
		size_t BufferSize = 1024*32;
		if(sock && sock!=INVALID_SOCKET)
		{
			char * buffer = new char[BufferSize+1];
			memset(buffer,0,BufferSize+1);
			if(buffer)
			{
				if (scpConnectionTypeTCP == connectionType)
				{
					do
					{
						len = recv(sock, (char *)buffer, BufferSize, 0);
						buffer[len] = 0;
						contentstr->content = STDSTRINGEXT::AToW(std::string(buffer));
					} while (0);

					int error;
#ifdef _WIN32
					error = WSAGetLastError();
					std::wstring errormessage = STDSTRINGEXT::Format(L"Error of receive %d", error);
					engine->PrintError(errormessage);
#endif					
					
					if (len == -1)
					{
#ifdef _WIN32
						error = WSAGetLastError();
						closesocket(sock);
#else
						shutdown(sock, 2);
#endif
						sock = 0;
						contentstr->content = L"";
						std::wstring errormessage = STDSTRINGEXT::Format(L"%s%s%d", ScpObjectNames::GetSingleInsatnce()->scpErrorReceiveFail.c_str(), ScpObjectNames::GetSingleInsatnce()->scpErrorCode.c_str(), error);
						if (error == 10054)
						{
							engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionClosed);
						}
						else
						{
							engine->PrintError(errormessage);
						}
						//engine->PrintError(scpErrorReceiveFail);
					}
				}
				else if (scpConnectionTypeUDP == connectionType)
				{
					//UDPЭ��һ�ν��յ����ݱ���С��65535�ֽ�
					struct sockaddr_in saremoteaddr;
#ifdef _WIN32
					int addrlen = sizeof saremoteaddr;
#else
					socklen_t addrlen = sizeof saremoteaddr;
#endif
					len = recvfrom(sock, buffer, BufferSize, 0, (sockaddr*)&saremoteaddr, &addrlen);
					if (len > 0)
					{
						buffer[len] = 0;
						contentstr->content = STDSTRINGEXT::AToW(std::string(buffer));
					}
					remoteAddress.ip = STDSTRINGEXT::AToW(inet_ntoa(saremoteaddr.sin_addr));
					wchar_t wport[10] = { 0 };
					swprintf(wport, 10, L"%d", ntohs(saremoteaddr.sin_port));
					remoteAddress.port = wport;					
				}

				delete[] buffer;
			}
		}
	}
	else if (contentobj && contentobj->GetType() == ObjMemory)
	{

		size_t BufferSize = 1024 * 32;
		
		if (sock && sock != INVALID_SOCKET)
		{
			char * buffer = new char[BufferSize + 1];
			memset(buffer, 0, BufferSize + 1);
			if (buffer)
			{
				if (scpConnectionTypeTCP == connectionType)
				{
					do
					{
						len = recv(sock, (char *)buffer, BufferSize, 0);
						if (len > 0)
						{

							buffer[len] = 0;							
							ULONG pos = contentmemory->GetSize();
							contentmemory->Extend(len);
							contentmemory->Write(buffer, pos,len);
						}
						
					} while (0);

					int error;
#ifdef _WIN32
					error = WSAGetLastError();
					std::wstring errormessage = STDSTRINGEXT::Format(L"Error of receive %d", error);
					engine->PrintError(errormessage);
#endif					
					
					if (len == -1)
					{
#ifdef _WIN32
						error = WSAGetLastError();
						closesocket(sock);
#else
						shutdown(sock, 2);
#endif
						sock = 0;
						std::wstring errormessage = STDSTRINGEXT::Format(L"%s%s%d", ScpObjectNames::GetSingleInsatnce()->scpErrorReceiveFail.c_str(), ScpObjectNames::GetSingleInsatnce()->scpErrorCode.c_str(), error);
						if (error == 10054)
						{
							engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorConnectionClosed);
						}
						else
						{
							engine->PrintError(errormessage);
						}
						//engine->PrintError(scpErrorReceiveFail);
					}
				}
				else if (scpConnectionTypeUDP == connectionType)
				{
					//UDPЭ��һ�ν��յ����ݱ���С��65535�ֽ�
					struct sockaddr_in saremoteaddr;
#ifdef _WIN32
					int addrlen = sizeof saremoteaddr;
#else
					socklen_t addrlen = sizeof saremoteaddr;
#endif
					len = recvfrom(sock, buffer, BufferSize, 0, (sockaddr*)&saremoteaddr, &addrlen);
					if (len > 0)
					{
						buffer[len] = 0;						
						ULONG pos = contentmemory->GetSize();
						contentmemory->Extend(len);
						contentmemory->Write(buffer, pos, len);
					}
					remoteAddress.ip = STDSTRINGEXT::AToW(inet_ntoa(saremoteaddr.sin_addr));
					wchar_t wport[10] = { 0 };
					swprintf(wport, 10, L"%d", ntohs(saremoteaddr.sin_port));
					remoteAddress.port = wport;
				}

				delete[] buffer;
			}
		}
	}
	return len;
}
int ScpSocketObject::Receive(std::wstring contentobj,CScriptEngine *engine)
{
	int len=-1;
	ScpObject * obj=engine->GetCurrentObjectSpace()->FindObject(contentobj);
	len=Receive(obj,engine);	
	return len;
}
int  ScpSocketObject::Accept(ScpObject * sockobj,CScriptEngine *engine)
{
	int ret = -1;
	struct sockaddr_in saremoteaddr;
#ifdef _WIN32
		int addrlen=sizeof saremoteaddr; 
#else
		socklen_t addrlen=sizeof saremoteaddr;
#endif
		ScpSocketObject * connsock=(ScpSocketObject * )sockobj;
		connsock->sock=	accept(sock,(struct sockaddr*)&saremoteaddr,&addrlen);
		if(connsock->sock!=INVALID_SOCKET)
		{
			connsock->connectionType = L"TCP";
			ret=0;
		}
		return ret;
}
int ScpSocketObject::Accept(std::wstring sockobjname,CScriptEngine *engine)
{
	int ret = -1;
	ScpSocketObject * connsock=(ScpSocketObject * )engine->GetCurrentObjectSpace()->FindObject(sockobjname);
	if(connsock)
	{
		ret =Accept(connsock,engine);
	}
	return ret;
}
int  ScpSocketObject::Listen(CScriptEngine * engine)
{
	int ret = -1;
	std::wstring text ;
	std::wstring ip=address.GetIp();
	int port =address.GetPort();
	ret = listen(sock,0);
	text = STDSTRINGEXT::Format(L"SOCKET OBJECT Listen addr %s %d",ip.c_str(),port);	
	engine->PrintError(text);	
	return ret;
}
int ScpSocketObject::Connect(std::wstring addrobjname,CScriptEngine * engine)
{
	int ret=0;
	ScpAddressObject * RemoteAddress=(ScpAddressObject *)engine->GetCurrentObjectSpace()->FindObject(addrobjname);
	if (RemoteAddress)
	{
		remoteAddress = *RemoteAddress;
		if (scpConnectionTypeTCP == connectionType)
		{
			struct sockaddr_in saremoteaddr;
			saremoteaddr.sin_family = AF_INET;
			saremoteaddr.sin_addr.s_addr = inet_addr(STDSTRINGEXT::WToA(RemoteAddress->GetIp()).c_str());
			saremoteaddr.sin_port = htons(RemoteAddress->GetPort());
			ret = connect(sock, (struct sockaddr*)&saremoteaddr, sizeof saremoteaddr);
		}

	}
	return ret;
}
int ScpSocketObject::Create(std::wstring type)
{
	int ret =-1;
	connectionType = type;
	if(scpConnectionTypeUDP== connectionType)
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	else if (scpConnectionTypeTCP== connectionType)
		sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock!=INVALID_SOCKET)
	{
		ret = 0;
	}
	return ret;
}
int ScpSocketObject::ShutDown()
{
	int error=0;
#ifdef _WIN32
	if(sock)
	{
		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
		error=WSAGetLastError();
	if(error!=0)
	{
		std::wstring text;
		text = STDSTRINGEXT::Format(L"ShutDown failed with error %d\n", error);
		if(_engine)
			_engine->PrintError(text);
	}
#else
	if(sock)
	{
		shutdown(sock,2);
	}
#endif

	return error;
}

ScpObject * ScpSocketObject::InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	thisObject->Show(engine);
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
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

ScpObject * ScpSocketObject::InnerFunction_set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 2)
	{
		//����һЩSocketѡ��
		std::wstring optionname = parameters->at(0);
		std::wstring optionvalue = parameters->at(1);
		StringStripQuote(optionname);
		StringStripQuote(optionvalue);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(optionname);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			optionname = ((ScpStringObject *)objparam0)->content;
		}
		ScpObject * objparam1 = engine->GetCurrentObjectSpace()->FindObject(optionvalue);
		if (objparam1 && objparam1->GetType() == ObjString)
		{
			optionvalue = ((ScpStringObject *)objparam1)->content;
		}
		int opt = 0;
		if (wcsicmp(optionvalue.c_str(), L"true") == 0 ||
			wcsicmp(optionvalue.c_str(), L"1") == 0)
		{
			opt = 1;
		}
		else
		{
			opt = StringToInt(optionvalue);
		}
		if (wcsicmp(optionname.c_str(), L"TCP_NODELAY") == 0)
		{
#ifdef _WIN32
			//����socket ѡ�� ������negale�㷨 
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&opt, sizeof(opt));
#else
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, O_NDELAY, (const char *)&opt, sizeof(opt));
			
#endif
		}
		else if (wcsicmp(optionname.c_str(), L"SO_REUSEADDR") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
		}
		else if (wcsicmp(optionname.c_str(), L"SO_SNDTIMEO") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_SNDTIMEO, (const char *)&opt, sizeof(opt));
		}
		else if (wcsicmp(optionname.c_str(), L"SO_RCVTIMEO") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_RCVTIMEO, (const char *)&opt, sizeof(opt));
		}
		else if (wcsicmp(optionname.c_str(), L"SO_SNDBUF") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_SNDBUF, (const char *)&opt, sizeof(opt));
		}
		else if (wcsicmp(optionname.c_str(), L"SO_RCVBUF") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_RCVBUF, (const char *)&opt, sizeof(opt));
		}
		else if (wcsicmp(optionname.c_str(), L"SO_KEEPALIVE") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_KEEPALIVE, (const char *)&opt, sizeof(opt));
		}
		else if (wcsicmp(optionname.c_str(), L"SO_OOBINLINE") == 0)
		{
			setsockopt(((ScpSocketObject*)thisObject)->sock, IPPROTO_TCP, SO_OOBINLINE, (const char *)&opt, sizeof(opt));
		}
		else
		{
			engine->PrintError("unsupported socket option");
		}
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_send(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring content = parameters->at(0);
		StringStripQuote(content);
		ScpObject * obj = engine->GetCurrentObjectSpace()->FindObject(parameters->at(0));
		if (obj && obj->GetType() == ObjString)
		{
			content = ((ScpStringObject*)obj)->content;
		}
		ScpIntObject * len = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		int ret = ((ScpSocketObject*)thisObject)->Send(content, engine);
		if (len)
		{
			len->value = ret;
		}
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_receive(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring content = parameters->at(0);
		StringStripQuote(content);
		ScpIntObject * len = (ScpIntObject *)engine->GetCurrentObjectSpace()->AcquireTempObject(ObjInt);
		int ret = ((ScpSocketObject*)thisObject)->Receive(content, engine);
		if (len)
		{
			len->value = ret;

		}
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_watch(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		((ScpSocketObject*)thisObject)->Listen(engine);
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_bind(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		((ScpSocketObject*)thisObject)->Bind(param0, engine);
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_connect(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		((ScpSocketObject*)thisObject)->Connect(param0, engine);
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_create(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 0)
	{
		((ScpSocketObject*)thisObject)->Create();
	}
	else if (parameters->size() == 1)
	{
		std::wstring conntype = parameters->at(0);
		StringStripQuote(conntype);
		ScpObject * objparam0 = engine->GetCurrentObjectSpace()->FindObject(conntype);
		if (objparam0 && objparam0->GetType() == ObjString)
		{
			conntype = ((ScpStringObject *)objparam0)->content;
		}
		((ScpSocketObject*)thisObject)->Create(conntype);
	}
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpSocketObject*)thisObject)->ShutDown();
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_listen(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	((ScpSocketObject*)thisObject)->Listen(engine);
	return thisObject;
}

ScpObject * ScpSocketObject::InnerFunction_accept(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine)
{
	if (parameters->size() == 1)
	{
		std::wstring param0 = parameters->at(0);
		StringStripQuote(param0);
		((ScpSocketObject*)thisObject)->Accept(param0, engine);
	}
	return thisObject;
}
