// 21/07/11 = Sun

/* Homework Problem 2.95 (***)

Following the bit-level floating-point coding rules, implement the function
with the following prototype:

// Computer 0.5 * f. If f is NaN, then return f.
float_bits float_half(float_bits f);

For floating-point number f, this functions computes 0.5 * f. If f is NaN, your
function should simply return f.

Test your function by evaluating it for all 2^32 values of argument f and
comparing the result to what would be obtained using your machine's floating-
point operations. */

// ----------
// Sample Run
// ----------
// float_half(0x00000000) = 0x00000000:
//   as_float(0x00000000)       = 0, while
//   as_float(0x00000000) / 2.f = 0
// float_half(0x00000001) = 0x00000000:
//   as_float(0x00000000)       = 0, while
//   as_float(0x00000001) / 2.f = 0
// float_half(0xffffffff) = 0xffffffff:
//   as_float(0xffffffff)       = nan, while
//   as_float(0xffffffff) / 2.f = nan
// float_half(0x00bc614e) = 0x005e30a7:
//   as_float(0x005e30a7)       = 8.64999e-39, while
//   as_float(0x00bc614e) / 2.f = 8.64999e-39
// Exhaustive test passed with 4294967296 tests in 36.7 seconds!

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
float_bits float_half(float_bits f)
{
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if (exp == 0xff /* nan or inf */) {
    return f;
  }
  else if (exp == 0 /* denormalized */) {
    unsigned lsb = frac & 0x1;
    frac >>= 1;
    // round to even
    if (lsb && (frac & 0x1))
      ++frac;
  }
  else if (exp == 1 /* normalized --> denormalized */) {
    exp = 0;
    unsigned lsb = frac & 0x1;
    frac >>= 1;
    frac |= 0x400000;
    // round to even
    if (lsb && (frac & 01))
      ++frac;
  }
  else /* normalized and won't downgrad to denormalized */ {
    --exp;
  }
  return (sign << 31) | (exp << 23) | frac;
}

void test(float_bits f)
{
  float_bits h = float_half(f);
  printf("float_half(0x%08x) = 0x%08x:\n"
         "\tas_float(0x%08x)       = %g, while\n"
         "\tas_float(0x%08x) / 2.f = %g\n",
         f, h, h, as_float(h), f, as_float(f) / 2.f);
}

void exhaustive_test()
{
  clock_t tbeg = clock();
  unsigned long count = 0;
  unsigned f = 0;
  do {
    float_bits h = float_half(f);
    float result = as_float(f) / 2.f;
    if (isnan(result)) {
      if (f != h) {
        printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
        return;
      }
    }
    else {
      if (as_float(h) != result) {
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
