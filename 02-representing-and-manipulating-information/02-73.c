// 21/07/06 = Tue

/* Homework Problem 2.73 (**)

Write code for a function with the following prototype.

// Addition that saturates to TMin or TMax
int saturating_add(int x, int y);

Instead of oveflowing the way normal two's-complement addition does, saturating
addition return TMax when there would be positive overflow, and TMin when there
would be negative overflow. Saturating arithmetic is commonly used in programs
that perform digital signal processing.

You function should follow the bit-level integer coding rules. */

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
// saturating_add( 2147483646,           1) = 2147483647
// saturating_add( 2147483647,           1) = 2147483647
// saturating_add( 2147483647,  2147483647) = 2147483647
// saturating_add( 2147483647, -2147483648) = -1
// saturating_add(-2147483647,          -1) = -2147483648
// saturating_add(-2147483648,          -1) = -2147483648
// saturating_add(-2147483648, -2147483648) = -2147483648

#include <limits.h>
#include <stdio.h>

int saturating_add(int x, int y)
{
  int sum = (unsigned)x + y;
  int v = (sizeof(int) << 3) - 1;
  // mask is 0xffffffff if overflow else 0x00000000
  int mask = (~(x ^ y) & (x ^ sum)) >> v;
  // min_max is 0x80000000 if sum >= 0 else 0x7fffffff
  int min_max = (1 << v) ^ (sum >> v);
  return (~mask & sum) + (mask & min_max);
}

void test(int x, int y)
{
  printf("saturating_add(%11d, %11d) = %d\n", x, y, saturating_add(x, y));
}

int main()
{
  test(INT_MAX - 1, 1);
  test(INT_MAX, 1);
  test(INT_MAX, INT_MAX);
  test(INT_MAX, INT_MIN);
  test(INT_MIN + 1, -1);
  test(INT_MIN, -1);
  test(INT_MIN, INT_MIN);
  return 0;
}
