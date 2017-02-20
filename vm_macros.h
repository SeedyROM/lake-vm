#ifndef __VM_MACROS_H__
#define __VM_MACROS_H__

#define PROGRAM_INFO(vm) printf( \
  "IP: %d\tOP: %d\n", \
  vm->instruction_pointer, \
  vm->current_program[abs(vm->instruction_pointer)] \
)

#define PRINT_REGS(vm) printf("Reg[A]: %d\n", vm->registers[A].data); \
                       printf("Reg[B]: %d\n", vm->registers[B].data); \
                       printf("Reg[C]: %d\n\n", vm->registers[C].data)

#endif
