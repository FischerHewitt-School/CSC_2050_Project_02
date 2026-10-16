#include<stdio.h>

//purpose: to count the number of characters, words, and lines and print to the stdout
//input: file pointer
//output: void
//result: prints #lines #words #characters

void wc_helper(FILE *fp){
	int lines = 0;
	int words = 0;
	int word_flag = 0;
	int characters = 0;
	int c;
	while((c = fgetc(fp)) > -1){
		characters++;
		//checks for '\n'
		if (c == 10){
			// adds 1 to lines
			lines++;
			//this also marks the end of a word
			word_flag = 0;
		}
	// if it is a character that is not a blank space,
	// we are either currently in a word and dont need to increase the words,
	// but keep word length flagged
	// or word_length is 0 and we need to increase the amount of words
	// ascii(32) = ' ', ascii(9) = \t = '   ', ascii(13) = '/r', ascii(11) = '\v', ascii(12) = '\f'      
		else if (c != 32 && c != 9 && c != 13 && c != 11 && c != 12){
			// if we are not currently keeping track of a word, then we need to flag it
			// and that means we hit a new word
			if (word_flag == 0){
				words++;
			}
			word_flag = 1;
		} 
		// if its a white space, then we are at the end of the word so we need to set the flag
		// to false essentially
		else {
			word_flag = 0;
		}
	}
	printf(" %d %d %d ",lines, words, characters);
	return;
}

int main(int argc, char *argv[]) {
	FILE *fp;
	// if there are two arguments
	if (argc == 2) {
		// open the file
		fp = fopen(argv[1],"r");
		if (fp == NULL){
			//if file could not open
			perror("File could not open");
			return -1;
		}
	}
        // if the only argument is the executable
	else if (argc == 1)  {
		// start the standard input (keyboard)
		fp = stdin;
	} else {
		printf("to many arguments");
		return -1;
	}
	//count lines, words, characters
	wc_helper(fp);
	fclose(fp);
	if (argc == 2) {printf("%s",argv[1]);}
	printf("\n");
	return 0;
}


