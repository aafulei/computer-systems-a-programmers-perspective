// 20/04/08 = Wed

// gcc -o hostinfo -Wall -Wextra -pedantic -std=gnu11 11-04.c && ./hostinfo yahoo.com
// 72.30.35.10
// 72.30.35.9
// 98.138.219.231
// 98.137.246.8
// 98.137.246.7
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
    struct addrinfo *p, *listp, hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    char buf[MAXLINE];
    int rc;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        return 0;
    }
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }
    for (p = listp; p; p = p->ai_next) {
        if (inet_ntop(AF_INET, &((struct sockaddr_in *)p->ai_addr)->sin_addr, buf, MAXLINE) != NULL)
            printf("%s\n", buf);
        else
            fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
    }
    freeaddrinfo(listp);
    exit(0);
}
