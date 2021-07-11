// 21/07/11 = Sun

/* Homework Problem 2.92 (**)

Following the bit-level floating-point coding rules, implement the function
with the following prototype:

// Compute -f. If f is NaN, then return f.
float_bits float_negate(float_bits f);

For floating-point number f, this functions computes -f. If f is NaN, your
function should simply return f.

Test your function by evaluating it for all 2^32 values of argument f and
comparing the result to what would be obtained using your machine's floating-
point operations. */

// ----------
// Sample Run
// ----------
// float_negate(0x00000000) = 0x80000000:
//    as_float(0x80000000) = -0, while
//   -as_float(0x00000000) = -0
// float_negate(0x00000001) = 0x80000001:
//    as_float(0x80000001) = -1.4013e-45, while
//   -as_float(0x00000001) = -1.4013e-45
// float_negate(0xffffffff) = 0xffffffff:
//    as_float(0xffffffff) = nan, while
//   -as_float(0xffffffff) = nan
// float_negate(0x00bc614e) = 0x80bc614e:
//    as_float(0x80bc614e) = -1.73e-38, while
//   -as_float(0x00bc614e) = -1.73e-38
// Exhaustive test passed with 4294967296 tests in 29.2 seconds!

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
float_bits float_negate(float_bits f)
{
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if (exp == 0xff && frac != 0)
    return f;
  else
    return (~f & 0x80000000) | (exp << 23) | frac;
}

void test(float_bits f)
{
  float_bits n = float_negate(f);
  printf("float_negate(0x%08x) = 0x%08x:\n"
         "\t as_float(0x%08x) = %g, while\n"
         "\t-as_float(0x%08x) = %g\n",
         f, n, n, as_float(n), f, -as_float(f));
}

void exhaustive_test()
{
  clock_t tbeg = clock();
  unsigned long count = 0;
  unsigned f = 0;
  do {
    float_bits n = float_negate(f);
    float result = -as_float(f);
    if (isnan(result)) {
      if (f != n) {
        printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
        return;
      }
    }
    else {
      if (as_float(n) != result) {
        printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
        return;
      }
    }
    ++f;
    ++count;
  } while (f);
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
