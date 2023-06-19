#include <cstdlib>
#include <climits>
#include <iostream>

#include "../state/state.hpp"
#include "./minimax.hpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){

  if(!state->legal_actions.size())
     state->get_legal_actions();

    int value = 0;
    
    auto actions = state->legal_actions;
    if(state->player == 0){ //self是 0 白 先手
      int max_value=INT_MIN;
      int max = 0;
      for(size_t i=0;i<actions.size();i++){
        State *tmp;
        tmp = state->next_state(actions[i]);
          
        value = Minimax::minimax(tmp, depth-1, 1);
        if(value > max_value){
          max_value = value;
          max = i;
        }
        delete tmp;  
      }
      return actions[max];
    }
    else{ //self是 1 黑 後手
      int min_value=INT_MAX;
      int min = 0;

      for(size_t i=0;i<actions.size();i++){
        State *tmp;
        tmp = state->next_state(actions[i]);
          
        value = Minimax::minimax(tmp, depth-1, 0);
        if(value < min_value){
          min_value = value;
          min = i;
        }
        delete tmp;  
      }
      return actions[min];
    }

}

int Minimax::minimax(State *state, int depth, bool player){

  auto actions = state->legal_actions;
  if(depth==0){
    return state->evaluate();
  }

  if(player==0){
    int best_value = INT_MIN;
    int value=0;
    for(size_t i=0;i<actions.size();i++){
      State *tmp;
      tmp = state->next_state(actions[i]);
      value = Minimax::minimax(tmp, depth-1, 1);
      best_value = std::max(best_value,value);
      //delete tmp;
    }
    return best_value;
  }
  else{
    int best_value = INT_MAX;
    int value=0;
    for(size_t i=0;i<actions.size();i++){
      State *tmp;
      tmp = state->next_state(actions[i]);
      value = Minimax::minimax(tmp, depth-1, 0);
      best_value = std::min(best_value,value);
      //delete tmp;
    }
    return best_value;
  }
}