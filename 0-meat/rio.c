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

void inbuf_init(struct inbuf *ib, int fd, unsigned maxtries, unsigned sleep_ms)
{

  ib->fd = fd;
  ib->size = 0;
  ib->next = ib->buf;
  ib->ntries = 0;
  ib->maxtries = maxtries;
  ib->sleep_ms = sleep_ms;
}

static ssize_t inbuf_read(struct inbuf *ib, void *dest, size_t n)
{
  while (ib->size == 0) {
    int rc = read(ib->fd, ib->buf, sizeof(ib->buf));
    if (rc == -1) {
      if (errno == EINTR)
        continue;
      else if (errno == EAGAIN) {
        if (ib->ntries++ < ib->maxtries) {
          usleep(ib->sleep_ms * 1000);
          continue;
        }
        else
          return -1;
      }
      else
        return -1;
    }
    else if (rc == 0) {
      return 0;
    }
    else {
      ib->size = rc;
      ib->next = ib->buf;
    }
  }
  if (ib->size < n)
    n = ib->size;
  memcpy(dest, ib->next, n);
  ib->next += n;
  ib->size -= n;
  return n;
}

ssize_t inbuf_readn(struct inbuf *ib, void *dest, size_t n)
{
  char *p = dest;
  size_t rest = n;
  while (rest != 0) {
    int rc = inbuf_read(ib, p, rest);
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
//  1 empty line     (just an '\n' or "\r\n")
//  2 completed line (a non-empty line that ends with '\n')
//  3 oversized line (a line that does not end within lim characters)
int inbuf_readline(struct inbuf *ib, void *dest, size_t lim)
{
  char *p = dest;
  char c;
  size_t n;
  ssize_t rc;
  for (n = 0; n < lim; ++n) {
    rc = inbuf_read(ib, &c, 1);
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
  else if (n == 1 && *(p - 1) == '\r') {
    *(p-1) = '\0';
    return 1;
  }
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
