/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # game.c
  # Functions that create a blackjack game
*-----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//Card Struct. Values - card values. Suit - card suit
struct card{
	int value;
	int suit;
};

//Create x number of decks
void create_desk(struct card *deck, int deck_num){
	//struct card deck[52 * deck_num];
	//Deck index
	int i = 0;
	int x, y, z;
	//Number of decks to create
	for (x = 0; x < deck_num; x++){
		//Heart, Dia, Spade, Club
		for (y = 1; y < 5; y++){
			//Ace to King
			for (z = 1; z < 14; z++){
				deck[i].value =  y;
				deck[i].suit = z;
				//printf("Current x: %d, Current y: %d, Current z: %d ", x, y, z);
				//printf("Card %d: %d:%d\n", i, deck[i].value, deck[i].suit);
				i++;
			}
		}
	}
	return;
}

//Randomize deck array
//Modified version of Ben Pfaff code
//Reference - https://benpfaff.org/writings/clc/shuffle.html
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

//Return a single new card. Do some error checking later to see if out of index
void hit(struct card *deck, int *current_deck_index, struct card *hand,
			int *current_hand_index){
	hand[*current_hand_index] = deck[*current_deck_index];
	*current_deck_index = *current_deck_index + 1;
	*current_hand_index = *current_hand_index + 1;
	return;
}

//Deal two cards initial for the start of a round
void deal(struct card *deck, int *current_deck_index, struct card *hand, 
			int *current_hand_index){
	hit(deck, current_deck_index, hand, current_hand_index);
	hit(deck, current_deck_index, hand, current_hand_index);
	return;
}


//Still need to caclulate value (Ace is 1 or 11 depend on bust or not)
int main(){
	int deck_num = 1;
	struct card deck[52 * deck_num];
	int current_deck_index = 0;
	
	struct card player_hand[21];  //Max amount of cards possible for a hand is 21
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
	/*
	int i;
	for (i = 0; i < (52 * deck_num); i++){
		printf("Card %d: %d:%d\n", i, deck[i].value, deck[i].suit);
	}
	*/
}