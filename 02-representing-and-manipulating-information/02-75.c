// todo

// 21/07/07 = Wed

/* Homework Problem 2.75 (***)

Suppose we want to compute the complete 2w-bit representation of x * y, where
both x and y are unsigned, on a machine for which data type unsigned is w bits.
The low-order w bits of the product can be computed with expression x * y, so
we only require a procedure with prototype

  unsigned unsigned_high_prod(unsigned x, unsigned y);

that computes the high-order w bits of x * y for unsigned variables.

We have the access to a library function with prototype

  int signed_high_prod(int x, int y);

that computes the high-order bits of x * y for the case where x and y are in
two's-complement form. Write code calling this procedure to implement the
function for unsigned arguments. Justify the correctness of your solution.

Hint: Look at the relationship between the signed product x * y and the
unsigned product x' * y' in the derivation of Equation 2.18. */

// Reference - Equation 2.18
//
// Let x' = x + x_{w-1} 2^w, and y' = y + y_{w-1} 2^w. We have
//   (x' * y') mod 2^w
// = [(x + x_{w-1} 2^w) * (y + y_{w-1} 2^w)] mod 2^w
// = [x * y + (x_{w-1} + y_{w-1}) 2^w + x_{w-1} y_{w-1} 2^{2w}] mod 2^w
// = (x * y) mod 2^w
//
// Reference - Equation 2.6
// T2U_w(x) = x + x_{w-1} 2^w

#include <stdio.h>

static int signed_high_prod(int x, int y)
{
  unsigned w = sizeof(int) << 3;
  return ((long)x * y) >> w;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
  unsigned v = (sizeof(int) << 3) - 1;
  unsigned xsb = x >> v;
  unsigned ysb = y >> v;
  return signed_high_prod(x, y) + (xsb ^ ysb) << v;
}

void test(unsigned x, unsigned y)
{
  unsigned z = unsigned_high_prod(x, y);
  unsigned long prod = (unsigned long)x * y;
  printf("unsigned_high_prod(%d=0x%08x, %d=0x%08x) = (%d=0x%08x), "
         "while %d * %d = (%ld=0x%016lx), ",
         x, x, y, y, z, z, x, y, prod, prod);
}

int main()
{
  test(128, 128);
  test(128, -128);
  test(-128, 128);
  test(-128, -128);
  test(0x00010000, 0x00010000);
  test(0x00010000, 0x10010000);
  test(0x10010000, 0x00010000);
  test(0x10010000, 0x10010000);
  return 0;
}
