/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPMAPOBJECT
#define _H_SCPMAPOBJECT
#include "ScpObject.h"
#include "ScpObjectSpace.h"
typedef std::map<std::string ,std::string> ScpObjectNameMap;
typedef std::map<std::string ,std::string>::iterator ITScpObjectNameMap;



class ScpMapObject : public ScpObject
{
public:
	ScpMapObject();
	~ScpMapObject();
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
    virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

    BOOL MapObject(std::string& key,std::string& value, CScriptEngine * engine);
    BOOL UnMapObject(std::string& key);
	BOOL UnMapObject(int index);
    ScpObject* GetKeyObject(std::string& key,ScpObjectSpace * objectSpace);
    ScpObject* GetValueObject(std::string& key,ScpObjectSpace * objectSpace);
	ScpObject* GetValueObject(int index);
    

	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_add(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_enum(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);





	USEROBJMAP scpobjectmap;
};

ScpObject * __stdcall ScpMapObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPMAPOBJECT