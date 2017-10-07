#
CFLAGS = -g
all : kkrandom.o
	gcc -o kkrandom $(CFLAGS) kkrandom.o
.c.o:
	gcc -c $(CFLAGS) $<
