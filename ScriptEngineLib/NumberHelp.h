/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//��ֵ���ַ����໥ת���ĸ�������
*/
#ifndef _H_NUMBERHELP
#define _H_NUMBERHELP
#include <errno.h>
#include "commanddefine.h"
#include <string>
BOOL IsStaticNumber(std::wstring Expression);
BOOL IsStaticDoubleNumber(std::wstring Expression);
BOOL IsStaticString(std::wstring Expression);
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