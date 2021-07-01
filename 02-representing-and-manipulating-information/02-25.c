/* Practice Problem 2.25

Consider the following code that attempts to sum the elements of an array a,
where the number of elements is given by parameter length:

// Warning: This is buggy code
float sum_elements(float a[], unsigned length)
{
  int i;
  float result = 0;
  for (i = 0; i <= length - 1; i++)
    result += a[i];
  return result;
}

When run with argument length equal to 0, this code should return 0.0. Instead,
it encounters a memory error. Explain why this happens. Show how this code can
be corrected. */

// Answer: length is an unsigned, so (length - 1) is computed as a subtraction
// between two unsigned integers, which evaluates to 4294967295, or 2^32-1,
// assuming that an unsigned interger has 32 bits. Now (i <= length - 1) will
// be computed as a comparison between two unsigned intergers, which evaluates
// to 1 as long as i is no larger than 4294967295. (In fact, it always will,
// since an int is capped at 2^31-1, or 2147483647, in this case.) This leads
// to an illegal memory access.

#include <stdio.h>

float sum_elements(float a[], unsigned length)
{
  unsigned i;
  float result = 0;
  for (i = 0; i != length; ++i)
    result += a[i];
  return result;
}

int main()
{
  float a[1];
  printf("%.1f\n", sum_elements(a, 0));
  return 0;
}
