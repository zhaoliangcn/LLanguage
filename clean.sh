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
