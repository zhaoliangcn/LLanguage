#ifndef _H_SCPGLOBALCOMMANDS
#define _H_SCPGLOBALCOMMANDS
#include "ScpObject.h"
namespace GlobalCommands
{
	BOOL __stdcall Do_Sleep_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);
	//对象操作
	BOOL __stdcall Do_Clear_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);//vtparameters 参数列表 engine 当前脚本引擎的上下文
	BOOL __stdcall Do_Shutdown_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Popup_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Run_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Show_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Delete_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Open_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Seek_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Copy_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Connect_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Capture_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Compare_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Acquire_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Release_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Write_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Read_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Start_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Getsubstring_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Insert_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Match_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Find_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Replace_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Move_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Getsize_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Enum_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Generate_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Refresh_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Getelement_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Traverse_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Sort_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Format_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Get_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Set_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Transform_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Split_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Push_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Print_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Create_Command(VTPARAMETERS * vtparameters,CScriptEngine * engine);
	BOOL __stdcall Do_Save_Command(VTPARAMETERS * vtparameters, CScriptEngine * engine);

}


#endif //_H_SCPGLOBALCOMMANDS