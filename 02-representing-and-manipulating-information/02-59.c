// 21/06/29 = Tue

/* Homework Problem 2.59 (**) Write a C expression that will yield a word
consisting of the least significant byte of x and the remaining bytes of y.
For operands x = 0x89ABCDEF and y = 0x76543210, this would give Ox765432EF. */

// ----------
// Sample Run
// ----------
// $ ./a.out
// usage: ./a.out [x=0x89ABCDEF] [y=0x76543210]
// mix(2309737967=0x89ABCDEF, 1985229328=0x76543210) = 1985229551 = 0x765432EF
//
// $ ./a.out 1234 567890
// mix(1234=0x4D2, 567890=0x8AA52) = 568018 = 0x8AAD2

#include <stdio.h>

unsigned mix(unsigned x, unsigned y)
{
  return (x & 0xff) | (y & ~0xff);
}

int main(int argc, char *argv[])
{
  unsigned x = 0x89ABCDEF;
  unsigned y = 0x76543210;
  if (argc < 3) {
    fprintf(stderr, "usage: %s [x=0x89ABCDEF] [y=0x76543210]\n", argv[0]);
  }
  else {
    if (sscanf(argv[1], "%u", &x) != 1 || sscanf(argv[2], "%u", &y) != 1) {
      fprintf(stderr, "failed to sscanf %s and/or %s to integers\n", argv[1],
              argv[2]);
      return 1;
    }
  }
  unsigned z = mix(x, y);
  printf("mix(%u=0x%X, %u=0x%X) = %u = 0x%X\n", x, x, y, y, z, z);
  return 0;
}
