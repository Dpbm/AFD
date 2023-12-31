#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "automaton.h"
#include "utils.h"

#define DEBUG 0

int main(){
	Alphabet *alphabet = (Alphabet*)calloc(1, sizeof(Alphabet));
	
	unsigned int alphabet_size = 0;
	printf("Alphabet Size: ");
	scanf("%d", &alphabet_size);

	if(alphabet_size <= 0){
		printf("INVALID ALPHABET SIZE!!\n");
		return 1;
	}

	char *alphabet_symbols = (char*)calloc(alphabet_size, sizeof(char));
	printf("\nAlphabet symbols\nInsert all symbols WITHOUT SEPARATION between them: ");
	scanf("%s", alphabet_symbols);

	#if (DEBUG==1)
		printf("\n\n--ALPHABET--\n");
		printf("size: %d\n", alphabet_size);
		printf("strlen(): %d\n", strlen(alphabet_symbols));
		printf("symbols: %s\n\n", alphabet_symbols);
	#endif 

	if(strlen(alphabet_symbols) != alphabet_size){
		printf("ALPHABET IS DIFFERENT IN SIZE!\n");
		return 1;
	}

	alphabet->size = alphabet_size;
	alphabet->symbols = (char*)calloc(alphabet_size, sizeof(char));
	strcpy(alphabet->symbols, alphabet_symbols);
	free(alphabet_symbols);

	unsigned int total_states = 0;
	printf("\nHow many states do you have? ");
	scanf("%d", &total_states);

	printf("\nType in each row the label of the state from your table (USE THE SAME ORDER)\nmark the FINAL STATE with a '*' BEFORE its label\n");
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

	printf("\nType each Transition\n");

	unsigned int total_transitions = alphabet_size;
	for(i = 0; i < total_states; i++){
		
		State *parent = states[i]; 

		unsigned int j;
		for(j = 0; j < total_transitions; j++){
		
			char symbol = alphabet->symbols[j];

			State *state = NULL;
			do{
				printf("Transtion from %s when the symbol is %c: ", parent->label, symbol);
				char *label = get_label();

				state = find_state(states, label, total_states);

				#if (DEBUG==1)
					if(state != NULL){
						printf("\n\n--FOUND STATE--\n");
						printf("label: %s\n\n", state->label);
					}else{
						printf("\n\n--NOT FOUND STATE--\n");
						printf("input label: %s\n\n", label);
					}
				#endif

				if(state == NULL)
					printf("\nINVALID STATE %s, TYPE AGAIN!!!\n", label);

			}while(state == NULL);
		
			add_transition(symbol, state, &parent);
		}
	}
	free(states);

	while(1){
		unsigned int sequence_buffer_size = 50;
		char *input = (char*)calloc(sequence_buffer_size, sizeof(char));
		printf("\nInsert the sequence to test\nType '!' to STOP\n");
		scanf("%s", input);
		
		if(strcmp(input, "!") == 0)
			break;

		if(test(automaton, alphabet, input))
			printf("ACCEPTED!\n");
		else
			printf("NOT ACCEPTED!\n");

	}

	return 0;
}

