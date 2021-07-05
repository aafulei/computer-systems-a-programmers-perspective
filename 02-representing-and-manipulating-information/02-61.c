// 21/07/05 = Mon

/* Practice Problem 2.61 (**)

  Write C expressions that evaluate to 1 when the following conditions are true
  and to 0 when they are false. Assume x is of type int.

  A. Any bit of x equals 1.

  B. Any bit of x equals 0.

  C. Any bit in the least significant byte of x equals 1.

  D. Any bit in the most significant byte of x equals 1. */

/* ------------------------------
   Bit-Level Integer Coding Rules
   ------------------------------

  - Assumptions

    - two's-complement form

    - right shifts performed arithmetically

    - int is w bits long (use sizeof(int) << 3 to compute w)

  - Forbidden

    - conditionals, loops, switch, function calls, and macro invocations

    - division, modulus, and multiplication

    - relative comparisons (<, >, <=, and >=)

  - Allowed

    - all bit-level and logic operations

    - left and right shifts, with amounts between 0 and w - 1

    - addition and subtraction

    - equality (==) and inequality (!=) (some problems do not allow these)

    - INT_MIN and INT_MAX

    - casting between int and unsigned */

// ----------
// Sample Run
// ----------
// has_one(0x00000000) = 0
// has_one(0x00000001) = 1
// has_one(0x00001010) = 1
// has_one(0xffffffff) = 1
// has_zero(0x00000000) = 1
// has_zero(0x00000001) = 1
// has_zero(0x00001010) = 1
// has_zero(0xffffffff) = 0
// lsb_has_one(0x00000080) = 1
// lsb_has_one(0x00000100) = 0
// msb_has_one(0x00ffffff) = 0
// msb_has_one(0x80000000) = 1

#include <stdio.h>

int has_one(int x)
{
  return !!x;
}

int has_zero(int x)
{
  return !!~x;
}

int lsb_has_one(int x)
{
  return !!(x << ((sizeof(int) - 1) << 3));
}

int msb_has_one(int x)
{
  return !!(x >> ((sizeof(int) - 1) << 3));
}


int main()
{
  printf("has_one(0x%08x) = %d\n", 0x0000, has_one(0x0000));
  printf("has_one(0x%08x) = %d\n", 0x0001, has_one(0x0001));
  printf("has_one(0x%08x) = %d\n", 0x1010, has_one(0x1010));
  printf("has_one(0x%08x) = %d\n", 0xffffffff, has_one(0xffffffff));
  printf("has_zero(0x%08x) = %d\n", 0x0000, has_zero(0x0000));
  printf("has_zero(0x%08x) = %d\n", 0x0001, has_zero(0x0001));
  printf("has_zero(0x%08x) = %d\n", 0x1010, has_zero(0x1010));
  printf("has_zero(0x%08x) = %d\n", 0xffffffff, has_zero(0xffffffff));
  printf("lsb_has_one(0x%08x) = %d\n", 0x0080, lsb_has_one(0x0080));
  printf("lsb_has_one(0x%08x) = %d\n", 0x0100, lsb_has_one(0x0100));
  printf("msb_has_one(0x%08x) = %d\n", 0xffffff, msb_has_one(0xffffff));
  printf("msb_has_one(0x%08x) = %d\n", 0x80000000, msb_has_one(0x80000000));
  return 0;
}
