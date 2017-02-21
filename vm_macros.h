#ifndef __VM_MACROS_H__
#define __VM_MACROS_H__

#define PROGRAM_INFO(vm) printf( \
  "IP: %d\tOP: %d\n", \
  vm->registers[IP].data, \
  vm->current_program[abs(vm->registers[IP].data)] \
)

#define PRINT_REGS(vm) printf("\nReg[A]: %d\n", vm->registers[A].data); \
printf("Reg[B]: %d\n", vm->registers[B].data); \
printf("Reg[C]: %d\n", vm->registers[C].data); \
printf("SP: %d\n", vm->registers[SP].data); \
printf("IP: %d\n\n", vm->registers[IP].data); \

#endif
