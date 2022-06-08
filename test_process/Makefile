src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src)) # 目标是.c文件编译为可执行文件

ALL:$(target)

%:%.c
	gcc $< -o $@

clean:
	-rm -rf $(target)

.PHONY: clean ALL