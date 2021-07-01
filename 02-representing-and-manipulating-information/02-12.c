// 21/06/28 = Mon

/* Practice Problem 2.12

Write C expressions, in terms of variable x, for the following values. Your
code should work for any word size w >= 8. For reference, we show the result of
evaluating the expressions for x = 0x87654321, with w = 32.

A. The least significant byte of x, with all other bits set to 0. [0x00000021]
B. All but least significant byte of x complemented, with the least significant
   byte left unchanged. [0x789ABC21]
C. The least significant byte set to all ones, and all other bytes of x left
   unchanged. [0x876543FF] */

// ----------
// Sample Run
// ----------
// 0x00000021
// 0x789ABC21
// 0x876543FF

#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc == 1) {
    fprintf(stderr, "usage: %s [hex=0x87654321]\n", argv[0]);
  }
  unsigned x = 0x87654321;
  if (argc > 1 && sscanf(argv[1], "0x%x", &x) != 1)
    return 1;
  printf("0x%08X\n", x);
  printf("0x%08X\n", x & 0xFF);
  printf("0x%08X\n", (~x & ~0xFF) | (x & 0xFF));
  printf("0x%08X\n", x | 0xFF);
  return 0;
}
