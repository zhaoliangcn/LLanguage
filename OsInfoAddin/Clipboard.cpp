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
	if (OpenClipboard(hwndOwner))    //打开剪切板
	{
		EmptyClipboard(); //清空剪切板
		HANDLE hclip;      //GlobalAlloc分配内存的句柄
		char *buf;         //返回的内存地址
		hclip = GlobalAlloc(GMEM_MOVEABLE, (Str.length() + 1));//在堆上分配制定数目的字节
		buf = (char*)GlobalLock(hclip);//对内存块加锁,并返回它的内存地址
		strcpy(buf, Str.c_str());        //将字符拷贝到内存中
		GlobalUnlock(hclip);     //解锁
		SetClipboardData(CF_TEXT, hclip);//向剪切板上放置内存中的数据
		CloseClipboard();        //关闭剪切板
	}
}
std::string CClipboard::GetString(HWND hwndOwner)
{
	std::string temp;
	if (OpenClipboard(hwndOwner))
	{
		if (IsClipboardFormatAvailable(CF_TEXT))   //判断剪切板上的数据格式
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
	if (OpenClipboard(hwndOwner))    //打开剪切板
	{
		EmptyClipboard();
		CloseClipboard();
	}
}