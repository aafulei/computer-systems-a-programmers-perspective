// 21/07/01 = Thu

/* Practice Problem 2.32

You are assigned the task of writing code for a function tsub_ok, with
arguments x and y, that will return 1 if computing x-y does not cause overflow.
Having just written the code for Problem 2.30, you write the following:

// Determine whether arguments can be subtracted without oveflow.
// WARNING: This code is buggy.
int tsub_ok(int x, int y)
{
  return tadd_ok(x, -y);
}

For what values of x and y will this function give incorrect results? Writing a
correct version of this function is left as an exercise (Problem 2.74) */

// Answer: When y = INT_MIN (-2147483648 for 32-bit int) this function will
// give incorrect results.

// ----------
// Sample Run
// ----------
// tsub_ok(-2147483647, -2147483648) = 0  /* should be 1! */
// tsub_ok(-1, -2147483648) = 0           /* should be 1! */
// tsub_ok(0, -2147483648) = 1            /* should be 0! */
// tsub_ok(1, -2147483648) = 1            /* should be 0! */

#include <limits.h>
#include <stdio.h>

int tadd_ok(int x, int y)
{
  return !(x > 0 && y > 0 && x + y <= 0 || x < 0 && y < 0 && x + y >= 0);
}

// Determine whether arguments can be subtracted without oveflow.
// WARNING: This code is buggy.
int tsub_ok(int x, int y)
{
  return tadd_ok(x, -y);
}

void test(int x, int y)
{
  printf("tsub_ok(%d, %d) = %d\n", x, y, tsub_ok(x, y));
}

int main()
{
  test(INT_MIN + 1, INT_MIN);
  test(-1, INT_MIN);
  test(0, INT_MIN);
  test(1, INT_MIN);
  return 0;
}
