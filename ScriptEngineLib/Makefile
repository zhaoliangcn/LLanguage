ARCH = $(shell getconf LONG_BIT)
CC := g++
CFLAGS := -g -Wno-attributes -Wno-deprecated -fPIC
TARGET := libScriptEngineLib.a
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
all:$(TARGET)
%.o:%.cpp
	$(CC) $(CFLAGS) -DLinux$(ARCH) -c $<
$(TARGET):$(OBJS)
	ar -rc $(TARGET) $^ ../EasyJson/EasyJson/CppEasyJson.o
clean:
	rm -rf $(TARGET) *.o
