// 21/07/07 = Wed

/* Homework Problem 2.78 (**)

Write code for a function with the following prototype:

// Divide by power of 2. Assume 0 <= k < w-1.
int divide_power2(int x, int k);

The function should compute x / 2^k with correct rounding, and it should follow
the bit-level integer coding rules. */

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
// divide_power2(x=0, k=0) = 0 (exact ~= 0.00)
// divide_power2(x=1, k=0) = 1 (exact ~= 1.00)
// divide_power2(x=-1, k=0) = -1 (exact ~= -1.00)
// divide_power2(x=1, k=1) = 0 (exact ~= 0.50)
// divide_power2(x=-1, k=1) = 0 (exact ~= -0.50)
// divide_power2(x=127, k=5) = 3 (exact ~= 3.97)
// divide_power2(x=-127, k=5) = -3 (exact ~= -3.97)

#include <math.h>
#include <stdio.h>

// translate (x < 0 ? x + (1 << k) - 1 : x) >> k with the coding rules
int divide_power2(int x, int k)
{
  unsigned v = (sizeof(int) << 3) - 1;
  int is_neg = (unsigned)x >> v;
  return (x + ((is_neg) << k) - (is_neg)) >> k;
}

void test(int x, int k)
{
  printf("divide_power2(x=%d, k=%d) = %d (exact ~= %.2f)\n", x, k,
         divide_power2(x, k), (float)x / pow(2, k));
}

int main()
{
  test(0, 0);
  test(1, 0);
  test(-1, 0);
  test(1, 1);
  test(-1, 1);
  test(127, 5);
  test(-127, 5);
  return 0;
}
