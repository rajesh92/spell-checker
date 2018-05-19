




CC = gcc

CFLAGS = -Wall

default: spell-checker

spell-checker: dict corrector
	$(CC) $(CFLAGS) spell-checker.c -o spell-checker dict.o corrector.o

dict: dict.c
	$(CC) $(CFLAGS) -c dict.c

corrector: corrector.c
	$(CC) $(CFLAGS) -c corrector.c

clean:
	$(RM) spell-checker *.o
