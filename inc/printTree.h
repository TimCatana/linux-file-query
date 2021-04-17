#ifndef PRINT_TREE_H_
#define PRINT_TREE_H_

/** Prints file statistics in inode format.
  * inode fomat: 
  * <owner name (group name)>    <inode number> <permissions>   <size in bytes>
        <Date of last access> <Date of last modification>
  * @param stats (struct stat) A file status structure containing the status of the current file being printed out
  *              stat man page: https://man7.org/linux/man-pages/man2/lstat.2.html
  * @param name (char*) The name of the file whose statistics we are printing
  */ 
void printTreeStats(struct stat stats, char *name);

/** Gets every file in current directory we are analyzing and prints using @function: printTreeStats
  * @importantnote: nameList and pathList MUST have files in the same order.
  *                 that is, nameList[i] = pathList[i]
  *                 Example:
  *                 nameList[i] = lol.txt THEREFORE pathList[i] = <path>/lol.txt 
  * @param nameList (char**) The list of file names in increasing order by inode
  * @param pathList (char**) The list of paths in increasint order by inode
  * @param numFiles (int) The number of files in nameList and pathList
  */ 
void printTree(char **nameList, char **pathList, int numFiles);

#endif
