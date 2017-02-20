#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "vm_macros.h"

VM *vm;

const vm_int_t program[] = {
  PUSH,  '\0',
  PUSH,  '!',
  PUSH,  'p',
  PUSH,  'l',
  PUSH,  'e',
  PUSH,  'H',
  MOV,   A, 6,

  SUB,   A, 1,
  POP,   C,
  OUT,   C,
  JGT,   A, 0, 15,
  HALT,
};

int main(int argc, char** argv) {
  vm = create_VM();
  load_VM_Program(vm, program);
  run_VM(vm);
  destroy_VM(vm);
  return 0;
}
