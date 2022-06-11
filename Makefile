BUILD?=DEBUG
all:
	$(MAKE) -C ./EasyJson/EasyJson
	rm -f ./ScriptEngineLib/ScpNumberObject.cpp ./ScriptEngineLib/ScpStateObject.cpp ./ScriptEngineLib/ScpScriptTranslate.cpp ./ScriptEngineLib/ScpDebugger.cpp 
	$(MAKE) -C ./ScriptEngineLib
	$(MAKE) -C ./ScriptEngine
	rm -f ./ScriptEngineDll/dllmain.cpp
	$(MAKE) -C ./ScriptEngineDll
	#make -C ./QScriptEditor -f QMakefile
	$(MAKE) -C ./SocketAddin
	$(MAKE) -C ./OsInfoAddin
	#make -C ./ZipAddin
dist:
	mkdir -p bin/Addin
	cp ./ScriptEngine/scriptengine ./bin
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
	cp ./ScriptEngine/scriptengine ./bin
	cp ./ScriptEngineDll/libScriptEngineDll.so ./bin
	cp ./SocketAddin/libsocketAddin.so ./bin/Addin
	cp ./OsInfoAddin/libosAddin.so ./bin/Addin
test:
	bin/scriptengine script/hello.scp
clean:
	$(MAKE) clean -C ./EasyJson/EasyJson
	rm -f ./ScriptEngineLib/ScpNumberObject.cpp ./ScriptEngineLib/ScpStateObject.cpp ./ScriptEngineLib/ScpScriptTranslate.cpp ./ScriptEngineLib/ScpDebugger.cpp 
	$(MAKE) clean -C ./ScriptEngineLib
	$(MAKE) clean -C ./ScriptEngine
	rm -f ./ScriptEngineDll/dllmain.cpp
	$(MAKE) clean -C ./ScriptEngineDll
	#make clean -C ./QScriptEditor -f QMakefile
	$(MAKE) clean -C ./SocketAddin
	#make clean -C ./ZipAddin
	$(MAKE) clean -C ./OsInfoAddin
	rm -fr ./bin
