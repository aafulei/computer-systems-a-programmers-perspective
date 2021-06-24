// wrong and unfinished

// gcc 11-12.c csapp.c && ./a.out 1234

/* ---- Homework Problem 11.12 (***) ------------------------------------------
 * Extend Tiny so that it serves dynamic content requested by the HTTP POST
 * method. Check your work using your favorite Web browser.
 * ------------------------------------------------------------------------- */

// The HTTP POST method sends data to the server. The type of the body of the
// request is indicated by the Content-Type header.

// clang-format off
// curl -i -X POST -H 'Content-Type: application/x-www-form-urlencoded' -d 'number1=13&number2=24' http://127.0.0.1:1234/cgi-bin/adder
// clang-format on

// telnet 127.0.0.1:1234
// POST /cgi-bin/adder HTTP/1.1
// Content-Type: application/x-www-form-urlencoded
//
// number1=13&number2=24

#include "csapp.h"

char g_post_data[MAXLINE];


void doit(int fd);
void read_requesthdrs(rio_t *rp, char *content_type);
void read_request_body(rio_t *rp, char *content_type);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize, int head_only);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, int head_only);
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
  sscanf(buf, "%s %s %s", method, uri, version);

  // The HTTP HEAD method requests the headers that would be returned if the
  // HEAD request's URL was instead requested with the HTTP GET method. For
  // example, if a URL might produce a large download, a HEAD request could
  // read its Content-Length header to check the filesize without actually
  // downloading the file.

  int head_only = 0;
  int do_post = 0;
  if (strcasecmp(method, "HEAD") == 0)
    head_only = 1;
  else if (strcasecmp(method, "POST") == 0)
    do_post = 1;
  else if (strcasecmp(method, "GET") != 0) {
    clienterror(fd, method, "501", "Not Implemented",
                "Tiny does not implement this method");
    return;
  }
  char content_type[MAXLINE];
  read_requesthdrs(&rio, content_type);
  if (do_post)
    read_request_body(&rio, content_type);
  is_static = parse_uri(uri, filename, cgiargs);
  if (stat(filename, &sbuf) < 0) {
    clienterror(fd, filename, "404", "Not found",
                "Tiny couldn't find this file");
    return;
  }

  if (is_static) {
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
      clienterror(fd, filename, "403", "Forbidden",
                  "Tiny couldn't read the file");
      return;
    }
    serve_static(fd, filename, sbuf.st_size, head_only);
  }
  else {
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
      clienterror(fd, filename, "403", "Forbidden",
                  "Tiny couldn't run the CGI program");
      return;
    }
    if (do_post)
      serve_dynamic(fd, filename, g_post_data, head_only);
    else
      serve_dynamic(fd, filename, cgiargs, head_only);

  }
}

void read_requesthdrs(rio_t *rp, char *content_type)
{
  char buf[MAXLINE];
  do {
    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
    if (strncmp("Content-Type:", buf, strlen("Content-Type:")) == 0) {
      char *pnewline = strchr(buf, '\r');
      strncpy(content_type, buf + 14, pnewline - (buf + 14));
      printf("Got content_type = \"%s\"\n", content_type);
    }
  }
  while (strcmp(buf, "\r\n") != 0);
}


void read_request_body(rio_t *rp, char *content_type)
{
  if (strcmp(content_type, "application/x-www-form-urlencoded") == 0) {
    char buf[MAXLINE];
    Rio_readlineb(rp, buf, MAXLINE);
    printf("read_request_body(): %s", buf);
    strcpy(g_post_data, buf);
  }
  else {
    printf("Warning: content_type \"%s\" not implemented\n", content_type);
  }
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
  char *ptr;

  if (!strstr(uri, "cgi-bin")) {
    /* Static content */
    strcpy(cgiargs, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    if (uri[strlen(uri) - 1] == '/')
      strcat(filename, "home.html");
    return 1;
  }
  else {
    ptr = index(uri, '?');
    if (ptr) {
      strcpy(cgiargs, ptr + 1);
      *ptr = '\0';
    }
    else
      strcpy(cgiargs, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    return 0;
  }
}

void serve_static(int fd, char *filename, int filesize, int head_only)
{
  int srcfd;
  char *srcp, filetype[MAXLINE], buf[MAXBUF];

  get_filetype(filename, filetype);
  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n", filesize);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
  Rio_writen(fd, buf, strlen(buf));
  if (head_only)
    return;
  srcfd = Open(filename, O_RDONLY, 0);
  srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
  Close(srcfd);
  Rio_writen(fd, srcp, filesize);
  Munmap(srcp, filesize);
}

void get_filetype(char *filename, char *filetype)
{
  if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
  else if (strstr(filename, ".gif"))
    strcpy(filetype, "image/gif");
  else if (strstr(filename, ".png"))
    strcpy(filetype, "image/png");
  else if (strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpeg");
  else if (strstr(filename, ".mp4"))
    strcpy(filetype, "video/mp4");
  else
    strcpy(filetype, "text/plain");
}

void serve_dynamic(
    int fd, char *filename, char *cgiargs, int head_only)
{
  char buf[MAXLINE], *emptylist[] = { NULL };

  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  Rio_writen(fd, buf, strlen(buf));
  if (head_only)
    return;

  if (Fork() == 0) { /* Child */
    setenv("QUERY_STRING", cgiargs, 1);
    Dup2(fd, STDOUT_FILENO);
    Execve(filename, emptylist, environ);
  }
  Wait(NULL);
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
