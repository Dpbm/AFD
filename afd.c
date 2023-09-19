#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "alphabet.h"


int main(){

	Alphabet *alphabet;
	
	unsigned int alphabet_size = 0;
	char *alphabet_symbols = calloc(alphabet_size, sizeof(char));

	printf("Alphabet Size: ");
	scanf("%d", &alphabet_size);

	printf("Aphabet symbols (insert all symbols without separation between them): ");
	scanf("%s", alphabet_symbols);

	if(strlen(alphabet_symbols) != alphabet_size){
		printf("Alphabet has different size!");
		return 1;
	}

	alphabet->size = alphabet_size;
	alphabet->symbols = alphabet_symbols;

	printf("size --> %d\n", alphabet_size);
	printf("symbols --> %s", alphabet_symbols);


	return 0;
}
