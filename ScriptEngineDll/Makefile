BUILD?=DEBUG
CC := g++
CFLAGS := -std=c++11 -Wno-attributes -Wno-deprecated -fPIC
ifeq ($(BUILD),DEBUG)
CFLAGS+= -g 
endif
TARGET := libScriptEngineDll.so
SRCS := ScriptEngineDll.cpp
OBJS := $(patsubst %cpp,%o,$(SRCS))
all:$(TARGET)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
$(TARGET):$(OBJS)
	$(CC) -fPIC -shared -o $@  $^ ../ScriptEngineLib/libScriptEngineLib.a -lm
clean:
	rm -rf $(TARGET) *.o
