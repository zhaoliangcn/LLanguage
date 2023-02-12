/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//正则表达式对象
*/
#ifndef _H_SCPREGEXPOBJECT
#define _H_SCPREGEXPOBJECT
#include "ScpObject.h"

#define USE_TR1
//#define USE_BOOST
#ifdef USE_TR1
#include <regex>
#include <string>
#include <algorithm>
#include <iterator>
using std::string;
#ifdef _WIN32
using std::regex;
using std::wregex;
using std::regex_search;
using std::cregex_iterator;
using std::cmatch;
using std::regex_match;
using namespace std::regex_constants;

typedef string::const_iterator seq_t;
typedef std::regex_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match_t;


typedef std::wstring::const_iterator wseq_t;
typedef std::regex_iterator<wseq_t> wrgxiter;
typedef wrgxiter::regex_type wrgx_t;
typedef wrgxiter::value_type wmatch_t;
#else
using std::regex;
using std::wregex;
using std::regex_search;
using std::cregex_iterator;
using std::cmatch;
using std::regex_match;
using namespace std::regex_constants;

typedef string::const_iterator seq_t;
typedef std::regex_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match_t;


typedef std::wstring::const_iterator wseq_t;
typedef std::regex_iterator<wseq_t> wrgxiter;
typedef wrgxiter::regex_type wrgx_t;
typedef wrgxiter::value_type wmatch_t;
#endif
#endif
class ScpRegExpObject:public ScpObject
{
	
public:
	ScpRegExpObject();
	~ScpRegExpObject();
	virtual ScpObject * Clone(std::string strObjName);
	virtual std::string ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);
	virtual bool IsInnerFunction(std::string & functionname);
	virtual ScpObject * CallInnerFunction(std::string & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	bool Compile(std::string regexp);
	bool Find(std::string Text);
	bool Match(std::string Text);
	bool Replace(std::string Text,std::string Text2);

	std::string wstrregexp;

	regex rgx;


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_match(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_find(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_replace(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

};


ScpObject * __stdcall ScpRegExpObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);

#endif //_H_SCPREGEXPOBJECT