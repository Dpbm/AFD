#ifndef AUTOMATON
#define AUTOMATON

#include <stdbool.h>

typedef struct Alphabet {
  unsigned int size;
  char *symbols;
} Alphabet;

struct State{
  char *label;
  bool final;
  unsigned int last_transition_index;
  unsigned int total_transitions;
  struct Transition **transitions;
};

typedef struct StatesList{
  unsigned int total_states;
  struct State **states;
} StatesList;

typedef struct State State;
typedef struct State Automaton;

typedef struct Transition{
  char symbol;
  struct State *next;
} Transition;


State *init_state(char *label, bool final, unsigned int alphabet_len);
State *find_state(State **states, char *label, unsigned int total_states);
Transition *create_transtion(char symbol, State *next);
bool test(Automaton *automaton, char *sequence);
StatesList *get_states(unsigned int total_transitions);
void add_transitions(Alphabet *alphabet, State **states, unsigned int total_states, unsigned int total_transitions);

#endif // !AUTOMATON
