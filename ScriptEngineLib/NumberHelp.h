/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//数值与字符串相互转换的辅助函数
*/
#ifndef _H_NUMBERHELP
#define _H_NUMBERHELP
#include <errno.h>
#include "commanddefine.h"
#include <string>
BOOL IsStaticNumber(std::wstring Expression);
BOOL IsStaticNumber(std::string Expression);
BOOL IsStaticDoubleNumber(std::wstring Expression);
BOOL IsStaticDoubleNumber(std::string Expression);
BOOL IsStaticString(std::wstring Expression);
BOOL IsStaticString(std::string Expression);
int StringToInt(std::string str);
int StringToInt(std::wstring str);
double StringToDouble(std::string str);
double StringToDouble(std::wstring str);
__int64 StringToInt64(std::string str);
__int64 StringToInt64(std::wstring str);
std::wstring IntToWString(int value);
std::wstring Int64ToWString(__int64 value);
std::wstring DoubleToWString(double value);
std::string IntToString(int value);
std::string Int64ToString(__int64 value);
std::string DoubleToString(double value);
#endif //_H_NUMBERHELP