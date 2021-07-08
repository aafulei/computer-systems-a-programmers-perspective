// 21/07/08 = Thu

/* Homework Problem 2.80 (***)

Write code for a function threefourths that, for integer argument x, computes
the value of 3/4 x, rounded towards zero. It should not overflow. Your function
should follow the bit-level integer coding rules. */

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
// threefourths(0) = 0 (exact ~= 0.0)
// threefourths(1) = 0 (exact ~= 0.8)
// threefourths(2) = 1 (exact ~= 1.5)
// threefourths(3) = 2 (exact ~= 2.2)
// threefourths(4) = 3 (exact ~= 3.0)
// threefourths(5) = 3 (exact ~= 3.8)
// threefourths(6) = 4 (exact ~= 4.5)
// threefourths(7) = 5 (exact ~= 5.2)
// threefourths(8) = 6 (exact ~= 6.0)
// threefourths(-1) = 0 (exact ~= -0.8)
// threefourths(-2) = -1 (exact ~= -1.5)
// threefourths(-3) = -2 (exact ~= -2.2)
// threefourths(-4) = -3 (exact ~= -3.0)
// threefourths(-5) = -3 (exact ~= -3.8)
// threefourths(-6) = -4 (exact ~= -4.5)
// threefourths(-7) = -5 (exact ~= -5.2)
// threefourths(-8) = -6 (exact ~= -6.0)
// threefourths(2147483647) = 1610612735 (exact ~= 1610612735.2)
// threefourths(-2147483648) = -1610612736 (exact ~= -1610612736.0)

#include <limits.h>
#include <stdio.h>

int threefourths(int x)
{
  unsigned v = (sizeof(int) << 3) - 1;
  int s = (unsigned)x >> v;
  int large = x >> 2;
  large = (large << 1) + large;
  int small = (x & 0x3);
  small = ((small << 1) + small) >> 2;
  // bias 1 for rounding-up negative numbers: negative and indivisible by 4
  int bias = s && (x & 0x3);
  return large + small + bias;
}

void test(int x)
{
  printf("threefourths(%d) = %d (exact ~= %.1f)\n", x, threefourths(x),
         x / 4.0 * 3);
}

int main()
{
  test(0);
  test(1);
  test(2);
  test(3);
  test(4);
  test(5);
  test(6);
  test(7);
  test(8);
  test(-1);
  test(-2);
  test(-3);
  test(-4);
  test(-5);
  test(-6);
  test(-7);
  test(-8);
  test(INT_MAX);
  test(INT_MIN);
  return 0;
}
