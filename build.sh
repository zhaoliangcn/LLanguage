make -C ./EasyJson/EasyJson
rm -f ./ScriptEngineLib/ScpNumberObject.cpp ./ScriptEngineLib/ScpStateObject.cpp ./ScriptEngineLib/ScpScriptTranslate.cpp ./ScriptEngineLib/ScpDebugger.cpp 
make -C ./ScriptEngineLib
make -C ./ScriptEngine
rm -f ./ScriptEngineDll/dllmain.cpp
make -C ./ScriptEngineDll
make -C ./SocketAddin
make -C ./OsInfoAddin
mkdir -p bin/Addin
cp ./ScriptEngine/scriptengine ./bin
cp ./ScriptEngineDll/libScriptEngineDll.so ./bin
cp ./SocketAddin/libsocketAddin.so ./bin/Addin
cp ./OsInfoAddin/libosAddin.so ./bin/Addin

