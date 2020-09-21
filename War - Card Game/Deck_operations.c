#include <stdio.h>
#include "Deck_operations.h"
#include "Constants.h"
#include "Structures.h"


card_t* allocate_mem_for_cards(int amount)
{
	card_t* pointer = (card_t*)malloc(sizeof(card_t) * amount);
	if (pointer == NULL)
	{
		printf("Lack of memory!");
		return NULL;
	}

	return pointer;
}
game_deck_t* allocate_mem_for_deck()
{
	game_deck_t* pointer = (game_deck_t*)malloc(sizeof(game_deck_t));
	if (pointer == NULL)
	{
		printf("Lack of memory!");
		return NULL;
	}

	return pointer;
}

// get card 1st in the queue
card_t* get_card_from_top(game_deck_t** deck)
{
	// Alocating memory for new card, then copying information from card which is on the top of the deck to this new card
	// So we can return pointer to copy of (*deck)->top
	card_t* wanted_card = allocate_mem_for_cards(1);

	if ((*deck)->top == NULL)
	{
		free(wanted_card);
		return NULL;
	}

	wanted_card->color = ((*deck)->top)->color;
	wanted_card->value = ((*deck)->top)->value;
	translate_card(wanted_card);
	wanted_card->next = NULL;
	wanted_card->previous = NULL;

	// This function is not returning object but pointer to an object because if there is no more cards in the deck it will return NULL and it will be helpful information for us
	return wanted_card;
}

// Adding card to the end of the queue
void deck_add_card(game_deck_t** deck, card_t* source)
{
	card_t* temp = allocate_mem_for_cards(1);

	// Copying information from the source
	temp->value = source->value;
	temp->color = source->color;
	translate_card(temp);

	// Adding new card to the queue
	if ((*deck)->top == NULL)
	{
		temp->next = NULL;
		temp->previous = NULL;

		(*deck)->top = temp;
		(*deck)->bottom = temp;
		temp = NULL;
	}
	else
	{
		temp->next = (*deck)->bottom;
		temp->previous = NULL;

		((*deck)->bottom)->previous = temp;
		(*deck)->bottom = temp;
		temp = NULL;
	}
	(*deck)->size++;
}

// Deleting card from the beginning of the queue
void deck_remove_card(game_deck_t** deck)
{
	card_t* temp = (*deck)->top;
	if (temp != NULL)
	{
		(*deck)->top = ((*deck)->top)->previous;
		if ((*deck)->top != NULL)
			((*deck)->top)->next = NULL;
		else
			((*deck)->bottom) = NULL;

		free(temp);
		(*deck)->size--;
	}
}

// Adding card to the beginning of the que
void thrust_card_to_deck(game_deck_t** deck, card_t* source)
{
	card_t* temp = NULL;

	temp = (card_t*)malloc(sizeof(card_t));

	if (temp == NULL)
		return;

	// Copying information from the source
	temp->value = source->value;
	temp->color = source->color;
	translate_card(temp);

	// Adding new card to the queue
	if ((*deck)->top == NULL)
	{
		temp->next = NULL;
		temp->previous = NULL;

		(*deck)->top = temp;
		(*deck)->bottom = temp;
		temp = NULL;
	}
	else
	{
		temp->previous = (*deck)->top;
		temp->next = NULL;

		((*deck)->top)->next = temp;
		(*deck)->top = temp;
		temp = NULL;
	}
	(*deck)->size++;
}

// Printing the whole deck from the last card in the queue to the first one
void print_deck(game_deck_t** deck)
{
	if ((*deck)->size < 1)
	{
		printf("empty \n");
	}
	else
	{
		card_t* temp = (*deck)->bottom;
		while (temp != NULL)
		{
			printf("%s of %s", temp->text_value, temp->text_color);
			printf("\n");
			temp = temp->next;
		}
	}
}

// Sets variables at the beginning of the program 
void reset_decks(game_deck_t* decks[], int length)
{
	for (int i = 0; i < length; i++)
	{
		decks[i]->top = NULL;
		decks[i]->bottom = NULL;
		decks[i]->size = 0;
		decks[i]->rank = 0;
	}
}

