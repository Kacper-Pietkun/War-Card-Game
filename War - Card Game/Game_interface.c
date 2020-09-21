#include <stdio.h>
#include "Game_interface.h"
#include "Structures.h"
#include "Constants.h"
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void draw_template()
{
	printf("|-------------------------------|     |----------------------------------|  |----------------------------------|\n");
	printf("|          DECK SIZES:          |     |   This Player puts only 1 card:  |  |     This Player puts 2 cards:    |\n");
	printf("|-------------------------------|     |----------------------------------|  |----------------------------------|\n");
	printf("|                               |     |                                  |  |                                  |\n");
	printf("|-------------------------------|     |----------------------------------|  |----------------------------------|\n");
	printf("|                               |     | Played card:                     |  |         Cards to choose:         |\n");
	printf("|-------------------------------|     |----------------------------------|  |----------------------------------|\n");
	printf("                                                                            |                                  |\n");
	printf("                                                                            |----------------------------------|\n");
	printf("                                                                            |                                  |\n");
	printf("                                                                            |----------------------------------|\n");
	printf("                                                                               (Type 1 or 2 to choose a card)   \n");
	printf("                                                                                                                \n");
	printf("                               |------------------------------------------------|                               \n");
	printf("                               |                       VS                       |                               \n");
	printf("                               |------------------------------------------------|                               \n");
	printf("                               |                                                |                               \n");
	printf("                               |------------------------------------------------|                               \n");
}

void pause_clear_UI()
{
	system("pause");
	system("cls");
}
void pause_clear_game(file_t* my_file)
{
	if (my_file->save_file == NULL)
	{
		system("pause");
		system("cls");
		if (my_file->path == WISE_WAR_PATH)
			draw_template();
	}
}

void wise_UI_their_turn_information(file_t* my_file, int index, char* value, char* color)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(52, 3);
		printf("Player %d", index);
		gotoxy(53, 5);
		printf("%s of %s", value, color);
		gotoxy(37, 14);
		printf("%s of %s", value, color);
	}
}
void wise_UI_not_their_turn_card_1_information(file_t* my_file, int index, char* value, char* color)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(90, 3);
		printf("Player %d", index);
		gotoxy(78, 7);
		printf("1. %s of %s", value, color);
		gotoxy(42, 19);
	}
}
void wise_UI_not_their_turn_card_2_information(file_t* my_file, char* value, char* color)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(78, 9);
		printf("2. %s of %s", value, color);
		gotoxy(42, 19);
	}
}
void wise_UI_player_chosen_card(file_t* my_file, char* value, char* color)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(60, 14);
		printf("%s of %s", value, color);
	}
}
void wise_UI_round_winner(file_t* my_file, int index)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(45, 16);
		printf("Player %d wins this time", index);
		gotoxy(42, 19);
	}
}
void wise_UI_error_input(file_t* my_file)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(42, 19);
		printf("There is no such option!");
		gotoxy(42, 20);
	}
}
void wise_UI_upside_down(file_t* my_file)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(37, 14);
		printf("card upside down");
		gotoxy(60, 14);
		printf("card upside down");
		gotoxy(42, 19);
	}
}
void wise_UI_draw_info(file_t* my_file)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(45, 16);
		printf("DRAW! It means war!");
		gotoxy(42, 19);
	}
}
void wise_UI_cards_played_during_war(file_t* my_file, char* value_1, char* color_1, char* value_2, char* color_2)
{
	if (my_file->save_file == NULL)
	{
		gotoxy(37, 14);
		printf("%s of %s", value_1, color_1);
		gotoxy(60, 14);
		printf("%s of %s", value_2, color_2);
	}
}


void print_deck_size(file_t* my_file, int size_1, int size_2)
{
	if (my_file->save_file == NULL)
	{
		if (my_file->path == WISE_WAR_PATH)
		{
			gotoxy(3, 3);
			printf("Player 1 has got: %d cards\n", size_1);
			gotoxy(3, 5);
			printf("Player 2 has got: %d cards\n\n", size_2);
		}
		else
		{
			printf("Player 1 has got: %d cards\n", size_1);
			printf("Player 2 has got: %d cards\n\n", size_2);
		}

	}
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
	{
		fprintf(my_file->save_file, "Player 1 has got: %d cards\n", size_1);
		fprintf(my_file->save_file, "Player 2 has got: %d cards\n\n", size_2);
	}
}
// Prints card and color of the played card
void print_played_cards(file_t* my_file, char* text_1_color, char* text_1_value, char* text_2_color, char* text_2_value)
{
	if (my_file->save_file == NULL)
	{
		printf("Player 1 plays: %s of %s\n", text_1_value, text_1_color);
		printf("Player 2 plays: %s of %s\n\n", text_2_value, text_2_color);
	}
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
	{
		fprintf(my_file->save_file, "Player 1 plays: %s of %s\n", text_1_value, text_1_color);
		fprintf(my_file->save_file, "Player 2 plays: %s of %s\n\n", text_2_value, text_2_color);
	}

}
void print_upside_down(file_t* my_file)
{
	if (my_file->save_file == NULL)
	{
		printf("Player 1 plays: card upside down\n");
		printf("Player 2 plays: card upside down\n\n");
	}
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
	{
		fprintf(my_file->save_file, "Player 1 plays: card upside down\n");
		fprintf(my_file->save_file, "Player 2 plays: card upside down\n\n");
	}

}
void presenting_information(file_t* my_file, char* text)
{
	if (my_file->save_file == NULL)
		printf(text);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text);
}

void presenting_information_with_one_arguments_int(file_t* my_file, char* text, int arg_1)
{
	if (my_file->save_file == NULL)
		printf(text, arg_1);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text, arg_1);
}
void presenting_information_with_two_arguments_int(file_t* my_file, char* text, int arg_1, int arg_2)
{
	if (my_file->save_file == NULL)
		printf(text, arg_1, arg_2);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text, arg_1, arg_2);
}
void presenting_information_with_three_arguments_int(file_t* my_file, char* text, int arg_1, int arg_2, int arg_3)
{
	if (my_file->save_file == NULL)
		printf(text, arg_1, arg_2, arg_3);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text, arg_1, arg_2, arg_3);
}

void presenting_information_with_one_arguments_char(file_t* my_file, char* text, char* arg_1)
{
	if (my_file->save_file == NULL)
		printf(text, arg_1);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text, arg_1);
}
void presenting_information_with_two_arguments_char(file_t* my_file, char* text, char* arg_1, char* arg_2)
{
	if (my_file->save_file == NULL)
		printf(text, arg_1, arg_2);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text, arg_1, arg_2);
}
void presenting_information_with_three_arguments_char(file_t* my_file, char* text, char* arg_1, char* arg_2, char* arg_3)
{
	if (my_file->save_file == NULL)
		printf(text, arg_1, arg_2, arg_3);
	else if (my_file->path == FIRST_EXPERIMENT_1_GAME_PATH || my_file->path == THIRD_EXPERIMENT_1_GAME_PATH)
		fprintf(my_file->save_file, text, arg_1, arg_2, arg_3);
}
