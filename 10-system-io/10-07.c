/* 10.7 Modify the cpfile program in Figure 10.5 so that it uses the Rio
 * functions to copy standard input to standard output, MAXBUF bytes at a time.
 */

#include "csapp.h"

int main(int argc, char **argv)
{
  int n;
  rio_t rio;
  char buf[MAXLINE];

  Rio_readinitb(&rio, STDIN_FILENO);
  // ssize_t Rio_readn(int fd, void *ptr, size_t nbytes)
  while ((n = Rio_readnb(&rio, buf, MAXBUF)) > 0)
    Rio_writen(STDOUT_FILENO, buf, n);
}
