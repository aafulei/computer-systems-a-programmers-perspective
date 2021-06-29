/* Homework Problem 2.59 (**) Write a C expression that will yield a word
consisting of the least significant byte of x and the remaining bytes of y.
For operands x = 0x89ABCDEF and y = 0x76543210, this would give Ox765432EF. */

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
      fprintf(stderr, "failed to sscanf %s and %s to integers\n", argv[1],
              argv[2]);
      return 1;
    }
  }
  unsigned z = mix(x, y);
  printf("mix(%u=0x%X, %u=0x%X) = %u = 0x%X\n", x, x, y, y, z, z);
  return 0;
}