// The bigger is SHUFFLE_POWER the more shuffled is deck
void shuffle_deck(card_t** deck, const int length)
{
	int rand_x, rand_y;
	int buf;
	char buf_array[MAX_REDABLE];
	for (int i = 0; i < SHUFFLE_POWER; i++)
	{
		rand_x = rand() % length;
		rand_y = rand() % length;

		// Swapping elements

		buf = (*deck)[rand_x].value;
		(*deck)[rand_x].value = (*deck)[rand_y].value;
		(*deck)[rand_y].value = buf;

		buf = (*deck)[rand_x].color;
		(*deck)[rand_x].color = (*deck)[rand_y].color;
		(*deck)[rand_y].color = buf;

		strcpy_s(buf_array, MAX_REDABLE, (*deck)[rand_x].text_color);
		strcpy_s((*deck)[rand_x].text_color, MAX_REDABLE, (*deck)[rand_y].text_color);
		strcpy_s((*deck)[rand_y].text_color, MAX_REDABLE, buf_array);

		strcpy_s(buf_array, MAX_REDABLE, (*deck)[rand_x].text_value);
		strcpy_s((*deck)[rand_x].text_value, MAX_REDABLE, (*deck)[rand_y].text_value);
		strcpy_s((*deck)[rand_y].text_value, MAX_REDABLE, buf_array);
	}
}

//Based on integer values of variables in card, it puts adequate string to text_color and text_value
void translate_card(card_t* source)
{
	switch (source->color)
	{
	case HEARTS:
		strcpy_s(source->text_color, MAX_REDABLE, "hearts");
		break;
	case DIAMONDS:
		strcpy_s(source->text_color, MAX_REDABLE, "diamonds");
		break;
	case CLUBS:
		strcpy_s(source->text_color, MAX_REDABLE, "clubs");
		break;
	case SPADES:
		strcpy_s(source->text_color, MAX_REDABLE, "spades");
		break;
	default:
		strcpy_s(source->text_color, MAX_REDABLE, "error");
	}

	switch (source->value)
	{
	case TWO:
		strcpy_s(source->text_value, MAX_REDABLE, "two");
		break;
	case THREE:
		strcpy_s(source->text_value, MAX_REDABLE, "three");
		break;
	case FOUR:
		strcpy_s(source->text_value, MAX_REDABLE, "four");
		break;
	case FIVE:
		strcpy_s(source->text_value, MAX_REDABLE, "five");
		break;
	case SIX:
		strcpy_s(source->text_value, MAX_REDABLE, "six");
		break;
	case SEVEN:
		strcpy_s(source->text_value, MAX_REDABLE, "seven");
		break;
	case EIGHT:
		strcpy_s(source->text_value, MAX_REDABLE, "eight");
		break;
	case NINE:
		strcpy_s(source->text_value, MAX_REDABLE, "nine");
		break;
	case TEN:
		strcpy_s(source->text_value, MAX_REDABLE, "ten");
		break;
	case JACK:
		strcpy_s(source->text_value, MAX_REDABLE, "jack");
		break;
	case QUEEN:
		strcpy_s(source->text_value, MAX_REDABLE, "queen");
		break;
	case KING:
		strcpy_s(source->text_value, MAX_REDABLE, "king");
		break;
	case ACE:
		strcpy_s(source->text_value, MAX_REDABLE, "ace");
		break;
	default:
		strcpy_s(source->text_value, MAX_REDABLE, "error");
	}
}

// Fills deck with aces, then with kings, ..., at the end with twos
/*
	14 is value for ace
	13 is value for king
	.
	.
	.
	2 is value for 2
	*/
void fill_starting_deck(card_t** starting_deck, const int length)
{
	for (int i = 0, val = 15; i < length; i++)
	{
		if (i % 4 == 0)
			val--;

		(*starting_deck)[i].value = val;
		(*starting_deck)[i].color = i % 4;
		(*starting_deck)[i].next = NULL;
		(*starting_deck)[i].previous = NULL;
		translate_card(&(*starting_deck)[i]);
	}
}
void random_fill_starting_deck(card_t** starting_deck, const int length)
{
	card_t buf;
	card_t* arr = allocate_mem_for_cards(length);

	for (int i = 0; i < length; i++)
	{
		do
		{
			buf.value = rand() % 13 + 2;
			buf.color = rand() % 4;

		} while (card_repeat(arr, buf, i) == 0);

		copy_information(&arr[i], buf);
		copy_information(&(*starting_deck)[i], buf);

		(*starting_deck)[i].next = NULL;
		(*starting_deck)[i].previous = NULL;
		translate_card(&(*starting_deck)[i]);
	}
	free(arr);
}

