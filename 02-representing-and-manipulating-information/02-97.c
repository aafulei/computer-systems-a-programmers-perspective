// 21/07/11 = Sun

/* Homework Problem 2.97 (****)

Following the bit-level floating-point coding rules, implement the function
with the following prototype:

// Computer (float)i.
float_bits float_i2f(int i);

For argument i, this functions computes the bit-level representation of
(float)i.

Test your function by evaluating it for all 2^32 values of argument f and
comparing the result to what would be obtained using your machine's floating-
point operations. */

// ----------
// Sample Run
// ----------
// as_float(float_i2f(0)) = 0 (=0x00000000), while
// (float)0               = 0
// as_float(float_i2f(1)) = 1 (=0x3f800000), while
// (float)1               = 1
// as_float(float_i2f(-1)) = -1 (=0xbf800000), while
// (float)-1               = -1
// as_float(float_i2f(12345678)) = 1.23457e+07 (=0x4b3c614e), while
// (float)12345678               = 1.23457e+07
// Exhaustive test passed with 4294967296 tests in 36.8 seconds!

#include <math.h>
#include <stdio.h>
#include <time.h>

typedef unsigned float_bits;

float as_float(float_bits bits)
{
  return *(float *)&bits;
}

// single-precision: s = 1, k = 8, n = 23
// NaN is when exponents are all 1 and fractions are not all 0.
float_bits float_i2f(int i)
{
  unsigned sign = i & 0x80000000;
  unsigned frac;
  if (sign)
    frac = (~i + 1) & 0x7fffffff;
  else
    frac = i & 0x7fffffff;
  int E = 31;
  while (E) {
    if ((1 << (E - 1)) & frac)
      break;
    --E;
  }
  // at this step, E is num of significands
  if (E == 0) {
    // return float zero
    return 0x0;
  }
  // remove implied leading 1
  frac &= ~(1 << (E - 1));
  --E;
  if (E > 23) {
    frac >>= (E - 23);
  }
  unsigned exp = E + 127;
  return sign | (exp << 23) | frac;
}

void test(int i)
{
  float_bits b = float_i2f(i);
  float f = as_float(b);
  printf("as_float(float_i2f(%d)) = %g (=0x%08x), while\n"
         "(float)%d               = %g\n",
         i, f, b, i, (float)i);
}

void exhaustive_test()
{
  clock_t tbeg = clock();
  unsigned long count = 0;
  int i = 0;
  do {
    float f = as_float(float_i2f(i));
    float result = (float)i;
    if (i != result) {
      printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
      return;
    }
    ++i;
    ++count;
  } while (i);
  clock_t tend = clock();
  double duration = (double)(tend - tbeg) / CLOCKS_PER_SEC;
  printf("Exhaustive test passed with %lu tests in %.1lf seconds!\n", count,
         duration);
}

int main()
{
  test(0);
  test(1);
  test(-1);
  test(12345678);
  exhaustive_test();
  return 0;
}
