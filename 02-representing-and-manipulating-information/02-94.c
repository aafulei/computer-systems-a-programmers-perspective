// 21/07/11 = Sun

/* Homework Problem 2.94 (***)

Following the bit-level floating-point coding rules, implement the function
with the following prototype:

// Computer 2 * f. If f is NaN, then return f.
float_bits float_twice(float_bits f);

For floating-point number f, this functions computes 2.0 * f. If f is NaN, your
function should simply return f.

Test your function by evaluating it for all 2^32 values of argument f and
comparing the result to what would be obtained using your machine's floating-
point operations. */

// ----------
// Sample Run
// ----------
// float_twice(0x00000000) = 0x00000000:
//   as_float(0x00000000)       = 0, while
//   as_float(0x00000000) * 2.0 = 0
// float_twice(0x00000001) = 0x00000002:
//   as_float(0x00000002)       = 2.8026e-45, while
//   as_float(0x00000001) * 2.0 = 2.8026e-45
// float_twice(0xffffffff) = 0xffffffff:
//   as_float(0xffffffff)       = nan, while
//   as_float(0xffffffff) * 2.0 = nan
// float_twice(0x00bc614e) = 0x013c614e:
//   as_float(0x013c614e)       = 3.46e-38, while
//   as_float(0x00bc614e) * 2.0 = 3.46e-38
// Exhaustive test passed with 4294967296 tests in 34.9 seconds!

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
float_bits float_twice(float_bits f)
{
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if (exp == 0xff /* nan or inf */)
    return f;
  else if (exp == 0 /* denormalized */) {
    if (frac & 0x400000 /* denormalized --> normalized */) {
      ++exp;
    }
    frac <<= 1;
  }
  else if (exp == 0xfe /* normalized and would overflow */) {
    frac = 0;
    ++exp;
  }
  else /* normalized and won't overflow */ {
    ++exp;
  }

  return (sign << 31) | (exp << 23) | frac;
}

void test(float_bits f)
{
  float_bits t = float_twice(f);
  printf("float_twice(0x%08x) = 0x%08x:\n"
         "\tas_float(0x%08x)       = %g, while\n"
         "\tas_float(0x%08x) * 2.0 = %g\n",
         f, t, t, as_float(t), f, as_float(f) * 2.0);
}

void exhaustive_test()
{
  clock_t tbeg = clock();
  unsigned long count = 0;
  unsigned f = 0;
  do {
    float_bits t = float_twice(f);
    float result = as_float(f) * 2.0;
    if (isnan(result)) {
      if (f != t) {
        printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
        return;
      }
    }
    else {
      if (as_float(t) != result) {
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