// Used during random filling cards
int card_repeat(card_t* arr, card_t buf, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i].color == buf.color && arr[i].value == buf.value)
			return 0;
	}
	return 1;
}

// Adding card to stake deck and deleting this same card from original deck
void transfer_from_deck_to_stake(game_deck_t* decks[], game_deck_t* stake_decks[], card_t* curr_player_card[])
{
	deck_add_card(&stake_decks[PLAYER_1], curr_player_card[PLAYER_1]);
	deck_remove_card(&decks[PLAYER_1]);

	deck_add_card(&stake_decks[PLAYER_2], curr_player_card[PLAYER_2]);
	deck_remove_card(&decks[PLAYER_2]);
}

void copy_information(card_t* to, const card_t from)
{
	to->value = from.value;
	to->color = from.color;
}

// Dealing cards from main deck to two other decks by turns
void dealing_cards(card_t** main_deck, game_deck_t* decks[], int length)
{
	decks[PLAYER_1]->rank = 0;
	decks[PLAYER_2]->rank = 0;

	for (int i = 0; i < length; i++)
		deck_add_card(&decks[i % 2], &((*main_deck)[i])); // i%2 - 0(PLAYER_1) or 1(PLAYER_2)
}

void count_deck_rank(int method, game_deck_t* decks[])
{
	if (method == 1)
	{
		count_deck_rank_method_1(&decks[PLAYER_1]);
		count_deck_rank_method_1(&decks[PLAYER_2]);
	}
	else if (method == 2)
	{
		count_deck_rank_method_2(&decks[PLAYER_1]);
		count_deck_rank_method_2(&decks[PLAYER_2]);
	}
	else
	{
		count_deck_rank_method_3(&decks[PLAYER_1]);
		count_deck_rank_method_3(&decks[PLAYER_2]);
	}
}
// Sum of value of every card
void count_deck_rank_method_1(game_deck_t** deck)
{
	card_t* temp = (*deck)->top;
	for (int i = 0; i < (*deck)->size; i++)
	{
		(*deck)->rank += temp->value;
		temp = temp->previous;
	}
}

// Sum of value of aces, kings, queens, jacks
void count_deck_rank_method_2(game_deck_t** deck)
{
	card_t* temp = (*deck)->top;
	for (int i = 0; i < (*deck)->size; i++)
	{
		if (temp->value > 10)
			(*deck)->rank += temp->value;
		temp = temp->previous;
	}
}

// Sum of value of cards with even values (twos, fours and so on)
// Additionaly 10 points if the first or the last card in the deck is ace, king or queen
// Additionaly 5 points if the second or the last but one card in the deck is ace, king or queen
// Additionaly 4 points if decks constis of 4 tens
void count_deck_rank_method_3(game_deck_t** deck)
{
	card_t* temp = (*deck)->top;

	if (temp->value == ACE || temp->value == KING || temp->value == QUEEN)
		(*deck)->rank += 10;
	temp = temp->previous;
	if (temp->value == ACE || temp->value == KING || temp->value == QUEEN)
		(*deck)->rank += 5;

	temp = (*deck)->top;
	for (int i = 0; i < (*deck)->size; i++)
	{
		if (temp->value % 2 == 0)
			(*deck)->rank += temp->value;
		temp = temp->previous;
	}

	temp = (*deck)->bottom;
	if (temp->value == ACE || temp->value == KING || temp->value == QUEEN)
		(*deck)->rank += 10;
	temp = temp->next;
	if (temp->value == ACE || temp->value == KING || temp->value == QUEEN)
		(*deck)->rank += 5;
}

