#ifndef main_menu_h
#define main_menu_h
#include "Constants.h"
#include "Structures.h"

// MENU INTERFACE | FUNCTIONS
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Allows player to choose mode of the game/experiment
// Returns a pointer (to function) which points at chosen game mode
game_status_t(*choose_game_mode())(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]);
void choose_strategy(strategy_t player_strategy[]);
int choose_experiment_deck_size();
void experiment_menu(experiment_number_t exp_number, card_t** starting_deck, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]));
void start_main_menu(card_t** starting_deck, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]));
// ------------------------------------------------------------------------------------------------------------------------------------------------------


#endif // !main_menu_h
