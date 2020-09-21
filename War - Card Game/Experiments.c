#include <stdio.h>
#include "Experiments.h"
#include "Structures.h"
#include "Constants.h"
#include "War.h"

int carry_out_satisfaction_experiment(experiment_number_t exp_number, int number_of_games, card_t** starting_deck, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]))
{
	char* save_path;
	int rounds_counter = 0;
	int deck_size;
	experiment_data_t game_info;
	strategy_t player_strategy[NUMBER_OF_PLAYERS];
	file_t my_file;

	if (exp_number == FIRST_EXPERIMENT)
	{
		game_mode = choose_game_mode();
		if (game_mode == NULL)
			return GO_BACK;
	}
	else if (exp_number == THIRD_EXPERIMENT)
	{
		game_mode = &war_version_a; // Only A mode in wise war
		choose_strategy(player_strategy);
		if (player_strategy[PLAYER_1] == go_back || player_strategy[PLAYER_2] == go_back) // When player chose strategy and he chose to go back to menu then we set my_stratrgy to no_strategy
			return GO_BACK;

		if (player_strategy[PLAYER_1] == no_strategy || player_strategy[PLAYER_2] == no_strategy)
		{
			printf("You cannot do that!\n");
			pause_clear_UI();
			return GO_BACK;
		}
	}

	deck_size = choose_experiment_deck_size();
	if (deck_size == 0)
		return GO_BACK;

	set_file_path(exp_number, number_of_games, &save_path);
	my_file.save_file = fopen(save_path, "w");
	if (my_file.save_file == NULL)
		return GO_BACK;

	my_file.path = save_path;

	for (int i = 0; i < number_of_games; i++)
	{
		printf("Experiment progress:%4d%%\r", i / 10);
		const_decks_preparations(starting_deck, deck_size, decks);
		if (exp_number == FIRST_EXPERIMENT)
			game_info = start_standard_game(&my_file, starting_deck, deck_size, decks, game_mode);
		else // THIRD_EXPERIMENT
			game_info = start_wise_game(player_strategy, &my_file, starting_deck, deck_size, decks);
		clear_memory(decks, NUMBER_OF_PLAYERS, starting_deck);

		// if game was infinite
		if (game_info.rounds_counter == INFINITE)
			number_of_games--;

		if ((my_file.path == FIRST_EXPERIMENT_1_GAME_PATH || my_file.path == THIRD_EXPERIMENT_1_GAME_PATH) && game_info.rounds_counter == INFINITE)
		{
			printf("OH NO! It seems that this game will be played forever!\nExiting the game\n\n");
			break;
		}
		rounds_counter += game_info.rounds_counter;
		// Minus one because there could have been an infinite game during the last iteration of the loop
		if (i >= number_of_games - 1)
		{
			printf("Experiment progress:%4d%%", 100);
			printf("\nExperiment completed successfully!\n");
		}

	}

	if (my_file.path == FIRST_EXPERIMENT_1000_GAMES_PATH || my_file.path == THIRD_EXPERIMENT_1000_GAMES_PATH)
		fprintf(my_file.save_file, "Number of rounds: %d", rounds_counter / number_of_games);
	fclose(my_file.save_file);
	pause_clear_UI();

	return CONTINUE;
}
int carry_out_second_experiment(card_t** starting_deck, int number_of_games, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]))
{
	file_t my_file;
	experiment_data_t game_info;
	int deck_size;
	int rank_method;

	my_file.save_file = fopen(SECOND_EXPERIMENT_PATH, "w");
	my_file.path = SECOND_EXPERIMENT_PATH;

	if (my_file.save_file == NULL)
		return GO_BACK;

	game_mode = choose_game_mode();
	if (game_mode == NULL)
		return GO_BACK;
	deck_size = choose_experiment_deck_size();
	if (deck_size == 0)
		return GO_BACK;

	rank_method = choose_rank_method();
	if (rank_method == 0)
		return GO_BACK;

	for (int i = 0; i < number_of_games; i++)
	{
		printf("Experiment progress:%4d%%\r", (int)((i / (float)number_of_games) * 100));
		random_decks_preparations(starting_deck, deck_size, decks);
		count_deck_rank(rank_method, decks);
		game_info = start_standard_game(&my_file, starting_deck, deck_size, decks, game_mode);
		clear_memory(decks, NUMBER_OF_PLAYERS, starting_deck);
		if (game_info.rank_player_1 != 0 && game_info.rank_player_2 != 0)
		{
			if (game_info.winner_index == PLAYER_1)
			{
				fprintf(my_file.save_file, "%d 1 ", game_info.rank_player_1);
				fprintf(my_file.save_file, "%d 0\n", game_info.rank_player_2);
			}
			else
			{
				fprintf(my_file.save_file, "%d 0 ", game_info.rank_player_1);
				fprintf(my_file.save_file, "%d 1\n", game_info.rank_player_2);
			}
		}
	}
	printf("Experiment progress:%4d%%", 100);
	printf("\nExperiment completed successfully!\n");

	fclose(my_file.save_file);
	pause_clear_UI();
	return CONTINUE;
}
int carry_out_fourth_experiment(card_t** starting_deck, int number_of_games, game_deck_t* decks[])
{
	int wins[NUMBER_OF_PLAYERS] = { 0,0 };
	int draws = 0;
	game_status_t(*game_mode)(file_t * my_file, experiment_data_t * data_for_exp, game_deck_t * decks[], card_t * curr_player_card[], game_deck_t * stake_decks[]);
	file_t my_file;
	experiment_data_t game_info;
	strategy_t player_strategy[NUMBER_OF_PLAYERS];
	int deck_size = STANDARD_DECK_SIZE;

	my_file.save_file = fopen(FOURTH_EXPERIMENT_PATH, "w");
	my_file.path = FOURTH_EXPERIMENT_PATH;

	if (my_file.save_file == NULL)
		return GO_BACK;

	game_mode = &war_version_a;
	choose_strategy(player_strategy);
	if (player_strategy[PLAYER_1] == go_back || player_strategy[PLAYER_2] == go_back)
		return GO_BACK;
	if (player_strategy[PLAYER_1] == no_strategy || player_strategy[PLAYER_2] == no_strategy)
	{
		printf("You cannot do that!\n");
		pause_clear_UI();
		return GO_BACK;
	}

	for (int i = 0; i < number_of_games; i++)
	{
		printf("Experiment progress:%4d%%\r", (int)((i / (float)number_of_games) * 100));
		random_decks_preparations(starting_deck, deck_size, decks);
		game_info = start_wise_game(player_strategy, &my_file, starting_deck, deck_size, decks);
		clear_memory(decks, NUMBER_OF_PLAYERS, starting_deck);

		if (game_info.strategy_winner != no_strategy && game_info.strategy_loser != no_strategy)
			wins[game_info.winner_index]++;
		else
			draws++;
	}


	printf("Experiment progress:%4d%%", 100);
	printf("\nExperiment completed successfully!\n");

	save_fourth_experiment_results(&my_file, wins, player_strategy, draws);

	fclose(my_file.save_file);
	pause_clear_UI();
	return CONTINUE;
}

