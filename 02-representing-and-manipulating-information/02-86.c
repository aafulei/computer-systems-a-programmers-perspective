// 21/07/10 = Sat

/* Homework Problem 2.86 (*)

Intel-compatible processors also support an "extended-precision" floating-point
format with an 80-bit word divided into a sign bit, k = 15 exponent bits, a
single integer bit, and n = 63 fraction bits. The integer bit is an explicit
copy of the implied bit in the IEEE floating-point representation. That is, it
equals 1 for normalized values and 0 for denomalized values. Fill in the
following table giving the approximate values of some "interesting" numbers in
this format:

                                  Extended precision
                                  ----------------------------------
Description                       Value              Decimal
--------------------------------------------------------------------
Smallest positive denormalized
Smallest positive normalized
Largest normalized

This format can be used in C programs compiled for Intel-compatible machines by
declaring the data to be of type long double. However, it forces the compiler
to generate code based on the legacy 8087 floating-point instructions. The
resulting program will most likely run much slower than would be the case for
data type float or double.

Answer:


                                  Extended precision
                                  ----------------------------------
Description                       Value              Decimal
--------------------------------------------------------------------
Smallest positive denormalized    2^(-16445)          3.6452e-4951
Smallest positive normalized      2^(-16382)          3.3621e-4932
Largest normalized                2^16384 - 2^16320   1.18973e+4932

Steps:

Smallest positive denormalized
------------------------------
[ 0 | 0...0 | 0 | 0...1 ]

Bias = 2^{k-1} - 1 = 2^14 - 1

E = 1 - Bias = 1 - ((2^14) - 1) = 2 - 16834 = -16382

Exponent = 2^E = 2^(-16382)

Value = Exponent * M = 2^(-16382) * 1 * 2^(-63) = 2^(-16445)

Smallest positive normalized
----------------------------
[ 0 | 0...1 | 1 | 0...0 ]

E = e - Bias = 1 - Bias = -16382

Exponent = 2^E = 2^(-16382)

Value = Exponent * M = 2^(-16382) * 1 = 2^(-16382)

Largest normalized
------------------
[ 0 | 1...10 | 1 | 1...1 ]

E = e - Bias = (2^15 - 2) - (2^14 - 1) = 2^14 - 1 = 16383

Exponent = 2^E = 2^16383

Value = Exponent * M = 2^(16383) * 1 * ((1 - (1/2)^64) / (1 - 1/2))
      = 2^(16383) * (2 - 2^(-63))
      = 2^16384 - 2^16320

*/

// compile on a little-endian, intel machine (macbook pro 16" 2019 intel i9)

// ----------
// Sample Run
// ----------
// Smallest positive denormalized = 00 00 00 00 00 00 00 00 00 01 3.6452e-4951
// Smallest positive normalized   = 00 01 80 00 00 00 00 00 00 00 3.3621e-4932
// Largest normalized             = 7f fe ff ff ff ff ff ff ff ff 1.18973e+4932

#include <stdio.h>
#include <string.h>

void repr(void *x)
{
  char *p = x;
  for (int i = 9; i >= 0; --i)
    printf("%02hhx ", p[i]);
  long double *q = x;
  printf("%Lg\n", *q);
}

int main()
{
  char fake[10];
  for (int i = 0; i != 10; ++i)
    fake[i] = 0x00;

  // [ 0 | 0...0 | 0 | 0...1 ]
  fake[0] = 0x01;
  printf("Smallest positive denormalized = ");
  repr(fake);
  // [ 0 | 0...1 | 1 | 0...0 ]
  memset(fake, 0, 10);
  fake[7] = 0x80;
  fake[8] = 0x01;
  printf("Smallest positive normalized   = ");
  repr(fake);
  // [ 0 | 1..10 | 1 | 1...1 ]
  memset(fake, 0xff, 10);
  fake[8] = 0xfe;
  fake[9] = 0x7f;
  printf("Largest normalized             = ");
  repr(fake);
  return 0;
}
