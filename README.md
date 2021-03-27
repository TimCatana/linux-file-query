# Author 
- Timothy Catana

# OS
- Linux

# General 
- recursively queries a given directory printing out specific statistics about each sub-file/directories
- There is no limit to how many levels deep the program queries the file
    * Technically, there is a way for it to crash if too much memory is allocated (i.e. the file your queruying is HUGE)
    * I queried my root directory which was pretty big and it didn't break, so it's safe to say it probably you probably won't exceed memory boundaries

# Compilation
`make`

# Excecution
`bin/FSreport <-tree OR -inode> <filepath>`