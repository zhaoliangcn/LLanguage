#pragma once
#include "../ScriptEngineLib/ScpObject.h"
#include "ScpAddressObject.h"
const static char * scpConnectionTypeTCP = "TCP";
const static char * scpConnectionTypeUDP = "UDP";
const static ScpObjectType ObjSocket = 300;

const static char * str_CN_ObjSocket = "套接字";
const static char * scpcommand_cn_bind = "绑定";
const static char * scpcommand_cn_listen = "侦听";
const static char * scpcommand_cn_accept = "接受";

const static char * str_EN_ObjSocket = "socket";
const static char * scpcommand_en_bind = "bind";
const static char * scpcommand_en_listen = "listen";
const static char * scpcommand_en_accept = "accept";
#include "../ScriptEngineLib/ScriptEngine.h"
class ScpSocketObject :
	public ScpObject
{

public:
	ScpSocketObject(void);
	~ScpSocketObject(void);


	virtual void Show(CScriptEngine * engine) ;
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);
	int Bind(std::string addrobjname,CScriptEngine * engine);
	int Bind(ScpObject *  addrobj,CScriptEngine * engine);
	int Connect(std::string addrobjname,CScriptEngine * engine);
	int Send(std::wstring & content,CScriptEngine * engine);
	int Send(std::string &content,CScriptEngine * engine);
	int Send(ScpObject * contentobj, CScriptEngine *engine);
	int Listen(CScriptEngine * engine);
	int Receive(std::string contentobj,CScriptEngine *engine);
	int Receive(ScpObject * contentobj,CScriptEngine *engine);
	int Create(std::string type= scpConnectionTypeTCP);
	int ShutDown();
	int Accept(std::string sockobjname,CScriptEngine *engine);
	int Accept(ScpObject * sockobj,CScriptEngine *engine);
	ScpAddressObject address;
	ScpAddressObject remoteAddress;
	CScriptEngine * _engine;

#ifdef _WIN32
	SOCKET sock;
#else 
	int sock;
#endif
	std::string connectionType;


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
