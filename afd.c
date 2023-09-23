#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "automaton.h"
#include "utils.h"

#define DEBUG 1

char *get_label();

int main(){
	Alphabet *alphabet = calloc(1, sizeof(Alphabet));
	
	unsigned int alphabet_size = 0;
	printf("Alphabet Size: ");
	scanf("%d", &alphabet_size);

	if(alphabet_size <= 0){
		printf("Invalid Alphabet Size!!\n");
		return 1;
	}

	char *alphabet_symbols = calloc(alphabet_size, sizeof(char));
	printf("\nAphabet symbols\nInsert all symbols WITHOUT SEPARATION between them: ");
	scanf("%s", alphabet_symbols);

	#if (DEBUG==1)
		printf("\n\n--ALPHABET--\n");
		printf("size: %d\n", alphabet_size);
		printf("strlen(): %d\n", strlen(alphabet_symbols));
		printf("symbols: %s\n\n", alphabet_symbols);
	#endif 

	if(strlen(alphabet_symbols) != alphabet_size){
		printf("Alphabet is different in size!");
		return 1;
	}

	alphabet->size = alphabet_size;
	alphabet->symbols = alphabet_symbols;



	unsigned int total_states = 0;
	printf("\nHow many states do you have? ");
	scanf("%d", &total_states);

	printf("\nType in each row the label of the state from your table (USE THE SAME ORDER)\n");
	State **states = calloc(total_states, sizeof(State*));
	
	unsigned int i;
	for(i = 0; i < total_states; i++){

		char *label = get_label();
		bool final = false;

		#if(DEBUG==1)
			printf("\n\n--INPUT LABEL--\n");
			printf("label: %s\n\n", label);
		#endif

		if(label[0] == '*'){
			final = true;
			label = remove_first_char(label);
			
			#if(DEBUG==1)
				printf("\n\n--FINAL STATE--\n");
				printf("label updated: %s\n\n", label);
			#endif
		}

		states[i] = init_state(label, final, alphabet_size);
		free(label);
	}

	Automaton *automaton = states[0];

	printf("\nNow type each Transition:\n");
	unsigned int total_transitions = alphabet_size;
	for(i = 0; i < total_states; i++){
		
		State *parent = states[i]; 

		unsigned int j;
		for(j = 0; j < total_transitions; j++){
		
			char symbol = alphabet->symbols[j];

			State *state = NULL;
			do{
				char *label = calloc(1, sizeof(char));
				printf("Transtion %s when the symbol is %c: ", parent->label, symbol);
				scanf("%s", label);

				state = find_state(states, label, total_states);

				#if (DEBUG==1)
					printf("!FOUND STATE!\n");
					printf("label --> %s\n", state->label);
				#endif

				if(state == NULL)
					printf("\nINVALID STATE %s, TYPE AGAIN!!!\n", label);
			}while(state == NULL);
		
			add_transition(symbol, state, &parent);
		}
	}

	while(1){

		char *input = calloc(1, sizeof(char));
		printf("\nInsert the sequence to test:\nType ! to stop\n");
		scanf("%s", input);
		
		if(strcmp(input, "!") == 0)
			break;

		if(test(automaton, input))
			printf("ACCEPTED!\n");
		else
			printf("NOT ACCEPTED!\n");

	}

	return 0;
}

char *get_label(){
	int max_label_size = 20;
	char *buffer = (char*)calloc(max_label_size, sizeof(char));
	scanf("%s", buffer);
	return buffer;
}
