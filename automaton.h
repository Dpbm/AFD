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

typedef struct Transition{
  char symbol;
  struct State *next;
} Transition;

typedef struct State State;
typedef struct State Automaton;

State *init_state(char *label, bool final, unsigned int total_transitions);
State *find_state(State **states, char *label, unsigned int total_states);
Transition *create_transtion(char symbol, State *next);
void add_transition(char symbol, State *next, State **parent);
bool test(Automaton *automaton, Alphabet *alphabet, char *sequence);
char *get_label();

#endif
