/* Homework Problem 2.58 (**) Write a procedure is_little_endian that will
return 1 when compiled and run on a little-endian machine, and will return 0
when compiled and run on a big-endian machine. This program should run on any
machine, regardless of its word size. */

// ----------
// Sample Run
// ----------
// is_little_endian? 1

#include <stdio.h>

int is_little_endian()
{
  // int is guaranteed to have at least 16 bits or 2 bytes
  int val = 0x0102;
  return *(unsigned char *)&val == 0x02;
}

int main()
{
  printf("is_little_endian? %d\n", is_little_endian());
  return 0;
}
