/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//������Ϣ�ص��������������Ϣ���ض��������Ӷ�IDE��֧��
*/
#include "UIMessage.h"
CUIMessage::CUIMessage()
{
	messagecallback = NULL;
	UIClass = NULL;

}
CUIMessage::~CUIMessage()
{

}
bool CUIMessage::RegisterUICallBack(void * uiclass, UICallBack callback)
{
	if (uiclass != NULL && callback != NULL)
	{
		messagecallback = callback;
		UIClass = uiclass;
        return true;
	}
    return false;
}
bool CUIMessage::RegisterUIStepCallBack(void * uiclass, UICallBack callback)
{
	if (uiclass != NULL && callback != NULL)
	{
		stepcallback = callback;
		UIClass = uiclass;
        return true;
	}
    return false;
}
bool CUIMessage::PostUIStepMessage(int currentline)
{
	stepcallback(UIClass, NULL);
    return true;
}
bool CUIMessage::PostUIMessage(const char * message, bool withnewline )
{
	if (messagecallback)
	{
		messagecallback(UIClass, STDSTRINGEXT::AToW(message).c_str());
}
	else
	{
		if (withnewline)
			printf("%s\n", message);
		else
			printf("%s", message);
	}
    return true;
}
bool CUIMessage::PostUIMessage(const wchar_t *message, bool withnewline )
{
#ifdef _WIN32
	if (messagecallback)
	{
		messagecallback(UIClass, message);
	}
	else
	{
		if (withnewline)
			printf("%s\n", STDSTRINGEXT::WToA(message).c_str());
		else
			printf("%s", STDSTRINGEXT::WToA(message).c_str());
	}
	return TRUE;
#else
    return PostUIMessage(STDSTRINGEXT::W2UTF(message).c_str(), withnewline);
#endif
}
