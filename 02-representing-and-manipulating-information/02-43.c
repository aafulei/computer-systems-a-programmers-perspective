// 21/07/02 = Fri

/* Practice Problem 2.43

In the following code, we have omitted the definitions of constants M and N:

#define M       // Mystery number 1
#define N       // Mystery number 2

int arith(int x, int y)
{
  int result = 0;
  result = x * M + y / N;
  return result;
}

We have compiled this code for particular values of M and N. The compiler
optimized the multiplication and division using the methods we have discussed.
The following is a transalation of the generated machine code back into C:

// Transalation of assembly code for arith
int optarith(int x, int y)
{
  int t = x;
  x <<= 5;
  x -= t;
  if (y < 0)
    y += 7;
  y >>= 3;    // arithmetic shift
  return x + y;
}

What are the values of M and N? */

// Answer: M is 31, N is 8.

#include <stdio.h>

#define M 31 // Mystery number 1
#define N 8  // Mystery number 2

int arith(int x, int y)
{
  int result = 0;
  result = x * M + y / N;
  return result;
}

int optarith(int x, int y)
{
  int t = x;
  x <<= 5;
  x -= t;
  if (y < 0)
    y += 7;
  y >>= 3; // arithmetic shift
  return x + y;
}

void test(int x, int y)
{
  printf("arith(%d, %d) = %d, optarith(%d, %d) = %d, equal ? %d\n", x, y,
         arith(x, y), x, y, optarith(x, y), arith(x, y) == optarith(x, y));
}

int main()
{
  test(176, 420);
  test(-88, 777);
  test(515, -314);
  return 0;
}
