/* Practice Problem 2.36

For the case where data type int has 32 bits, devise a version of tmult_ok
(Problem 2.35) that uses the 64-bit precision of data type int64_t, without
using division. */

// ----------
// Sample Run
// ----------
// tmult_ok(0, 2147483647) = 1
// tmult_ok(-2147483648, 0) = 1
// tmult_ok(1, -2147483648) = 1
// tmult_ok(-1, -2147483648) = 0
// tmult_ok(46340, 46340) = 1
// tmult_ok(46341, 46341) = 0
// tmult_ok(2147483647, -2147483648) = 0

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

int tmult_ok(int x, int y)
{
  return x * y == (int64_t)x * y;
}

void test(int x, int y)
{
  printf("tmult_ok(%d, %d) = %d\n", x, y, tmult_ok(x, y));
}

int main()
{
  test(0, INT_MAX);
  test(INT_MIN, 0);
  test(1, INT_MIN);
  test(-1, INT_MIN);
  test(sqrt(INT_MAX), sqrt(INT_MAX));
  test(sqrt(INT_MAX) + 1, sqrt(INT_MAX) + 1);
  test(INT_MAX, INT_MIN);
  return 0;
}
