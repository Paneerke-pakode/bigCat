#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0;
	int opt;

	while ((opt = getopt(argc, argv, "bens")) != -1){
		switch(opt) {
			case 'b':
				bflag = 1;
				break;
			case 'e':
				eflag = 1;
				break;
			case 'n':
				nflag = 1;
				break;
			case 's':
				sflag = 1;
				break;
			default:
				fprintf(stderr, "usage: cat [-bens] [file ...]\n");
				exit(1);
		}
	}


	const int bufferSize = 4096;
	char buffer[bufferSize];

	int lastLineBlank = 0;
	int lineNumber = 1;

	if (optind >= argc) {
		FILE *fp = stdin;

		while (fgets(buffer, bufferSize, fp)) {
			int length = strlen(buffer);
			int currentLineBlank = 0;

			if (length > 0 && buffer[length - 1] == '\n'){
				buffer[length - 1] = '\0';
				length--;
			}

			currentLineBlank = (length == 0);

			if (sflag) {
				if (lastLineBlank && currentLineBlank)
					continue;

				lastLineBlank = currentLineBlank;
			}

			if (bflag && !currentLineBlank){
				char tmp[bufferSize];
				snprintf(tmp, bufferSize, "%6d\t%s", lineNumber++, buffer);
				strncpy(buffer, tmp, bufferSize - 1);
				buffer[bufferSize - 1] = '\0';
			}
			else if (nflag){
				char tmp[bufferSize];
				snprintf(tmp, bufferSize, "%6d\t%s", lineNumber++, buffer);
				strncpy(buffer, tmp, bufferSize - 1);
				buffer[bufferSize - 1] = '\0';
			}

			if (eflag){
				strncat(buffer, "$", bufferSize - strlen(buffer) - 1);
			}

			fprintf(stdout, "%s\n", buffer);
		}
		return 0;
	}



	for (int i = optind; i < argc; i++){
		FILE *fp = fopen(argv[i], "rb");

		if (!fp){
			perror(argv[i]);
			continue;
		}

		while (fgets(buffer, bufferSize, fp)) {

			int length = strlen(buffer);

			if (length > 0 && buffer[length - 1] == '\n') {
				buffer[length - 1] = '\0';
				length--;
			}

			int currentLineBlank = (length == 0);

			if (sflag) {
				if (lastLineBlank && currentLineBlank)
					continue;

				lastLineBlank = currentLineBlank;
			}

			if (bflag && !currentLineBlank){
				char tmp[bufferSize];
				snprintf(tmp, bufferSize, "%6d\t%s", lineNumber++, buffer);
				strncpy(buffer, tmp, bufferSize - 1);
				buffer[bufferSize - 1] = '\0';
			}
			else if (nflag){
				char tmp[bufferSize];
				snprintf(tmp, bufferSize, "%6d\t%s", lineNumber++, buffer);
				strncpy(buffer, tmp, bufferSize - 1);
				buffer[bufferSize - 1] = '\0';
			}

			if (eflag){
				strncat(buffer, "$", bufferSize - strlen(buffer) - 1);
			}

			fprintf(stdout, "%s\n", buffer);
		}

		fclose(fp);
	}

	return 0;
}
