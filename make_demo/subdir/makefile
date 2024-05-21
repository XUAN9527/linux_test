# 定义编译器
CC = gcc
AR = ar
BUILD_DIR = build
# 定义编译选项
CFLAGS=-Wall -g

# 定义目标文件
TARGET = lib/libsubmake.a

INCLUDE = -Iinc

C_SOURCES = $(wildcard src/*.c)

C_OBJECTS = $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))

.PHONY : clean all

# 编译静态库
all : $(TARGET)
	chmod 755 $(TARGET)

clean :
	rm -rf build/ lib/

# 静态库依赖于源文件
$(TARGET): $(C_OBJECTS)
	mkdir -p $(dir $@)
	$(AR) rcs $(TARGET) $<

# 编译单个源文件为对象文件
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@