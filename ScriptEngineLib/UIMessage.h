/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_UIMESSAGE
#define _H_UIMESSAGE

typedef void (*UICallBack)(void * UIClass,const wchar_t * Message);


#include <string>
#include "../Common/stdstringext.hpp"

class CUIMessage
{
public:
    CUIMessage();
    ~CUIMessage();
    bool RegisterUICallBack(void * uiclass, UICallBack callback);
    bool RegisterUIStepCallBack(void * uiclass, UICallBack callback);
    bool PostUIStepMessage(int currentline);
    bool PostUIMessage(const char * message, bool withnewline = true);
    bool PostUIMessage(const wchar_t *message, bool withnewline = true);

private:
	UICallBack messagecallback;
	UICallBack stepcallback;
	void *UIClass;
#ifdef  _WIN32
    CRITICAL_SECTION cs;
#endif
};

#endif //_H_UIMESSAGE