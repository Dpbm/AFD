#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "automaton.h"


State *init_state(char *label, bool final, unsigned int total_transitions){
	State *new_state = calloc(1, sizeof(State));
	
	new_state->label = (char*)calloc(strlen(label), sizeof(char));
	strcpy(new_state->label, label);

	new_state->final = final;
	new_state->last_transition_index = -1;
	new_state->total_transitions = total_transitions;
	new_state->transitions = calloc(total_transitions, sizeof(Transition*));
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

bool symbol_in_alphabet(Alphabet *alphabet, char symbol){
	unsigned int i;
	for(i = 0; i < alphabet->size; i++)
		if(alphabet->symbols[i] == symbol)
			return true;

	return false;
}

bool test(Automaton *automaton, Alphabet *alphabet, char *sequence){
	unsigned int i;
	unsigned int sequence_len = strlen(sequence);
	State *actual_state = automaton;

	for(i = 0; i < sequence_len; i++){
		char symbol = sequence[i];

		if(!symbol_in_alphabet(alphabet, symbol))
			return false;

		unsigned int state_total_transitions = actual_state->total_transitions; 
		unsigned int transition_index;
		for(transition_index = 0; transition_index < state_total_transitions; transition_index++){
		
			Transition *actual_transition = actual_state->transitions[transition_index];

			if(actual_transition->symbol == symbol){
				actual_state = actual_transition->next;
				break;
			}

		}
	}

	return actual_state->final;
}

char *get_label(){
	int max_label_size = 20;
	char *buffer = (char*)calloc(max_label_size, sizeof(char));
	scanf("%s", buffer);
	return buffer;
}
