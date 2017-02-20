CC= gcc
FLAGS= -Wall -std=c11 -g -O0

all: vm.o
	$(CC) main.c vm.o -o lake-vm $(FLAGS)

vm.o: vm.h vm.c vm_macros.h vm_opcodes.h vm_types.h
	$(CC) -c vm.c $(FLAGS)
