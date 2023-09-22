#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "automaton.h"
#include "utils.h"
#include "debug.h"

int main(){

	printf("Aphabet symbols (insert all symbols without separation between them): ");
	
	char *alphabet_symbols = get_string();
	if(alphabet_symbols == NULL){
		printf("Invalid symbols!!!\n");
		return 1;
	}

	unsigned int alphabet_size = strlen(alphabet_symbols);
	if(alphabet_size <= 0){
		printf("Invalid Alphabet size!\n");
		return 1;
	}

	Alphabet *alphabet = calloc(1, sizeof(Alphabet));
	alphabet->size = alphabet_size;
	alphabet->symbols = alphabet_symbols;

	#if (DEBUG==1)
		printf("size --> %d\n", alphabet_size);
		printf("symbols --> %s\n", alphabet_symbols);
	#endif 

	free(alphabet_symbols);
	
	printf("\nType in each row the label of the state from your table (the same order):\nType ! to stop\n");
	StatesList *states_list = get_states(alphaet_size);
	if(states_list->states == NULL){
		printf("No states were provided!\n");
		return 1;
	}
	
	Automaton *automaton = states_list->states[0];

	printf("\nNow type each Transition:\n");
	unsigned int total_transitions = alphabet_size;
	//for(i = 0; i < total_states; i++){
		
		//State *parent = states[i]; 

		//unsigned int j;
		//for(j = 0; j < total_transitions; j++){
		
			//char symbol = alphabet->symbols[j];

			//State *state = NULL;
			//do{
				//printf("Transtion %s when the symbol is %c: ", parent->label, symbol);
				//char *label = get_string();

				//state = find_state(states, label, total_states);

				//#if (DEBUG==1)
					//printf("!FOUND STATE!\n");
					//printf("label --> %s\n", state->label);
				//#endif

				//if(state == NULL)
					//printf("\nINVALID STATE %s, TYPE AGAIN!!!\n", label);
			//}while(state == NULL);
		
			//add_transition(symbol, state, &parent);
		//}
	//}

	while(1){

		printf("\nInsert the sequence to test:\nType ! to stop\n");
		char *input = get_string();
		
		if(strcmp(input, "!") == 0)
			break;

		if(test(automaton, input))
			printf("ACCEPTED!\n");
		else
			printf("NOT ACCEPTED!\n");

	}

	return 0;
}

