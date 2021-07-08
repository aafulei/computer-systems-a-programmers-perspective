// 21/07/08 = Thu

/* Homework Problem 2.84 (*)

Fill in the return value for the following procedure, which tests whether its
first argument is less than or equal to its second. Assume the function f2u
returns an unsigned 32-bit number having the same bit representation as its
floating-point argument. You can assume that neither argument is NaN. The two
flavors of zero, +0, and -0, are considered equal.

int float_le(float x, float y)
{
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);

  // Get the sign bits
  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;

  // Give an expression using only ux, uy, sx, and sy
  return     ;
}

*/

// ----------
// Sample Run
// ----------
// float_le(0, 0) = 1
// float_le(1e+10, 1e+10) = 1
// float_le(-1e-10, -1e-10) = 1
// float_le(-0.11, -0.01) = 1
// float_le(-0.01, -0.11) = 0
// float_le(1.11, 2.34) = 1
// float_le(2.34, 1.11) = 0
// float_le(0.001, 100) = 1
// float_le(100, 0.001) = 0
// float_le(-1000, 0.0001) = 1
// float_le(0.0001, -1000) = 0
// float_le(0, 0.0001) = 1
// float_le(0.0001, 0) = 0
// float_le(-1e+10, 1e-10) = 1
// float_le(1e-10, -1e+10) = 0

#include <stdio.h>

static unsigned f2u(float x)
{
  fprintf(stderr, "(debug) f2u(%g) = 0x%08x\n", x, *(unsigned *)&x);
  return *(unsigned *)&x;
}

int float_le(float x, float y)
{
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);

  // Get the sign bits
  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;

  // Give an expression using only ux, uy, sx, and sy
  return (ux == uy) || (sx > sy) || (sx == sy && (ux < uy) ^ sx);
}

void test(float x, float y)
{
  printf("float_le(%g, %g) = %d\n", x, y, float_le(x, y));
  if (x != y)
    printf("float_le(%g, %g) = %d\n", y, x, float_le(y, x));
}

int main()
{
  test(-0, 0);
  test(1e10, 1e10);
  test(-1e-10, -1e-10);
  test(-0.11, -0.01);
  test(1.11, 2.34);
  test(0.001, 100);
  test(-1000, 0.0001);
  test(0, 0.0001);
  test(-1e10, 1e-10);
  return 0;
}
