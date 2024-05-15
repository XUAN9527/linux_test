BUILD_DIR = build

INCLUDE = -Iinclude

C_SOURCES = main.c \
sort/insert.c \
sort/select.c

C_OBJECTS = $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	cc -c $(INCLUDE) $< -o $@

.PHONY : clean all

all : $(BUILD_DIR)/edit

$(BUILD_DIR)/edit: $(C_OBJECTS)
	cc -o $@ $(C_OBJECTS)

clean :
	rm -rf build

-include $(wildcard $(BUILD_DIR)/**/*.d)	# 包含所有生成的依赖文件，避免重复编译、提高效率
