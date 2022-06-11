BUILD?=DEBUG
CPPFLAGS:=-Wno-attributes -fPIC -std=c++11 -Wno-deprecated
ifeq ($(BUILD),DEBUG)
CPPFLAGS+=-g
endif
all:OsInfoAddin.o ScpOsInfoObject.o ScpOsInfoObject.o ScpComputerObject.o ScpClipboardObject.o ScpPipeObject.o ScpProcObject.o ScpShareMemoryObject.o ScpThreadObject.o ScpTimerObject.o
	g++ $(CPPFLAGS) -shared -o libosAddin.so OsInfoAddin.o ScpOsInfoObject.o ScpComputerObject.o ScpClipboardObject.o ScpPipeObject.o ScpProcObject.o ScpShareMemoryObject.o ScpThreadObject.o ScpTimerObject.o ../ScriptEngineLib/libScriptEngineLib.a
OsInfoAddin.o:OsInfoAddin.cpp OsInfoAddin.h
	g++ $(CPPFLAGS) -c OsInfoAddin.cpp
ScpOsInfoObject.o:ScpOsInfoObject.cpp ScpOsInfoObject.h
	g++ $(CPPFLAGS) -c ScpOsInfoObject.cpp
ScpComputerObject.o:ScpComputerObject.cpp ScpComputerObject.h
	g++ $(CPPFLAGS) -c ScpComputerObject.cpp
ScpClipboardObject.o:ScpClipboardObject.h ScpClipboardObject.cpp
	g++ $(CPPFLAGS) -c ScpClipboardObject.cpp
ScpPipeObject.o:ScpPipeObject.h ScpPipeObject.cpp
	g++ $(CPPFLAGS) -c ScpPipeObject.cpp
ScpProcObject.o:ScpProcObject.h ScpProcObject.cpp
	g++ $(CPPFLAGS) -c ScpProcObject.cpp
ScpShareMemoryObject.o:ScpShareMemoryObject.h ScpShareMemoryObject.cpp
	g++ $(CPPFLAGS) -c ScpShareMemoryObject.cpp
ScpThreadObject.o:ScpThreadObject.h ScpThreadObject.cpp
	g++ $(CPPFLAGS) -c ScpThreadObject.cpp
ScpTimerObject.o:ScpTimerObject.h ScpTimerObject.cpp
	g++ $(CPPFLAGS) -c ScpTimerObject.cpp
clean:
	rm -f *.o *.so