// Lets user to fill deck by himself (not randomly)
void manually_dealed_cards(game_deck_t* decks[], int size)
{
	card_t buf;

	char choice = 1;
	int index;
	int value;
	int color;

	while (size--)
	{
		printf("Choose Player: \n");
		printf("Player 1 - 0\nPlayer 2 - 1\n");
		scanf_s("%d", &index);

		printf("Choose Card's Value: \n");
		printf("ACE - 14\nKING - 13\nQUEEN - 12\nJACK - 11\nTEN - 10\nNINE - 9\nEIGHT - 8\nSEVEN - 7\nSIX - 6\nFIVE - 5\nFOUR - 4\nTHREE - 3\nTWO - 2\n");
		scanf_s("%d", &value);

		printf("Choose Card's Color: \n");
		printf("HEARTHS - 0\nDIAMONDS - 1\nCLUBS - 2\nSPADES - 3\n");
		scanf_s("%d", &color);

		buf.value = value;
		buf.color = color;
		translate_card(&buf);
		deck_add_card(&decks[index], &buf);
		system("cls");
	}

	print_deck(&decks[PLAYER_1]);
	printf("\n\n");
	print_deck(&decks[PLAYER_2]);
	system("pause");
	system("cls");
}

// Triggered after round has ended in STANDARD WAR
// Adding card to winner's deck from his own stake_deck (1)
// Adding cards to winner's deck from loser's stake_deck (2)
void get_cards_from_battle(game_deck_t* decks[], game_deck_t* stake_decks[], const int winner_index, const int loser_index)
{
	// (1)
	int size = stake_decks[winner_index]->size;
	for (int i = 0; i < size; i++)
	{
		deck_add_card(&decks[winner_index], stake_decks[winner_index]->top);
		deck_remove_card(&stake_decks[winner_index]);
	}

	// (2)
	size = stake_decks[loser_index]->size;
	for (int i = 0; i < size; i++)
	{
		deck_add_card(&decks[winner_index], stake_decks[loser_index]->top);
		deck_remove_card(&stake_decks[loser_index]);
	}
}

// Triggered after round has ended in WISE WAR
void get_cards_from_battle_wisely(game_deck_t** deck, game_deck_t* stake_decks[])
{
	int random;
	game_deck_t* buf = allocate_mem_for_deck();
	reset_decks(&buf, 1);

	// Putting cards from both stake decks to one buffor deck
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		while (stake_decks[i]->size > 0)
		{
			deck_add_card(&buf, stake_decks[i]->top);
			deck_remove_card(&stake_decks[i]);
		}
	}

	// Cards should be given to player in random order
	// This loop simulate shuffling cards
	while (buf->size > 0)
	{
		random = rand() % 2;
		// don't add it to player's deck yet
		if (random == 0)
		{
			deck_add_card(&buf, buf->top);
			deck_remove_card(&buf);
		}
		else
		{
			deck_add_card(deck, buf->top);
			deck_remove_card(&buf);
		}
	}
	free(buf);
}

// After game is finished, we have to "free()" all the memory from decks
void clear_memory(game_deck_t* decks[], int length, card_t** starting_deck)
{
	card_t* temp;
	card_t* cleaner;

	for (int i = 0; i < length; i++)
	{
		if (decks[i]->size >= 1)
		{
			temp = decks[i]->bottom;
			cleaner = decks[i]->bottom;

			while (temp != NULL)
			{
				temp = temp->next;
				free(cleaner);
				cleaner = temp;
			}
		}

		decks[i]->bottom = NULL;
		decks[i]->top = NULL;
		decks[i]->size = 0;
	}
	free(*starting_deck);
}

// Used for standard war game and 1st experiment (2nd experiment uses different becasue we need to generate cards randomly there)
// It starts filling deck with aces then kings ... and at the end twos
void const_decks_preparations(card_t** starting_deck, int starting_deck_size, game_deck_t* decks[])
{
	*starting_deck = allocate_mem_for_cards(starting_deck_size);
	fill_starting_deck(starting_deck, starting_deck_size);
	shuffle_deck(starting_deck, starting_deck_size);
	dealing_cards(starting_deck, decks, starting_deck_size);
	//manually_dealed_cards(decks, starting_deck_size); // FOR TESTING PURPOSES
}

// Starting deck is always filled with random cards
void random_decks_preparations(card_t** starting_deck, int starting_deck_size, game_deck_t* decks[])
{
	*starting_deck = allocate_mem_for_cards(starting_deck_size);
	// Don't need to shuffle deck which is generated randomly
	random_fill_starting_deck(starting_deck, starting_deck_size);
	dealing_cards(starting_deck, decks, starting_deck_size);
	//manually_dealed_cards(decks, starting_deck_size); // FOR TESTING PURPOSES
}
