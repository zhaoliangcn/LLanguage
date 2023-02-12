#ifndef _H_MAPOBJECTS
#define _H_MAPOBJECTS


#include <string>
#include <map>
#include <vector>
//#include <hash_map>



#define USE_GOOGLE_HASHMAP
#undef USE_GOOGLE_HASHMAP
typedef std::pair<std::string,ScpObject *> VTITEM;
typedef std::vector<VTITEM> USEROBJMAP3;
typedef std::vector<VTITEM>::iterator ITUSEROBJMAP3;

typedef std::map<std::string,ScpObject *> USEROBJMAP2;
typedef std::map<std::string,ScpObject *>::iterator ITUSEROBJMAP2;
typedef std::map<std::string, HANDLE> HANDLESMAP;
typedef std::map<std::string, HANDLE>::iterator ITHANDLESMAP;

#ifdef USE_GOOGLE_HASHMAP
#include "../googlehashmap/sparsehash/dense_hash_map"
typedef google::dense_hash_map<std::string,ULONG> CHSCOMMANDMAP;
typedef google::dense_hash_map<std::string,ULONG>::iterator ITCHSCOMMANDMAP;
typedef google::dense_hash_map<std::string,ScpObjectType> CHSOBJECTMAP;
typedef google::dense_hash_map<std::string,ScpObjectType>::iterator ITCHSOBJECTMAP;
typedef google::dense_hash_map<std::string,ScpObject *> USEROBJMAP;
typedef google::dense_hash_map<std::string,ScpObject *>::iterator ITUSEROBJMAP;
typedef google::dense_hash_map<std::string,ULONG> MEMBERATTRMAP;
typedef google::dense_hash_map<std::string,ULONG>::iterator ITMEMBERATTRMAP;
typedef google::dense_hash_map<std::string,std::string> STRINGMAP;
typedef google::dense_hash_map<std::string,std::string>::iterator ITSTRINGMAP;
#else 

#ifdef _WIN32
#include <unordered_map>
#if (_MSC_VER == 1500 || _MSC_VER == 1600|| _MSC_VER == 1700|| _MSC_VER == 1800)
typedef std::tr1::unordered_map<std::string, ULONG> CHSCOMMANDMAP;
typedef std::tr1::unordered_map<std::string, ULONG>::iterator ITCHSCOMMANDMAP;
typedef std::tr1::unordered_map<std::string, ULONG> CHSOBJECTMAP;
typedef std::tr1::unordered_map<std::string, ULONG>::iterator ITCHSOBJECTMAP;
typedef std::tr1::unordered_map<std::string, ScpObject *> USEROBJMAP;
typedef std::tr1::unordered_map<std::string, ScpObject *>::iterator ITUSEROBJMAP;
typedef std::tr1::unordered_map<std::string, ULONG> MEMBERATTRMAP;
typedef std::tr1::unordered_map<std::string, ULONG>::iterator ITMEMBERATTRMAP;
typedef std::tr1::unordered_map<std::string,std::string> STRINGMAP;
typedef std::tr1::unordered_map<std::string,std::string>::iterator ITSTRINGMAP;
typedef std::tr1::unordered_map<ULONG,std::string> VALUESTRINGMAP;
typedef std::tr1::unordered_map<ULONG,std::string>::iterator ITVALUESTRINGMAP;



#elif (_MSC_VER == 1900|| _MSC_VER == 1910|| _MSC_VER >= 1911)
typedef std::unordered_map<std::string,ULONG> CHSCOMMANDMAP;
typedef std::unordered_map<std::string,ULONG>::iterator ITCHSCOMMANDMAP;
typedef std::unordered_map<std::string,ScpObjectType> CHSOBJECTMAP;
typedef std::unordered_map<std::string,ScpObjectType>::iterator ITCHSOBJECTMAP;
typedef std::unordered_map<std::string,ScpObject *> USEROBJMAP;
typedef std::unordered_map<std::string,ScpObject *>::iterator ITUSEROBJMAP;
typedef std::unordered_map<std::string,ULONG> MEMBERATTRMAP;
typedef std::unordered_map<std::string,ULONG>::iterator ITMEMBERATTRMAP;
typedef std::unordered_map<std::string,std::string> STRINGMAP;
typedef std::unordered_map<std::string,std::string>::iterator ITSTRINGMAP;
typedef std::unordered_map<ULONG,std::string> VALUESTRINGMAP;
typedef std::unordered_map<ULONG,std::string>::iterator ITVALUESTRINGMAP;


#endif 




#else 
#include <ext/hash_map>
#include <tr1/unordered_map>
using namespace std;
typedef tr1::unordered_map<std::string,ULONG> CHSCOMMANDMAP;
typedef tr1::unordered_map<std::string,ULONG>::iterator ITCHSCOMMANDMAP;
typedef tr1::unordered_map<std::string,ScpObjectType> CHSOBJECTMAP;
typedef tr1::unordered_map<std::string,ScpObjectType>::iterator ITCHSOBJECTMAP;
typedef tr1::unordered_map<std::string,ScpObject *> USEROBJMAP;
typedef tr1::unordered_map<std::string,ScpObject *>::iterator ITUSEROBJMAP;
typedef tr1::unordered_map<std::string,ULONG> MEMBERATTRMAP;
typedef tr1::unordered_map<std::string,ULONG>::iterator ITMEMBERATTRMAP;
typedef tr1::unordered_map<std::string,std::string> STRINGMAP;
typedef tr1::unordered_map<std::string,std::string>::iterator ITSTRINGMAP;
typedef std::tr1::unordered_map<ULONG,std::string> VALUESTRINGMAP;
typedef std::tr1::unordered_map<ULONG,std::string>::iterator ITVALUESTRINGMAP;



#endif

#endif 



#endif //_H_MAPOBJECTS