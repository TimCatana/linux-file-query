# Author 
- Timothy Catana

# OS
- Linux

# General 
- Recursively queries a given directory printing out specific statistics about each sub-file/directories
- There is no limit to how many levels deep the program queries the file
    * Technically, there is a way for it to crash if too much memory is allocated (i.e. the file your queruying is HUGE)
    * I queried my root directory which was pretty big and it didn't break, so it's safe to say it probably you probably won't exceed memory boundaries
- The query queries each branch of the tree individually until it reaches a leaf and then it comes back and eventually queries another branch


# Compilation
`make`

# Excecution
`bin/FSreport <-tree OR -inode> <filepath>`