#ifndef __VM_TYPES_H__
#define __VM_TYPES_H__

#include <stdint.h>

#if _____LP64_____
  typedef uint64_t vm_uint_t;
#else
  typedef uint32_t vm_uint_t;
#endif

#if _____LP64_____
  typedef int64_t vm_int_t;
#else
  typedef int32_t vm_int_t;
#endif

#endif

typedef double vm_float_t;
