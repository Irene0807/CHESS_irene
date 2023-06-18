#include <cstdlib>

#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int min_value=0, min;
  for(int i=0; i<actions.size(); i++){
    State *tmp;
    tmp = state->next_state(actions[i]);
    if(tmp->evaluate() <min_value){
      min_value = tmp->evaluate();
      min = i;
    }
  }

  return actions[min%actions.size()];
}