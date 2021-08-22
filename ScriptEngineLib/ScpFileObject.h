/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//文件对象
*/
#ifndef _H_SCPFILEOBJECT
#define _H_SCPFILEOBJECT
#include "ScpObject.h"
#include "ScpTableObject.h"
#include "ScpStringObject.h"
#include "ScpTimeObject.h"
#include "ScpMemoryObject.h"



const static wchar_t* str_CN_file_attribute_readonly = L"只读";
const static wchar_t* str_CN_file_attribute_hide = L"隐藏";
const static wchar_t* str_CN_file_attribute_normal = L"平常";
const static wchar_t* str_CN_file_attribute_archive = L"存档";
const static wchar_t* str_CN_file_attribute_system = L"系统";
const static wchar_t* str_CN_file_attribute_temporary = L"临时";
const static wchar_t* str_CN_file_mode_readonly = L"只读";
const static wchar_t* str_CN_file_mode_readwrite = L"读写";
const static wchar_t* str_CN_file_mode_append = L"追加";
const static wchar_t* str_CN_file_pos_begin = L"起始";
const static wchar_t* str_CN_file_pos_end = L"结尾";
const static wchar_t* str_CN_file_create_time = L"创建时间";
const static wchar_t* str_CN_file_access_time = L"访问时间";
const static wchar_t* str_CN_file_modify_time = L"修改时间";
const static wchar_t* scpcommand_readall_CN = L"读取全部";
const static wchar_t* scpcommand_readall_line_CN =L"读取所有行";
const static wchar_t* scpcommand_erase_CN = L"擦除";
const static wchar_t* scpcommand_select_open_CN = L"选择打开";
const static wchar_t* scpcommand_select_save_CN = L"选择保存";
const static wchar_t* scpcommand_append_CN = L"追加";
const static wchar_t* inner_function_exist_CN = L"存在";
const static wchar_t* str_CN_ObjDrive = L"驱动器";
const static wchar_t* str_CN_ObjFilename = L"文件名";
const static wchar_t* str_CN_ObjPath = L"路径";
const static wchar_t* str_CN_ObjExtension = L"扩展名";

const static wchar_t* str_EN_file_attribute_readonly = L"readonly";
const static wchar_t* str_EN_file_attribute_hide = L"hide";
const static wchar_t* str_EN_file_attribute_normal = L"normal";
const static wchar_t* str_EN_file_attribute_archive = L"archive";
const static wchar_t* str_EN_file_attribute_system = L"system";
const static wchar_t* str_EN_file_attribute_temporary = L"temporary";
const static wchar_t* str_EN_file_mode_readonly = L"readonly";
const static wchar_t* str_EN_file_mode_readwrite = L"readwrite";
const static wchar_t* str_EN_file_mode_append = L"append";
const static wchar_t* str_EN_file_pos_begin = L"begin";
const static wchar_t* str_EN_file_pos_end = L"end";
const static wchar_t* str_EN_file_create_time = L"createtime";
const static wchar_t* str_EN_file_access_time = L"accesstime";
const static wchar_t* str_EN_file_modify_time = L"modifytime";
const static wchar_t* scpcommand_readall_EN = L"readall";
const static wchar_t* scpcommand_readall_line_EN = L"readallline";
const static wchar_t* scpcommand_erase_EN = L"erase";
const static wchar_t* scpcommand_select_open_EN = L"selectopen";
const static wchar_t* scpcommand_select_save_EN = L"selectsave";
const static wchar_t* scpcommand_append_EN = L"append";
const static wchar_t* inner_function_exist_EN = L"exist";
const static wchar_t* str_EN_ObjDrive = L"drive";
const static wchar_t* str_EN_ObjFilename = L"filename";
const static wchar_t* str_EN_ObjPath = L"path";
const static wchar_t* str_EN_ObjExtension = L"extension";
class ScpFileObject:public ScpObject
{
public:
	ScpFileObject();
	~ScpFileObject();
	virtual ScpObject * Clone(std::wstring strObjName);
	virtual std::wstring ToString();
	virtual void Release() ;
	virtual void Show(CScriptEngine * engine);

