// 21/06/29 = Tue

/* Homework Problem 2.57 (*) Write procedures show_short, show_long, and
 * show_double that print the byte representations of C objects of types short,
 * long, and double, respectively. Try these out on several machines. */

#include <stddef.h>
#include <stdio.h>

void show_short(short x)
{
  unsigned char *p = (unsigned char *)&x;
  for (size_t i = 0, N = sizeof(short); i != N; ++i) {
    printf("%.2x%c", *p++, (i != N - 1 ? ' ' : '\n'));
  }
}

void show_long(long x)
{
  unsigned char *p = (unsigned char *)&x;
  for (size_t i = 0, N = sizeof(long); i != N; ++i) {
    printf("%.2x%c", *p++, (i != N - 1 ? ' ' : '\n'));
  }
}

void show_double(double x)
{
  unsigned char *p = (unsigned char *)&x;
  for (size_t i = 0, N = sizeof(double); i != N; ++i) {
    printf("%.2x%c", *p++, (i != N - 1 ? ' ' : '\n'));
  }
}

int main(int argc, char *argv[])
{
  short short_val;
  long long_val;
  double double_val;
  if (argc == 1) {
    fprintf(stderr, "usage: %s [val=258]\n", argv[0]);
    short_val = long_val = double_val = 258;
  }
  else {
    if (sscanf(argv[1], "%hd", &short_val) != 1
        || sscanf(argv[1], "%ld", &long_val) != 1
        || sscanf(argv[1], "%lf", &double_val) != 1) {
      fprintf(stderr, "failed to scan value\n");
      return 1;
    }
  }
  printf("show_short(%hd): ", short_val);
  show_short(short_val);
  printf("show_long(%ld): ", long_val);
  show_long(long_val);
  printf("show_double(%lf): ", double_val);
  show_double(double_val);
  return 0;
}
