// 21/07/11 = Sun

/* Homework Problem 2.93 (**)

Following the bit-level floating-point coding rules, implement the function
with the following prototype:

// Computer |f|. If f is NaN, then return f.
float_bits float_absval(float_bits f);

For floating-point number f, this functions computes |f|. If f is NaN, your
function should simply return f.

Test your function by evaluating it for all 2^32 values of argument f and
comparing the result to what would be obtained using your machine's floating-
point operations. */

// ----------
// Sample Run
// ----------
// float_absval(0x80000000) = 0x00000000:
//        as_float(0x00000000)  = 0, while
//   fabs(as_float(0x80000000)) = 0
// float_absval(0x3f800000) = 0x3f800000:
//        as_float(0x3f800000)  = 1, while
//   fabs(as_float(0x3f800000)) = 1
// float_absval(0xbf800000) = 0x3f800000:
//        as_float(0x3f800000)  = 1, while
//   fabs(as_float(0xbf800000)) = 1
// float_absval(0xcb3c614e) = 0x4b3c614e:
//        as_float(0x4b3c614e)  = 1.23457e+07, while
//   fabs(as_float(0xcb3c614e)) = 1.23457e+07
// Exhaustive test passed with 4294967296 tests in 30.8 seconds!

#include <math.h>
#include <stdio.h>
#include <time.h>

typedef unsigned float_bits;

float_bits as_bits(float value)
{
  return *(float_bits *)&value;
}

float as_float(float_bits bits)
{
  return *(float *)&bits;
}

float float_abs(float value)
{
  return fabs(value);
}

// single-precision: s = 1, k = 8, n = 23
// NaN is when exponents are all 1 and fractions are not all 0.
float_bits float_absval(float_bits f)
{
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if (exp == 0xff && frac != 0)
    return f;
  else
    return f << 1 >> 1;
}

void test(float_bits f)
{
  float_bits n = float_absval(f);
  printf("float_absval(0x%08x) = 0x%08x:\n"
         "\t     as_float(0x%08x)  = %g, while\n"
         "\tfabs(as_float(0x%08x)) = %g\n",
         f, n, n, as_float(n), f, float_abs(as_float(f)));
}

void exhaustive_test()
{
  clock_t tbeg = clock();
  unsigned long count = 0;
  unsigned f = 0;
  do {
    float_bits n = float_absval(f);
    float value = as_float(f);
    if (isnan(value)) {
      if (f != n) {
        printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
        return;
      }
    }
    else {
      if (as_float(n) != float_abs(value)) {
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
  test(as_bits(-0.f));
  test(as_bits(1.f));
  test(as_bits(-1.f));
  test(as_bits(-12345678.f));
  exhaustive_test();
  return 0;
}
