// 21/06/23 = Wed

// gcc 11-06.c csapp.c && ./a.out 1234

/* ----- Homework Problem 11.6 ------------------------------------------------

A. Modify Tiny so that it echoes every request line and request header.

B. Use your favorite browser to make a request to Tiny for static content.
Capture the output from Tiny in a file.

C. Inspect the output from Tiny to determine the version of HTTP your browser
uses.

D. Consult the HTTP/1.1 standard in RFC 2616 to determine the meaning of each
header in the HTTP request from your browser. You can obtain RFC 2616 from
www.rfc-editor.org/rfc.html.

 * ------------------------------------------------------------------------- */

// clang-format off

// Mozilla Firefox 89.0
// Address Bar: 127.0.0.1:1234

// GET /abcd HTTP/1.1
// Host: 127.0.0.1:1234
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1

// clang-format on

// https://www.rfc-editor.org/rfc/rfc2616.txt

#include "csapp.h"

void doit(int fd);
void read_echo_request_headers(rio_t *rp);
void clienterror(
    int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

int main(int argc, char **argv)
{
  int listenfd, connfd;
  char hostname[MAXLINE], port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);
  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE,
                0);
    printf("Accepted connection from (%s, %s)\n", hostname, port);
    doit(connfd);
    Close(connfd);
  }
}

void doit(int fd)
{
  int is_static;
  struct stat sbuf;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char filename[MAXLINE], cgiargs[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, fd);
  if (!Rio_readlineb(&rio, buf, MAXLINE))
    return;
  printf("%s", buf);
  // echo
  Rio_writen(fd, buf, strlen(buf));

  sscanf(buf, "%s %s %s", method, uri, version);
  if (strcasecmp(method, "GET") != 0) {
    clienterror(fd, method, "501", "Not Implemented",
                "Tiny does not implement this method");
    return;
  }
  read_echo_request_headers(&rio);
}

// MODIFIED
void read_echo_request_headers(rio_t *rp)
{
  char buf[MAXLINE];

  Rio_readlineb(rp, buf, MAXLINE);
  printf("%s", buf);
  Rio_writen(rp->rio_fd, buf, strlen(buf));

  while (strcmp(buf, "\r\n")) {
    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
    Rio_writen(rp->rio_fd, buf, strlen(buf));
  }
  return;
}

void clienterror(
    int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
  char buf[MAXLINE];

  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n\r\n");
  Rio_writen(fd, buf, strlen(buf));

  sprintf(buf, "<html><title>Tiny Error</title>");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "<body bgcolor="
               "ffffff"
               ">\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
  Rio_writen(fd, buf, strlen(buf));
}
