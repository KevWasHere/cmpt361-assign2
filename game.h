/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # game.h
  # game.c header
*-----------------------------------------------------------------------*/

#ifndef GAME_H
#define GAME_H

//Card Struct. Values - card values. Suit - card suit
struct card{
	int value;
	int suit;
};

/*Prototypes*/

//Create x number of 52 card decks
//Parameters: deck - Deck array of approiate size for cards 
//deck_num - Number of decks to be created
void create_desk(struct card *deck, int deck_num);

//Randomize deck array. Modified version of Ben Pfaff code
//Reference - https://benpfaff.org/writings/clc/shuffle.html
//Parameters: deck - Deck array
//deck_num - Number of decks in the array
void shuffle(struct card *deck, int deck_num);

//Return a single new card
//Parameters: deck - Deck array
//current_deck_index - Current card index of the deck
//Hand - Hand (Dealer or player) array to hit to
//current_hand_index - Current card index of the hand
void hit(struct card *deck, int *current_deck_index, struct card *hand, 
			int *current_hand_index);
			
//Deal two cards initially to a hand for the start of a round
//Parameters: deck - Deck array
//current_deck_index - Current card index of the deck
//Hand - Hand (Dealer or player) array to hit to
//current_hand_index - Current card index of the hand
void deal(struct card *deck, int *current_deck_index, struct card *hand, 
			int *current_hand_index);

//Return byte value (for byte string) of current card
//Hand - Hand (Dealer or player) array to hit to
//current_hand_index - Current card index of the hand
uint8_t card_value(struct card *hand, int *current_hand_index);
#endif