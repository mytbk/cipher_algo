CFLAGS=-g -Werror

OBJS=sms4.o

all: sms4.o

test1: test1.o $(OBJS)

test2: test2.o $(OBJS)

encrypt1.o: encrypt.c
	gcc -c $(CFLAGS) -DPRINT_PROCESS encrypt.c -o encrypt1.o

main: main.o des.o encrypt1.o

clean:
	rm -f *.o main test1 test2

.PHONY: main clean
