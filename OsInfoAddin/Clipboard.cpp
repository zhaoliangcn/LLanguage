#include "stdafx.h"
#include "Clipboard.h"


CClipboard::CClipboard()
{
}


CClipboard::~CClipboard()
{
}
void CClipboard::SetString(HWND hwndOwner, std::string Str)
{
	if (OpenClipboard(hwndOwner))
	{
		EmptyClipboard();
		HANDLE hclip;
		char *buf; 
		hclip = GlobalAlloc(GMEM_MOVEABLE, (Str.length() + 1));
		buf = (char*)GlobalLock(hclip);
		strcpy(buf, Str.c_str());
		GlobalUnlock(hclip); 
		SetClipboardData(CF_TEXT, hclip);
		CloseClipboard(); 
	}
}
std::string CClipboard::GetString(HWND hwndOwner)
{
	std::string temp;
	if (OpenClipboard(hwndOwner))
	{
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			HANDLE hclip;
			char *buf;
			hclip = GetClipboardData(CF_TEXT);
			buf = (char*)GlobalLock(hclip);
			GlobalUnlock(hclip);
			if (buf)
				temp = buf;
		}
		CloseClipboard();
	}	
	return temp;
}
void CClipboard::Clear(HWND hwndOwner)
{
	if (OpenClipboard(hwndOwner))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}