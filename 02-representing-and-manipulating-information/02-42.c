// 21/07/02 = Fri

/* Practice Problem 2.42

Write a function div16 that returns the value x / 16 for integer argument x.
Your function should not use division, modulus, multiplication, any
conditionals (if or ?:), any comparison operators (e.g. <, >, or ==), or any
loops. You may assume that data type int is 32 bits long and uses a two's-
complement representation, and that right shifts are performed arithmetically.

*/

// ----------
// Sample Run
// ----------
// div16(0) = 0
// div16(1) = 0
// div16(15) = 0
// div16(16) = 1
// div16(17) = 1
// div16(31) = 1
// div16(32) = 2
// div16(33) = 2
// div16(1023) = 63
// div16(1024) = 64
// div16(1025) = 64
// div16(2147483647) = 134217727
// div16(-1) = 0
// div16(-15) = 0
// div16(-16) = -1
// div16(-17) = -1
// div16(-31) = -1
// div16(-32) = -2
// div16(-33) = -2
// div16(-1023) = -63
// div16(-1024) = -64
// div16(-1025) = -64
// div16(-2147483647) = -134217727
// div16(-2147483648) = -134217728

#include <stdio.h>

int div16(int x)
{
  // signed(|x| / 16) + (bias 1 if x is negative and indivisible by 16)
  return     (x >> 4) + ((x >> 31) && (x & 0xf));
}

void test(int x)
{
  printf("div16(%d) = %d\n", x, div16(x));
}

int main()
{
  test(0);
  test(1);
  test(15);
  test(16);
  test(17);
  test(31);
  test(32);
  test(33);
  test(1023);
  test(1024);
  test(1025);
  test(2147483647);
  test(-1);
  test(-15);
  test(-16);
  test(-17);
  test(-31);
  test(-32);
  test(-33);
  test(-1023);
  test(-1024);
  test(-1025);
  test(-2147483647);
  test(-2147483648);
  return 0;
}
