// 21/07/07 = Wed

/* Homework Problem 2.77 (**)

Suppose we are given the task of generating code to multiply integer variable x
by various different constant factors K. To be efficient, we want to use only
the operations +, -, and <<. For the following values of K, write C expressions
to performa the multiplication using at most three operations per expression.

A. K = 17

B. K = -7

C. K = 60

D. K = -112 */

// ----------
// Sample Run
// ----------
// mult_17(0) = 0
// mult_n7(0) = 0
// mult_60(0) = 0
// mult_n112(0) = 0
// mult_17(1) = 17
// mult_n7(1) = -7
// mult_60(1) = 60
// mult_n112(1) = -112
// mult_17(-1) = -17
// mult_n7(-1) = 7
// mult_60(-1) = -60
// mult_n112(-1) = 112
// mult_17(2) = 34
// mult_n7(2) = -14
// mult_60(2) = 120
// mult_n112(2) = -224
// mult_17(-3) = -51
// mult_n7(-3) = 21
// mult_60(-3) = -180
// mult_n112(-3) = 336

#include <stdio.h>

int mult_17(int x)
{
  return (x << 4) + x;
}

int mult_n7(int x)
{
  return -((x << 3) - x);
}

int mult_60(int x)
{
  return (x << 6) - (x << 2);
}

int mult_n112(int x)
{
  return (x << 4) - (x << 7);
}

void test(int x)
{
  printf("mult_17(%d) = %d\n", x, mult_17(x));
  printf("mult_n7(%d) = %d\n", x, mult_n7(x));
  printf("mult_60(%d) = %d\n", x, mult_60(x));
  printf("mult_n112(%d) = %d\n", x, mult_n112(x));
}

int main()
{
  test(0);
  test(1);
  test(-1);
  test(2);
  test(-3);
  return 0;
}
