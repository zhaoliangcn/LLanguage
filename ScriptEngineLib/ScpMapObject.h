/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPMAPOBJECT
#define _H_SCPMAPOBJECT
#include "ScpObject.h"
#include "ScpObjectSpace.h"
typedef std::map<std::wstring ,std::wstring> ScpObjectNameMap;
typedef std::map<std::wstring ,std::wstring>::iterator ITScpObjectNameMap;



class ScpMapObject : public ScpObject
{
public:
	ScpMapObject();
	~ScpMapObject();
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
    virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

    BOOL MapObject(std::wstring& key,std::wstring& value, CScriptEngine * engine);
    BOOL UnMapObject(std::wstring& key);
	BOOL UnMapObject(int index);
    ScpObject* GetKeyObject(std::wstring& key,ScpObjectSpace * objectSpace);
    ScpObject* GetValueObject(std::wstring& key,ScpObjectSpace * objectSpace);
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