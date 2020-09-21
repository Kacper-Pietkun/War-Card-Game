#ifndef deck_operations_h
#define deck_operations_h
#include "Constants.h"
#include "Structures.h"

// OPERATIONS ON DECKS | FUNTIONS
// ------------------------------------------------------------------------------------------------------------------------------------------------------

// ALOCATING MEMORY | FUNCTIONS
// ------------------------------------------------------------------------------------------------------------------------------------------------------
card_t* allocate_mem_for_cards(int amount);
game_deck_t* allocate_mem_for_deck();
// ------------------------------------------------------------------------------------------------------------------------------------------------------

// get card 1st in the queue
card_t* get_card_from_top(game_deck_t** deck);


// Adding card to the end of the queue
void deck_add_card(game_deck_t** deck, card_t* source);


// Deleting card from the beginning of the queue
void deck_remove_card(game_deck_t** deck);


// Adding card to the beginning of the que
void thrust_card_to_deck(game_deck_t** deck, card_t* source);


// Printing the whole deck from the last card in the queue to the first one
void print_deck(game_deck_t** deck);


// Sets variables at the beginning of the program 
void reset_decks(game_deck_t* decks[], int length);


// The bigger is SHUFFLE_POWER the more shuffled is deck
void shuffle_deck(card_t** deck, const int length);


//Based on integer values of variables in card, it puts adequate string to text_color and text_value
void translate_card(card_t* source);


// Fills deck with aces, then with kings, ..., at the end with twos
/*
	14 is value for ace
	13 is value for king
	.
	.
	.
	2 is value for 2
	*/
void fill_starting_deck(card_t** starting_deck, const int length);

void random_fill_starting_deck(card_t** starting_deck, const int length);


// Used during random filling cards
int card_repeat(card_t* arr, card_t buf, int n);


// Adding card to stake deck and deleting this same card from original deck
void transfer_from_deck_to_stake(game_deck_t* decks[], game_deck_t* stake_decks[], card_t* curr_player_card[]);


void copy_information(card_t* to, const card_t from);

// Dealing cards from main deck to two other decks by turns
void dealing_cards(card_t** main_deck, game_deck_t* decks[], int length);


void count_deck_rank(int method, game_deck_t* decks[]);

// Sum of value of every card
void count_deck_rank_method_1(game_deck_t** deck);


// Sum of value of aces, kings, queens, jacks
void count_deck_rank_method_2(game_deck_t** deck);


// Sum of value of cards with even values (twos, fours and so on)
// Additionaly 10 points if the first or the last card in the deck is ace, king or queen
// Additionaly 5 points if the second or the last but one card in the deck is ace, king or queen
// Additionaly 4 points if decks constis of 4 tens
void count_deck_rank_method_3(game_deck_t** deck);


// Lets user to fill deck by himself (not randomly)
void manually_dealed_cards(game_deck_t* decks[], int size);


// Triggered after round has ended in STANDARD WAR
// Adding card to winner's deck from his own stake_deck (1)
// Adding cards to winner's deck from loser's stake_deck (2)
void get_cards_from_battle(game_deck_t* decks[], game_deck_t* stake_decks[], const int winner_index, const int loser_index);


// Triggered after round has ended in WISE WAR
void get_cards_from_battle_wisely(game_deck_t** deck, game_deck_t* stake_decks[]);


// After game is finished, we have to "free()" all the memory from decks
void clear_memory(game_deck_t* decks[], int length, card_t** starting_deck);


// Used for standard war game and 1st experiment (2nd experiment uses different becasue we need to generate cards randomly there)
// It starts filling deck with aces then kings ... and at the end twos
void const_decks_preparations(card_t** starting_deck, int starting_deck_size, game_deck_t* decks[]);


// Starting deck is always filled with random cards
void random_decks_preparations(card_t** starting_deck, int starting_deck_size, game_deck_t* decks[]);

// ------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // !deck_operations_h

