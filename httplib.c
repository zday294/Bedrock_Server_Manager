#include <bsd/string.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>




#define null NULL
#define MAX_HEADERS 10


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


// Returns 1 on success,
// -1 on invalid HTTP request,
// -2 on I/O error,g_settings
// -3 on malloc failure
int parseHttp(FILE *in, http_request_t **request) 
{

    // printf("made it to parseHttp\n");

    http_request_t *req = NULL;
    int rc = -1;

    // TODO: Allocate memory for req
    if((req = calloc(1, sizeof(http_request_t))) == NULL){
        rc = -3;
        goto cleanup;
    }
    

    // TODO: Read HTTP request from <in>

    char* line = null;
    size_t linelen = 0;
    int er;
    if( (er = getline(&line, &linelen, in)) <= 0){    //theoretically, doing this should allow it to read a line of any size?
         blog("error reading in data. errno = %d, er = %d\n", errno, er);
         return -2;
    }   

    //printf("request read in\n");
    //printf("request: %s\n", line);

    char *spot;

    req->verb = malloc(6);
    req->path = malloc(920);
    req->version = malloc(32);



    char * arg = strtok_r(line, " ", &spot);
    if (arg == null) { rc = -7; goto cleanup; }
    strlcpy(req->verb, arg, 6);
    // printf("verb = %s\n", arg);

    arg = strtok_r(null, " ", &spot);
    if (arg == null) { rc = -7; goto cleanup; }
    strlcpy(req->path, arg, 31);
    // printf("path = %s\n", arg);

    arg = strtok_r(null, " ", &spot);
    if (arg == null) { rc = -7; goto cleanup; }
    strlcpy(req->version, arg, 11);
    // printf("version = %s\n", arg);



    //Validate verb
    if (strcmp(req->verb, "GET") && strcmp(req->verb, "POST")){   //since 0 == false in c, as long as one of them evaluates to 0, the if statment won't execute
        rc = -4; //-4 invalid verb
        goto cleanup;
    }


    //Validate path
    if ( req->path[0] != '/'){ 
        // printf("req->path[0] == '%c' \n", req->path[0]);
        rc = -5; //-5 invalid path
        goto cleanup;
    }
    
    char validchar[] = "/.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_-";  //an array of all the valid characters
    char found;
    for (int i = 1; i < strlen(req->path); ++i ){       //for each character in the path
        found = 0;                                      //found = false
        for(int j = 0; j < sizeof(validchar); ++j){     //for each valid character
            if(req->path[i] == validchar[j]){           //if the currect character is one of the valid characters
                ++found;                                //found = true
                break;                                  //break the loop
            }
        }
        if(!found){                                     //if the current character was not found among the valid characters
            rc = -5;                                    //set the return code to -5
            goto cleanup;                               //move to cleanup
        }
    }


    //Validate version
    if(req->version == null || *(req->version) =='\n'){
        rc = -6; //-6 invalid version
        goto cleanup;
    }    


    for(int i = 0; i < 20; ++i){
        char* headline;
        size_t headsize = 0;
        // printf("removing headers\n");

        getline(&headline, &headsize, in);
        if(*headline == '\n' || *headline == '\r'){
            free(headline);
            break;
        }
        free(headline);
    }

    
    // TODO: On success, return req
    *request = req; 

    free(line);
    rc = 1;
    return rc;

cleanup:

    free(req->verb);
    free(req->path);
    free(req->version);

    for(int i = 0; i < MAX_HEADERS; ++i){
        free(req->headers[i].name);
        free(req->headers[i].value);
    }

    free(line);
    free(req);  // It's OK to free() a NULL pointer 
    return rc;

}




//Go through the path backwards to find a "."
//Copy the file extention into type
//Return 0 on success, 1 on failure 
int getFileType(char** path, char** type){
    // printf("getting file type\n");
    int length = strlen(*path);
    int periodIsAt = 0;


    for(int i = length-1; i > length - 7; --i){
        if ((*path)[i] == '.'){
            //what happens when we encounter a period
            //mark the position of the period 
            periodIsAt = i;
            break;
        }
    }

    //what happens if period is not found?
    if (periodIsAt == 0){
        strlcpy(*type, "unkown", 8);
        return 1; //well, we don't know the file type
    }

    //and now, we need to copy from the path to the file extension
    // printf("length - periodIsAt == %d\n", (length - periodIsAt) +1);
    strlcpy(*type, (*path)+ periodIsAt, (length - periodIsAt) + 1);

    //if nothing has gone wrong now, return the 0
    return 0;
}





int getContentType(char* fileType, char ** contentType){

    *contentType = malloc(41);

    switch(fileType[1]){
        case 'h':
            if(strcmp(".html", fileType) == 0 || strcmp(".htm", fileType) == 0){
                strlcpy(*contentType, "Content-Type: text/html", 25);
                break;
            }
            else{
                goto defcase;
            }
        case 'j':
            if(strcmp(".jpg", fileType) == 0 || strcmp(".jpeg", fileType) == 0){
                strlcpy(*contentType, "Content-Type: image/jpeg", 26);
                break;
            }
            else{
                goto defcase;
            }
        case 'c':
            if(strcmp(".css", fileType) == 0){
                strlcpy(*contentType, "Content-Type: text/css", 24);
                break;
            }
            else{
                goto defcase;
            }
        case 't':
            if(strcmp(".txt", fileType) == 0){
                strlcpy(*contentType, "Content-Type: text/plain", 26);
                break;
            }
            else{
                goto defcase;
            }
        case 'g':
            if(strcmp(".gif", fileType) == 0){
                strlcpy(*contentType, "Content-Type: image/gif", 25);
                break;
            }
            else{
                goto defcase;
            }
        case 'p':
            if(strcmp(".png", fileType) == 0){
                strlcpy(*contentType, "Content-Type: image/png", 25);
                break;
            }
            else{
                goto defcase;
            }
    defcase:
        default:
            strlcpy(*contentType, "Content-Type: application/octet-stream", 40);
            break; 
    }
}