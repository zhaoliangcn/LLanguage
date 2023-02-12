#ifndef _H_VECTOROBJECTS
#define _H_VECTOROBJECTS
#include <vector>
#include <string>


class ScpObject;

typedef std::vector<std::string> VTPARAMETERS;
typedef std::vector<std::string>::iterator ITPARAMETERS;

typedef std::vector<std::string> VTSTRINGS;
typedef std::vector<std::string>::iterator  ITSTRINGS;

typedef std::vector<std::wstring> VTSTRINGSW;
typedef std::vector<std::wstring>::iterator  ITSTRINGSW;

typedef std::vector<int> VTINT;
typedef std::vector<int>::iterator ITINT;

typedef std::vector<ScpObject *> VTPOBJECTS;
typedef std::vector<ScpObject *>::iterator ITPOBJECTS;

#endif// _H_VECTOROBJECTS