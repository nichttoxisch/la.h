CC = clang-21
CFLAGS = -Wno-absolute-value -Wall -Wextra -Werror -ggdb -std=c11 -O2

all: example

always:
	mkdir -p build

example: examples/vec.c always
	$(CC) $(CFLAGS) -I.  examples/vec.c -o build/vec
	./build/vec

clean: 
	rm -rf build
