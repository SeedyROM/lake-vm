#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

VM *vm;

const vm_int_t program[] = {
  MOV, A, 16,
  SUB, A, 1,
  BNZ, A, 3,
  HALT
};

int main(int argc, char** argv) {
  vm = create_VM();
  load_VM_Program(vm, program);
  run_VM(vm);
  destroy_VM(vm);
  return 0;
}
