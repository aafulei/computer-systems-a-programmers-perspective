// 21/06/29 = Tue

/* Homework Problem 2.60 (**) Suppose we number the bytes in a w-bit word from
0 (least significant) to w/8 - 1 (most significant). Writy code for the
following C function, which return an unsigned value in which_byte i of
argument x has been replaced by byte b:

  unsigned replace_byte(unsigned x, int i, unsigned char b);

Here are some examples showing how the function should work:

  replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
  replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB

*/

// ----------
// Sample Run
// ----------
// replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
// replace_byte(0x12345678, 1, 0xAB) --> 0x1234AB78
// replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
// replace_byte(0x12345678, 3, 0xAB) --> 0xAB345678

#include <inttypes.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
  return x & ~(0xff << i * 8) | (b << i * 8);
}

int main()
{
  unsigned x = 0x12345678;
  int i = 2;
  unsigned char b = 0xAB;
  for (int i = 0; i != sizeof x; ++i)
    printf("replace_byte(0x%X, %d, 0x%X) --> 0x%X\n", x, i, b,
           replace_byte(x, i, b));
  return 0;
}
