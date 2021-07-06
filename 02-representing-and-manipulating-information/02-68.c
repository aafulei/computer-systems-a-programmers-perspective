// 21/07/06 = Tue

/* Homework Problem 2.68 (**)

  Write code for a function with the following prototype:

  // Mask with least significant n bits set to 1
  // Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
  // Assume 1 <= n <= w
  int lower_one_mask(int n);

  Your function should follow the bit-level integer coding rules. Be careful of
  the case n = w. */

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
// lower_one_mask(00) = 0xffffffff
// lower_one_mask(01) = 0x00000001
// lower_one_mask(03) = 0x00000007
// lower_one_mask(17) = 0x0001ffff
// lower_one_mask(32) = 0xffffffff

#include <stdio.h>

int lower_one_mask(int n)
{
  int w = sizeof(int) << 3;
  // unsigned int and signed int are guaranteed to have the same size
  return (unsigned)-1 >> (w - n);
}

void test(int n)
{
  printf("lower_one_mask(%02d) = 0x%08x\n", n, lower_one_mask(n));
}

int main()
{
  test(1);
  test(3);
  test(17);
  test(32);
  return 0;
}
