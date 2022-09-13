CC = clang
CFLAGS = -std=gnu11 -Wall -pedantic -O0 -g -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = -fsanitize=address

.PHONY: clean
clean:
	rm -f *.o
	rm -f test
	rm -f test2
	rm -f test3

.PHONY : all
all : test test2 test3

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

my_vect: my_vect.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: test.o ant_tool.o my_vect.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test2: test2.o ant_tool.o my_vect.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test3: test3.o ant_tool.o my_vect.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
