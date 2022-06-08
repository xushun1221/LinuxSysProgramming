src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))

incPath = ./inc
myArgs = -Wall #-g ...

ALL:test.out

test.out:$(obj)
	gcc $^ -o ./bin/$@ $(myArgs)

$(obj):./obj/%.o:./src/%.c
	gcc -c $< -o $@ $(myArgs) -I $(incPath)

clean:
	-rm -rf $(obj) ./bin/test.out

.PHONY: clean ALL