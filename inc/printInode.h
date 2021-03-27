#ifndef PRINT_INODE_H_
#define PRINT_INODE_H_

/** Prints file statistics in inode format.
  * inode fomat: 
  * <Inode number>: <size (in bytes)>   <number of 512-byte blocks allocated to the file>    <file size/512>    <file/directory name>
  * @param stats (struct stat) A file status structure containing the status of the current file being printed out
  *              stat man page: https://man7.org/linux/man-pages/man2/lstat.2.html
  * @param name (char*) The name of the file whose statistics we are printing
  */ 
void printInodeStats(struct stat stats, char *name);

/** Gets every file in current directory we are analyzing and prints using @function: printInodeStats
  * @importantnote: nameList and pathList MUST have files in the same order.
  *                 that is, nameList[i] = pathList[i]
  *                 Example:
  *                 nameList[1] = lol.txt THEREFORE pathList[i] = <path>/lol.txt 
  * @param nameList (char**) The list of file names in increasing order by inode
  * @param pathList (char**) The list of paths in increasint order by inode
  * @param numFiles (int) The number of files in nameList and pathList
  */ 
void printInode(char **nameList, char **pathList, int numFiles);

#endif
