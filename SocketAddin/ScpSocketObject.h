#pragma once
#include "../ScriptEngineLib/ScpObject.h"
#include "ScpAddressObject.h"
const static wchar_t * scpConnectionTypeTCP = L"TCP";
const static wchar_t * scpConnectionTypeUDP = L"UDP";
const static ScpObjectType ObjSocket = 300;

const static wchar_t * str_CN_ObjSocket = L"套接字";
const static wchar_t * scpcommand_cn_bind = L"绑定";
const static wchar_t * scpcommand_cn_listen = L"侦听";
const static wchar_t * scpcommand_cn_accept = L"接受";

const static wchar_t * str_EN_ObjSocket = L"socket";
const static wchar_t * scpcommand_en_bind = L"bind";
const static wchar_t * scpcommand_en_listen = L"listen";
const static wchar_t * scpcommand_en_accept = L"accept";
#include "../ScriptEngineLib/ScriptEngine.h"
class ScpSocketObject :
	public ScpObject
{

public:
	ScpSocketObject(void);
	~ScpSocketObject(void);


	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);
	int Bind(std::wstring addrobjname,CScriptEngine * engine);
	int Bind(ScpObject *  addrobj,CScriptEngine * engine);
	int Connect(std::wstring addrobjname,CScriptEngine * engine);
	int Send(std::wstring & content,CScriptEngine * engine);
	int Send(std::string &content,CScriptEngine * engine);
	int Send(ScpObject * contentobj, CScriptEngine *engine);
	int Listen(CScriptEngine * engine);
	int Receive(std::wstring contentobj,CScriptEngine *engine);
	int Receive(ScpObject * contentobj,CScriptEngine *engine);
	int Create(std::wstring type= scpConnectionTypeTCP);
	int ShutDown();
	int Accept(std::wstring sockobjname,CScriptEngine *engine);
	int Accept(ScpObject * sockobj,CScriptEngine *engine);
	ScpAddressObject address;
	ScpAddressObject remoteAddress;
	CScriptEngine * _engine;

#ifdef _WIN32
	SOCKET sock;
#else 
	int sock;
#endif
	std::wstring connectionType;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_set(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_send(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_receive(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_watch(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_bind(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_connect(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_create(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_listen(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_accept(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
};


ScpObject *  __stdcall SocketObjFactory(VTPARAMETERS * paramters, CScriptEngine * engine);
