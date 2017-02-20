#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "vm_macros.h"

VM *vm;

const vm_int_t program[] = {
  MOV,  A, 20,
  MOV,  B, 10,
  MOV,  C, 9,
  ADD, -A, B,
 -JLT,  A, 327132, C,
  HALT,
};

int main(int argc, char** argv) {
  vm = create_VM();
  load_VM_Program(vm, program);
  run_VM(vm);
  PRINT_REGS(vm);
  return 0;
}
