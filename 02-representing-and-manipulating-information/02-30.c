// 21/07/01 = Thu

/* Practice Problem 2.30

Write a function with the following prototype:

// Determine whether arguments can be added without overflow
int tadd_ok(int x, int y);

This function should return 1 if arguments x and y can be added without causing
overflow. */

// ----------
// Sample Run
// ----------
// tadd_ok(0, 2147483647) = 1
// tadd_ok(0, -2147483648) = 1
// tadd_ok(2147483647, 2147483647) = 0
// tadd_ok(-2147483648, -1) = 0
// tadd_ok(-2147483648, 2147483647) = 1

#include <limits.h>
#include <stdio.h>

int tadd_ok(int x, int y)
{
  return !(x > 0 && y > 0 && x + y <= 0 || x < 0 && y < 0 && x + y >= 0);
}

void test(int x, int y)
{
  printf("tadd_ok(%d, %d) = %d\n", x, y, tadd_ok(x, y));
}

int main()
{
  test(0, INT_MAX);
  test(0, INT_MIN);
  test(INT_MAX, INT_MAX);
  test(INT_MIN, -1);
  test(INT_MIN, INT_MAX);
  return 0;
}
