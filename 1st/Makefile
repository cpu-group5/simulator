CC = gcc

all: simulator

simulator: main.o simulator.o decoder.o exec.o debugger.o print_op.o
	$(CC) -g main.o simulator.o decoder.o exec.o debugger.o print_op.o -o simulator -Wall -lm
main.o: main.c
	$(CC) -c -g main.c -Wall -lm

simulator.o: simulator.c simulator.h
	$(CC) -c -g simulator.c -Wall -lm

decoder.o: decoder.c decoder.h
	$(CC) -c -g decoder.c -Wall -lm

exec.o: exec.c
	$(CC) -c -g exec.c -Wall -lm

debugger.o: debugger.c
	$(CC) -c -g debugger.c -Wall -lm

print_op.o: print_op.c
	$(CC) -c -g print_op.c -Wall -lm
clean:
	rm -f *.o simulator
