#ifndef game_interface_h
#define game_interface_h
#include "Constants.h"
#include "Structures.h"

// INTERFACE DURING GAME | FUNCTIONS
// Prints ifromation either to file or to the console
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y);
void draw_template(); // Draws board for wise war

// CLEANER
void pause_clear_UI();
void pause_clear_game(file_t* my_file);

// WISE UI
void wise_UI_their_turn_information(file_t* my_file, int index, char* value, char* color);
void wise_UI_not_their_turn_card_1_information(file_t* my_file, int index, char* value, char* color);
void wise_UI_not_their_turn_card_2_information(file_t* my_file, char* value, char* color);
void wise_UI_player_chosen_card(file_t* my_file, char* value, char* color);
void wise_UI_round_winner(file_t* my_file, int index);
void wise_UI_error_input(file_t* my_file);
void wise_UI_upside_down(file_t* my_file);
void wise_UI_draw_info(file_t* my_file);
void wise_UI_cards_played_during_war(file_t* my_file, char* value_1, char* color_1, char* value_2, char* color_2);

void print_deck_size(file_t* my_file, int size_1, int size_2); // Prints card and color of the played card
void print_played_cards(file_t* my_file, char* text_1_color, char* text_1_value, char* text_2_color, char* text_2_value);
void print_upside_down(file_t* my_file);
void presenting_information(file_t* my_file, char* text);
void presenting_information_with_one_arguments_int(file_t* my_file, char* text, int arg_1);
void presenting_information_with_two_arguments_int(file_t* my_file, char* text, int arg_1, int arg_2);
void presenting_information_with_three_arguments_int(file_t* my_file, char* text, int arg_1, int arg_2, int arg_3);
void presenting_information_with_one_arguments_char(file_t* my_file, char* text, char* arg_1);
void presenting_information_with_two_arguments_char(file_t* my_file, char* text, char* arg_1, char* arg_2);
void presenting_information_with_three_arguments_char(file_t* my_file, char* text, char* arg_1, char* arg_2, char* arg_3);
// ------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // !game_interface_h