	virtual bool IsInnerFunction(std::wstring & functionname);
	virtual ScpObject * CallInnerFunction(std::wstring & functionname,VTPARAMETERS * parameters,CScriptEngine * engine);

	static ScpTimeObject * GetLastAccessTime(std::wstring FileName1);
	static ScpTimeObject * GetCreateTime(std::wstring FileName1);
	static ScpTimeObject * GetLastModifyTime(std::wstring FileName1);
	static int Compare(std::wstring FileName1,std::wstring FileName2);
	static ScpTableObject * GetArrtibute(std::wstring FileName,ScpTableObject * tableobj);
	static BOOL ChangeAttribute(std::wstring FileName,ScpTableObject * table);
	static BOOL GetArrtibute(std::wstring FileName,VTPARAMETERS & attrlist);
	static BOOL ChangeAttribute(std::wstring FileName,VTPARAMETERS & attrlist);
	static std::wstring GetFileExt(std::wstring FileName);
	BOOL Open(std::wstring FileName,std::wstring mode);
	BOOL Create(std::wstring FileName, std::wstring mode);
	BOOL Save(std::wstring newFileName);
	static BOOL FileExist(std::wstring FileName);
	static BOOL IsDir(std::wstring FileName);
	BOOL read(__int64 pos,std::string &content,unsigned int length);
	BOOL write(__int64 pos,std::wstring &content,unsigned int length);
	BOOL read(__int64 pos,ULONG& size,void **Buffer);
	BOOL write(__int64 pos,ULONG size,void *Buffer);
	BOOL append(ULONG size, void *Buffer);
	BOOL append(std::wstring &content);
	BOOL write(std::wstring &content);
	BOOL write(std::string &content);
	BOOL read(std::wstring &content);
	BOOL read(std::string &content);
	BOOL readline(std::wstring &line);
	BOOL readline(std::string &line);
	BOOL readall_line(ScpTableObject * tableobj, CScriptEngine * engine);
	BOOL writeall_line(ScpTableObject * tableobj, CScriptEngine * engine);
	BOOL readall();
	BOOL readall(ScpMemoryObject * memobj);
	void Close();
	static BOOL Clear(std::wstring filename);
	BOOL Clear();
	__int64 seek(std::wstring pos);
	__int64 seek(__int64 pos);
	__int64 GetCurrentPos();
	void Print(CScriptEngine * engine);
	static BOOL Delete(std::wstring filename);
	static BOOL Erase(std::wstring filename);
	static BOOL Encrypt(std::wstring filename,std::wstring password, std::wstring algorithm);
	static BOOL Decrypt(std::wstring filename, std::wstring password, std::wstring algorithm);
	static BOOL Move(std::wstring src,std::wstring dst);
	static BOOL Copy(std::wstring src,std::wstring dst);
	static __int64 GetSize(std::wstring filename);
	std::wstring filename;
	unsigned char * content;
	__int64 currentpos;
	std::wstring openmode;
	__int64 filesize;

#ifdef _WIN32
	HANDLE file;
#else
    int file;
#endif
	


	static ScpObject * InnerFunction_Show(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_Get(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);

	static ScpObject * InnerFunction_delete(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_getsize(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_clear(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_create(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_save(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_print(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_move(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_shutdown(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_close(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_compare(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_seek(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_readall(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_readall_line(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_erase(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_read(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_write(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_copy(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_select_open(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_select_save(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_append(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);
	static ScpObject * InnerFunction_exist(ScpObject * thisObject, VTPARAMETERS * parameters, CScriptEngine * engine);


};


ScpObject * __stdcall ScpFileObjectFactory(VTPARAMETERS * paramters, CScriptEngine * engine);


#endif //_H_SCPFILEOBJECT