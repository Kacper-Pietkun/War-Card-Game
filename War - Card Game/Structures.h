#ifndef structures_h
#define structures_h
#include "Constants.h"
#include "Structures.h"

typedef struct card
{
	value_t value;
	color_t color;
	struct card* next;
	struct card* previous;
	char text_value[MAX_REDABLE];
	char text_color[MAX_REDABLE];
}card_t;

typedef struct
{
	card_t* top;
	card_t* bottom;
	int rank;
	int size;
	int initial_size; // During the round size will change and initial_size will be updated once per round
}game_deck_t;

typedef struct
{
	FILE* save_file;
	char* path;
}file_t;

typedef struct
{
	int winner_index;
	int loser_index;
	int rank_player_1;
	int rank_player_2;
	int rounds_counter;
	strategy_t strategy_winner;
	strategy_t strategy_loser;
}experiment_data_t;

#endif // !structures_h
