#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "automaton.h"
#include "utils.h"

State *init_state(char *label, bool final, unsigned int total_transitions){
	State *new_state = calloc(1, sizeof(State));
	new_state->label = label;
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


StatesList *get_states(unsigned int total_transitions){
	unsigned int total_states = 0;
	State **states = NULL;
	
	while(1){
		char *label = NULL;

		do{

			label = get_string();
			if(label == NULL)
				printf("\nType the label of the state!\n");
		
		}while(label == NULL);
		
		if(strcmp(label, "!") == 0)
			break;
	
		total_states++;
		states = (State**)realloc(states, total_states);

		bool final = false;

		#if(DEBUG==1)
			printf("\n\n--INPUT LABEL--\n");
			printf("label: %s\n\n", label);
		#endif
		
		if(label[0] == '*'){
			final = true;
			label = remove_first_char(label);
			
			#if(DEBUG==1)
				printf("\n\n--INSERTED A FINAL STAETE--\n");
				printf("label updated: %s\n\n", label);
			#endif
		}
	
		states[total_states-1] = init_state(label, final, total_transitions);
		free(label);
	}
	
	StatesList *states_list = calloc(1, sizeof(StatesList));
	states_list->total_states = total_states;
	states_list->states = states;

	return states_list;
}
