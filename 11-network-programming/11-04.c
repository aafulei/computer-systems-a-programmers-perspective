// 20/04/08 = Wed

// The geti,ddrinfo and getnalneinfo functions subsume the functionality of
// inet_ pton and inet_ntop, respectively, and they provide a higher-level of
// abstraction that is independent of any.particular address format. To
// convince yourself how handy this is, write a version of HOSTINFO
// (Figure 11.17) that ns~s inet_ntop in- stead of getnameinfo to convert each
// socket address to a dotted-decimal address string.

// gcc -o hostinfo -Wall -Wextra -pedantic -std=gnu11 11-04.c && ./hostinfo
// yahoo.com 72.30.35.10 72.30.35.9 98.138.219.231 98.137.246.8 98.137.246.7
// 98.138.219.232

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAXLINE 16

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
    return 0;
  }
  // get a linked list of addrinfo structs
  struct addrinfo *listp,
      hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
  int rc;
  if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
    return 1;
  }
  // walk the list and print IP addresses
  char buf[MAXLINE];
  for (struct addrinfo *p = listp; p; p = p->ai_next) {
    if (inet_ntop(AF_INET, &((struct sockaddr_in *)p->ai_addr)->sin_addr, buf,
                  MAXLINE)
        != NULL)
      printf("%s\n", buf);
    else
      fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
  }
  // free the list
  freeaddrinfo(listp);
  return 0;
}
