CC = clang
CFLAGS = -std=gnu11 -Wall -pedantic -O0 -g -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = -fsanitize=address

.PHONY: clean
clean:
	rm -f *.o
	rm -f test

.PHONY : all
all : test

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

my_vect: my_vect.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: test.o ant_tool.o my_vect.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
