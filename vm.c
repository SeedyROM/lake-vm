#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "vm.h"
#include "vm_macros.h"

#define _ip this->instruction_pointer
#define _regs this->registers
#define _program this->current_program

// Move along, nothing to see here.
void _VM_NOP(VM* this) { _ip++; }

// Load a value into a register
void _VM_MOV(VM* this) {
  // LOADi a, 56;
  _ip++;
  if(_program[_ip] - 1 < 0) {
    _regs[-_program[_ip]].data = _regs[_program[_ip + 1]].data;
  } else {
    _regs[ _program[_ip]].data = (vm_int_t)_program[_ip + 1];
  }
  _ip += 2;
}

// Add to a number or a register
void _VM_ADD(VM* this) {
  _ip++;
  if(_program[_ip] - 1 < 0) {
    _regs[-_program[_ip]].data = _regs[_program[_ip + 1]].data;
  } else {
    _regs[ _program[_ip]].data += (vm_int_t)_program[_ip + 1];
  }
  _ip += 2;
}

// Subtract to a number or a register
void _VM_SUB(VM* this) {
  _ip++;
  if(_program[_ip] - 1 < 0) {
    _regs[-_program[_ip]].data -= _regs[_program[_ip + 1]].data;
  } else {
    _regs[ _program[_ip]].data -= (vm_int_t)_program[_ip + 1];
  }
  _ip += 2;
}

// Multiply to a number or a register
void _VM_MUL(VM* this) {
  _ip++;
  if(_program[_ip] - 1 < 0) {
    _regs[-_program[_ip]].data *= _regs[_program[_ip + 1]].data;
  } else {
    _regs[ _program[_ip]].data *= (vm_int_t)_program[_ip + 1];
  }
  _ip += 2;
}

// Multiply to a number or a register
void _VM_DIV(VM* this) {
  _ip++;
  if(_program[_ip] - 1 < 0) {
    _regs[-_program[_ip]].data /= _regs[_program[_ip + 1]].data;
  } else {
    _regs[ _program[_ip]].data /= (vm_int_t)_program[_ip + 1];
  }
  _ip += 2;
}

// Set the instruction pointer.
void _VM_JMP(VM* this) {
  _ip++;
  if(_program[_ip] - 1 < 0) {
    _ip = _regs[_program[_ip]].data;
  } else {
    _ip = (vm_int_t)_program[_ip];
  }
}

// Branch if zero.
void _VM_BZ(VM* this) {
  _ip++;
  if(_regs[_program[_ip]].data == 0) {
    if(_program[_ip] - 1 < 0) {
      _ip = _regs[_program[_ip + 1]].data;
    } else {
      _ip = (vm_int_t)_program[_ip + 1];
    }
  } else {
    _ip += 2;
  }
}

// Branch if not zero.
void _VM_BNZ(VM* this) {
  _ip++;
  if(_regs[_program[_ip]].data != 0) {
    if(_program[_ip] - 1 < 0) {
      _ip = _regs[_program[_ip + 1]].data;
    } else {
      _ip = (vm_int_t)_program[_ip + 1];
    }
  } else {
    _ip += 2;
  }
}

void (*opcodes[])(VM*) = {
  [NOP]  = _VM_NOP,
  [MOV]  = _VM_MOV,
  [ADD]  = _VM_ADD,
  [SUB]  = _VM_SUB,
  [MUL]  = _VM_MUL,
  [DIV]  = _VM_DIV,
  [JMP]  = _VM_JMP,
  [BZ]   = _VM_BZ,
  [BNZ]  = _VM_BNZ,
  [HALT] = _VM_NOP,
};

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
  free(_regs);
  free(this);
}

int load_VM_Program(VM* this, const vm_int_t* program) {
  _program = (vm_int_t *)program;
  return 0;
}

void run_VM(VM* this) {
  assert(_program);
  PROGRAM_INFO(this);
  while (_program[_ip] != HALT) {
    (*opcodes[_program[_ip]])(this);
    PROGRAM_INFO(this);
    PRINT_REGS(this);
  }
}

#undef _ip
#undef _regs
#undef _program
