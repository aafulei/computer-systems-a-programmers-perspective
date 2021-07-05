// 21/07/05 = Mon

/* Homework Problem 2.65 (****)

Write code to implement the following function:

// Return 1 when x contains an odd number of 1s; 0 otherwise.
// Assume w = 32
int odd_ones(unsigned x);

Your function should follow the bit-level integer coding rules, except that you
may assume that data type int has w = 32 bits.

Your code should contain a total of at most 12 arithmetic, bitwise and logical
operations. */

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
// odd_ones(0x00000000) = 0
// odd_ones(0x00000001) = 1
// odd_ones(0x0000000e) = 1
// odd_ones(0x000000ff) = 0
// odd_ones(0x00007000) = 1
// odd_ones(0x0008ffff) = 1
// odd_ones(0xabdb14cd) = 0
// odd_ones(0xabdb15cd) = 1

#include <stdio.h>

int odd_ones(unsigned x)
{
  x ^= (x >> 16);
  x ^= (x >> 8);
  x ^= (x >> 4);
  x ^= (x >> 2);
  x ^= (x >> 1);
  return (x &= 1);
}

void test(unsigned x)
{
  printf("odd_ones(0x%08x) = %d\n", x, odd_ones(x));
}

int main()
{
  test(0x0);
  test(0x1);
  test(0xe);
  test(0xff);
  test(0x00007000);
  test(0x0008ffff);
  test(0xabdb14cd);
  test(0xabdb15cd);
  return 0;
}
