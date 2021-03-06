#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "vm_macros.h"

VM *vm;

const vm_int_t program[] = {
  MOV,  -G,  0,
  MOV,  -F, IP,
  PUSH,  '\0',
  PUSH,  '\n',
  PUSH,  '!',
  PUSH,  'p',
  PUSH,  'l',
  PUSH,  'e',
  PUSH,  'H',
  MOV,   A, 7,

  MOV,  -B, IP,
  SUB,   A, 1,
  POP,   C,
  OUT,   C,
 -JGT,   A, 0, B,

  ADD,   G, 1,
 -JLT,   G, 20000, F,

  HALT,
};

int main(int argc, char** argv) {
  vm = create_VM();
  load_VM_Program(vm, program);
  run_VM(vm);
  PRINT_REGS(vm);
  destroy_VM(vm);
  return 0;
}
