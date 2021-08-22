CC := g++
CFLAGS := -std=c++11 -g -Wno-attributes -Wno-deprecated -fPIC
TARGET := libScriptEngineDll.so
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
all:$(TARGET)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
$(TARGET):$(OBJS)
	$(CC) -fPIC -shared -o $@  $^ ../ScriptEngineLib/libScriptEngineLib.a -lm
clean:
	rm -rf $(TARGET) *.o
