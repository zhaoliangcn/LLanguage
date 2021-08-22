all:main.o
	g++ -o scriptengine main.o ../ScriptEngineLib/libScriptEngineLib.a -ldl
main.o:main.cpp
	g++ -Wno-attributes -Wno-deprecated -c main.cpp 
clean:
	rm -f scriptengine *.o
