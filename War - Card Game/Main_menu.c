#include <stdio.h>
#include <stdlib.h>
#include "Main_menu.h"
#include "Constants.h"
#include "Structures.h"
#include "Experiments.h"
#include "War.h"
#include "Game_interface.h"
#include "Deck_operations.h"


game_status_t(*choose_game_mode())(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[])
{
	game_status_t(*pointer)(file_t * my_file, experiment_data_t * data_for_exp, game_deck_t * decks[], card_t * curr_player_card[], game_deck_t * stake_decks[]);
	int choice;
	pointer = NULL;
	do
	{
		system("cls");
		printf("Choose mode of the game: \n");
		printf("1. mode: A\n");
		printf("2. mode: B\n");
		printf("3. Go back B\n");
		choice = getch() - '0';

		switch (choice)
		{
		case 1:
			pointer = &war_version_a;
			break;
		case 2:
			pointer = &war_version_b;
			break;
		case 3:
			pointer = NULL;
			break;
		default:
			printf("There is no such option! \n\n");
			system("pause");
		}
	} while (choice != 1 && choice != 2 && choice != 3);

	system("cls");
	return *pointer;
}

void choose_strategy(strategy_t player_strategy[])
{
	int choice;
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		if (i == 1 && player_strategy[PLAYER_1] == go_back)
		{
			player_strategy[PLAYER_2] = go_back;
			break;
		}
		system("cls");
		printf("Choose strategy for Player %d: \n", i + 1);
		do
		{
			system("cls");
			printf("1. Random\n");
			printf("2. Furious\n");
			printf("3. Peaceful\n");
			printf("4. My strategy\n");
			printf("5. Without strategy\n");
			printf("6. Go back\n");
			choice = getch() - '0';

			switch (choice)
			{
			case 1:
				system("cls");
				player_strategy[i] = random;
				break;
			case 2:
				system("cls");
				player_strategy[i] = furious;
				break;
			case 3:
				system("cls");
				player_strategy[i] = peaceful;
				break;
			case 4:
				system("cls");
				player_strategy[i] = my_strategy;
				break;
			case 5:
				system("cls");
				player_strategy[i] = no_strategy;
				break;
			case 6:
				system("cls");
				player_strategy[i] = go_back;
				break;
			default:
				printf("There is no such option! \n\n");
				system("pause");
			}
		} while (choice < 1 || choice > 6);
	}
}

int choose_rank_method()
{
	int choice;
	system("cls");
	printf("Choose the way rank of the deck will be counted: \n");
	do
	{
		printf("1. 1st method\n");
		printf("2. 2nd method\n");
		printf("3. 3rd method\n");
		printf("4. Go back\n");
		choice = getch() - '0';

		switch (choice)
		{
		case 1:
			system("cls");
			return 1;
			break;
		case 2:
			system("cls");
			return 2;
			break;
		case 3:
			system("cls");
			return 3;
			break;
		case 4:
			system("cls");
			return 0;
			break;
		default:
			printf("There is no such option! \n\n");
			system("pause");
		}
	} while (choice < 1 || choice > 4);

	return 0;
}

// Allows to choose deck size for experiment
// Returns size of the deck 
int choose_experiment_deck_size()
{
	int choice;
	int deck_size = 0;
	do
	{
		system("cls");
		printf("Choose size of the deck: \n");
		printf("1. From tens to aces\n");
		printf("2. From nines to aces\n");
		printf("3. From eights to aces\n");
		printf("4. From sevens to aces\n");
		printf("5. From sixs to aces\n");
		printf("6. From fives to aces\n");
		printf("7. From fours to aces\n");
		printf("8. From threes to aces\n");
		printf("9. From twos to aces\n");
		printf("0. Go back\n");

		choice = getch() - '0';

		switch (choice)
		{
		case 1:
			deck_size = 20;
			break;
		case 2:
			deck_size = 24;
			break;
		case 3:
			deck_size = 28;
			break;
		case 4:
			deck_size = 32;
			break;
		case 5:
			deck_size = 36;
			break;
		case 6:
			deck_size = 40;
			break;
		case 7:
			deck_size = 44;
			break;
		case 8:
			deck_size = 48;
			break;
		case 9:
			deck_size = 52;
			break;
		case 0:
			deck_size = 0;
			break;
		default:
			printf("There is no such option! \n\n");
			system("pause");
		}
	} while (choice < 0 || choice > 9);

	system("cls");
	return deck_size;
}

