#include <stdio.h>
#include <stdlib.h>
#include "War.h"
#include "Constants.h"
#include "Structures.h"
#include "Game_interface.h"
#include "Deck_operations.h"

experiment_data_t start_standard_game(file_t* my_file, card_t** starting_deck, int starting_deck_size, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]))
{
	experiment_data_t data_for_exp;
	data_for_exp.rounds_counter = 0;

	game_status_t status = STILL_PLAYING;

	// This decks will contain all cards played by each player in one round
	game_deck_t* stake_decks[NUMBER_OF_PLAYERS];
	stake_decks[PLAYER_1] = allocate_mem_for_deck();
	stake_decks[PLAYER_2] = allocate_mem_for_deck();
	reset_decks(stake_decks, NUMBER_OF_PLAYERS);


	card_t* curr_player_card[NUMBER_OF_PLAYERS];
	curr_player_card[PLAYER_1] = NULL;
	curr_player_card[PLAYER_2] = NULL;
	do
	{
		// Updating once per round
		update_initial_size(decks);

		curr_player_card[PLAYER_1] = get_card_from_top(&decks[PLAYER_1]);
		curr_player_card[PLAYER_2] = get_card_from_top(&decks[PLAYER_2]);

		if (curr_player_card[PLAYER_1] == NULL)
		{
			presenting_information(my_file, "Player 1 is out of cards\n\n");
			status = PLAYER_2_WON_GAME;
			break;
		}
		else if (curr_player_card[PLAYER_2] == NULL)
		{
			presenting_information(my_file, "Player 2 is out of cards\n\n");
			status = PLAYER_1_WON_GAME;
			break;
		}

		print_deck_size(my_file, decks[PLAYER_1]->initial_size, decks[PLAYER_2]->initial_size);
		print_played_cards(my_file, curr_player_card[PLAYER_1]->text_color, curr_player_card[PLAYER_1]->text_value, curr_player_card[PLAYER_2]->text_color, curr_player_card[PLAYER_2]->text_value);

		// Adding card to stake deck and deleting this same card from original deck
		transfer_from_deck_to_stake(decks, stake_decks, curr_player_card);
		data_for_exp.rounds_counter++;

		// It is really really rare but sometimes a game can be played infinitely, this if statement handles this case
		is_game_infinite(my_file, &data_for_exp);
		if (data_for_exp.rounds_counter == INFINITE)
			break;

		status = compare_cards_standard(my_file, &data_for_exp, decks, curr_player_card, stake_decks, game_mode);
		if (status != STILL_PLAYING)
			break;

		free_curr_cards(curr_player_card);

		pause_clear_game(my_file);

	} while (status == STILL_PLAYING);

	if (data_for_exp.rounds_counter != INFINITE)
	{
		strategy_t player_strategy[NUMBER_OF_PLAYERS] = { no_strategy, no_strategy };
		who_is_the_winner(player_strategy, status, &data_for_exp, my_file, decks);
	}

	free_curr_cards(curr_player_card);
	free(stake_decks[PLAYER_1]);
	free(stake_decks[PLAYER_2]);

	return data_for_exp;
}
experiment_data_t start_wise_game(strategy_t player_strategy[], file_t* my_file, card_t** starting_deck, int starting_deck_size, game_deck_t* decks[])
{
	game_status_t status = STILL_PLAYING;
	int their_turn = PLAYER_1; // PLAYER_1 always starts game (he puts one card)
	int not_their_turn = PLAYER_2;
	experiment_data_t data_for_exp;
	data_for_exp.rounds_counter = 0;

	// In contrast to standard game, in wise war we need only one stake_deck because winner will take cards that he has won in a random order (they will be shuffled)
	game_deck_t* stake_decks[NUMBER_OF_PLAYERS];
	stake_decks[PLAYER_1] = allocate_mem_for_deck();
	stake_decks[PLAYER_2] = allocate_mem_for_deck();
	reset_decks(stake_decks, NUMBER_OF_PLAYERS);

	// This deck will contain two cards that player will be able to play
	card_t* players_hand[CARD_POSSIBILITY];
	players_hand[PLAYER_1] = NULL;
	players_hand[PLAYER_2] = NULL;

	card_t* curr_player_card[NUMBER_OF_PLAYERS];
	curr_player_card[PLAYER_1] = NULL;
	curr_player_card[PLAYER_2] = NULL;

	do
	{
		if (my_file->save_file == NULL)
		{
			system("cls");
			draw_template();
		}


		// Updating once per round
		update_initial_size(decks);

		curr_player_card[their_turn] = get_card_from_top(&decks[their_turn]);
		if (curr_player_card[their_turn] == NULL)
		{
			presenting_information_with_one_arguments_int(my_file, "Player %d is out of cards\n", their_turn + 1);
			if (their_turn == PLAYER_1)
				status = PLAYER_2_WON_GAME;
			else
				status = PLAYER_1_WON_GAME;
			break;
		}

		deck_add_card(&stake_decks[their_turn], curr_player_card[their_turn]);
		deck_remove_card(&decks[their_turn]);


		for (int i = 0; i < CARD_POSSIBILITY; i++)
		{
			curr_player_card[not_their_turn] = get_card_from_top(&decks[not_their_turn]);
			if (curr_player_card[not_their_turn] != NULL)
			{
				players_hand[i] = curr_player_card[not_their_turn];
				deck_remove_card(&decks[not_their_turn]);
			}
		}

		// We can say player has lost only if both hands are empty
		if (players_hand[CARD_1] == NULL && players_hand[CARD_2] == NULL)
		{
			presenting_information_with_one_arguments_int(my_file, "Player %d is out of cards\n", not_their_turn + 1);
			if (not_their_turn == PLAYER_1)
				status = PLAYER_2_WON_GAME;
			else
				status = PLAYER_1_WON_GAME;
			break;
		}

		player_choose_card(player_strategy, my_file, decks, curr_player_card, players_hand, stake_decks, not_their_turn, their_turn);

		data_for_exp.rounds_counter++;
		// It is really really rare but sometimes a game can be played infinitely, this if statement handles this case
		is_game_infinite(my_file, &data_for_exp);
		if (data_for_exp.rounds_counter == INFINITE)
			break;

		status = compare_cards_wise(my_file, &data_for_exp, decks, curr_player_card, stake_decks, their_turn, not_their_turn);
		if (status != STILL_PLAYING)
			break;

		free_curr_cards(curr_player_card);
		swap_int(&their_turn, &not_their_turn);
		pause_clear_game(my_file);

	} while (status == STILL_PLAYING);

	if (data_for_exp.rounds_counter != INFINITE)
		who_is_the_winner(player_strategy, status, &data_for_exp, my_file, decks);

	free_curr_cards(curr_player_card);
	free(stake_decks[PLAYER_1]);
	free(stake_decks[PLAYER_2]);
	return data_for_exp;
}

