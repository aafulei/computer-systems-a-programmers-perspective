// 21/07/08 = Thu

/* Homework Problem 2.81 (**)

Write C expressions to generate the bit patterns that follow, where a^k
represents k repititions of symbol a. Assume a w-bit data type. Your code amy
contain references to parameters j and k, representing the value of j and k,
but not a parameter represeting w.

A. 1^{w-k} 0^{k}

B. 0^{w-k-j} 1^{k} 0^{j} */

// ----------
// Sample Run
// ----------
// A(k=0)               = 0xffffffff
// B(j=0, k=0)          = 0x00000000
// A(k=31)              = 0x80000000
// B(j=0, k=31)         = 0x7fffffff
// A(k=0)               = 0xffffffff
// B(j=31, k=0)         = 0x00000000
// A(k=4)               = 0xfffffff0
// B(j=3, k=4)          = 0x00000078
// A(k=7)               = 0xffffff80
// B(j=17, k=7)         = 0x00fe0000
//
// A: k is num of 0s from right
// B: k is num of 1s in middle, j is num of 0s from right

// Answer: Note that j, k in the range of [0, w), and (k + j) <= w.
#include <stdio.h>

unsigned A(int k)
{
  unsigned v = (sizeof(int) << 3) - 1;
  return (int)(1 << v) >> (v - k);
}

unsigned B(int j, int k)
{
  unsigned w = sizeof(int) << 3;
  unsigned v = w - 1;
  // note: can't do >> (k - 1) when k is 0
  return (unsigned)((int)(1 << v) >> k << 1) >> (w - k - j);
}

void test(int j, int k)
{
  char sa[100], sb[100];
  sprintf(sa, "A(k=%d)", k);
  sprintf(sb, "B(j=%d, k=%d)", j, k);
  printf("%-20s = 0x%08x\n", sa, A(k));
  printf("%-20s = 0x%08x\n", sb, B(j, k));
}

int main()
{
  test(0, 0);
  test(0, (sizeof(int) << 3) - 1);
  test((sizeof(int) << 3) - 1, 0);
  test(3, 4);
  test(17, 7);
  putchar('\n');
  printf("A: k is num of 0s from right\n");
  printf("B: k is num of 1s in middle, j is num of 0s from right\n");
  return 0;
}
