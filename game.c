/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # game.c
  # Functions that create a blackjack game
*-----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <math.h>
#include <time.h>

#include "game.h"

void create_desk(struct card *deck, int deck_num){
	//Deck index
	int i = 0;
	int x, y, z;
	//Number of decks to create
	for (x = 0; x < deck_num; x++){
		//Heart, Dia, Spade, Club
		for (y = 0; y < 4; y++){
			//Ace to King
			for (z = 1; z < 14; z++){
				deck[i].value =  z;
				deck[i].suit = y;
				i++;
			}
		}
	}
	return;
}

void shuffle(struct card *deck, int deck_num){
	int i;
	//Seed random
	srand(time(NULL));
	for (i = 0; i < (52 * deck_num); i++){
		int j = i + rand() / (RAND_MAX / (deck_num * 52 - i) + 1);
		struct card t = deck[j];
		deck[j] = deck[i];
		deck[i] = t;
	}
	return;
}


void hit(struct card *deck, int *current_deck_index, struct card *hand,
			int *current_hand_index){
	hand[*current_hand_index] = deck[*current_deck_index];
	//"Remove" the card from the deck. -1 the card
	deck[*current_deck_index].value = -1;
	deck[*current_deck_index].suit = -1;
	*current_deck_index = *current_deck_index + 1;
	*current_hand_index = *current_hand_index + 1;
	return;
}


void deal(struct card *deck, int *current_deck_index, struct card *hand, 
			int *current_hand_index){
	hit(deck, current_deck_index, hand, current_hand_index);
	hit(deck, current_deck_index, hand, current_hand_index);
	return;
}


uint8_t card_value(struct card *hand, int *current_hand_index){
	struct card current_card =  hand[*current_hand_index];
	uint8_t card_byte = (current_card.value + (current_card.suit * 13));
	return card_byte;
}

//Main exist for testing purposes
//Still need to caclulate value (Ace is 1 or 11 depend on bust or not)
int main(){
	int deck_num = 2;
	struct card deck[52 * deck_num];
	int current_deck_index = 0;

	//Max amount of cards possible for a hand is 21
	//Ex - 21 aces for atleast 6 decks
	struct card player_hand[21];
	int current_player_hand_index = 0;

	create_desk(deck, deck_num);
	shuffle(deck, deck_num);
	deal(deck, &current_deck_index, player_hand, &current_player_hand_index);

	//First Card
	printf("Player Card %d: %d:%d\n", current_player_hand_index - 2,
			player_hand[current_player_hand_index - 2].value,
			player_hand[current_player_hand_index - 2].suit);
	//Second Card
	printf("Player Card %d: %d:%d\n", current_player_hand_index - 1,
			player_hand[current_player_hand_index - 1].value,
			player_hand[current_player_hand_index - 1].suit);

	//First and Second card of the deck
	printf("Deck Card %d: %d:%d\n", current_deck_index - 2,
			deck[current_deck_index - 2].value, deck[current_deck_index - 2].suit);
	printf("Deck Card %d: %d:%d\n", current_deck_index - 1,
			deck[current_deck_index - 1].value, deck[current_deck_index - 1].suit);

	//Byte value of the card for the header
	uint8_t byte_value = card_value(player_hand, &current_player_hand_index - 2);

	printf("Byte Card %d: %d\n", current_deck_index - 2, byte_value);
	return 0;
}