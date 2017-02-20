#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define STACK_SIZE 31

#include "vm.h"
#include "vm_macros.h"
#include "vm_opcodes.h"

VM *create_VM() {
  VM *this;
  this = malloc(sizeof(VM));
  assert(this);

  // Allocate the memory for the virtual registers.
  size_t r_length = 0;
  for(; r_length < FLAGS; r_length++);
  this->registers = calloc((r_length + 1), sizeof(Register));
  assert(this->registers != NULL);

  // Allocate our stack.
  this->stack = calloc((STACK_SIZE + 1), sizeof(vm_int_t));
  assert(this->stack != NULL);

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
  assert(this->current_program != NULL);
  // PRINT_REGS(this);
  while(this->current_program[this->registers[IP].data] != HALT) {
    (*opcodes[
      abs(this->current_program[this->registers[IP].data])
    ])(this);
    // PRINT_REGS(this);
  }
}
