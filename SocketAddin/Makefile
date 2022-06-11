BUILD?=DEBUG
CFLAGS:= -Wno-attributes -Wno-deprecated -fPIC -shared -std=c++11 
ifeq ($(BUILD),DEBUG)
CFLAGS+= -g
endif
all:SocketAddin.o ScpAddressObject.o ScpNetConnectionObject.o ScpSocketObject.o
	#g++ -g -Wno-attributes -fPIC -shared  -std=c++11 -o libsocketAddin.so SocketAddin.cpp ScpAddressObject.cpp ScpNetConnectionObject.cpp ScpSocketObject.cpp 
	g++ $(CFLAGS) -o libsocketAddin.so SocketAddin.o ScpAddressObject.o ScpNetConnectionObject.o ScpSocketObject.o ../ScriptEngineLib/libScriptEngineLib.a
SocketAddin.o:SocketAddin.cpp
	gcc $(CFLAGS) -c SocketAddin.cpp
ScpAddressObject.o:ScpAddressObject.cpp ScpAddressObject.h
	g++ $(CFLAGS) -c ScpAddressObject.cpp
ScpNetConnectionObject.o:ScpNetConnectionObject.cpp ScpNetConnectionObject.h
	g++ $(CFLAGS) -c ScpNetConnectionObject.cpp
ScpSocketObject.o:ScpSocketObject.cpp ScpSocketObject.h
	g++ $(CFLAGS) -c ScpSocketObject.cpp
clean:
	rm -f *.o *.so


