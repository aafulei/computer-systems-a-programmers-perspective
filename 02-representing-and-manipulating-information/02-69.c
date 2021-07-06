// 21/07/06 = Tue

/* Homework Problem 2.69 (***)

Write code for a function with the following prototype:

// Do rotating left shift. Assume 0 <= n < w.
// Examples when x = 0x12345678 and w = 32:
//    n = 4 -> 0x23456781, n = 20 -> 0x67812345
// unsigned rotate_left(unsigned x, int n);

Your function should follow the bit-level integer coding rules. Be case of the
case n = 0. */

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
// rotate_left(0x12345678, 0) = 0x12345678
// rotate_left(0x12345678, 1) = 0x2468acf0
// rotate_left(0x12345678, 4) = 0x23456781
// rotate_left(0x12345678, 20) = 0x67812345
// rotate_left(0x12345678, 31) = 0x091a2b3c

#include <stdio.h>

unsigned rotate_left(unsigned x, int n)
{
  unsigned w = sizeof(int) << 3;
  unsigned oldx = x;
  x <<= n;
  return x |= (oldx >> (w - n));
}

void test(unsigned x, int n)
{
  printf("rotate_left(0x%08x, %d) = 0x%08x\n", x, n, rotate_left(x, n));
}

int main()
{
  test(0x12345678, 0);
  test(0x12345678, 1);
  test(0x12345678, 4);
  test(0x12345678, 20);
  test(0x12345678, 31);
  return 0;
}
