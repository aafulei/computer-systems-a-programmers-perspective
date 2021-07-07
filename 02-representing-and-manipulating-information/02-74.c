// 21/07/07 = Wed

/* Homework Problem 2.74 (**)

Write a function with the following prototype:

// Determine whether arguments can be subtracted without overflow
int tsub_ok(int x, int y);

This function should return 1 if the computation x - y does not overflow. */

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
// tsub_ok(0, 0) = 0
// tsub_ok(0, -1) = 0
// tsub_ok(2147483647, 2147483647) = 0
// tsub_ok(-2147483647, 1) = 0
// tsub_ok(0, -2147483648) = 1
// tsub_ok(2147483647, -2147483648) = 1
// tsub_ok(-2147483648, 2147483647) = 1
// tsub_ok(-2147483648, 1) = 1

#include <limits.h>
#include <stdio.h>

int tsub_ok(int x, int y)
{
  unsigned v = (sizeof(int) << 3) - 1;
  return (unsigned)((x ^ y) & ((x - y) ^ x)) >> v;
}

void test(int x, int y)
{
  printf("tsub_ok(%d, %d) = %d\n", x, y, tsub_ok(x, y));
}

int main()
{
  test(0, 0);
  test(0, -1);
  test(INT_MAX, INT_MAX);
  test(INT_MIN + 1, 1);
  test(0, INT_MIN);
  test(INT_MAX, INT_MIN);
  test(INT_MIN, INT_MAX);
  test(INT_MIN, 1);
  return 0;
}
