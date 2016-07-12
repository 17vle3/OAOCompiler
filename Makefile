OBJS	= bison.o lex.o main.o
CC	= g++
CFLAGS	= -g -Wall -pedantic -std=c++11 -O0

ccompiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ccompiler -ll

lex.o: lex.c
	$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c: ccompiler.lex
	flex ccompiler.lex
	cp lex.yy.c lex.c

bison.o: bison.c
	$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c: ccompiler.y
	bison -d -v ccompiler.y
	cp ccompiler.tab.c bison.c
	cmp -s ccompiler.tab.h tok.h || cp ccompiler.tab.h tok.h

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

lex.o yac.o main.o: heading.h
lex.o main.o: tok.h

clean:
	rm -f *.o *~ lex.c lex.yy.c bison.c tok.h ccompiler.tab.c ccompiler.tab.h ccompiler.output ccompiler
