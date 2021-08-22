all:SocketAddin.o ScpAddressObject.o ScpNetConnectionObject.o ScpSocketObject.o
	#g++ -g -Wno-attributes -fPIC -shared  -std=c++11 -o libsocketAddin.so SocketAddin.cpp ScpAddressObject.cpp ScpNetConnectionObject.cpp ScpSocketObject.cpp 
	g++ -g -Wno-attributes -fPIC -shared -std=c++11 -o libsocketAddin.so SocketAddin.o ScpAddressObject.o ScpNetConnectionObject.o ScpSocketObject.o ../ScriptEngineLib/libScriptEngineLib.a
SocketAddin.o:SocketAddin.cpp
	gcc -g -Wno-attributes -Wno-deprecated -fPIC -c SocketAddin.cpp
ScpAddressObject.o:ScpAddressObject.cpp ScpAddressObject.h
	g++ -g -Wno-attributes -Wno-deprecated -fPIC -std=c++11 -c ScpAddressObject.cpp
ScpNetConnectionObject.o:ScpNetConnectionObject.cpp ScpNetConnectionObject.h
	g++ -g -Wno-attributes -Wno-deprecated -fPIC -std=c++11 -c ScpNetConnectionObject.cpp
ScpSocketObject.o:ScpSocketObject.cpp ScpSocketObject.h
	g++ -g -Wno-attributes -Wno-deprecated -fPIC -std=c++11 -c ScpSocketObject.cpp
clean:
	rm -f *.o *.so


