/* 10.9 Consider the following invocation of the fstatcheck program from
Problem 10.8:

linux> fstatcheck 3 < foo.txt

You might expect that this invocation of fstatcheck would fetch and display
metadata for file foo.txt. However, when we run it on our system, it fails with
a "bad file descriptor." Given this behavior, fill in the pseudocode that the
shell must be executing between the fork and execve calls:

if (Fork() == 0) {  // child
  // What code is the shell executing right here?
  Execve("fstatcheck", argv, envp);
}
*/

#include "csapp.h"

int main(int argc, char **argv)
{
  if (Fork() == 0) {
    char *envp[] = { NULL };
    Dup2(0, atoi(argv[1]));
    Execve("fstatcheck", argv, envp);
  }
}
