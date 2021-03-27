#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>

void printTreeStats(struct stat stats, char *name) {
    struct group *grp = getgrgid(stats.st_gid);
    struct passwd *pwd =  getpwuid(stats.st_uid);

    printf("%s (%s)\t", pwd->pw_name, grp->gr_name);
    printf("%ld\t", stats.st_ino);

    printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
    printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
    printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
    printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
    printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
    printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
    printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
    printf( (stats.st_mode & S_IROTH) ? "r" : "-");
    printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
    printf( (stats.st_mode & S_IXOTH) ? "x\t" : "-\t");

    printf("%ld\t", stats.st_size);
    printf("%s\t", name);

    printf("\n\t%.24s\t",  ctime(&stats.st_atime));
    printf("%.24s\n", ctime(&stats.st_mtime));
}

void printTree(char **nameList, char **pathList, int numFiles) {
    struct stat status;
    int i;

    printf("Directories\n");
    for(i = 0; i < numFiles; i++) {
        stat(pathList[i], &status);

        if( (strcmp(nameList[i], ".") != 0) && (strcmp(nameList[i], "..") != 0) && S_ISDIR(status.st_mode) ) {
            printTreeStats(status, nameList[i]);
        }
    }

    printf("\nFiles\n");
    for(i = 0; i < numFiles; i++) {
        stat(pathList[i], &status);

        if( !(S_ISDIR(status.st_mode)) ) {
            printTreeStats(status, nameList[i]);
        }
    }
    printf("\n");
}