// Allows player to choose type of experiment
void experiment_menu(experiment_number_t exp_number, card_t** starting_deck, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]))
{
	games_number_t number_of_games;
	int choice;
	do
	{
		system("cls");
		printf("Chose experiment details: \n");
		printf("1. Test one deck (1000 games) \n");
		printf("2. Test one deck (1 game) \n");
		printf("3. Choose custom size (Only for second experiment)\n");
		printf("4. Back to main menu \n");
		choice = getch() - '0';

		switch (choice)
		{
		case 1:
			number_of_games = ONE_THOUSAND;
			if (exp_number == FIRST_EXPERIMENT || exp_number == THIRD_EXPERIMENT)
				choice = carry_out_satisfaction_experiment(exp_number, number_of_games, starting_deck, decks, game_mode);
			else if (exp_number == SECOND_EXPERIMENT)
				choice = carry_out_second_experiment(starting_deck, number_of_games, decks, game_mode);
			else
				choice = carry_out_fourth_experiment(starting_deck, number_of_games, decks);

			break;
		case 2:
			number_of_games = ONE;
			if (exp_number == FIRST_EXPERIMENT || exp_number == THIRD_EXPERIMENT)
				choice = carry_out_satisfaction_experiment(exp_number, number_of_games, starting_deck, decks, game_mode);
			else if (exp_number == SECOND_EXPERIMENT)
				choice = carry_out_second_experiment(starting_deck, number_of_games, decks, game_mode);
			else
				choice = carry_out_fourth_experiment(starting_deck, number_of_games, decks);
			break;
		case 3:
			if (exp_number != SECOND_EXPERIMENT)
			{
				printf("You cannot do that! \n\n");
				pause_clear_UI();
				choice = 0;
				break;
			}
			printf("How many games do you want to be played: ");
			scanf_s("%d", &number_of_games);
			if (number_of_games <= 0)
			{
				printf("Incorret input\n\n");
				pause_clear_UI();
				choice = 0;
				break;
			}
			choice = carry_out_second_experiment(starting_deck, number_of_games, decks, game_mode);
			break;
		case 4:
			break;
		default:
			printf("There is no such option! \n\n");
			pause_clear_UI();
			break;
		}

	} while (choice < 1 || choice > 4);
}

// Allows player to choose what he wants to do in this program
void start_main_menu(card_t** starting_deck, game_deck_t* decks[], game_status_t(*game_mode)(file_t* my_file, experiment_data_t* data_for_exp, game_deck_t* decks[], card_t* curr_player_card[], game_deck_t* stake_decks[]))
{
	file_t no_file;
	experiment_number_t exp_number;
	strategy_t player_strategy[NUMBER_OF_PLAYERS];
	int choice;
	do
	{
		system("cls");
		printf("What do you want to do: \n");
		printf("--------- GAME ---------\n");
		printf("1. Standard war \n");
		printf("2. Wise war \n");
		printf("----- EXPERMINENTS -----\n");
		printf("3. First experiment (standard war)\n");
		printf("4. Second experiment (standard war)\n");
		printf("5. Third experiment (wise war)\n");
		printf("6. Fourth experiment (wise war)\n");
		printf("------------------------\n");
		printf("7. End program \n");
		choice = getch() - '0';

		switch (choice)
		{
		case 1:
			game_mode = choose_game_mode();
			if (game_mode == NULL)
				break;

			no_file.save_file = NULL; // Pointer is pointing at NULL because this is the condition to print output to the console not to the file
			no_file.path = STANDARD_WAR_PATH;
			random_decks_preparations(starting_deck, STANDARD_DECK_SIZE, decks);
			start_standard_game(&no_file, starting_deck, STANDARD_DECK_SIZE, decks, game_mode);

			clear_memory(decks, NUMBER_OF_PLAYERS, starting_deck); // free memory after game
			pause_clear_UI();
			break;
		case 2:
			choose_strategy(player_strategy);
			if (player_strategy[PLAYER_1] == go_back || player_strategy[PLAYER_2] == go_back)
				break;
			no_file.save_file = NULL; // Pointer is pointing at NULL because this is the condition to print output to the console not to the file
			no_file.path = WISE_WAR_PATH;
			random_decks_preparations(starting_deck, STANDARD_DECK_SIZE, decks);
			system("cls");
			start_wise_game(player_strategy, &no_file, starting_deck, STANDARD_DECK_SIZE, decks);

			clear_memory(decks, NUMBER_OF_PLAYERS, starting_deck); // free memory after game
			pause_clear_UI();
			break;
		case 3:
			exp_number = FIRST_EXPERIMENT;
			experiment_menu(exp_number, starting_deck, decks, game_mode);
			break;
		case 4:
			exp_number = SECOND_EXPERIMENT;
			experiment_menu(exp_number, starting_deck, decks, game_mode);
			break;
		case 5:
			exp_number = THIRD_EXPERIMENT;
			experiment_menu(exp_number, starting_deck, decks, game_mode);
			break;
		case 6:
			exp_number = FOURTH_EXPERIMENT;
			experiment_menu(exp_number, starting_deck, decks, game_mode);
			break;
		case 7:
			printf("Closing program! \n\n");
			break;
		default:
			printf("There is no such option! \n\n");
			pause_clear_UI();
			break;
		}
	} while (choice != 7);
}
