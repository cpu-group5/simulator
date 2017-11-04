CC = gcc

all: simulator

# simulator: main.o op_def.o
simulator: main.o simulator.o decoder.o exec.o
	$(CC) -g main.o simulator.o decoder.o exec.o -o simulator -Wall
main.o: main.c
	$(CC) -c -g main.c -Wall

simulator.o: simulator.c simulator.h
	$(CC) -c -g simulator.c -Wall

decoder.o: decoder.c decoder.h
	$(CC) -c -g decoder.c -Wall

exec.o: exec.c exec.h
	$(CC) -c -g exec.c -Wall
# op_def.o: op_def.c
# 	$(CC) -c -g op_def.c -Wall
clean:
	rm -f *.o simulator
