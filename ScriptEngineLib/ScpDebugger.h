#pragma once
#include "ScpObject.h"
class ScpDebugger
{
public:
	ScpDebugger();
	~ScpDebugger();

	VTSTRINGS GetInnerFunctions(ScpObject* obj, int lang);
};

