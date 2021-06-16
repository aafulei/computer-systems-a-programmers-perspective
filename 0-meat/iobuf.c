#include <errno.h>
#include <stddef.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 8192

typedef struct
{
  int fd;
  int size;
  char *next;
  char buf[BUFSIZE];
} iobuf_t;

// POSIX system calls
ssize_t read(int fd, void *dest, size_t size);
ssize_t write(int fd, const void *src, size_t size);

void iobuf_init(iobuf_t *iob, int fd)
{
  iob->fd = fd;
  iob->size = 0;
  iob->next = iob->buf;
}

static ssize_t iobuf_read(iobuf_t *iob, void *dest, size_t n)
{
  while (iob->size == 0) {
    int rc = read(iob->fd, iob->buf, sizeof(iob->buf));
    if (rc == -1) {
      if (errno == EINTR)
        continue;
      else
        return -1;
    }
    else if (rc == 0) {
      return 0;
    }
    else {
      iob->size = rc;
      iob->next = iob->buf;
    }
  }
  if (iob->size < n)
    n = iob->size;
  memcpy(dest, iob->next, n);
  iob->next += n;
  iob->size -= n;
  return n;
}

ssize_t iobuf_readn(iobuf_t *iob, void *dest, size_t n)
{
  char *p = dest;
  size_t rest = n;
  while (rest != 0) {
    int rc = iobuf_read(iob, p, rest);
    if (rc == -1)
      return -1;
    else if (rc == 0)
      break;
    else {
      rest -= rc;
      p += rc;
    }
  }
  return n - rest;
}

// read a line with at most lim characters to dest
// (1) lim does not count the ending '\0'
// (2) '\n' will not be copied
// -----------
// return code
// -----------
// -1 read error
//  0 end of file    (EOF)
//  1 empty line     (just an '\n')
//  2 completed line (a non-empty line that ends with '\n')
//  3 oversized line (a line that does not end within lim characters)
int iobuf_readline(iobuf_t *iob, void *dest, size_t lim)
{
  char *p = dest;
  char c;
  size_t n;
  ssize_t rc;
  for (n = 0; n < lim; ++n) {
    rc = iobuf_read(iob, &c, 1);
    if (rc == -1)
      return -1;
    else if (rc == 0 || c == '\n')
      break;
    else
      *p++ = c;
  }
  *p = '\0';
  if (rc == 0)
    return 0;
  else if (n == 0)
    return 1;
  else if (c == '\n')
    return 2;
  else
    return 3;
}

ssize_t nobuf_readn(int fd, void *dest, size_t n)
{
  char *p = dest;
  size_t rest = n;
  while (rest) {
    int rc = read(fd, p, rest);
    if (rc == -1) {
      if (errno == EINTR)
        continue;
      else
        return -1;
    }
    else if (rc == 0)
      break;
    else {
      rest -= rc;
      p += rc;
    }
  }
  return n - rest;
}

ssize_t nobuf_writen(int fd, const void *src, size_t n)
{
  const char *p = src;
  size_t rest = n;
  while (rest) {
    int rc = write(fd, p, rest);
    if (rc == -1) {
      if (errno == EINTR)
        continue;
      else
        return -1;
    }
    else {
      rest -= rc;
      p += rc;
    }
  }
  return n;
}

#include <stdio.h>

// echo
int main()
{
  iobuf_t stdin_buf;
  iobuf_init(&stdin_buf, 0);
  char line[10 + 1];
  int n;
  while ((n = iobuf_readline(&stdin_buf, line, 10)) > 0) {
    printf("%s\n", line);
  }
  return 0;
}
