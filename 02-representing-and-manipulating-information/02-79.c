// 21/07/07 = Wed

/* Homework Problem 2.79 (**)

Write code for a function mul3div4 that, for integer argument x, computes
3 * x / 4 but follows the bit-level integer coding rules. Your code should
replicate the fact that the computation 3 * x can cause oveflow. */

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
// mul3div4(0) = 0
// mul3div4(1) = 0
// mul3div4(-1) = 0
// mul3div4(2) = 1
// mul3div4(-2) = -1
// mul3div4(400) = 300
// mul3div4(-400) = -300
// mul3div4(19999) = 14999
// mul3div4(-19999) = -14999
// mul3div4(20000) = 15000
// mul3div4(-20000) = -15000
// mul3div4(20001) = 15000
// mul3div4(-20001) = -15000
// mul3div4(2000000000) = 426258176
// mul3div4(-2000000000) = -426258176

#include <limits.h>
#include <stdio.h>

int mul3div4(int x)
{
  unsigned v = (sizeof(int) << 3) - 1;
  int is_neg = (unsigned)x >> v;
  int mul3 = (x << 1) + x;
  return (mul3 + ((is_neg) << 2) - (is_neg)) >> 2;
}

void test(int x)
{
  printf("mul3div4(%d) = %d\n", x, mul3div4(x));
}

int main()
{
  test(0);
  test(1);
  test(-1);
  test(2);
  test(-2);
  test(400);
  test(-400);
  test(19999);
  test(-19999);
  test(20000);
  test(-20000);
  test(20001);
  test(-20001);
  test(2000000000);
  test(-2000000000);
  return 0;
}
