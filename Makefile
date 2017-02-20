CC= gcc
FLAGS= -Wall -std=c11 -g -O0 

all: vm.o
	$(CC) main.c vm.o -o lake-vm $(FLAGS)

vm.o: vm.h vm.c
	$(CC) -c vm.c
