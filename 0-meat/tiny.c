#include "tiny.h"

void doit(int fd)
{
  int is_static;
  struct stat sbuf;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char filename[MAXLINE], cgiargs[MAXLINE];
  rio_t rio;

  inbuf_init(&rio, fd);
  if (!inbuf_readline(&rio, buf, MAXLINE))
    return;
  printf("%s", buf);
  sscanf(buf, "%s %s %s", method, uri, version);
  if (strcasecmp(method, "GET")) {
    clienterror(fd, method, "501", "Not Implemented",
                "Tiny does not implement this method");
    return;
  }
  read_requesthdrs(&rio);

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
    serve_static(fd, filename, sbuf.st_size);
  }
  else {
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
      clienterror(fd, filename, "403", "Forbidden",
                  "Tiny couldn't run the CGI program");
      return;
    }
    serve_dynamic(fd, filename, cgiargs);
  }
}

void read_requesthdrs(rio_t *rp)
{
  char buf[MAXLINE];

  inbuf_readline(rp, buf, MAXLINE);
  printf("%s", buf);
  while (strcmp(buf, "\r\n")) {
    inbuf_readline(rp, buf, MAXLINE);
    printf("%s", buf);
  }
  return;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
  char *ptr;

  if (!strstr(uri, "cgi-bin")) {
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

void serve_static(int fd, char *filename, int filesize)
{
  int srcfd;
  char *srcp, filetype[MAXLINE], buf[MAXBUF];

  get_filetype(filename, filetype);
  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n", filesize);
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
  nobuf_writen(fd, buf, strlen(buf));

  srcfd = Open(filename, O_RDONLY, 0);
  srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
  Close(srcfd);
  nobuf_writen(fd, srcp, filesize);
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
  else
    strcpy(filetype, "text/plain");
}

void serve_dynamic(int fd, char *filename, char *cgiargs)
{
  char buf[MAXLINE], *emptylist[] = { NULL };

  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  nobuf_writen(fd, buf, strlen(buf));

  if (Fork() == 0) {
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
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n\r\n");
  nobuf_writen(fd, buf, strlen(buf));

  sprintf(buf, "<html><title>Tiny Error</title>");
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "<body bgcolor="
               "ffffff"
               ">\r\n");
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
  nobuf_writen(fd, buf, strlen(buf));
  sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
  nobuf_writen(fd, buf, strlen(buf));
}

int open_clientfd(char *hostname, char *port)
{
  int clientfd, rc;
  struct addrinfo hints, *listp, *p;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV;
  hints.ai_flags |= AI_ADDRCONFIG;
  if ((rc = getaddrinfo(hostname, port, &hints, &listp)) != 0) {
    fprintf(stderr, "getaddrinfo failed (%s:%s): %s\n", hostname, port,
            gai_strerror(rc));
    return -2;
  }

  for (p = listp; p; p = p->ai_next) {
    if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
      continue;
    if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
      break;
    if (close(clientfd) < 0) {
      fprintf(stderr, "open_clientfd: close failed: %s\n", strerror(errno));
      return -1;
    }
  }
  freeaddrinfo(listp);
  if (!p)
    return -1;
  else
    return clientfd;
}

int open_listenfd(char *port)
{
  struct addrinfo hints, *listp, *p;
  int listenfd, rc, optval = 1;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  hints.ai_flags |= AI_NUMERICSERV;
  if ((rc = getaddrinfo(NULL, port, &hints, &listp)) != 0) {
    fprintf(stderr, "getaddrinfo failed (port %s): %s\n", port,
            gai_strerror(rc));
    return -2;
  }

  for (p = listp; p; p = p->ai_next) {
    if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
      continue;
    setsockopt(listenfd, SOL_SOCKET,
               SO_REUSEADDR,
               (const void *)&optval, sizeof(int));

    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
      break;
    if (close(listenfd) < 0) {
      fprintf(stderr, "open_listenfd close failed: %s\n", strerror(errno));
      return -1;
    }
  }

  freeaddrinfo(listp);
  if (!p)
    return -1;
  if (listen(listenfd, LISTENQ) < 0) {
    close(listenfd);
    return -1;
  }
  return listenfd;
}

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
  return 0;
}
