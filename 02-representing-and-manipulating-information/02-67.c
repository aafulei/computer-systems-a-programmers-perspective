// 21/07/06 = Tue

/* Homework Problem 2.67 (**)

You are given the task of writing a procedure int_size_is_32() that yields 1 on
a machine for which an int is 32 bits, and yields 0 otherwise. You are not
allowed to used the sizeof operator. Here is a first attemp:

int bad_int_size_is_32()
{
  int set_msb = 1 << 31;
  int beyond_msb = 1 << 32;
  // set_msb is nonzero when word size >= 32
  // beyond_msb is zero when word size <= 32
  return set_msb && !beyond_msb;
}

When compiled an run on a 32-bit SUN SPARC, however, this procedure returns 0.
The following compiler message gives us an indication of the problem:

  warning: left shift count >= width of type

A. In what way does our code fail to comply with the C standard?

B. Modify the code to run properly on any machine for which data type int is at
   least 32 bits.

C. Modify the code to run properly on any machine for which data type int is at
   least 16 bits. */

// Answer: A. The C standard requires that a bitwise shift be within range
//            [0, sizeof(int_type) * 8) given an integer type int_type. For a
//            32-bit integer, the valid range is [0, 32), or [0, 31]. The
//            expression 1 << 32 fails to comply with the standard on a 32-bit
//            machine. What's more, if the machine is 16-bit, then the
//            expression 1 << 31 fails to comply with the standard as well.
//
//         B. and C. See code below.

// ------------
// Sample Build
// ------------
// warning: result of '2 << 31' requires 34 bits to represent, but 'int' only
// has 32 bits [-Wshift-overflow=]

// ----------
// Sample Run
// ----------
// int_size_is_32_at_least_32() = 1
// int_size_is_32_at_least_16() = 1

#include <stdio.h>

int int_size_is_32_at_least_32()
{
  return !(2 << 31);
}

int int_size_is_32_at_least_16()
{
  int set_msb = 0x8000 << 15 << 1;
  int beyond_msb = set_msb << 1;
  return set_msb && !beyond_msb;
}

int main()
{
  printf("int_size_is_32_at_least_32() = %d\n", int_size_is_32_at_least_32());
  printf("int_size_is_32_at_least_16() = %d\n", int_size_is_32_at_least_16());
  return 0;
}
