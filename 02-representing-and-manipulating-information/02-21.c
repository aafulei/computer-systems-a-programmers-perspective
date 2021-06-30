// 21/06/30 = Wed

/* Practice Problem 2.21

Assuming the expressions are evaluated when executing a 32-bit program on a
machine that uses two's-complement arithmetic, fill the following table ...

Expression                        Type            Evaluation
------------------------------------------------------------
-2147483647-1 == 2147483648U
-2147483647-1 < 2147483647
-2147483647-1U < 2147483647
-2147483647-1U < -2147483647
-2147483647-1U < -2147483647

Answer:

Expression                        Type            Evaluation
------------------------------------------------------------
-2147483647-1 == 2147483648U      unsigned        1
-2147483647-1 < 2147483647        signed          1
-2147483647-1U < 2147483647       unsigned        0
-2147483647-1 < -2147483647       signed          1
-2147483647-1U < -2147483647      unsigned        1

*/

// ----------
// Sample Run
// ----------
// -2147483647-1 == 2147483648U evaluates to 1
// -2147483647-1 < 2147483647 evaluates to 1
// -2147483647-1U < 2147483647 evaluates to 0
// -2147483647-1 < -2147483647 evaluates to 1
// -2147483647-1U < -2147483647 evaluates to 1

#include <stdio.h>

int main()
{
  printf("-2147483647-1 == 2147483648U evaluates to %d\n",
         -2147483647 - 1 == 2147483648U);
  printf("-2147483647-1 < 2147483647 evaluates to %d\n",
         -2147483647 - 1 < 2147483647);
  printf("-2147483647-1U < 2147483647 evaluates to %d\n",
         -2147483647 - 1U < 2147483647);
  printf("-2147483647-1 < -2147483647 evaluates to %d\n",
         -2147483647 - 1 < -2147483647);
  printf("-2147483647-1U < -2147483647 evaluates to %d\n",
         -2147483647 - 1U < -2147483647);
  return 0;
}
