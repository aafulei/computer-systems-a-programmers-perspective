/* Suppose the disk file foobar.txt consists of the six ASCII characters
 * foobar. Then what is the output of the following program? */

// Answer: f

#include "csapp.h"

int main()
{
  int fd1, fd2;
  char c;

  fd1 = Open("foobar.txt", O_RDONLY, 0);
  fd2 = Open("foobar.txt", O_RDONLY, 0);
  Read(fd1, &c, 1);
  Read(fd2, &c, 1);
  printf("c = %c\n", c);
  exit(0);
}
