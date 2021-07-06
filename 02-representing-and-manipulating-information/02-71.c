// 21/07/06 = Tue

/* Homework Problem 2.71 (*)

  Your just started working for a company that is implementing a set of
  procedures to operate on a data structure where 4 signed bytes are packed
  into a 32-bit unsigned. Bytes within the word are numbered from 0 (least
  significant) to 3 (most significant) ...

  typedef unsigned packed_t;

  // Extract byte from word. Return as signed integer.
  int xbyte(packed_t word, int bytenum);

  That is, the function will extract the designated byte and sign extend it to
  be a 32-bit int.

  // Problematic code
  int xbyte(packed_t word, int bytenum)
  {
    return (word >> (bytenum << 3)) & 0xFF;
  }

  A. What is wrong with this code?

  B. Give a correct implementation of the function that uses only left and
     right shifts, along with one subtraction. */

// Answer: A. The sign bit is not extended properly, as word is an unsigned.
//
//         B. See the code below.

// ----------
// Sample Run
// ----------
// xbyte(0x78abcdef, 0) = 0xffffffef = -17
// xbyte(0x78abcdef, 1) = 0xffffffcd = -51
// xbyte(0x78abcdef, 2) = 0xffffffab = -85
// xbyte(0x78abcdef, 3) = 0x00000078 = 120

#include <stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
  return (int)word << ((3 - bytenum) << 3) >> 24;
}

void test(packed_t word, int bytenum)
{
  int x = xbyte(word, bytenum);
  printf("xbyte(0x%08x, %d) = 0x%08x = %d\n", word, bytenum, x, x);
}

int main()
{
  test(0x78abcdef, 0);
  test(0x78abcdef, 1);
  test(0x78abcdef, 2);
  test(0x78abcdef, 3);
  return 0;
}
