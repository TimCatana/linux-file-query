#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "FSreportHelpers.h"
#include "printTree.h"
#include "printInode.h"

#define NUMFOLDERCONTENTS 500

void getDirContents(char *path, char *name, int level, int printFormat) {
    DIR* dir;
    struct dirent *curRead;
    struct stat status;

    int i = 0;
    int iNodeNum = 0;
    int listIdx = 0;
    char *curName;

    char **nameList = malloc(NUMFOLDERCONTENTS * sizeof(char*) );
    checkMalloc(nameList, "nameList", "getDirContents", -1);
    for (i = 0; i < NUMFOLDERCONTENTS; i++) {
        nameList[i] = malloc(255); // Linux max filename length (for most systems)
        checkMalloc(nameList[i], "nameList[i] where i =", "getDirContents", i);
    }

    char **pathList = malloc(NUMFOLDERCONTENTS * sizeof(char*));
    checkMalloc(pathList, "pathList", "getDirContents", -1);
    for (i = 0; i < NUMFOLDERCONTENTS; i++) {
        pathList[i] = malloc(4096); // Linux max path name (for most systems) 
        checkMalloc(nameList[i], "nameList[i] where i =", "getDirContents", i);
    }

    // Read and store directory contents
    dir = opendir(path);
    if(dir == NULL) {
        fprintf(stderr, "ERROR - Failed to open directory: %s\n", path);
        exit(-1);
    }

    while ( (curRead = readdir(dir)) != NULL ) {
        if( (strcmp(curRead->d_name, ".") == 0) || (strcmp(curRead->d_name, "..") == 0) ) {
            continue;
        }

        strcpy(pathList[listIdx], path);
        strcat(pathList[listIdx], "/");
        strcat(pathList[listIdx], curRead->d_name);

        if(printFormat == TREE) {
            strcpy(nameList[listIdx], curRead->d_name);
        }
        if(printFormat == INODE) {
            // Set to format "inodeNum.name" so that I can sort nameList using qSort and get the same result as pathList sorted by nodes numbers.
            stat(pathList[listIdx], &status);
            iNodeNum = status.st_ino;
            sprintf(nameList[listIdx], "%d.", iNodeNum);
            strcat(nameList[listIdx], curRead->d_name);
        }

        listIdx++;
    }
    closedir(dir);

    // Sort by name, -tree requires the output to be sorted by name and print tree format
    if(printFormat == TREE) {
        qsort(nameList, listIdx, sizeof(char*), compareStrings);
        qsort(pathList, listIdx, sizeof(char*), compareStrings);

        printf("Level %d: %s\n", level, name);
        printTree(nameList, pathList, listIdx);
    } 

    // Sort by name, -inode requires the output to be sorted by inode and print inode format
    if(printFormat == INODE) {
        qsort(nameList, listIdx, sizeof(char*), compareStrings);
        qsort(pathList, listIdx, sizeof(char*), compareInodes);

        printf("Level %d: %s\n", level, name);
        printInode(nameList, pathList, listIdx);
    }

    // Increment level for recursive call
    level++;
    for(i = 0; i < listIdx; i++) {
        stat(pathList[i], &status);

        if(printFormat == TREE) {
            if( S_ISDIR(status.st_mode) ) {
                getDirContents(pathList[i], nameList[i], level, printFormat);
            }
        }

        if(printFormat == INODE) {
            curName = strchr(nameList[i], '.');
            curName = curName + 1; 

            if( S_ISDIR(status.st_mode) ) {
                getDirContents(pathList[i], curName, level, printFormat);
            }
        }

    }

    // Free Contents
    for (i = 0; i < NUMFOLDERCONTENTS; i++) {
        free(nameList[i]);
    }
    free(nameList);

    for (i = 0; i < NUMFOLDERCONTENTS; i++) {
        free(pathList[i]);
    }
    free(pathList);

    free(curRead);
}


int main(int argc, char **argv) {
    if( (argc != 3) || ( (strcmp(argv[1], "-tree") != 0) && (strcmp(argv[1], "-inode") != 0) )  ) {
        fprintf(stderr, "Excecution: ./FSreport <-tree OR -inode> <file path>\n");
        exit(-1);
    }

    if( strcmp(argv[1], "-tree") == 0) {
        getDirContents(argv[2], argv[2], 1, TREE);
    }
    if( strcmp(argv[1], "-inode") == 0) {
        getDirContents(argv[2], argv[2], 1, INODE);
    }

    // start with true recursive call, cause then it becomes false immediately on first call
    // getDirContents(argv[2], argv[2], 1);

    return 0;
}