CC = gcc

all: simulator

simulator: main.o simulator.o decoder.o exec.o debugger.o print_op.o
	$(CC) -g main.o simulator.o decoder.o exec.o debugger.o print_op.o -o simulator -Wall
main.o: main.c
	$(CC) -c -g main.c -Wall

simulator.o: simulator.c simulator.h
	$(CC) -c -g simulator.c -Wall

decoder.o: decoder.c decoder.h
	$(CC) -c -g decoder.c -Wall

exec.o: exec.c
	$(CC) -c -g exec.c -Wall

debugger.o: debugger.c
	$(CC) -c -g debugger.c -Wall

print_op.o: print_op.c
	$(CC) -c -g print_op.c -Wall
clean:
	rm -f *.o simulator
