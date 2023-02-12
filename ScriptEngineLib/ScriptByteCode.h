#ifndef _H_SCRIPTBYTECODE
#define _H_SCRIPTBYTECODE
#include "ScpAst.h"
#include <string>
#include "ScpObject.h"
#include "ScpResourcePool.h"
#include "ScpByteCode.h"

//字节码生成类
class CScriptEngine;

class ByteCodeMemoryStream
{
public:
	ByteCodeMemoryStream();
	~ByteCodeMemoryStream();
	void Release();
	int GetByteCodeCommandCount();
	unsigned char * AppendByteCode(ByteCodeMemoryStream * other);
	unsigned char * AppendByteCode(unsigned char * code,unsigned int codelen);
	unsigned char * membuf;
	unsigned int bufsize;
	unsigned char * curpos;
	unsigned int codelength;

};
class ScriptByteCode
{
public:
	friend class CScriptEngine;
	ScriptByteCode();
	~ScriptByteCode();

	bool GenByteCodeFromSouceLine(std::string& wsSourceLine, ByteCodeMemoryStream& memstream);
    bool GenByteCodeFromCommand(const unsigned int & commandvalue, VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream, CScriptEngine * engine);
	bool GenByteCodeObjectDefine(ScpObjectType type,VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream);
	bool GenByteCodeClassObjectDefine(ScpObjectType type, VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream);
	bool GenByteCodeClassInstanceDefine(ScpObjectType type, VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream);
	bool GenByteCodeFunctionDefine(VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream, CScriptEngine * engine);
	bool GenByteCodeLoad(VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream);
	bool GenByteCodeImport(VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream);
	bool GetByteCodeInitRes(std::string res, ByteCodeMemoryStream& memstream,ULONG &resid);
	bool GetByteCodeBinaryOp(std::string op, ULONG idret, ULONG idleft, ULONG idright,ByteCodeMemoryStream& memstream);
	bool GenByteCodeUnaryOp(std::string op,ULONG idobj, ByteCodeMemoryStream& memstream);
	bool GenByteCodeCallInner(std::string objectname, std::string innerfuncname,VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream, CScriptEngine * engine);
	bool GenByteCodeIfstatement(ByteCodeMemoryStream & streamcondition, ByteCodeMemoryStream & streamtrueblock, ByteCodeMemoryStream& streamfalseblock,ByteCodeMemoryStream & memstreamif);
	bool GenByteCodeFunctionBody(ByteCodeMemoryStream & memstreamfunc);
	bool GetByteCodeCompute(VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream, CScriptEngine * engine);
	bool GenByteCodeCallFunc(std::string funcname, VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream);
	bool GenByteCodeReturn(VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream, CScriptEngine * engine);
	bool GenByteCodeWhilestatement(ByteCodeMemoryStream & streamcondition, ByteCodeMemoryStream & streamwhileblock, ByteCodeMemoryStream & memstreamwhile);
	bool GetByteCodeLoop(VTPARAMETERS & vtparameters, ByteCodeMemoryStream& memstream, CScriptEngine * engine);
	void Init();
	bool DumpToFile(const char * bytecodefile);

	ByteCodeMemoryStream * bytecodemem;
	ScpResourcePool * resourcepool;
	
};

#endif //_H_SCRIPTBYTECODE