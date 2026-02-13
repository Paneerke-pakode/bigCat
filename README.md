# bigCat

This Repository contains my exploration of the UNIX 'cat' command, implemented in C language.

The project is divided into two parts :

1. **Basic reimplementation of `cat` (myCat) -** which focuses on the basic functions performed by the 'cat' command i.e, File reading, Standard input (stdin), Stream copying, ans Binary-safe file opening.
Location : `base/`

2. **Enhanced version of the `cat` command (bigCat) -** this version is built upon the prior understanding of the command, and builds upon that understanding. It features the following functions : 
- `-n` -> line numbering
- `-b` -> Number non-blank lines
- `-s` -> squeeze multiple blank lines
- `-e` -> show end-of-line (`$`)
- Stateful stream processing
- Safer string handling
Location : `enhanced/`

**The purpose of this project is to understand how the UNIX utility `cat` works and what drawbacks does it face that can be enhanced further.**


##### Basic version

`gcc base/myCat.c -o myCat`

##### Enhanced version

`gcc enhanced/bigCat.c -o bigCat`


##### ----- EXAMPLE USAGE -----
```
./myCat file.txt
./bigCat -n file.txt
cat file.txt | ./bigCat -s
```
