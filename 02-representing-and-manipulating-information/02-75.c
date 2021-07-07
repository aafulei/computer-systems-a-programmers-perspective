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
// = [x * y + (x_{w-1} * y + y_{w-1} * x) 2^w + x_{w-1} y_{w-1} 2^{2w}] mod 2^w
// = (x * y) mod 2^w
//
// Reference - Equation 2.6
// T2U_w(x) = x + x_{w-1} 2^w

// Answer: From Equation 2.18, we can tell that for the high-order bits
//
//           (x' * y') / 2^w
//         = [(x + x_{w-1} 2^w) * (y + y_{w-1} 2^w)] / 2^w
//         = (x*y) / 2^w + (x_{w-1} * y + y_{w-1} * x) + x_{w-1} y_{w-1} * 2^w
//
//         Therefore, the difference between a signed product and an unsigned
//         product is (x_{w-1} * y + y_{w-1} * x) + x_{w-1} y_{w-1} * 2^w.
//
//         If we confine the above difference within w bits, that's
//
//                (x_{w-1} * y + y_{w-1} * x)

// gcc 02-75.c&& ./a.out 2>/dev/null
// ----------
// Sample Run
// ----------
//        128 *        128 = 0x0000000000004000 = [00000000|00004000]
//        128 * 4294967168 = 0x0000007fffffc000 = [0000007f|ffffc000]
// 4294967168 * 4294967168 = 0xffffff0000004000 = [ffffff00|00004000]
// 4294957093 *     476859 = 0x000746b9de000107 = [000746b9|de000107]
// 2147483648 * 2147483647 = 0x3fffffff80000000 = [3fffffff|80000000]
// 4294967295 * 4294967295 = 0xfffffffe00000001 = [fffffffe|00000001]

#include <limits.h>
#include <stdio.h>

static int signed_high_prod(int x, int y)
{
  unsigned w = sizeof(int) << 3;
  return ((long)x * y) >> w;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
  unsigned v = (sizeof(int) << 3) - 1;
  unsigned s = signed_high_prod(x, y);
  unsigned c1 = (((int)x >> v) & y);
  unsigned c2 = (((int)y >> v) & x);
  fprintf(stderr, "(debug)  s = 0x%08x\n", s);
  fprintf(stderr, "(debug) c1 = 0x%08x\n", c1);
  fprintf(stderr, "(debug) c2 = 0x%08x\n", c2);
  return s + c1 + c2;
}

void test(unsigned x, unsigned y)
{
  unsigned z = unsigned_high_prod(x, y);
  printf("%10u * %10u = 0x%016lx = [%08x|%08x]\n", x, y, (unsigned long)x * y,
         z, x * y);
}

int main()
{
  test(128, 128);
  test(128, -128);
  test(-128, -128);
  test(-10203, 476859);
  test(INT_MIN, INT_MAX);
  test(-1, -1);
  return 0;
}
