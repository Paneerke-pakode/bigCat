#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//THIS IS A WORKING MODEL OF THE `cat` COMMAND FROM UNIX.
//A WORKING COPY OF THIS MUST BE PRESENT IN THE UBUNTU FILES
//IN THE COMPUTER, WHICH WILL HENCE RESULT IN THE CODE WORKING INSIDE UBUNTU UNIX.
//myCat.c is a wokring version of this in the ubuntu codes inside the ubuntu folders.
int main(int argc, char **argv){

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0;
	int opt;

	while ((opt = getopt(argc, argv, "bens?")) != -1){
		switch(opt) {
			case 'b':
				bflag++;
				break;
			case 'e':
				eflag++;
				break;
			case 'n':
				nflag++;
				break;
			case 's':
				sflag++;
				break;
			case '?':
				printf("usage: cat [-bens] [file ...]\n");
				exit(1);
		}
	}
	
	
	const int bufferSize = 4096;
	char buffer[bufferSize];
	int currentFile = optind;
	FILE *fp;
	
	while (currentFile <= argc) {
	if (currentFile != argc) {
		fp = fopen(argv[currentFile], "rb");
		if (fp == NULL) {
			fprintf(stderr, "%s: %s: No such file or directory", argv[0], argv[currentFile]);
			exit(1);
		}
	}
	// above if condition runs iff the file is empty

	int lastLineBlank = 0;
	int lineNumber = 1;

	while (fgets(buffer, bufferSize, (fp == NULL ? stdin : fp))) {
		// triggers when either standard input or file input.
		int length = strlen(buffer);
		buffer[length - 1] = '\0';
		
		if (sflag) {
			length = strlen(buffer);
			int currentLineBlank = (length <= 1) ? 1 : 0;
			if (lastLineBlank && currentLineBlank) {
				continue;
			}
			lastLineBlank = currentLineBlank;
		}
		// Squeeze multiple adjacent empty lines, causing the output to be single spaced.

		if (bflag) {
			length = strlen(buffer);
			if (length >= 1) {
				char *tmp = strdup(buffer);
				buffer[0] = '\0';
				sprintf(buffer, "%*d\t", 6, lineNumber++);
				strcat(buffer, tmp);
			}
		}
		// number the non-blank output lines, starting at 1

		else if (nflag) {
			char *tmp = strdup(buffer);
			buffer[0] = '\0';
			sprintf(buffer, "%*d\t", 6, lineNumber++);
			strcat(buffer, tmp);
		}
		// number of output lines, starting at 1

		if (eflag) {
			length = strlen(buffer);
			buffer[length] = '$';
			buffer[length + 1] = '\0';
		}
		// displays non-printing characters and display a dollar sign ('$') at the end of each line

		fprintf(stdout, "%s\n", buffer);
	}

	fclose(fp);
	currentFile++;

	}

	return 0;
}