game_status_t compare_cards_wise(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], int their_turn, int not_their_turn)
{
	game_status_t status = STILL_PLAYING;

	if (curr_player_card[their_turn]->value == curr_player_card[not_their_turn]->value)
	{
		status = war_version_a(my_file, data_for_exp, decks, curr_player_card, stake_decks);
		if (status != STILL_PLAYING)
			return status;
	}

	if (curr_player_card[their_turn]->value > curr_player_card[not_their_turn]->value)
	{
		wise_UI_round_winner(my_file, their_turn + 1);
		get_cards_from_battle_wisely(&decks[their_turn], stake_decks);
	}
	else
	{
		wise_UI_round_winner(my_file, not_their_turn + 1);
		get_cards_from_battle_wisely(&decks[not_their_turn], stake_decks);
	}
	return STILL_PLAYING;
}
game_status_t compare_cards_standard(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]))
{
	game_status_t status = STILL_PLAYING;
	if (curr_player_card[PLAYER_1]->value == curr_player_card[PLAYER_2]->value)
	{
		status = (*game_mode)(my_file, data_for_exp, decks, curr_player_card, stake_decks); // Starting adequate mode of war 
		if (status != STILL_PLAYING)
			return status;
	}

	if (curr_player_card[PLAYER_1]->value > curr_player_card[PLAYER_2]->value)
	{
		presenting_information(my_file, "Player 1 wins this time\n\n");
		get_cards_from_battle(decks, stake_decks, PLAYER_1, PLAYER_2);
	}
	else
	{
		presenting_information(my_file, "Player 2 wins this time\n\n");
		get_cards_from_battle(decks, stake_decks, PLAYER_2, PLAYER_1);
	}
	return STILL_PLAYING;
}

