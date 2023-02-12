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

//1、在剪切板上放置数据
//
//if(OpenClipboard())    //打开剪切板
//{
//    EmptyClipboard(); //清空剪切板
//    CString str;       //从控件中取出字符
//    HANDLE hclip;      //GlobalAlloc分配内存的句柄
//    char *buf;         //返回的内存地址
//    GetDlgItemText(IDC_EDIT_SEND,str);    //取字符
//    hclip=GlobalAlloc(GMEM_MOVEABLE,str.GetLength()+1);//在堆上分配制定数目的字节
//    buf=(char*)GlobalLock(hclip);//对内存块加锁,并返回它的内存地址
//    strcpy(buf,str);        //将字符拷贝到内存中
//    GlobalUnlock(hclip);     //解锁
//    SetClipboardData(CF_TEXT,hclip);//向剪切板上放置内存中的数据
//    CloseClipboard();        //关闭剪切板
//}
//
//2、提取剪切板上的数据
//
//if(IsClipboardFormatAvailable(CF_TEXT))   //判断剪切板上的数据格式
//{
//    HANDLE hclip;
//    char *buf;
//    hclip=GetClipboardData(CF_TEXT);
//    buf=(char*)GlobalLock(hclip);
//    GlobalUnlock(hclip);
//    SetDlgItemText(IDC_EDIT_RECV,buf);
//}