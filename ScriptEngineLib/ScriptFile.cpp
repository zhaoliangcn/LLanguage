/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//脚本文件加载和字符编码识别
*/
#include "ScriptFile.h"
#include "ScpObject.h"
#include "ScpScriptLex.h"
#include "commanddefine.h"
#include <fstream>
#include "../Common/stdstringext.hpp"
#include "../Common/commonutil.hpp"
CScriptFile::CScriptFile(void)
{
}


CScriptFile::~CScriptFile(void)
{
}
bool CScriptFile::IsValidScript(std::string headline)
{
	return STDSTRINGEXT::ToLowerA(headline)=="#scp";
}
bool CScriptFile::IsValidScript(std::wstring headline)
{
	return STDSTRINGEXT::ToLowerW(headline)==L"#scp";
}
bool CScriptFile::IsValidScriptLib(std::string headline)
{
	return STDSTRINGEXT::ToLowerA(headline)=="#scplib";
}
bool CScriptFile::IsValidScriptLib(std::wstring headline)
{
	return STDSTRINGEXT::ToLowerW(headline)==L"#scplib";
}
bool CScriptFile::IsComment(std::string& commandline)
{
	std::string headtoken = commandline.substr(0,1);
	return (headtoken==scpComment);	
}
bool CScriptFile::IsCppComment(std::string & commandline)
{
	std::string headtoken = commandline.substr(0, 2);
	return (headtoken == scpCppComment);
}
bool  CScriptFile::ReadAllFromMemory(const char *memoryscript,VTSTRINGS& body)
{
	if(memoryscript)
	{
		std::string all;
		if (!STDSTRINGEXT::IsTextUTF8((char*)memoryscript,strlen(memoryscript)))
		{
			all= STDSTRINGEXT::AToU(memoryscript);
		}
		else
		{
			all = memoryscript;
		}		
		std::string temp;
		std::string::iterator itlast = all.begin();
		std::string::iterator it = all.begin();
		while (it != all.end())
		{
			if (*it == '\r')
			{
				if (*(it + 1) == '\n')
				{				
					//windows格式的回车换行
					if (itlast == it)
					{
						body.push_back("");
						itlast = it + 2;
						it+=2;
						continue;
					}
					else
					{
						temp = std::string(itlast, it);
						STDSTRINGEXT::trim(temp);
						body.push_back(temp);
						itlast = it + 2;
						it += 2;
						continue;
					}
				}
				else
				{
					//macintosh格式的回车
					if (itlast == it)
					{
						body.push_back("");
						itlast = it + 1;
						it++;
						continue;
					}
					else
					{
						temp = std::string(itlast, it);
						STDSTRINGEXT::trim(temp);
						body.push_back(temp);
						itlast = it + 1;
						it += 1;
						continue;
					}
					
				}
			}
			else if (*(it) == '\n')
			{
				//unix格式的换行
				temp = std::string(itlast, it);
				STDSTRINGEXT::trim(temp);
				body.push_back(temp);
				itlast = it + 1;
			}
			it++;
		}
		if (itlast != it)
		{
			temp = std::string(itlast, it);
			STDSTRINGEXT::trim(temp);
			body.push_back(temp);
		}
		return true;
	}
	return false;
}
bool  CScriptFile::ReadAll(const char *scriptfilename, VTSTRINGS& body)
{
	if(STDSTRINGEXT::IsTextUTF8((char*)scriptfilename,strlen(scriptfilename)))
		return ReadAll(STDSTRINGEXT::UTF2W(scriptfilename).c_str(),body);
	else
		return ReadAll(STDSTRINGEXT::AToW(scriptfilename).c_str(), body);
}
bool  CScriptFile::ReadAll(const wchar_t *scriptfilename,VTSTRINGS& body)
{
	EncodeType encodetype ;
	encodetype= GetScriptEncodeType(scriptfilename);
	#ifndef _WIN32
	encodetype=Utf8;
	#endif
	if(encodetype == Unicode)
	{
		std::wstring all;
#ifdef _WIN32
		std::ifstream infile(scriptfilename,std::ios::binary);
#else
		std::ifstream infile(STDSTRINGEXT::WToA(scriptfilename).c_str(),std::ios::binary);
#endif
		infile.seekg(0,std::ios::end);
		size_t size = infile.tellg();
		infile.seekg(2,std::ios::beg);
		char * buffer =(char*) malloc(size);
		memset(buffer,0,size);
		infile.read(buffer,size);
		all=(wchar_t*)buffer;
		free(buffer);

		std::wstring temp;
		size_t pos =0;
		pos = all.find(L"\n",pos);
		while(pos!=std::wstring::npos)
		{
			temp=all.substr(0,pos-1);
			STDSTRINGEXT::trim(temp);
			body.push_back(STDSTRINGEXT::W2UTF(temp));
			all=all.substr(pos+1,all.length()-pos-1);
			pos =all.find(L"\n",0);
		}
		infile.close();
	}
	else if (Ansi == encodetype)
	{

		std::string commandline;
		std::string headline;
#ifdef _WIN32
		std::ifstream infile(scriptfilename);
#else
		std::ifstream infile(STDSTRINGEXT::W2UTF(scriptfilename).c_str());
#endif

		if(std::getline(infile, headline))
		{
			STDSTRINGEXT::trim(headline);
			if(!IsValidScript(headline) && !IsValidScriptLib(headline))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		commandline= headline;
		STDSTRINGEXT::trim(commandline);
		body.push_back(commandline);

		while(std::getline(infile,commandline))
		{
			STDSTRINGEXT::trim(commandline);
			body.push_back(commandline);
		}
		infile.close();
	}
	else if (Utf8 == encodetype)
	{

		std::string commandline;
		std::string headline;
#ifdef _WIN32
		std::ifstream infile(scriptfilename);
#else
		std::ifstream infile(STDSTRINGEXT::W2UTF(scriptfilename).c_str());
#endif

		if(std::getline(infile, headline))
		{
			STDSTRINGEXT::trim(headline);
			if(!IsValidScript(headline) && !IsValidScriptLib(headline))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		commandline= headline;
		STDSTRINGEXT::trim(commandline);
		body.push_back(commandline);

		while(std::getline(infile,commandline))
		{
			STDSTRINGEXT::trim(commandline);
			body.push_back(commandline);
		}
		infile.close();
	}
	else if (Utf8BOM == encodetype)
	{
		std::string commandline;
		std::string headline;
#ifdef _WIN32
		std::ifstream infile(scriptfilename);
#else
		std::ifstream infile(STDSTRINGEXT::W2UTF(scriptfilename).c_str());
#endif

		if (std::getline(infile, headline))
		{
			headline = headline.substr(3);
			STDSTRINGEXT::trim(headline);
			if (!IsValidScript(headline) && !IsValidScriptLib(headline))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		commandline = headline;
		STDSTRINGEXT::trim(commandline);
		body.push_back(commandline);

		while (std::getline(infile, commandline))
		{
			STDSTRINGEXT::trim(commandline);
			body.push_back(commandline);
		}
		infile.close();
	}
	else
	{
		return false;
	}
	return true;

}

EncodeType CScriptFile::GetScriptEncodeType(const wchar_t *scriptfilename)
{
	EncodeType type=EncodeUnknown;
	char srcBuff[1024]={0};
	char header[3];
	unsigned char uniTxt[] = {0xFF, 0xFE};			// Unicode file header
	unsigned char endianTxt[] = {0xFE, 0xFF};		// Unicode big endian file header
	unsigned char utf8Txt[] = {0xEF, 0xBB, 0xBF};	// UTF_8 file header
	int len = 0;
	int ascii = 0;
#ifdef _WIN32
	std::ifstream infile(scriptfilename);
#else
	std::ifstream infile(STDSTRINGEXT::W2UTF(scriptfilename).c_str());
#endif
	infile.read(srcBuff,1024);

	for (int i = 0; i < 4; i++)
	{
		header[0] = srcBuff[0];
		header[1] = srcBuff[1];
		header[2] = srcBuff[2];

		if (srcBuff[i] < 0 || srcBuff[i]>127)
		{
			ascii++;
		}
	}
	if (0 == ascii)		// ASCII file
	{
		type = Ansi;
		if (STDSTRINGEXT::IsTextUTF8(srcBuff, infile.gcount()))
		{
			type = Utf8;
		}
	}
	else if ((2 == ascii) && (0 == memcmp(header, uniTxt, sizeof(uniTxt))))		// Unicode file
	{
		type = Unicode;

	}
	else if ((2 == ascii) && (0 == memcmp(header, endianTxt, sizeof(endianTxt))))	//  Unicode big endian file
	{
		type = UnicodeBigEndian;
	}
	else if ((3 == ascii) && (0 == memcmp(header, utf8Txt, sizeof(utf8Txt))))		// UTF-8 file
	{
		type = Utf8BOM;
	}
	else  //Unknow
	{
		if (STDSTRINGEXT::IsTextUTF8(srcBuff, infile.gcount()))
		{
			type = Utf8;
		}
	}	
	infile.close();
	return type;
}
std::wstring CScriptFile::GetPath(const wchar_t* FullPathName)
{
	std::wstring temp; 
#ifdef _WIN32
	if (FullPathName)
	{
		wchar_t Drv[MAX_PATH] = { 0 };
		wchar_t Dir[MAX_PATH] = { 0 };
		_wsplitpath_s(FullPathName, Drv, MAX_PATH, Dir, MAX_PATH, NULL, 0, NULL, 0);
		wcscat_s(Drv, MAX_PATH, Dir);
		temp = Drv;
	}
#else
	if (FullPathName)
	{
		char Drv[MAX_PATH] = { 0 };
		char Dir[MAX_PATH] = { 0 };
        _splitpath(STDSTRINGEXT::W2UTF(FullPathName).c_str(), Drv,  Dir, NULL, NULL);
		strcat(Drv,  Dir);
		temp = STDSTRINGEXT::UTF2W(Drv).c_str();
	}
	
#endif
	return temp;
}
bool CScriptFile::FileExist(std::wstring FilePathName)
{
	bool Exist = false;
#ifdef _WIN32
	HANDLE hFile=CreateFileW(FilePathName.c_str(),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		Exist = true;
		CloseHandle(hFile);
	}
#else
	if (access(STDSTRINGEXT::W2UTF(FilePathName).c_str(), F_OK) == 0)
		return true;
	return false;
#endif
	return Exist;
}
std::string CScriptFile::GetPath(const char* FullPathName)
{
	std::string temp;
#ifdef _WIN32
	if (FullPathName)
	{
		char Drv[MAX_PATH] = { 0 };
		char Dir[MAX_PATH] = { 0 };
		_splitpath_s(FullPathName, Drv, MAX_PATH, Dir, MAX_PATH, NULL, 0, NULL, 0);
		strcat_s(Drv, MAX_PATH, Dir);
		temp = Drv;
	}
#else
	if (FullPathName)
	{
		char Drv[MAX_PATH] = { 0 };
		char Dir[MAX_PATH] = { 0 };
		_splitpath(FullPathName, Drv, Dir, NULL, NULL);
		strcat(Drv, Dir);
		temp = Drv;
	}

#endif
	return temp;
}
bool CScriptFile::FileExist(std::string FilePathName)
{
	bool Exist = false;
#ifdef _WIN32
	HANDLE hFile = CreateFileA(FilePathName.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		Exist = true;
		CloseHandle(hFile);
	}
#else
	if (access(FilePathName.c_str(), F_OK) == 0)
		return true;
	return false;
#endif
	return Exist;
}