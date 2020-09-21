#ifndef constants_h
#define constants_h

//VisualStudio compatibility 
#ifdef _MSC_VER 
#define _CRT_SECURE_NO_DEPRECATE 
#pragma warning (disable : 4996)
#endif
//

#define NUMBER_OF_PLAYERS 2
#define	STANDARD_DECK_SIZE 52
#define SHUFFLE_POWER 200 // Defines how many iterations there will be in the loop during shuffling cards
#define MAX_REDABLE 20 // Description for cards
#define PLAYER_1 0
#define PLAYER_2 1
#define PLAYER_1_STR "1"
#define PLAYER_2_STR "2"
#define ENDLESS_GAME_MAX 500000 // If number of rounds reach this limit we assume that the game will never end so we stop it

#define CARD_POSSIBILITY 2 // In wise war player choose between two cards
#define CARD_1 0
#define CARD_2 1 

// Paths to the files where results of the experiments will be saved
#define FIRST_EXPERIMENT_1_GAME_PATH "exp_1_game_logs.txt"
#define FIRST_EXPERIMENT_1000_GAMES_PATH "exp_1_games_result.txt"
#define SECOND_EXPERIMENT_PATH "exp_2_games_result.txt"
#define THIRD_EXPERIMENT_1_GAME_PATH "exp_3_game_logs.txt"
#define THIRD_EXPERIMENT_1000_GAMES_PATH "exp_3_games_result.txt"
#define FOURTH_EXPERIMENT_PATH "exp_4_games_result.txt"

// We need this two consts two determine if we should print GUI during game (ONLY WISE WAR)
#define STANDARD_WAR_PATH "standard_war"
#define WISE_WAR_PATH "wise_war"

// Navigating in the menu
#define GO_BACK 0
#define CONTINUE 1

#define INFINITE 0 // it will set number of rounds to 0 if the game was infinite

// What experiment did player choose
typedef enum
{
	FIRST_EXPERIMENT = 1,
	SECOND_EXPERIMENT,
	THIRD_EXPERIMENT,
	FOURTH_EXPERIMENT
}experiment_number_t;

// What strategy did player choose
typedef enum
{
	go_back = -1,
	no_strategy,
	random,
	furious,
	peaceful,
	my_strategy
}strategy_t;


// During standard war in mode B if one player is out of cards during war he can borrow cards from the other player only one time during one round (They cannot do it two times in the row)
typedef enum
{
	NO,
	YES
}already_helped_t;

// Number of games that one experiment will carry out
typedef enum
{
	ONE = 1,
	ONE_THOUSAND = 1000
}games_number_t;

// Describes if we should end game or still play it
typedef enum
{
	STILL_PLAYING = -1,
	PLAYER_1_WON_GAME,
	PLAYER_2_WON_GAME,
	DRAW
}game_status_t;

// Colors of cards
typedef enum
{
	HEARTS,
	DIAMONDS,
	CLUBS,
	SPADES
}color_t;

// values of cards
typedef enum
{
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
}value_t;

#endif // !constants_h

