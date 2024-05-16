OBJ_NAME = edit
BUILD_DIR = build
COMPILE_FLAGS = -MMD

INCLUDE = -Iapplication \
-Iutils

C_SOURCES = application/main.c \
utils/common.c \
$(wildcard chapter_sorting/*.c)

C_OBJECTS = $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	cc -c $(COMPILE_FLAGS) $(INCLUDE) $< -o $@

.PHONY : clean all

all : $(OBJ_NAME)

$(OBJ_NAME): $(C_OBJECTS)
	cc -o $@ $(C_OBJECTS)

clean :
	rm -rf build $(OBJ_NAME)

-include $(wildcard $(BUILD_DIR)/**/*.d)	# 包含所有生成的依赖文件，避免重复编译、提高效率
