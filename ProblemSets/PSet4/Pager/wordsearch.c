//Ridwan Hussain & Nicholas Storniolo - From a given file input, take in a list of words
//as potential matches, and check if those words appear in stdin. If a match occurs, 
//echo the word to standard output.

#include <stdio.h>
#include <errno.h>
#include <string.h>

void wordSearch(FILE* dictFP);

int main(int argc, char* argv[]) {
	FILE* dictFP;
	if (argc < 2) {
		fprintf(stderr, "Error, no file input was given. Exiting program.\n");
		return 1;
	} else if ((dictFP = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error Opening Dictionary File %s\nError Number: %d, StrError: %s\n", argv[1], errno, strerror(errno));
		return errno;
	}
	wordSearch(dictFP);
	fclose(dictFP);
	return 0;
}

void wordSearch(FILE* dictFP) {
	char* dictLine; size_t lineLen = 0;
	char c; int lines = 0; int nc = 8+2;
	
	//Count Number of lines
	for (c = getc(dictFP); c != EOF; c = getc(dictFP)) {
		if (c == '\n') {
			lines++;
		}
	}
	rewind(dictFP);
	
	//Store dictionary into string array
	//int nc = 8 + 1; //The 8 is the char limit from wordgen, the +1 for \n
	char dict[lines][nc+2]; //+1 here is for the \0 
	for (int i = 0; getline(&dictLine, &lineLen, dictFP) != EOF; i++) {
		fprintf(stdout, "%d --> |%s|", strlen(dictLine)-1, dictLine);
		strncpy(dict[i], dictLine, strlen(dictLine)-1);
		dict[i][strlen(dictLine)-1] = '\0';
		fprintf(stdout, "Fin --> |%s|", dict[i]);
	}

	char userInput[nc+1];
	while(1) {
		while((fgets(userInput, nc, stdin) == NULL)) {
			if ((c = getchar()) == EOF) {
				fprintf(stdout, "\n");
				return;
			}
		}

		if (userInput == NULL) { //maybe OR strlen(userInput) < 3)
			continue;
		}
		userInput[strlen(userInput) - 1] = '\0';
		fprintf(stdout, "UserInput = |%s|\n", userInput);
		for (int i = 0; i < lines; i++) {
			fprintf(stdout, "|%s|\n", dict[i]);
			if (!strcmp(userInput, dict[i])) {
				fprintf(stdout, "Found a match: %s\n", dict[i]);
			}
		}
		
	}

}