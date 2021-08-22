#ifndef _H_VECTOROBJECTS
#define _H_VECTOROBJECTS
#include <vector>
#include <string>


class ScpObject;

typedef std::vector<std::wstring> VTPARAMETERS;
typedef std::vector<std::wstring>::iterator ITPARAMETERS;

typedef std::vector<std::wstring> VTSTRINGS;
typedef std::vector<std::wstring>::iterator  ITSTRINGS;

typedef std::vector<int> VTINT;
typedef std::vector<int>::iterator ITINT;

typedef std::vector<ScpObject *> VTPOBJECTS;
typedef std::vector<ScpObject *>::iterator ITPOBJECTS;

#endif// _H_VECTOROBJECTS