game_status_t war_version_a(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[])
{
	do
	{
		if (my_file->path == WISE_WAR_PATH)
			wise_UI_draw_info(my_file);
		else
			presenting_information(my_file, "DRAW! It means war!\n\n");

		pause_clear_game(my_file);

		for (int i = 0; i < 2; i++)
		{
			// Cleaning at the beginning of the loop because after this loop we need last two cards
			free_curr_cards(curr_player_card);
			curr_player_card[PLAYER_1] = get_card_from_top(&decks[PLAYER_1]);
			curr_player_card[PLAYER_2] = get_card_from_top(&decks[PLAYER_2]);

			// Checking if each player has got a card
			if (curr_player_card[PLAYER_1] == NULL && curr_player_card[PLAYER_2] == NULL)
			{
				presenting_information(my_file, "Both players are out of cards\n\n");
				return DRAW;
			}
			else if (curr_player_card[PLAYER_1] == NULL)
			{
				presenting_information(my_file, "Player 1 is out of cards\n\n");
				return PLAYER_2_WON_GAME;
			}
			else if (curr_player_card[PLAYER_2] == NULL)
			{
				presenting_information(my_file, "Player 2 is out of cards\n\n");
				return PLAYER_1_WON_GAME;
			}

			transfer_from_deck_to_stake(decks, stake_decks, curr_player_card);
			data_for_exp->rounds_counter++;

			if (i == 0)
			{
				print_deck_size(my_file, decks[PLAYER_1]->initial_size, decks[PLAYER_2]->initial_size);
				if (my_file->path == WISE_WAR_PATH)
					wise_UI_upside_down(my_file);
				else
					print_upside_down(my_file);
				pause_clear_game(my_file);
			}
		}

		print_deck_size(my_file, decks[PLAYER_1]->initial_size, decks[PLAYER_2]->initial_size);
		if (my_file->path == WISE_WAR_PATH)
			wise_UI_cards_played_during_war(my_file, curr_player_card[PLAYER_1]->text_value, curr_player_card[PLAYER_1]->text_color, curr_player_card[PLAYER_2]->text_value, curr_player_card[PLAYER_2]->text_color);
		else
			print_played_cards(my_file, curr_player_card[PLAYER_1]->text_color, curr_player_card[PLAYER_1]->text_value, curr_player_card[PLAYER_2]->text_color, curr_player_card[PLAYER_2]->text_value);


	} while (curr_player_card[PLAYER_1]->value == curr_player_card[PLAYER_2]->value);

	return STILL_PLAYING;
}
game_status_t war_version_b(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[])
{
	// Player can only borrow cards from other player once per round
	already_helped_t helped = NO;
	game_status_t b_status = STILL_PLAYING;
	int wars_in_this_round = 0; // We use initial size of deck to check if any of players started war with two or one card, but if one of them started war \
								// with four cards and that war ended with another war initial size of deck won't change so we have to substract two cards \
								// to check if one of them has one or two cards
	int who_needs_help;
	do
	{
		if (helped == YES)
		{
			presenting_information(my_file, "Player cannot use cards of the other players twice\n\n");
			if (who_needs_help == PLAYER_1)
				return PLAYER_2_WON_GAME;
			else
				return PLAYER_1_WON_GAME;
		}

		presenting_information(my_file, "DRAW! It means war!\n\n");
		pause_clear_game(my_file);

		free_curr_cards(curr_player_card);

		if (decks[PLAYER_1]->initial_size - 2 * wars_in_this_round == 2 && decks[PLAYER_2]->initial_size - 2 * wars_in_this_round == 2 ||
			decks[PLAYER_1]->initial_size - 2 * wars_in_this_round == 1 && decks[PLAYER_2]->initial_size - 2 * wars_in_this_round == 1)
		{
			presenting_information(my_file, "Both players are out of cards\n\n");
			return DRAW;
		}

		// Checking if player needs help with cards
		if (decks[PLAYER_1]->initial_size - 2 * wars_in_this_round == 2)
		{
			who_needs_help = PLAYER_1;
			helped = YES;

			b_status = handle_version_b_2_cards(my_file, data_for_exp, decks, curr_player_card, stake_decks, PLAYER_2, PLAYER_1);
			if (b_status != STILL_PLAYING)
				return b_status;
		}
		else if (decks[PLAYER_2]->initial_size - 2 * wars_in_this_round == 2)
		{
			who_needs_help = PLAYER_2;
			helped = YES;

			b_status = handle_version_b_2_cards(my_file, data_for_exp, decks, curr_player_card, stake_decks, PLAYER_1, PLAYER_2);
			if (b_status != STILL_PLAYING)
				return b_status;
		}
		else if (decks[PLAYER_1]->initial_size - 2 * wars_in_this_round == 1)
		{
			who_needs_help = PLAYER_1;
			helped = YES;

			b_status = handle_version_b_1_cards(my_file, data_for_exp, decks, curr_player_card, stake_decks, PLAYER_2, PLAYER_1);
			if (b_status != STILL_PLAYING)
				return b_status;
		}
		else if (decks[PLAYER_2]->initial_size - 2 * wars_in_this_round == 1)
		{
			who_needs_help = PLAYER_2;
			helped = YES;

			b_status = handle_version_b_1_cards(my_file, data_for_exp, decks, curr_player_card, stake_decks, PLAYER_1, PLAYER_2);
			if (b_status != STILL_PLAYING)
				return b_status;
		}
		// If nobody needs help then we continue normal war
		else
		{
			for (int i = 0; i < 2; i++)
			{
				// Cleaning at the beginning of the loop because after this loop we need last two cards
				free_curr_cards(curr_player_card);

				// We don't have to check if someone is out of cards because in this loop we are sure (100%) that every player have more than two cards

				curr_player_card[PLAYER_1] = get_card_from_top(&decks[PLAYER_1]);
				curr_player_card[PLAYER_2] = get_card_from_top(&decks[PLAYER_2]);

				// Adding card to stake deck and deleting this same card from original deck
				transfer_from_deck_to_stake(decks, stake_decks, curr_player_card);
				data_for_exp->rounds_counter++;

				if (i == 0)
				{
					print_deck_size(my_file, decks[PLAYER_1]->initial_size, decks[PLAYER_2]->initial_size);
					print_upside_down(my_file);
					pause_clear_game(my_file);
				}
			}
		}
		if (curr_player_card[PLAYER_1] == NULL || curr_player_card[PLAYER_2] == NULL)
		{
			printf("\nERROR CURRENT CARDS\n");
			exit(-1);
		}
		print_deck_size(my_file, decks[PLAYER_1]->initial_size, decks[PLAYER_2]->initial_size);
		print_played_cards(my_file, curr_player_card[PLAYER_1]->text_color, curr_player_card[PLAYER_1]->text_value, curr_player_card[PLAYER_2]->text_color, curr_player_card[PLAYER_2]->text_value);


		wars_in_this_round++;
	} while (curr_player_card[PLAYER_1]->value == curr_player_card[PLAYER_2]->value);

	return STILL_PLAYING;
}
game_status_t handle_version_b_1_cards(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], int index_more_cards, int index_less_cards)
{
	// Player with less cards takes two cards from player who has more cards
	for (int i = 0; i < 2; i++)
	{
		// curr_player_card points at card not at some random spot in the memory
		free(curr_player_card[index_less_cards]);

		curr_player_card[index_less_cards] = get_card_from_top(&decks[index_more_cards]);
		if (curr_player_card[index_less_cards] == NULL)
		{
			presenting_information_with_three_arguments_int(my_file, "Player %d is using player's %d cards and player %d is out of cards\n\n", index_less_cards + 1, index_more_cards + 1, index_more_cards + 1);
			if (index_more_cards == 1)
				return PLAYER_2_WON_GAME;
			else
				return PLAYER_1_WON_GAME;
		}
		deck_add_card(&stake_decks[index_less_cards], curr_player_card[index_less_cards]);
		deck_remove_card(&decks[index_more_cards]);
		presenting_information_with_two_arguments_int(my_file, "Player %d takes one card from player's %d deck\n", index_less_cards + 1, index_more_cards + 1);
	}
	data_for_exp->rounds_counter++;
	presenting_information(my_file, "\n");
	pause_clear_game(my_file);

	// Now Player with more cards takes two cards from his own deck
	for (int i = 0; i < 2; i++)
	{
		// curr_player_card points at card not at some random spot in the memory
		free(curr_player_card[index_more_cards]);

		curr_player_card[index_more_cards] = get_card_from_top(&decks[index_more_cards]);
		if (curr_player_card[index_more_cards] == NULL)
		{
			presenting_information_with_three_arguments_int(my_file, "Player %d is using player's %d cards and player %d is out of cards\n\n", index_less_cards + 1, index_more_cards + 1, index_more_cards + 1);
			if (index_more_cards == 1)
				return PLAYER_2_WON_GAME;
			else
				return PLAYER_1_WON_GAME;
		}
		deck_add_card(&stake_decks[index_more_cards], curr_player_card[index_more_cards]);
		deck_remove_card(&decks[index_more_cards]);
		presenting_information_with_one_arguments_int(my_file, "Player %d takes one card from his own deck\n", index_more_cards + 1);
	}
	data_for_exp->rounds_counter++;
	presenting_information(my_file, "\n");
	pause_clear_game(my_file);

	return STILL_PLAYING;
}
game_status_t handle_version_b_2_cards(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[], int index_more_cards, int index_less_cards)
{
	// Each player takes one card from their own deck
	// At this point player[index_less_cards] has 2 cards so we don't have to check if someone is out of cards
	curr_player_card[index_less_cards] = get_card_from_top(&decks[index_less_cards]);
	deck_add_card(&stake_decks[index_less_cards], curr_player_card[index_less_cards]);
	deck_remove_card(&decks[index_less_cards]);

	curr_player_card[index_more_cards] = get_card_from_top(&decks[index_more_cards]);
	deck_add_card(&stake_decks[index_more_cards], curr_player_card[index_more_cards]);
	deck_remove_card(&decks[index_more_cards]);

	data_for_exp->rounds_counter++;
	print_upside_down(my_file);
	pause_clear_game(my_file);

	free(curr_player_card[index_less_cards]);
	free(curr_player_card[index_more_cards]);

	// Now player with less cards takes one card from player who has more cards
	// But here we have to check
	curr_player_card[index_less_cards] = get_card_from_top(&decks[index_more_cards]);
	if (curr_player_card[index_less_cards] == NULL)
	{
		presenting_information_with_three_arguments_int(my_file, "Player %d is using player's %d cards and Player %d is out of cards\n\n", index_less_cards + 1, index_more_cards + 1, index_more_cards + 1);
		if (index_more_cards == 1)
			return PLAYER_2_WON_GAME;
		else
			return PLAYER_1_WON_GAME;
	}
	deck_add_card(&stake_decks[index_less_cards], curr_player_card[index_less_cards]);
	deck_remove_card(&decks[index_more_cards]);

	// Player who has more cards takes one card from his own deck
	curr_player_card[index_more_cards] = get_card_from_top(&decks[index_more_cards]);
	if (curr_player_card[index_more_cards] == NULL)
	{
		presenting_information_with_three_arguments_int(my_file, "Player %d is using player's %d cards and player %d is out of cards\n\n", index_less_cards + 1, index_more_cards + 1, index_more_cards + 1);
		if (index_more_cards == 1)
			return PLAYER_2_WON_GAME;
		else
			return PLAYER_1_WON_GAME;
	}
	deck_add_card(&stake_decks[index_more_cards], curr_player_card[index_more_cards]);
	deck_remove_card(&decks[index_more_cards]);
	data_for_exp->rounds_counter++;

	presenting_information_with_two_arguments_int(my_file, "Player %d takes one card from player's %d deck\n", index_less_cards + 1, index_more_cards + 1);
	presenting_information_with_one_arguments_int(my_file, "Player %d takes one card from his own deck\n\n", index_more_cards + 1);
	pause_clear_game(my_file);

	return STILL_PLAYING;
}

