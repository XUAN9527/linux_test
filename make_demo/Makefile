CC = gcc
OBJ_TARGET = edit
BUILD_DIR = build
COMPILE_FLAGS = -MMD
CFLAGS=-Wall -g

LIB_TARGET=subdir/lib/libsubmake.a

# 定义链接选项
LDFLAGS=-I./subdir/inc -L./subdir/lib -lsubmake

INCLUDE = -Iapplication \
-Iutils \
-Isubdir/inc

C_SOURCES = application/main.c \
utils/common.c \
$(wildcard chapter_sorting/*.c)

C_OBJECTS = $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))

.PHONY : clean all

all :$(OBJ_TARGET)

$(OBJ_TARGET) : $(C_OBJECTS) $(LIB_TARGET)
	$(CC) -o $@ $(C_OBJECTS) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(COMPILE_FLAGS) $(INCLUDE) $< -o $@

$(LIB_TARGET):
	make -C subdir/ all

clean :
	rm -rf build $(OBJ_TARGET)
	make -C subdir/ clean
	
-include $(wildcard $(BUILD_DIR)/**/*.d)	# 包含所有生成的依赖文件，避免重复编译、提高效率
