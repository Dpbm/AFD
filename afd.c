#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "automaton.h"

#define DEBUG 0

int main(){
	Alphabet *alphabet = calloc(1, sizeof(Alphabet));
	
	unsigned int alphabet_size = 0;
	char *alphabet_symbols = calloc(alphabet_size, sizeof(char));

	printf("Alphabet Size: ");
	scanf("%d", &alphabet_size);

	printf("Aphabet symbols (insert all symbols without separation between them): ");
	scanf("%s", alphabet_symbols);

	if(strlen(alphabet_symbols) != alphabet_size){
		printf("Alphabet is different in size!");
		return 1;
	}

	alphabet->size = alphabet_size;
	alphabet->symbols = alphabet_symbols;
	
	#if (DEBUG==1)
		printf("size --> %d\n", alphabet_size);
		printf("symbols --> %s", alphabet_symbols);
	#endif /* ifdef DEBUG */
	

	return 0;
}