void who_is_the_winner(strategy_t player_strategy[], game_status_t status, experiment_data_t* data_for_exp, file_t* my_file, game_deck_t* decks[])
{
	if (status == PLAYER_1_WON_GAME)
	{
		presenting_information(my_file, "Player 1 is the winner\n\n");
		fill_data_for_experiment(decks, data_for_exp, player_strategy, PLAYER_1, PLAYER_2);
	}
	else if (status == PLAYER_2_WON_GAME)
	{
		presenting_information(my_file, "Player 2 is the winner\n\n");
		fill_data_for_experiment(decks, data_for_exp, player_strategy, PLAYER_2, PLAYER_1);
	}
	else
	{
		presenting_information(my_file, "DRAW\n\n");
		fill_data_for_experiment(decks, data_for_exp, player_strategy, PLAYER_1, PLAYER_1); // Sending two times PLAYER_1 on purpose
	}
}
void fill_data_for_experiment(game_deck_t* decks[], experiment_data_t* data_for_exp, strategy_t player_strategy[], int winner_index, int loser_index)
{
	if (winner_index == loser_index)
	{
		data_for_exp->rank_player_1 = 0;
		data_for_exp->rank_player_2 = 0;
		data_for_exp->strategy_winner = no_strategy;
		data_for_exp->strategy_loser = no_strategy;
	}
	else
	{
		if (winner_index == PLAYER_1)
		{
			data_for_exp->rank_player_1 = decks[winner_index]->rank;
			data_for_exp->rank_player_2 = decks[loser_index]->rank;
		}
		else
		{
			data_for_exp->rank_player_1 = decks[loser_index]->rank;
			data_for_exp->rank_player_2 = decks[winner_index]->rank;
		}

		data_for_exp->strategy_winner = player_strategy[winner_index];
		data_for_exp->strategy_loser = player_strategy[loser_index];
		data_for_exp->winner_index = winner_index;
		data_for_exp->loser_index = loser_index;
	}

}
void swap_int(int* one, int* two)
{
	int buf;
	buf = *one;
	*one = *two;
	*two = buf;
}
void swap_char(char** one, char** two)
{
	char* buf;
	buf = *one;
	*one = *two;
	*two = buf;
}
void free_curr_cards(card_t* curr_player_card[])
{
	if (curr_player_card[PLAYER_1] != NULL)
		free(curr_player_card[PLAYER_1]);
	if (curr_player_card[PLAYER_2] != NULL)
		free(curr_player_card[PLAYER_2]);
	curr_player_card[PLAYER_1] = NULL;
	curr_player_card[PLAYER_2] = NULL;
}
void update_initial_size(game_deck_t* decks[])
{
	decks[PLAYER_1]->initial_size = decks[PLAYER_1]->size;
	decks[PLAYER_2]->initial_size = decks[PLAYER_2]->size;
}
void is_game_infinite(file_t* my_file, experiment_data_t* data)
{
	if (data->rounds_counter >= ENDLESS_GAME_MAX)
	{
		data->rank_player_1 = 0;
		data->rank_player_2 = 0;
		data->strategy_loser = no_strategy;
		data->strategy_winner = no_strategy;
		data->rounds_counter = INFINITE;
		presenting_information(my_file, "\n\nOH NO! It seems that this game will be played forever!\nExiting the game\n\n");
		pause_clear_game(my_file);
	}
}

