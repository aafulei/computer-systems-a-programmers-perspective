// 20/04/05 = Sun

// gcc -std=c11 -Wall -Wextra -pedantic -o hex2dd 11-02.c && ./hex2dd 0x8002c2f2
// 128.2.194.242

#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;
    uint32_t u;
    sscanf(argv[1], "%" SCNx32, &u);
    struct in_addr ip = { .s_addr = htonl(u) };
    char buf[16];
    if (inet_ntop(AF_INET, &ip, buf, 16) == NULL)
        fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
    else
        printf("%s\n", buf);
    return 0;
}
