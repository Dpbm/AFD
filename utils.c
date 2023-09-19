#include <string.h>
#include <stdlib.h>
#include "utils.h"

char *remove_first_char(char *text){
	unsigned int text_len = strlen(text);
	char *new_text = calloc(text_len-1, sizeof(char));
	
	unsigned int i;

	for(i = 1; i < text_len; i++)
		new_text[i-1] = text[i];
	
	return new_text;
}
