//http://www.algorytm.org/klasyczne/kolejka/kolejka-2-c.html?fbclid=IwAR110lpCu4GCicefHNAtfyDicFk3jsbDAp_AjfRKXDZze0EeDKNSa1qQ92U
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Constants.h"
#include "Deck_operations.h"
#include "Experiments.h"
#include "Game_interface.h"
#include "Main_menu.h"
#include "Structures.h"
#include "War.h"

int main()
{
	srand((unsigned int)time(NULL));

	// Two main structures in the game
	game_deck_t* decks[NUMBER_OF_PLAYERS];
	// Using card_t structure for starting deck, because we won't use it as a queue, we need just information about color and value, we will treat it like an array
	card_t* starting_deck = NULL;

	decks[PLAYER_1] = allocate_mem_for_deck();
	decks[PLAYER_2] = allocate_mem_for_deck();

	reset_decks(decks, NUMBER_OF_PLAYERS);

	// Pointer will trigger adequate game mode (A or B), which will be chosen by the player 
	game_status_t(*game_mode)(file_t * my_file, experiment_data_t * data_for_exp, game_deck_t * decks[], card_t * curr_player_card[], game_deck_t * stake_decks[]);
	game_mode = NULL;

	start_main_menu(&starting_deck, decks, game_mode);

	free(decks[PLAYER_1]);
	free(decks[PLAYER_2]);

	return 0;
}