#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void printInodeStats(struct stat stats, char *name) {
    printf("%ld:\t", stats.st_ino);
    printf("%ld\t", stats.st_size);
    printf("%ld\t", stats.st_blocks);
    printf("%ld\t", stats.st_size);
    printf("%s\n", name);
}


void printInode(char **nameList, char **pathList, int numFiles) {
    struct stat status;
    int i;
    char *name;

    printf("Directories\n");
    for(i = 0; i < numFiles; i++) {
        stat(pathList[i], &status);

        if( (strcmp(nameList[i], ".") != 0) && (strcmp(nameList[i], "..") != 0) && S_ISDIR(status.st_mode) ) {
            name = strchr(nameList[i], '.');
            name = name + 1; // strchr includes the '.' in return string
            printInodeStats(status, name);
        }
    }

    printf("\nFiles\n");
    for(i = 0; i < numFiles; i++) {
        stat(pathList[i], &status);

        if( !(S_ISDIR(status.st_mode)) ) {
            name = strchr(nameList[i], '.');
            name = name + 1; // strchr includes the '.' in return string
            printInodeStats(status, name);
        }
    }
    printf("\n");
}