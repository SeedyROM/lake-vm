#ifndef __VM_OPCODES_H__
#define __VM_OPCODES_H__

#include "vm.h"

//
// Helper macros.
//
#define _ip this->registers[IP].data
#define _regs this->registers
#define _program this->current_program
#define _sp this->registers[SP].data
#define _stack this->stack

// Clean up the condition opcodes.
#define CHECK_CONDITION_2(condition) _ip++; \
if(_regs[abs(_program[_ip])].data condition 0) { \
  if(_program[_ip] - 1 < 0) { \
    _ip = _regs[_program[_ip + 1]].data; \
  } else { \
    _ip = _program[_ip + 1]; \
  } \
} else { \
  _ip += 2; \
}

#define CHECK_CONDITION_3(condition) if(_program[_ip] - 1 < 0) { \
  if(_program[_ip + 1] - 1 < 0) { \
    if(_regs[-_program[_ip + 1]].data condition _regs[_program[_ip + 2]].data) { \
      _ip = _regs[_program[_ip + 3]].data; \
      return; \
    } \
  } else { \
    if(_regs[_program[_ip + 1]].data condition _program[_ip + 2]) { \
      _ip = _regs[_program[_ip + 3]].data; \
      return; \
    } \
  } \
} else { \
  if(_program[_ip + 1] - 1 < 0) { \
    if(_regs[-_program[_ip + 1]].data condition _program[_ip + 2]) { \
      _ip = _program[_ip + 3]; \
      return; \
    } \
  } else { \
    if(_regs[ _program[_ip + 1]].data condition _program[_ip + 2]) { \
      _ip = _program[_ip + 3]; \
      return; \
    } \
  } \
} \
_ip += 4;

#define ALTER_REGISTERS(operator) _ip++; \
if(_program[_ip] - 1 < 0) { \
  _regs[-_program[_ip]].data operator _regs[_program[_ip + 1]].data; \
} else { \
  _regs[ _program[_ip]].data operator _program[_ip + 1]; \
} \
_ip += 2;
//
// End helper macros.
//

// Move along, nothing to see here.
void _VM_NOP(VM* this) { _ip++; }

// Load a value into a register
void _VM_MOV(VM* this) {
  if(_program[_ip + 1] - 1 < 0) {
    if(_program[_ip + 2] == IP) {
      _regs[-_program[_ip + 1]].data = _regs[_program[_ip + 2]].data + 3;
    } else {
      _regs[-_program[_ip + 1]].data = _regs[_program[_ip + 2]].data;
    }
  } else {
    _regs[ _program[_ip + 1]].data = _program[_ip + 2];
  }
  _ip += 3;
}

// Add to a numJEr or a register
void _VM_ADD(VM* this) {
  ALTER_REGISTERS(+=);
}

// Subtract to a numJEr or a register
void _VM_SUB(VM* this) {
  ALTER_REGISTERS(-=);
}

// Multiply to a numJEr or a register
void _VM_MUL(VM* this) {
  ALTER_REGISTERS(*=);
}

// Multiply to a numJEr or a register
void _VM_DIV(VM* this) {
  ALTER_REGISTERS(/=);
}

// Set the instruction pointer.
void _VM_JMP(VM* this) {
  if(_program[_ip + 1] - 1 < 0) {
    _ip = _regs[_program[_ip + 1]].data;
  } else {
    _ip = _program[_ip + 1];
  }
  _ip++;
}

// Jump if zero.
void _VM_JZ(VM* this) {
  CHECK_CONDITION_2(==);
}

// Jump if not zero.
void _VM_JNZ(VM* this) {
  CHECK_CONDITION_2(!=);
}

// Jump if equal to value or register.
void _VM_JE(VM* this) {
  CHECK_CONDITION_3(==);
}

// Jump if not equal to value or register.
void _VM_JNE(VM* this) {
  CHECK_CONDITION_3(!=);
}

void _VM_JGT(VM* this) {
  CHECK_CONDITION_3(>);
}

void _VM_JLT(VM* this) {
  CHECK_CONDITION_3(<);
}

void _VM_PUSH(VM* this) {
  assert(_sp < STACK_SIZE);
  if(_program[_ip] - 1 < 0) {
    _stack[_sp] = _regs[_program[_ip + 1]].data;
  } else {
    _stack[_sp] = _program[_ip + 1];
  }
  // printf("PUSH: %c\nIP: %d\n", _stack[_sp], _ip);
  _sp++;
  _ip += 2;
}

void _VM_POP(VM* this) {
  assert(_sp >= 0);
  _regs[_program[_ip + 1]].data = _stack[--_sp];
  // printf("POP: %c\nIP: %d\n", _stack[_sp], _ip);
  _ip += 2;
}

void _VM_OUT(VM* this) {
  if(_program[_ip] - 1 < 0) {
    printf("%c", _program[_ip + 1]);
  } else {
    printf("%c", _regs[_program[_ip + 1]].data);
  }
  _ip += 2;
}

void (*opcodes[])(VM*) = {
  [NOP]  = _VM_NOP,
  [MOV]  = _VM_MOV,
  [ADD]  = _VM_ADD,
  [SUB]  = _VM_SUB,
  [MUL]  = _VM_MUL,
  [DIV]  = _VM_DIV,
  [JMP]  = _VM_JMP,
  [JZ]   = _VM_JZ,
  [JNZ]  = _VM_JNZ,
  [JE]   = _VM_JE,
  [JNE]  = _VM_JNE,
  [JLT]  = _VM_JLT,
  [JGT]  = _VM_JGT,
  [PUSH] = _VM_PUSH,
  [POP]  = _VM_POP,
  [OUT]  = _VM_OUT, // For debug only!
  [HALT] = _VM_NOP,
};


// Undefine our local macros.
#undef _ip
#undef _regs
#undef _program
#undef _sp
#undef _stack
#undef CHECK_CONDITION_2
#undef CHECK_CONDITION_3
#undef ALTER_REGISTERS

#endif
