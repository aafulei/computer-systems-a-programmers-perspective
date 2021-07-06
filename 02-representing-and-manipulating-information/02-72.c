// 21/07/06 = Tue

/* Homework Problem 2.72 (**)

You are given the task of writing a function that will copy an integer val into
a buffer buf, but it should do so only if enough space is available in the
buffer.

Here is the code you write:

// Copy integer into buffer if space is available
// WARNING: The following code is buggy.
void copy_int(int val, void *buf, int maxbytes)
{
  if (maxbytes - sizeof(val) >= 0)
    memcpy(buf, (void *)&val, sizeof(val));
}

This code makes use of the library function memcpy. Although its use is a bit
artificial here, where we simply want to copy an int, it illustrates an
approach commonly used to copy larger data structures.

You carefully test the code and discover that it always copies the value to the
buffer, even when maxbytes is too small.

A. Explain why the conditional test in the code always succeeds. Hint: The
   sizeof operator returns a value of type size_t.

B. Show how you can rewrite the conditional test to make it work properly. */

// Answer: A. sizeof returns an unsigned size_t, so the computation of
//            (maxbytes - sizeof(val)) is done between two unsigned size_t
//            types, which are always >= 0.
//
//         B. See the code below.

// ----------
// Sample Run
// ----------
// 12

#include <stdio.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes)
{
  if (maxbytes >= sizeof(val))
    memcpy(buf, (void *)&val, sizeof(val));
}

int main()
{
  int a = 42;
  copy_int(12, &a, 4);  // copied
  copy_int(34, &a, 3);  // not copied (space not enough)
  printf("%d\n", a);
  return 0;
}