void save_fourth_experiment_results(file_t* my_file, int wins[], strategy_t player_strategy[], int draws)
{
	if (player_strategy[PLAYER_1] == random)
		fprintf(my_file->save_file, "Player 1 (random) has won: ");
	else if (player_strategy[PLAYER_1] == furious)
		fprintf(my_file->save_file, "Player 1 (furious) has won: ");
	else if (player_strategy[PLAYER_1] == peaceful)
		fprintf(my_file->save_file, "Player 1 (peaceful) has won: ");
	else if (player_strategy[PLAYER_1] == my_strategy)
		fprintf(my_file->save_file, "Player 1 (my_strategy) has won: ");

	fprintf(my_file->save_file, "%d games\n", wins[PLAYER_1]);

	if (player_strategy[PLAYER_2] == random)
		fprintf(my_file->save_file, "Player 2 (random) has won: ");
	else if (player_strategy[PLAYER_2] == furious)
		fprintf(my_file->save_file, "Player 2 (furious) has won: ");
	else if (player_strategy[PLAYER_2] == peaceful)
		fprintf(my_file->save_file, "Player 2 (peaceful) has won: ");
	else if (player_strategy[PLAYER_2] == my_strategy)
		fprintf(my_file->save_file, "Player 2 (my_strategy) has won: ");

	fprintf(my_file->save_file, "%d games\n", wins[PLAYER_2]);
	fprintf(my_file->save_file, "There has been %d draws", draws);

}
// Before the experiment we choose a name of the file where results will be saved
void set_file_path(experiment_number_t exp_number, int number_of_games, char** save_path)
{
	if (exp_number == FIRST_EXPERIMENT)
	{
		if (number_of_games == ONE)
			*save_path = FIRST_EXPERIMENT_1_GAME_PATH;
		else if (number_of_games == ONE_THOUSAND)
			*save_path = FIRST_EXPERIMENT_1000_GAMES_PATH;;
	}
	else if (exp_number == THIRD_EXPERIMENT)
	{
		if (number_of_games == ONE)
			*save_path = THIRD_EXPERIMENT_1_GAME_PATH;
		else if (number_of_games == ONE_THOUSAND)
			*save_path = THIRD_EXPERIMENT_1000_GAMES_PATH;;
	}
}
