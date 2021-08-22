#pragma once
#include <string>
class CClipboard
{
public:
	CClipboard();
	~CClipboard();
	void SetString(HWND hwndOwner,std::string Str);
	std::string GetString(HWND hwndOwner);
	void Clear(HWND hwndOwner);
};

