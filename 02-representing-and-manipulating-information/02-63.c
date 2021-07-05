// 21/07/05 = Mon

/* Practice Problem 2.63

Fill in code for the following C functions. Function srl performs a logical
right shift using an arithmetic right shift (given by value xsra), followed by
other operations not including right shifts or division. funciton sra performs
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

#include <stdio.h>

unsigned srl(unsigned x, int k)
{
  // Perform shift arithmetically
  unsigned xsra = (int)x >> k;
}

int sra(int x, int k)
{
  // Perform shift logically
  int xsrl = (unsigned)x >> k;
}

int main()
{
  return 0;
}
