#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "automaton.h"
#include "utils.h"

#define DEBUG 0

State *init_state(char *label, bool final, unsigned int alphabet_len);
State *find_state(State **states, char *label, unsigned int total_states);
Transition *create_transtion(char symbol, State *next);
void add_transition(char symbol, State *next, State **parent);
bool test(Automaton *automaton, char *sequence);

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
	State **states = calloc(total_states, sizeof(State*));

	unsigned int i;
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

		states[i] = init_state(label, final, alphabet_size);
	}

	automaton = states[0];

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

State *init_state(char *label, bool final, unsigned int alphabet_len){
	State *new_state = calloc(1, sizeof(State));
	new_state->label = label;
	new_state->final = final;
	new_state->last_transition_index = -1;
	new_state->total_transitions = alphabet_len;
	new_state->transitions = calloc(alphabet_len, sizeof(Transition*));
	return new_state;
}

State *find_state(State **states, char *label, unsigned int total_states){
	unsigned int i;
	for(i = 0; i < total_states; i++){
		State *actual_state = states[i];
		if(strcmp(actual_state->label, label) == 0)
			return actual_state;
	}

	return NULL;
}


void add_transition(char symbol, State *next, State **parent){
	Transition *transition = create_transtion(symbol, next);
	unsigned int new_last_index = (*parent)->last_transition_index+1;
	(*parent)->transitions[new_last_index] = transition;
	(*parent)->last_transition_index = new_last_index;
}

Transition *create_transtion(char symbol, State *next){
	Transition *transition = calloc(1, sizeof(Transition));
	transition->symbol = symbol;
	transition->next = next;
	return transition;
}

bool test(Automaton *automaton, char *sequence){
	unsigned int i;

	State *actual_state = automaton;

	for(i = 0; i < strlen(sequence); i++){
		
		char symbol = sequence[i];

		unsigned int transition_index;
		for(transition_index = 0; transition_index < actual_state->total_transitions; transition_index++){
			Transition *actual_transition = actual_state->transitions[transition_index];
			if(actual_transition->symbol == symbol){
				actual_state = actual_transition->next;

				#if (DEBUG==1)
					printf("new state --> %s\n", actual_state->label);
				#endif

				break;
			}
		}
	}

	return actual_state->final;
}
