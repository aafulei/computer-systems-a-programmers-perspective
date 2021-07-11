// 21/07/11 = Sun

/* Homework Problem 2.96 (****)

Following the bit-level floating-point coding rules, implement the function
with the following prototype:

// Computer (int)f.
// If conversion causes overflow or f is NaN, return 0x80000000.
int float_f2i(float_bits f);

For floating-point number f, this functions computes (int)f. Your function
should round down towards zero. If f cannot be represented as an integer (e.g.
it is out of range, or it is NaN), then the function should return 0x80000000.

Test your function by evaluating it for all 2^32 values of argument f and
comparing the result to what would be obtained using your machine's floating-
point operations. */

// ----------
// Sample Run
// ----------
// float_f2i(          0) =        0 (=0x00000000), while
//      (int)          0  =        0
// float_f2i(          1) =        1 (=0x00000001), while
//      (int)          1  =        1
// float_f2i(         -1) =       -1 (=0xffffffff), while
//      (int)         -1  =       -1
// float_f2i(1.23457e+07) = 12345678 (=0x00bc614e), while
//      (int)1.23457e+07  = 12345678
// Exhaustive test passed with 4294967296 tests in 21.8 seconds!

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

// single-precision: s = 1, k = 8, n = 23
// NaN is when exponents are all 1 and fractions are not all 0.
int float_f2i(float_bits f)
{
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) & 0xff;
  unsigned frac = f & 0x7fffff;
  if (exp == 0xff)
    return 0x80000000;
  int E = exp - 127;
  if (E < 0)
    return 0;
  frac |= 0x800000;
  if (E < 23)
    frac >>= (23 - E);
  else if (E < 31)
    frac <<= (E - 23);
  else {
    // overflow
    return 0x80000000;
  }
  if (sign)
    return ~frac + 1;
  else
    return frac;
}

void test(float value)
{
  int i = float_f2i(as_bits(value));
  printf("float_f2i(%11g) = %8d (=0x%08x), while\n"
         "     (int)%11g  = %8d\n",
         value, i, i, value, (int)value);
}

void exhaustive_test()
{
  clock_t tbeg = clock();
  unsigned long count = 0;
  unsigned f = 0;
  do {
    int i = float_f2i(f);
    int result = (int)as_float(f);
    if (i != result) {
      printf("Exhaustive test failed with float_bits 0x%08x!\n", f);
      return;
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
  test(0.f);
  test(1.f);
  test(-1.f);
  test(12345678.f);
  exhaustive_test();
  return 0;
}
