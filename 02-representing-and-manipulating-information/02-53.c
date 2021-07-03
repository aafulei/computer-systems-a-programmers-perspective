// 21/07/03 = Sat

/* Practice Problem 2.53

Fill in the following macro definitions to generate the double-precision values
+inf, -inf, and -0:

#define POS_INFINITY
#define NEG_INFINITY
#define NEG_ZERO

You cannot use any include files (such as math.h), but you can make use of the
fact that the largest finite number that can be represented with double
precision is around 1.8e308. */

// gcc -Wno-overflow 02-53.c && ./a.out

// ----------
// Sample Run
// ----------
// POS_INFINITY == INFINITY ? 1
// NEG_INFINITY == INFINITY ? 0
// NEG_INFINITY == -INFINITY ? 1
// sign_bit(0.0) = 0
// sign_bit(-0.0) = 1

#define POS_INFINITY (1e400)
#define NEG_INFINITY (-1e400)
#define NEG_ZERO     (-1.0/1e400)

#include <math.h>
#include <stdio.h>

// assuming both double and unsigned long long have 64 bits
int sign_bit(double x)
{
  return *(unsigned long long *)&x >> 63 & 0x1;
}

int main()
{
  printf("POS_INFINITY == INFINITY ? %d\n", POS_INFINITY == INFINITY);
  printf("NEG_INFINITY == INFINITY ? %d\n", NEG_INFINITY == INFINITY);
  printf("NEG_INFINITY == -INFINITY ? %d\n", NEG_INFINITY == -INFINITY);
  printf("sign_bit(%.1lf) = %d\n", 0.0, sign_bit(0.0));
  printf("sign_bit(%.1lf) = %d\n", NEG_ZERO, sign_bit(NEG_ZERO));

  return 0;
}
