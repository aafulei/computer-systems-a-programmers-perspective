// 21/07/05 = Mon

/* Homework Problem 2.63 (***)

Fill in code for the following C functions. Function srl performs a logical
right shift using an arithmetic right shift (given by value xsra), followed by
other operations not including right shifts or division. Funciton sra performs
an arithmetic right shift using a logical right shift (given by value xsrl),
followed by other operations not including right shifts or division. You may
use the computation 8 * sizeof(int) to determine w, the number of bits in data
type int. The shift amount k can range from 0 to w - 1.

unsigned srl(unsigned x, int k)
{
  // Perform shift arithmetically
  unsigned xsra = (int)x >> k;
  ...
}

int sra(int x, int k)
{
  // Perform shift logically
  int xsrl = (unsigned)x >> k;
  ...
} */

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
// srl(0x000000ff,  3) = 0x0000001f
// srl(0xff000000,  3) = 0x1fe00000
// srl(0xffffffff, 30) = 0x00000003
// srl(0xffffffff, 31) = 0x00000001
// sra(0x7f000000,  3) = 0x0fe00000
// sra(0xff000000,  3) = 0xffe00000
// sra(0x70000000, 30) = 0x00000001
// sra(0x80000000, 30) = 0xfffffffe
// sra(0x70000000, 31) = 0x00000000
// sra(0x80000000, 31) = 0xffffffff

#include <stdio.h>

unsigned srl(unsigned x, int k)
{
  // Perform shift arithmetically
  unsigned xsra = (int)x >> k;
  unsigned w = sizeof(int) << 3;
  unsigned mask = (2 << k) - 1;
  mask <<= w - k;
  return xsra &= ~mask;
}

int sra(int x, int k)
{
  // Perform shift logically
  int xsrl = (unsigned)x >> k;
  unsigned w = sizeof(int) << 3;
  int is_neg = !!(x & (1 << (w - 1)));
  int mask = ((is_neg + 1) << k) - is_neg;
  mask <<= w - k;
  return xsrl |= mask;
}

int main()
{
  printf("srl(0x000000ff,  3) = 0x%08x\n", srl(0xff, 3));
  printf("srl(0xff000000,  3) = 0x%08x\n", srl(0xff000000, 3));
  printf("srl(0xffffffff, 30) = 0x%08x\n", srl(0xffffffff, 30));
  printf("srl(0xffffffff, 31) = 0x%08x\n", srl(0xffffffff, 31));
  printf("sra(0x7f000000,  3) = 0x%08x\n", sra(0x7f000000, 3));
  printf("sra(0xff000000,  3) = 0x%08x\n", sra(0xff000000, 3));
  printf("sra(0x70000000, 30) = 0x%08x\n", sra(0x70000000, 30));
  printf("sra(0x80000000, 30) = 0x%08x\n", sra(0x80000000, 30));
  printf("sra(0x70000000, 31) = 0x%08x\n", sra(0x70000000, 31));
  printf("sra(0x80000000, 31) = 0x%08x\n", sra(0x80000000, 31));
  return 0;
}
