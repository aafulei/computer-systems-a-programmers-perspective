// 21/07/01 = Thu

/* Practice Problem 2.27

Write a function with the following prototype:

// Determine whether arguments can be added without overflow
int uadd_ok(unsigned x, unsigned y);

This function should return 1 if arguments x and y can be added without causing
overflow. */

// ----------
// Sample Run
// ----------
// uadd_ok(0, 1) = 1
// uadd_ok(1, 4294967294) = 1
// uadd_ok(1, 4294967295) = 0
// uadd_ok(4294967295, 4294967295) = 0
// uadd_ok(2147483647, 2147483648) = 1
// uadd_ok(2147483648, 2147483648) = 0

#include <stdio.h>

int uadd_ok(unsigned x, unsigned y)
{
  unsigned z = x + y;
  return z >=x && z >= y;
}

void test(unsigned x, unsigned y)
{
  printf("uadd_ok(%u, %u) = %d\n", x, y, uadd_ok(x, y));
}

int main()
{
  test(0, 1);
  test(1, -2);
  test(1, -1);
  test(-1, -1);
  test(((unsigned)-1) >> 1, (((unsigned)-1) >> 1) + 1);
  test((((unsigned)-1) >> 1) + 1, (((unsigned)-1) >> 1) + 1);
  return 0;
}
