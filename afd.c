#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "automaton.h"
#include "utils.h"

#define DEBUG 1

State *init_state(char *label, bool final, unsigned int alphabet_len);

int main(){
	Alphabet *alphabet = calloc(1, sizeof(Alphabet));
	
	unsigned int alphabet_size = 0;
	printf("Alphabet Size: ");
	scanf("%d", &alphabet_size);

	char *alphabet_symbols = calloc(alphabet_size, sizeof(char));
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
		printf("symbols --> %s\n", alphabet_symbols);
	#endif 
	
	
	Automaton *automaton = NULL;

	unsigned int total_states = 0;
	printf("\nHow many states do you have? ");
	scanf("%d", &total_states);

	printf("\nType in each row the label of the state from your table (the same order):\n");
	State *states = calloc(total_states, sizeof(State));

	int i;
	for(i = 0; i < total_states; i++){

		//!WARNING: MAY BE UNSECURE
		char *label = calloc(1, sizeof(char));
		bool final = false;

		scanf("%s", label);

		#if(DEBUG==1)
			printf("label --> %s\n", label);
		#endif

		if(label[0] == '*'){
			final = true;
			label = remove_first_char(label);
			
			#if(DEBUG==1)
				printf("!final state!\n");
				printf("label updated --> %s\n", label);
			#endif
		}

		states[i] = *init_state(label, final, alphabet_size);
	}
	
	return 0;
}

State *init_state(char *label, bool final, unsigned int alphabet_len){
	State *new_state = calloc(1, sizeof(State));
	new_state->label = label;
	new_state->final = final;
	new_state->total_transitions = alphabet_len;
	new_state->transitions = calloc(alphabet_len, sizeof(Transition));
	return new_state;
}

