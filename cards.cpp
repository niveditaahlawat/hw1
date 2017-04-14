#include "cards.h"
#include <cstdlib>
#include <iostream>

#include <iomanip>
#include <algorithm>

/* *************************************************
Card class
************************************************* */

/*
Card() is the default constructor for the card class
*/
Card::Card() {
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}

// Accessor: returns a string with the suit of the card in English 
string Card::get_english_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "coins";
		break;
	case COPAS:
		suitName = "cups";
		break;
	case ESPADAS:
		suitName = "spades";
		break;
	case BASTOS:
		suitName = "clubs";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in English 
string Card::get_english_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "One";
		break;
	case DOS:
		rankName = "Two";
		break;
	case TRES:
		rankName = "Three";
		break;
	case CUATRO:
		rankName = "Four";
		break;
	case CINCO:
		rankName = "Five";
		break;
	case SEIS:
		rankName = "Six";
		break;
	case SIETE:
		rankName = "Seven";
		break;
	case SOTA:
		rankName = "Jack";
		break;
	case CABALLO:
		rankName = "Knight";
		break;
	case REY:
		rankName = "King";
		break;
	default: break;
	}
	return rankName;
}

// Accessor: returns an int representing the rank of the card
int Card::get_rank() const {
	int card_rank;
	switch (rank) {
	case AS:
		card_rank = 1;
		break;
	case DOS:
		card_rank = 2;
		break;
	case TRES:
		card_rank = 3;
		break;
	case CUATRO:
		card_rank = 4;
		break;
	case CINCO:
		card_rank = 5;
		break;
	case SEIS:
		card_rank = 6;
		break;
	case SIETE:
		card_rank = 7;
		break;
	case SOTA:
		card_rank = 10;
		break;
	case CABALLO:
		card_rank = 11;
		break;
	case REY:
		card_rank = 12;
		break;
	default: break;
	}
	return card_rank;
}

// Accessor: returns an int representing the point value of the card
int Card::get_card_val() const {
	double card_val;
	switch (rank) {
		case AS:
			card_val = 1;
			break;
		case DOS:
			card_val = 2;
			break;
		case TRES:
			card_val = 3;
			break;
		case CUATRO:
			card_val = 4;
			break;
		case CINCO:
			card_val = 5;
			break;
		case SEIS:
			card_val = 6;
			break;
		case SIETE:
			card_val = 7;
			break;
		case SOTA:
			card_val = 0.5;
			break;
		case CABALLO:
			card_val = 0.5;
			break;
		case REY:
			card_val = 0.5;
			break;
		default: break;
	}
	return card_val;
}


// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return get_rank() < card2.get_rank();
}


/* *************************************************
Hand class
************************************************* */
// Implemente the member functions of the Hand class here.

Hand::Hand() { }

// calculates the point values of the cards in the hand
int Hand::hand_val() const {
	double sum = 0.0;
	for (auto x : vec_cards)
		sum += x.get_card_val();
	return sum;
}

// returns true if player has crossed 7.5 points
bool Hand::bust() const {
	if (hand_val() > 7.5)
		return true;
	else return false;
}


// adds a card to the hand
void Hand::add_card(Card c) {
	vec_cards.push_back(c);
}

/* *************************************************
Player class
************************************************* */
// Implemente the member functions of the Player class here.
Player::Player(int m) {
	money = m;
}
