all:
	make -C ./EasyJson/EasyJson
	rm -f ./ScriptEngineLib/ScpNumberObject.cpp ./ScriptEngineLib/ScpStateObject.cpp ./ScriptEngineLib/ScpScriptTranslate.cpp ./ScriptEngineLib/ScpDebugger.cpp 
	make -C ./ScriptEngineLib
	make -C ./ScriptEngine
	rm -f ./ScriptEngineDll/dllmain.cpp
	make -C ./ScriptEngineDll
	#make -C ./QScriptEditor -f QMakefile
	make -C ./SocketAddin
	#make -C ./ZipAddin
dist:
	mkdir -p bin/Addin
	cp ./ScritpEngine/scriptengine ./bin
	cp ./ScriptEngineDll/libScriptEngineDll.so ./bin
	cp ./SocketAddin/libsocketAddin.so ./bin/Addin
	#cp ./ZipAddin/libZipAddin.so ./bin/Addin
	cp ./OsInfoAddin/libosAddin.so ./bin/Addin
	#cp ./QScriptEditor/QScriptEditor ./bin
	sudo cp ./resource/application-x-scp.xml /usr/share/mime/packages
	sudo cp ./resource/*.desktop /usr/share/applications
	sudo cp ./resource/*.sh /usr/local/bin
	sudo update-mime-database /usr/share/mime
bin:
	mkdir -p bin/Addin
	cp ./ScritpEngine/scriptengine ./bin
	cp ./ScriptEngineDll/libScriptEngineDll.so ./bin
	cp ./SocketAddin/libsocketAddin.so ./bin/Addin
	cp ./OsInfoAddin/libosAddin.so ./bin/Addin
test:
	bin/scriptengine script/hello.scp
clean:
	make clean -C ./EasyJson/EasyJson
	rm -f ./ScriptEngineLib/ScpNumberObject.cpp ./ScriptEngineLib/ScpStateObject.cpp ./ScriptEngineLib/ScpScriptTranslate.cpp ./ScriptEngineLib/ScpDebugger.cpp 
	make clean -C ./ScriptEngineLib
	make clean -C ./ScriptEngine
	rm -f ./ScriptEngineDll/dllmain.cpp
	make clean -C ./ScriptEngineDll
	#make clean -C ./QScriptEditor -f QMakefile
	make clean -C ./SocketAddin
	#make clean -C ./ZipAddin
	make clean -C ./OsInfoAddin
	rm -fr ./bin
