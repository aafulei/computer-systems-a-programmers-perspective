// 20/04/05 = Sun

// gcc -o hex2dd 11-02.c && ./hex2dd 0x8002c2f2

/* ----- Practice Problem 11.2 -----------------------------------------------
 * Write a program hex2dd.c that converts its hex argument to a dotted-decimal
 * string and prints the result. For example,
 *
 * unix> ./hex2dd 0x8002c2f2
 * 128.2.194.242
 * ------------------------------------------------------------------------- */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "usage: %s hex\n", argv[0]);
    return 1;
  }
  uint32_t u;
  sscanf(argv[1], "%" SCNx32, &u);
  struct in_addr ip = { .s_addr = htonl(u) };
  char dotted_decimal[16];
  if (inet_ntop(AF_INET, &ip, dotted_decimal, 16) == NULL)
    perror("inet_ntop error");
  else
    printf("%s\n", dotted_decimal);
  return 0;
}
