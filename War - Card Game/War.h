#ifndef war_h
#define war_h
#include "Constants.h"
#include "Structures.h"

// WAR | FUNCTIONS
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Returns number of rounds, variable needed for 1st experiment
// In this function actual game takes place
experiment_data_t start_standard_game(file_t* my_file, card_t** starting_deck, int starting_deck_size, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]));
experiment_data_t start_wise_game(strategy_t player_strategy[], file_t* my_file, card_t** starting_deck, int starting_deck_size, game_deck_t* decks[]);

// At the end of the round comparing cards
game_status_t compare_cards_wise(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], int their_turn, int not_their_turn);
game_status_t compare_cards_standard(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]));

game_status_t war_version_a(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]);
game_status_t war_version_b(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]);
// Triggered when one player starts war with only 1 card
game_status_t handle_version_b_1_cards(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], int index_more_cards, int index_less_cards);
// Triggered when one player starts war with only 2 cards
game_status_t handle_version_b_2_cards(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], int index_more_cards, int index_less_cards);

void who_is_the_winner(strategy_t player_strategy[], game_status_t status, experiment_data_t* data_for_exp, file_t* my_file, game_deck_t* decks[]);
void fill_data_for_experiment(game_deck_t* decks[], experiment_data_t* data_for_exp, strategy_t player_strategy[], int winner_index, int loser_index);
void swap_int(int* one, int* two);
void free_curr_cards(card_t* curr_player_card[]);
void update_initial_size(game_deck_t* decks[]);
// Checking if game has reached its limit
void is_game_infinite(file_t* my_file, experiment_data_t* data);

void player_choose_card(strategy_t player_strategy[], file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
int trigger_strategy(strategy_t player_strategy[], file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
int no_strategy_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
int random_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
int furious_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
int peaceful_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
int my_strategy_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn);
// ------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // !war_h

