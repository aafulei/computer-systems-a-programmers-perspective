/* gcc -o hex2dd -Wall -Wextra -ansi -pedantic pp-11-02.c */

/* ----- Practice Problem 11.2 -----------------------------------------------
 * Write a program hex2dd.c that converts its hex argument to a dotted-decimal
 * string and prints the result. For example,
 *
 * unix> ./hex2dd 0x8002c2f2
 * 128.2.194.242
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

char *hex2dd(char *, char *);
int hc2i(char);
char *i2a(int, char *);

/* (32-bit) hex string to dotted-decimcal string */
char *hex2dd(char *hex, char *dd)
{
    int i, d;
    char *p = dd;

    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
        hex += 2;
    for (i = 0; i < 4; i++) {
        d = hc2i(*hex++) * 16;
        d += hc2i(*hex++);
        p = i2a(d, p);
        *p++ = i < 3 ? '.' : '\0';
    }
    return dd;
}

/* hex-digit char to int */
int hc2i(char h)
{
    if ('0' <= h && h <= '9')
        return h-'0';
    if ('a' <= h && h <= 'f')
        return h-'a'+10;
    if ('A' <= h && h <= 'F')
        return h-'A'+10;
    fprintf(stderr, "'%c' (%d) is not a valid hex digit!\n", h, h);
    exit(1);
}

/* write int to string, return pointer to next char */
char *i2a(int d, char *p)
{
    int q;

    if ((q = (d / 10)) > 0)
        p = i2a(q, p);
    *p++ = d - 10 * q + '0';
    return p;
}

int main(int argc, char **argv)
{
    char dd[16];

    if (argc != 2) {
        fprintf(stderr, "[Example]\n$ ./hex2dd 0x8002c2f2\n$ 128.2.194.242\n");
        exit(1);
    }
    printf("%s\n", hex2dd(argv[1], dd));
    return 0;
}
