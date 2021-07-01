// 21/07/01 = Thu

/* Practice Problem 2.31

Your coworker gets impatient with your analysis of the overflow conditions for
two's-complement addition and present you with the following implementation of
tadd_ok:

// Determine whether arguments can be added without overflow
// WARNING: This code is buggy.
int tadd_ok(int x, int y)
{
  int sum = x + y;
  return (sum-x == y) && (sum-y == x);
}

You look at the code and laugh. Explain why.

Answer: The code always returns 1, even when overflow happens. For example,
assuming that int has 32 bits, let x = 2147483647 (0x7f'ff'ff'ff), y = 1. Then
a positive overflow happens, and the sum is -2147483648 (0x80'00'00'00).
However, overflow happens as well for (sum-x) and (sum-y), and it is always
that (sum-x == y) and (sum-y == x). */

// ----------
// Sample Run
// ----------
// tadd_ok_debug(2147483647, 1): enter
// tadd_ok_debug(2147483647, 1): sum = -2147483648
// tadd_ok_debug(2147483647, 1): sum - x = (-2147483648) - (2147483647) = 1
// tadd_ok_debug(2147483647, 1): sum - y = (-2147483648) - (1) = 2147483647
// tadd_ok_debug(2147483647, 1): return 1

#include <stdio.h>

int tadd_ok_debug(int x, int y)
{
  printf("tadd_ok_debug(%d, %d): enter\n", x, y);
  int sum = x + y;
  printf("tadd_ok_debug(%d, %d): sum = %d\n", x, y, sum);
  printf("tadd_ok_debug(%d, %d): sum - x = (%d) - (%d) = %d\n", x, y, sum, x,
         sum - x);
  printf("tadd_ok_debug(%d, %d): sum - y = (%d) - (%d) = %d\n", x, y, sum, y,
         sum - y);
  printf("tadd_ok_debug(%d, %d): return %d\n", x, y,
         (sum - x == y) && (sum - y == x));
  return (sum - x == y) && (sum - y == x);
}

int main()
{
  tadd_ok_debug(0x7fffffff, 1);
  return 0;
}
