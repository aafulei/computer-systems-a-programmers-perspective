// 20/02/29 = Sat

/* gcc -o dd2hex -Wall -Wextra -ansi -pedantic pp-11-03.c */

/* ----- Practice Problem 11.3 ------------------------------------------------
 * Write a program dd2hex.c that converts its dotted-decimal argument to a hex
 * number and prints the result. For example,
 *
 * unix> ./dd2hex 128.2.194.242
 * 0x8002c2f2
 * ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

char *dd2hex(char *, char *);
char *i2ha(int, char *);
char h2c(int);

/* dotted-decimal string to hex string */
char *dd2hex(char *dd, char *hex)
{
    int d = 0, lastdot = 1;
    char *p = hex;

    *p++ = '0';
    *p++ = 'x';
    while (*dd != '\0') {
        if (*dd == '.') {
            if (lastdot) {
                fprintf(stderr, "Invalid dot position!\n");
                exit(1);
            }
            p = i2ha(d, p);
            d = 0;
            lastdot = 1;
        }
        else if ('0' <= *dd && *dd <= '9') {
            if ((d = d * 10 + *dd - '0') >= 256)  {
                fprintf(stderr, "%d is not in [0, 255]!\n", d);
                exit(1);
            }
            lastdot = 0;
        }
        else {
            fprintf(stderr, "'%c' (%d) is not a valid digit!\n", *dd, *dd);
            exit(1);
        }
        dd++;
    }
    if (lastdot) {
        fprintf(stderr, "Invalid dot position!\n");
        exit(1);
    }
    i2ha(d, p);
    return hex;
}

/* write int to hex string, return pointer to next char */
char *i2ha(int d, char *p)
{
    *p++ = h2c((d & 0xf0) >> 4);
    *p++ = h2c(d & 0xf);
    *p = '\0';
    return p;
}

/* hex digit to char */
char h2c(int h)
{
    if (0 <= h && h < 10)
        return h+'0';
    if (10 <= h && h < 16)
        return h-10+'a';
    fprintf(stderr, "%d is not a valid hex digit!\n", h);
    exit(1);
}

int main(int argc, char **argv)
{
    char hex[11];

    if (argc != 2) {
        fprintf(stderr, "[Example]\n$ ./dd2hex 128.2.194.242\n$ 0x8002c2f2\n");
        exit(1);
    }
    printf("%s\n", dd2hex(argv[1], hex));
    return 0;
}
