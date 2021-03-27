#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

int compareStrings (const void * a, const void * b ) {
    const char *x = *(const char**)a;
    const char *y = *(const char**)b;
    return strcmp(x, y);
}

int compareInodes (const void * a, const void * b ) {
    const char *x = *(const char**)a;
    const char *y = *(const char**)b;

    struct stat statusX;
    struct stat statusY;

    stat(x, &statusX);
    stat(y, &statusY);

    return statusX.st_ino - statusY.st_ino; // if negative, y.inode > x.inode. Therefore swap
}

void checkMalloc(void *ptr, char *varName, char *functionName, int index) {
    if(index == -1) {
        if(!ptr) {
            free(ptr);
            fprintf(stderr, "Error - not enough memory to allocate for %s in function %s\n", varName, functionName);
            exit(-1);
        }
    } else {
        if(!ptr) {
            free(ptr);
            fprintf(stderr, "Error - not enough memory to allocate for %s %d in function %s\n", varName, index, functionName);
            exit(-1);
        }
    }
}