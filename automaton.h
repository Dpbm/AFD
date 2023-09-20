#ifndef AUTOMATON
#define AUTOMATON

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

typedef struct State State;
typedef struct State Automaton;



typedef struct Transition{
  char symbol;
  struct State *next;
} Transition;



#endif // !AUTOMATON
