// httplib.h

#ifndef HTTPLIB
#define HTTPLIB

#include <stdlib.h>

#include <bsd/string.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>


#define null NULL
#define MAX_HEADERS 20

typedef struct http_header {
    char *name;
    char *value;
} http_header_t;

typedef struct http_request {
    char *verb;
    char *path;
    char *version;
    int num_headers;
    http_header_t headers[MAX_HEADERS];
} http_request_t;



http_request_t* parseHttpWrap(char* requestFile);

int parseHttp(FILE *in, http_request_t **request);

int getFileType(char** path, char** type);

int getContentType(char* fileType, char ** contentType);

#endif