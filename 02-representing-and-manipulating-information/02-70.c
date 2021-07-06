// 21/07/06 = Tue

/* Homework Problem 2.70 (**)

  Write code for the function with the following prototype:

  // Return 1 when x can be represented as an n-bit, two's-complment number, 0
  // otherwise. Assume 1 <= n <= w.
  int fits_bits(int x, int n);

  Your function should follow the bit-level integer coding rules. */

/* Bit-Level Integer Coding Rules

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
// fits_bits(0x00000000, 1) = 1
// fits_bits(0x00000001, 1) = 1
// fits_bits(0x00000002, 1) = 0
// fits_bits(0x00008000, 15) = 0
// fits_bits(0x00008000, 16) = 1
// fits_bits(0x00008000, 17) = 1
// fits_bits(0xffffffff, 1) = 0
// fits_bits(0xffffffff, 32) = 1
// fits_bits(0x7fffffff, 31) = 1
// fits_bits(0x80000000, 31) = 0
// fits_bits(0x80000000, 32) = 1

#include <limits.h>
#include <stdio.h>

int fits_bits(int x, int n)
{
  unsigned w = sizeof(int) << 3;
  int masked = x & ((unsigned)-1 >> (w - n));
  return !(x ^ masked);
}

void test(int x, int n)
{
  printf("fits_bits(0x%08x, %d) = %d\n", x, n, fits_bits(x, n));
}

int main()
{
  test(0x0, 1);
  test(0x1, 1);
  test(0x2, 1);
  test(0x00008000, 15);
  test(0x00008000, 16);
  test(0x00008000, 17);
  test(-1, 1);
  test(-1, sizeof(int) << 3);
  test(INT_MAX, (sizeof(int) << 3) - 1);
  test(INT_MIN, (sizeof(int) << 3) - 1);
  test(INT_MIN, (sizeof(int) << 3));
  return 0;
}
