// 21/07/11 = Sun

/* Homework Problem 2.89 (*)

We are running programs on a machine where values of type int have a 32-bit
two's-complement representation. Values of type float use the 32-bit IEEE
format, and values of type double use the 64-bit IEEE format.

We generate arbitrary integer values x, y, and z, and convert them to values of
double as follows:

// Create some arbitrary values
int x = random();
int y = random();
int z = random();

// Convert to double
double dx = (double)x;
double dy = (double)y;
double dz = (double)z;

For each of the following C expressions, you are to indicate whether or not the
expression always yields 1. If it always yields 1, describe the underlying
mathematical principles. Otherwise, give an example of arguments that make it
yield 0. Note that you cannot use an IA32 machine running GCC to test your
answers, since it would use the 80-bit extended-precision representation for
both float and double.

A. (float)x == (float)dx
B. dx - dy == (double)(x - y)
C. (dx + dy) + dz == dx + (dy + dz)
D. (dx * dy) * dz == dx * (dy * dz)
E. dx / dx == dz / dz

*/

/* Answer:

A. Always true. LHS is (float)x. RHS is (float)(double)x. Converting int to
   double preserves all the precision and will not overflow. When converting to
   float, both sides will round to even.

B. Not necessarily true, because the RHS may overflow while the LHS won't.
   Example: Let x be INT_MIN and y be 1. The LHS would have value INT_MIN - 1,
   while the RHS would still have a value within the range of type int
   (INT_MAX).

C. Always true. Note that dx, dy, and dz all assume values within the range of
   a 32-bit int. Overflow won't happen. Thus (dx + dy) + dz == dx + (dy + dz).

D. Not necessarily true. Note that for type double, number of exponent bits k =
   11 and number of siginificand bits n = 64 - 1 - 11 = 52. The multiplication
   of two 32-bit integers requires 64 bits to precisely represent all the
   values, which a double cannot entertain. Thus a loss of precision might
   occur. Example: Let x be 0x12345678, y be 0x87654321, z be 0x382abc2f.

E. Not necessarily true. Let x be 1 and z be 0. LHS is 1 but RHS is NaN.

*/

// ----------
// Sample Run
// ----------
// dx - dy = -2147483649.000000, while (double)(x-y) = 2147483647.000000
// (dx * dy) * dz = -582346066684446005167915008.000000, while
// dx * (dy * dz) = -582346066684446073887391744.000000
// dx / dx = 1.000000, while dz / dz = nan

#include <limits.h>
#include <stdio.h>

void B()
{
  int x = INT_MIN;
  int y = 1;
  double dx = (double)x;
  double dy = (double)y;
  double lhs = dx - dy;
  double rhs = (double)(x - y);
  printf("dx - dy = %lf, while (double)(x-y) = %lf\n", lhs, rhs);
}

void D()
{
   int x = 0x12345678;
   int y = 0x87654321;
   int z = 0x382abc2f;
   double dx = (double)x;
   double dy = (double)y;
   double dz = (double)z;
   double lhs = (dx * dy) * dz;
   double rhs = dx * (dy * dz);
   printf("(dx * dy) * dz = %lf, while\ndx * (dy * dz) = %lf\n", lhs, rhs);
}

void E()
{
  int x = 1;
  int z = 0;
  double dx = (double)x;
  double dz = (double)z;
  double lhs = dx / dx;
  double rhs = dz / dz;
  printf("dx / dx = %lf, while dz / dz = %lf\n", lhs, rhs);
}

int main()
{
  B();
  D();
  E();
  return 0;
}
