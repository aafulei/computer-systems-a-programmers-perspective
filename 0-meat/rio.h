#pragma once

#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 8192

struct inbuf
{
  int fd;
  size_t size;
  char *next;
  char buf[BUFSIZE];
  unsigned ntries;
  // -1 for de facto forever
  // 0 for no wait
  unsigned maxtries;
  unsigned sleep_ms;
};

void inbuf_init(struct inbuf *ib,
                int fd,
                unsigned maxtries,
                unsigned sleep_ms);
ssize_t inbuf_readn(struct inbuf *ib, void *dest, size_t n);
int inbuf_readline(struct inbuf *ib, void *dest, size_t lim);
ssize_t nobuf_readn(int fd, void *dest, size_t n);
ssize_t nobuf_writen(int fd, const void *src, size_t n);

// POSIX system calls
ssize_t read(int fd, void *dest, size_t size);
ssize_t write(int fd, const void *src, size_t size);
