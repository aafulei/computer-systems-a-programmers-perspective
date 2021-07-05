// 21/07/05 = Mon

/* Homework Problem 2.66 (***)

Write code to implement the following function:

// Generate mask indicating leftmost 1 in x. Assume w = 32.
// For example, 0xff00 --> 0x8000, and 0x6600 --> 0x4000.
// If x = 0, then return 0.
int leftmost_one(unsigned x)

Your function should follow the bit-level integer coding rules, except that you
may assume that data type int has w = 32 bits.

Your code should contain a total of at most 15 arithmetic, bitwise and logical
operations.

Hint: First transform x into a bit vector of the form [0...011...1]. */

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
// clang-format off
// leftmost_one(0x00000000) = 0x00000000, rightmost_one(0x00000000) = 0x00000000
// leftmost_one(0x70000000) = 0x40000000, rightmost_one(0x70000000) = 0x10000000
// leftmost_one(0x80000000) = 0x80000000, rightmost_one(0x80000000) = 0x80000000
// leftmost_one(0xfffffffe) = 0x80000000, rightmost_one(0xfffffffe) = 0x00000002
// leftmost_one(0x0000ff00) = 0x00008000, rightmost_one(0x0000ff00) = 0x00000100
// leftmost_one(0x00006600) = 0x00004000, rightmost_one(0x00006600) = 0x00000200
// leftmost_one(0x00770000) = 0x00400000, rightmost_one(0x00770000) = 0x00010000
// leftmost_one(0x00780000) = 0x00400000, rightmost_one(0x00780000) = 0x00080000
// leftmost_one(0x07800000) = 0x04000000, rightmost_one(0x07800000) = 0x00800000
// leftmost_one(0x0a780000) = 0x08000000, rightmost_one(0x0a780000) = 0x00080000
// clang-format on

#include <stdio.h>

int leftmost_one(unsigned x)
{
  unsigned long long xx = x;
  xx |= (xx >> 16);
  xx |= (xx >> 8);
  xx |= (xx >> 4);
  xx |= (xx >> 2);
  xx |= (xx >> 1);
  xx += 1;
  return xx >>= 1;
}

int rightmost_one(unsigned x)
{
  int nonzero = !!x;
  unsigned long long xx = x ^ (x - 1);
  xx += 1;
  // ugly, but I have no options as conditionals and multiplication are banned
  return xx >>= nonzero;
}

void test(unsigned x)
{
  printf("leftmost_one(0x%08x) = 0x%08x, ", x, leftmost_one(x));
  printf("rightmost_one(0x%08x) = 0x%08x\n", x, rightmost_one(x));
}

int main()
{
  test(0x0);
  test(0x70000000);
  test(0x80000000);
  test(0xfffffffe);
  test(0xff00);
  test(0x6600);
  test(0x00770000);
  test(0x00780000);
  test(0x07800000);
  test(0x0a780000);
  return 0;
}
