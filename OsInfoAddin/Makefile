CFLAGS := -std=c++11 -g -Wno-attributes -fPIC 
all:OsInfoAddin.o ScpOsInfoObject.o ScpOsInfoObject.o ScpComputerObject.o ScpClipboardObject.o ScpPipeObject.o ScpProcObject.o ScpShareMemoryObject.o ScpThreadObject.o ScpTimerObject.o
	g++ $(CFLAGS) -shared -o libosAddin.so OsInfoAddin.o ScpOsInfoObject.o ScpComputerObject.o ScpClipboardObject.o ScpPipeObject.o ScpProcObject.o ScpShareMemoryObject.o ScpThreadObject.o ScpTimerObject.o ../ScriptEngineLib/libScriptEngineLib.a
OsInfoAddin.o:OsInfoAddin.cpp OsInfoAddin.h
	g++ $(CFLAGS) -c OsInfoAddin.cpp
ScpOsInfoObject.o:ScpOsInfoObject.cpp ScpOsInfoObject.h
	g++ $(CFLAGS) -c ScpOsInfoObject.cpp
ScpComputerObject.o:ScpComputerObject.cpp ScpComputerObject.h
	g++ $(CFLAGS) -c ScpComputerObject.cpp
ScpClipboardObject.o:ScpClipboardObject.h ScpClipboardObject.cpp
	g++ $(CFLAGS) -c ScpClipboardObject.cpp
ScpPipeObject.o:ScpPipeObject.h ScpPipeObject.cpp
	g++ $(CFLAGS) -c ScpPipeObject.cpp
ScpProcObject.o:ScpProcObject.h ScpProcObject.cpp
	g++ $(CFLAGS) -c ScpProcObject.cpp
ScpShareMemoryObject.o:ScpShareMemoryObject.h ScpShareMemoryObject.cpp
	g++ $(CFLAGS) -c ScpShareMemoryObject.cpp
ScpThreadObject.o:ScpThreadObject.h ScpThreadObject.cpp
	g++ $(CFLAGS) -c ScpThreadObject.cpp
ScpTimerObject.o:ScpTimerObject.h ScpTimerObject.cpp
	g++ $(CFLAGS) -c ScpTimerObject.cpp
clean:
	rm -f *.o *.so


