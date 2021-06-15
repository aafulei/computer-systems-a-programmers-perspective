// 20/04/05 = Sun

// gcc -std=c11 -Wall -Wextra -pedantic -o dd2hex 11-03.c && ./dd2hex 128.2.194.242
// 0x8002c2f2

#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;
    struct in_addr ip;
    int result = inet_pton(AF_INET, argv[1], &ip);
    if (result == 1)
        printf("0x%" PRIx32 "\n", ntohl(ip.s_addr));
    else if (result == 0)
        fprintf(stderr, "inet_pton error: invalid network address %s\n", argv[1]);
    else
        fprintf(stderr, "inet_pton error: %s\n", strerror(errno));
    return 0;
}
