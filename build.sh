make -C ./EasyJson/EasyJson
rm -f ./ScriptEngineLib/ScpNumberObject.cpp ./ScriptEngineLib/ScpStateObject.cpp ./ScriptEngineLib/ScpScriptTranslate.cpp ./ScriptEngineLib/ScpDebugger.cpp 
make -C ./ScriptEngineLib
make -C ./ScriptEngine
rm -f ./ScriptEngineDll/dllmain.cpp
make -C ./ScriptEngineDll
#make -C ./QScriptEditor -f QMakefile
make -C ./SocketAddin
#make -C ./ZipAddin
make -C ./OsInfoAddin
mkdir -p bin/Addin
cp ./ScriptEngine/scriptengine ./bin
cp ./ScriptEngineDll/libScriptEngineDll.so ./bin
cp ./SocketAddin/libsocketAddin.so ./bin/Addin
#cp ./ZipAddin/libZipAddin.so ./bin/Addin
cp ./OsInfoAddin/libosAddin.so ./bin/Addin
#cp ./QScriptEditor/QScriptEditor ./bin
#sudo update-mime-database /usr/share/mime
