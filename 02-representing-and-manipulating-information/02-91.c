// 21/07/11 = Sun

/* Homework Problem 2.91 (*)

Around 250 B.C., the Greek mathematician Archimedes proved that

  233/71 < pi < 22/7.

Had he had access to a computer and the standard library <math.h>, he would
have been able to determine that the single-precision floating-point
approximation of pi has the hexadecimal representation 0x40490FBD. Of course,
all of these are just approximations, since pi is not rational.

A. What is the fractional binary number denoted by this floating-point value?

B. What is the fractional binary representation of 22/7? Hint: See Problem 2.83

C. At what bit position (relative to the binary point) do these two
   approximations to pi diverge? */

/* Answer:

A. The fractional binary number denoted by 0x40490FBD, or

   [ 0 | 1000 0000 | 1001 0010 0001 1111 0111 101 ], is

     2 ^ (128 - Bias) * (1 + [ 1001 0010 0001 1111 0111 101 ] (as binary frac))

   = 2 * (1 + 0.1001 0010 0001 1111 0111 101)

   = 2 * 1.1001 0010 0001 1111 0111 101

   = 11.0010 0100 0011 1110 1111 01

B. 22/7 = 3 + 1/7. Note that 1/7 = 1/8 + 1/8 * 1/7. Let R be the binary
   representation of 1/7. We have

      R = 0.001B + 0.001B * R, or

      0.111B * R = 0.001B. But how to solve this?

    Note that in decimal world, we have 1 / 0.999 = 1.001001001... = 1.(001).

    We guess that R = 0.001B * 1.(001)B = 0.001001001001... = 0.001(001).

    The above can be shown to be true.

    Therefore, the binary representation is

    3 + R = 11.(001) = 11.001001001001...

C. Compare 11.0010 0100 0011 1110 1111 01 with
           11.0010 0100 1001 0010 0010 01, we find that

   at the 9th bit after the binary point these two approximations diverge. */

// ----------
// Sample Run
// ----------
// 0x40490FBD as a float = 3.1415855884552
// sum_22_7 = 3.1428571428571, sum_22_7 * 7 = 22.0000000000000

#include <stdio.h>

void A()
{
  //     2 ^ (128 - Bias) * (1 + [ 1001 0010 0001 1111 0111 101 ])
  //   = 2 ^ (128 - 127)  * (1 + [ 1001 0010 0001 1111 0111 101 ])
  //   = 2 * (1.1001 0010 0001 1111 0111 101)
  //   = 2 * (1 + 1/2 + 1/16 + 1/128 + 1/4096 + 1/8192 + 1/16384 + 1/32768
  //   =        + 1/65536 + 1/262144 + 1/524288 + 1/1048576 + 1/2097152
  //   =        + 1/8388608)
  //   = 3.1415855884552
  unsigned value = 0x40490FBD;
  float pi = *(float *)&value;
  printf("0x40490FBD as a float = %.13f\n", pi);
}

void B()
{
  // 11.(001)...
  double sum_22_7 = 3.0;
  double term = 1/8.0;
  while (term) {
    sum_22_7 += term;
    term /= 8;
  }
  printf("sum_22_7 = %.13lf, sum_22_7 * 7 = %.13lf\n", sum_22_7, sum_22_7 * 7);
}

int main()
{
  A();  // 3.1415855884552
  B();  // 3.1428571428571, 22.0000000000000
  return 0;
}
