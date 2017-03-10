#ifndef __VM_H__
#define __VM_H__

#include "vm_types.h"

// Register.
typedef enum _Register_Names {
  A = 1,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  IP,
  SP,
  FLAGS,
} Register_Names;
typedef union _Register {
  struct {
    uint16_t ah : 16;
    uint16_t al : 16;
    uint16_t bh : 16;
    uint16_t bl : 16;
  } chunks;
  vm_int_t data;
} Register;

// OPCodes.
typedef enum _OPCode_Names {
  NOP,
  MOV,
  ADD,
  SUB,
  MUL,
  DIV,
  JZ,
  JNZ,
  JE,
  JNE,
  JLT,
  JGT,
  JMP,
  PUSH,
  POP,
  OUT,
  HALT,
} OPCode_Names;

// The VM.
typedef struct _VM {
  vm_int_t *stack;
  Register *registers;
  vm_int_t *current_program;
} VM;

// Create and destroy.
VM *create_VM();
void destroy_VM();

// Set attributes.
int load_VM_Program(VM*, const vm_int_t*);
void run_VM(VM*);

#endif
