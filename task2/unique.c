#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
//Purpose:This program echoes (to stdout) its input but will print only a single instance of consecutive matching lines.
//Input: FILE file-pointer
//Output: void
//Result: prints to the terminal different consective lines
//"This\nThis\nDifferent\nThis\nThis" -> "This\nDifferent\nThis" 
void unique_help(FILE *fp){
	char *prev_buffer = NULL;
	ssize_t prev_characters = 0;
	char *cur_buffer = NULL;
	size_t cur_size = 0;
	ssize_t cur_characters;
	while ((cur_characters = getline(&cur_buffer, &cur_size, fp)) > -1){
		// The first iteration, prev_buffer will be NULL
		if (prev_buffer == NULL	|| strcmp(prev_buffer, cur_buffer) != 0){
			// check for an edge case at the end where 
                        // strcomp("ab\n", "ab") 
                        // Unique would consider this a repetition and would not print "ab" again
                        if (prev_characters - cur_characters == 1) {

                                int same = 1; //same = TRUE
                                for (int i = 0; i < cur_characters; i++){
					// if the strings are different break the for loop so we can
					// print it
                                        if (*(prev_buffer + i) != *(cur_buffer + i) ){
                                                same = 0;
                                                break;
                                        }
                                }
				// if the strings are the same except for the new line at the end
				// break the while loop and dont print anything
                                if (same) {
                                        break;
                                }

                        }
			// Print the first line
			printf("%s", cur_buffer);
			// printing a new line to mimic uniq on last iteration
			if (*(cur_buffer + cur_characters - 1) != 10){
                                printf("\n");
                        }
			//if its not the first iteration, then we need to free prev_buffer
			if (prev_buffer != NULL){
				free(prev_buffer);
			}
			// Set the line to previous buffer
			prev_buffer = cur_buffer;
			prev_characters = cur_characters;
			// clear cur_buffer so it can be used again by getline
			cur_buffer = NULL;
			cur_size = 0;

		// if the current line is the same as the previous line
		} else {
			// free the current one
			free(cur_buffer);
			// reset so it can be used again by get line
			cur_buffer = NULL;
			cur_size = 0;
		} 

	}
	free(prev_buffer);
	free(cur_buffer);	
	return;
}

int main(int argc, char *argv[]){
	FILE *fp;
	// If there are two arguments
	if (argc == 2){
		// Attempt to open file
		fp = fopen(argv[1], "r");
		// error check
		if (fp == NULL){
			perror("Unable to open file\n");
			return -1;
		}

	// if only the executable as an argument
	} else if (argc == 1){
		// we are using standard input
		fp = stdin;
	} else {
		// otherwise we know there are to many arguments
		printf("Error: To many arguments\n");
		return -1;
	}
	unique_help(fp);
	fclose(fp);

	return 0;
}
