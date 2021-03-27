#ifndef FSREPOER_HELPERS_H_
#define FSREPOER_HELPERS_H_

/** Used to determine which format and what data we are printint out
  * i.e. TREE uses tree print functions, INODE uses inde print functions 
  */ 
typedef enum format {
    TREE, 
    INODE
} printFormat; 

/** Comparison function used by qsort to sort an array of strings in lexicographical order.
  * @param a (char*) An arbitrary string
  * @param b (char*) An arbitrary string
  * @return strcmp() return value which determines whether a comes before b or whether b comes before a
  */  
int compareStrings (const void *a, const void *b);

/** Comparison function used by qsort to sort filenames and filepaths according to their inode number (in increasing order).
  * @param a (char*) An arbitrary string
  * @param b (char*) An arbitrary string
  * @return negative value: file a has a larger inode number than file b. Therefore swap values
  *         positive value: file b has a larger inode number than file a. do nothing
  *         @note should never return 0 as we should always be comparing two different files.
  *               files should never have the same inode number
  */  
int compareInodes (const void *a, const void *b);

/** Checks to see if pointer allocated correctly
  * @param ptr a pointer
  * @param varName the name of the pointer ptr
  * @param functionName the name of the function the ptr is in
  * @param index > 0 if allocating a greater than single pointer (the index of the ptr accessed) (Ex ptr[i])
  *              = -1 if allocating a single pointer 
  */
void checkMalloc(void *ptr, char *varName, char *functionName, int index);

#endif