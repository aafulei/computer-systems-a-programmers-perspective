// 21/07/07 = Wed

/* Homework Problem 2.76 (*)

The library function calloc has the following declaration:

  void *calloc(size_t nmemb, size_t size);

According to the library documentation, "The calloc function allocates memory
for an array of nmemb elements of size bytes each. The memory is set to zero.
If nmemb or size is zero, then calloc returns NULL."

Write an implementation of calloc that performs the allocation by a call to
malloc and sets memory to zero via memset. Your code should not have any
vulnerabilities due to arithmetic overflow, and it should work correctly
regardless of the number of bits used to represent data of type size_t.

As a reference, functions malloc and memset have the following declarations:

void *malloc(size_t size)
void *memset(void *s, int c, size_t n); */

// Cross Reference: Practice Problem 2.37

// (optional) gcc 02-76.c&& ./a.out 2>/dev/null

// ----------
// Sample Run
// ----------
// (debug) zero-value argument(s)
// calloc_(0, 0) returns NULL
// (debug) zero-value argument(s)
// calloc_(0, 1) returns NULL
// (debug) zero-value argument(s)
// calloc_(1, 0) returns NULL
// (debug) multiplication overflow
// calloc_(18446744073709551615, 4) returns NULL
// (debug) multiplication overflow
// calloc_(4, 18446744073709551615) returns NULL
// calloc_(1, 1) returns OK
// calloc_(100, 1) returns OK
// (debug) failed to malloc
// calloc_(18446744073709551615, 1) returns NULL
// (debug) failed to malloc
// calloc_(1, 18446744073709551615) returns NULL

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *calloc_(size_t nmemb, size_t size)
{
  if (!nmemb || !size) {
    fprintf(stderr, "(debug) zero-value argument(s)\n");
    return NULL;
  }
  if (nmemb > (size_t)-1 / size) {
    fprintf(stderr, "(debug) multiplication overflow\n");
    return NULL;
  }
  size_t prod = nmemb * size;
  void *ret = malloc(prod);
  if (!ret) {
    fprintf(stderr, "(debug) failed to malloc\n");
    return NULL;
  }
  return memset(ret, 0, prod);
}

void test(size_t nmemb, size_t size)
{
  void *p = calloc_(nmemb, size);
  printf("calloc_(%zu, %zu) returns %s\n", nmemb, size, p ? "OK" : "NULL");
}

int main()
{
  test(0, 0);
  test(0, 1);
  test(1, 0);
  test(-1, sizeof(int));
  test(sizeof(int), -1);
  test(1, 1);
  test(100, 1);
  test(-1, 1);
  test(1, -1);
  return 0;
}
