#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "debug.h"

char *remove_first_char(char *text){
	unsigned int text_len = strlen(text);
	char *new_text = calloc(text_len-1, sizeof(char));
	
	unsigned int i;

	for(i = 1; i < text_len; i++)
		new_text[i-1] = text[i];
	
	return new_text;
}

char *get_string(){
	char *string = NULL;
	unsigned int length = 0;
	unsigned int capacity = 1;

	while(1){
		char input_char = getchar();

		#if (DEBUG == 1)
			printf("input char --> %c\n", input_char);
		#endif 

		if(input_char == EOF || input_char == '\n'){
			#if (DEBUG==1)
				printf("EOF - /n --> '%c'\n", input_char);
			#endif
			break;
		}

		if(length + 1 >= capacity){
			capacity *= 2;

			#if (DEBUG == 1)
				printf("new capacity --> %d\n", capacity);
			#endif

			string = (char*)realloc(string, capacity);
		}

		string[length++] = input_char;
		
		#if (DEBUG == 1)
			printf("string --> %s\n", string);
			printf("length --> %d\n", length);
		#endif
	}

	if(string == NULL){
		#if (DEBUG == 1)
			printf("NULL STRING!!\n");
		#endif
		return string;
	}

	if(length >= capacity){
		capacity++;
		
		#if (DEBUG == 1)
			printf("new capacity --> %d\n", capacity);
		#endif
		
		string = (char*)realloc(string, capacity);
	}

	string[length] = '\0';
	
	#if (DEBUG == 1)
		printf("final --> %s\n", string);
	#endif

	return string;
}
