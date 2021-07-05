// 21/07/05 = Mon

/* Homework Problem 2.64 (*)

Write code to implement the following function:

// Return 1 when odd bit of x equals 1; 0 otherwise.
// Assume w = 32
int any_odd_ones(unsigned x);

Your function should follow the bit-level integer coding rules, except that you
may assume that data type int has w = 32 bits. */

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
// any_odd_ones(0x80000000) = 0
// any_odd_ones(0x00000001) = 1
// any_odd_ones(0x00000200) = 0
// any_odd_ones(0x00400000) = 1
// any_odd_ones(0x80000000) = 0
// any_odd_ones(0x00abcdef) = 1
// any_odd_ones(0xaaaaaaaa) = 0

#include <stdio.h>

int any_odd_ones(unsigned x)
{
  return !!(x &= 0x55555555);
}

void test(unsigned x)
{
  printf("any_odd_ones(0x%08x) = %d\n", x, any_odd_ones(x));
}

int main()
{
  test(0x80000000);
  test(0x00000001);
  test(0x00000200);
  test(0x00400000);
  test(0x80000000);
  test(0x00abcdef);
  test(0xaaaaaaaa);
  return 0;
}
