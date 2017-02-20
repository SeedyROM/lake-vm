#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "vm.h"
#include "vm_macros.h"
#include "vm_opcodes.h"

VM *create_VM() {
  VM *this;
  this = malloc(sizeof(VM));

  // Allocate the memory for the registers.
  size_t r_length = 0;
  for(; r_length < FLAGS; r_length++);
  this->registers = malloc(sizeof(vm_int_t) * (r_length + 1));

  assert(this);
  return this;
}

void destroy_VM(VM* this) {
  free(this->registers);
  free(this);
}

int load_VM_Program(VM* this, const vm_int_t* program) {
  this->current_program = (vm_int_t *)program;
  return 0;
}

void run_VM(VM* this) {
  assert(this->current_program);
  while (this->current_program[this->instruction_pointer] != HALT) {
    (*opcodes[
      abs(this->current_program[this->instruction_pointer])
    ])(this);
    // PRINT_REGS(this);
  }
}
