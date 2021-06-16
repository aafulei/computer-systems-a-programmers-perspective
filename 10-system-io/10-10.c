/* 10.10 Modify the cpfile program in Figure 10.5 so that it takes an optional
command-line argument infile. If infile is given, then copy infile to standard
output; otherwise, copy standard input to standard output as before. The twist
is that your solution must use the original copy loop (lines 9–11) for both
cases. You are only allowed to insert code, and you are not allowed to change
any of the existing code.*/

#include "csapp.h"

int main(int argc, char **argv)
{
  int n;
  rio_t rio;
  char buf[MAXLINE];

  Rio_readinitb(&rio, STDIN_FILENO);
  if (argc > 1) {
    Dup2(atoi(argv[1]), STDIN_FILENO);
  }
  while ((n = Rio_readlineb(&rio, buf, MAXBUF)) != 0)
    Rio_writen(STDOUT_FILENO, buf, n);
}

