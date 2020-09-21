#ifndef experiments_h
#define experiments_h
#include "Constants.h"
#include "Structures.h"

// EXPERIMENTS | FUNCTIONS
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Preparing to trigger game for experiment purposes
int carry_out_satisfaction_experiment(experiment_number_t exp_number, int number_of_games, card_t** starting_deck, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]));
int carry_out_second_experiment(card_t** starting_deck, int number_of_games, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]));
int carry_out_fourth_experiment(card_t** starting_deck, int number_of_games, game_deck_t* decks[]);
void save_fourth_experiment_results(file_t* my_file, int wins[], strategy_t player_strategy[], int draws);
// Before the experiment we choose a name of the file where results will be saved
void set_file_path(experiment_number_t exp_number, int number_of_games, char** save_path);
// ------------------------------------------------------------------------------------------------------------------------------------------------------


#endif // !experiments_h