void player_choose_card(strategy_t player_strategy[], file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{

	int choice;
	do
	{
		print_deck_size(my_file, decks[PLAYER_1]->initial_size, decks[PLAYER_2]->initial_size);
		wise_UI_their_turn_information(my_file, their_turn + 1, curr_player_card[their_turn]->text_value, curr_player_card[their_turn]->text_color);
		if (players_hand[CARD_1] != NULL)
			wise_UI_not_their_turn_card_1_information(my_file, not_their_turn + 1, players_hand[CARD_1]->text_value, players_hand[CARD_1]->text_color);
		if (players_hand[CARD_2] != NULL)
			wise_UI_not_their_turn_card_2_information(my_file, players_hand[CARD_2]->text_value, players_hand[CARD_2]->text_color);

		// Depending on the strategy cards is chosen by player or a bot
		choice = trigger_strategy(player_strategy, my_file, decks, players_hand, curr_player_card, stake_decks, not_their_turn, their_turn);

		switch (choice)
		{
		case 1:
			if (players_hand[CARD_1] == NULL)
			{
				wise_UI_error_input(my_file);
				pause_clear_game(my_file);
				choice = 0;
				break;
			}
			wise_UI_player_chosen_card(my_file, players_hand[CARD_1]->text_value, players_hand[CARD_1]->text_color);
			curr_player_card[not_their_turn] = players_hand[CARD_1];
			deck_add_card(&stake_decks[not_their_turn], curr_player_card[not_their_turn]);
			players_hand[CARD_1] = NULL;
			if (players_hand[CARD_2] != NULL)
			{
				thrust_card_to_deck(&decks[not_their_turn], players_hand[CARD_2]);
				free(players_hand[CARD_2]);
				players_hand[CARD_2] = NULL;
			}
			break;
		case 2:
			if (players_hand[CARD_2] == NULL)
			{
				wise_UI_error_input(my_file);
				pause_clear_game(my_file);
				choice = 0;
				break;
			}
			wise_UI_player_chosen_card(my_file, players_hand[CARD_2]->text_value, players_hand[CARD_2]->text_color);
			curr_player_card[not_their_turn] = players_hand[CARD_2];
			deck_add_card(&stake_decks[not_their_turn], curr_player_card[not_their_turn]);
			players_hand[CARD_2] = NULL;
			if (players_hand[CARD_1] != NULL)
			{
				thrust_card_to_deck(&decks[not_their_turn], players_hand[CARD_1]);
				free(players_hand[CARD_1]);
				players_hand[CARD_1] = NULL;
			}
			break;
		default:
			wise_UI_error_input(my_file);
			pause_clear_game(my_file);
			break;
		}

	} while (choice != 1 && choice != 2);


}
int trigger_strategy(strategy_t player_strategy[], file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{
	if (player_strategy[not_their_turn] == no_strategy)
		return no_strategy_strategy(my_file, decks, players_hand, curr_player_card, stake_decks, not_their_turn, their_turn);
	else if (player_strategy[not_their_turn] == random)
		return  random_strategy(my_file, decks, players_hand, curr_player_card, stake_decks, not_their_turn, their_turn);
	else if (player_strategy[not_their_turn] == furious)
		return  furious_strategy(my_file, decks, players_hand, curr_player_card, stake_decks, not_their_turn, their_turn);
	else if (player_strategy[not_their_turn] == peaceful)
		return  peaceful_strategy(my_file, decks, players_hand, curr_player_card, stake_decks, not_their_turn, their_turn);
	else // MY STRATEGY
		return  my_strategy_strategy(my_file, decks, players_hand, curr_player_card, stake_decks, not_their_turn, their_turn);
}
int no_strategy_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{
	int choice;
	choice = getch() - '0';
	return choice;
}
int random_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{
	return  rand() % 2 + 1;;
}
int furious_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{
	if (players_hand[CARD_1] == NULL)
		return CARD_2 + 1;
	else if (players_hand[CARD_2] == NULL)
		return CARD_1 + 1;
	else if (curr_player_card[their_turn]->value == players_hand[CARD_1]->value)
		return CARD_1 + 1;
	else if (curr_player_card[their_turn]->value == players_hand[CARD_2]->value)
		return CARD_2 + 1;
	else
	{
		if (players_hand[CARD_2]->value > players_hand[CARD_1]->value)
			return CARD_1 + 1;
		else
			return CARD_2 + 1;
	}
}
int peaceful_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{
	if (players_hand[CARD_1] == NULL)
		return CARD_2 + 1;
	else if (players_hand[CARD_2] == NULL)
		return CARD_1 + 1;
	else if (curr_player_card[their_turn]->value == players_hand[CARD_1]->value)
		return CARD_2 + 1;
	else if (curr_player_card[their_turn]->value == players_hand[CARD_2]->value)
		return CARD_1 + 1;
	else
	{
		if (players_hand[CARD_2]->value > players_hand[CARD_1]->value)
			return CARD_1 + 1;
		else
			return CARD_2 + 1;
	}
}
int my_strategy_strategy(file_t* my_file, game_deck_t* decks[], card_t* curr_player_card[], card_t* players_hand[], game_deck_t* stake_decks[], int not_their_turn, int their_turn)
{
	int older_index;
	int younger_index;
	if (players_hand[CARD_1] == NULL)
		return CARD_2 + 1;
	else if (players_hand[CARD_2] == NULL)
		return CARD_1 + 1;
	else
	{
		if (players_hand[CARD_1]->value > players_hand[CARD_2]->value)
		{
			older_index = CARD_1;
			younger_index = CARD_2;
		}
		else
		{
			older_index = CARD_2;
			younger_index = CARD_1;
		}

		if (players_hand[older_index]->value < curr_player_card[their_turn]->value)
			return younger_index + 1;

		if (players_hand[older_index]->value - curr_player_card[their_turn]->value > 10)
			return younger_index + 1;
		else
			return older_index + 1;
	}
}