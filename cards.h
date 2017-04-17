/* *************************************
Ricardo Salazar, February 26, 2015

Interface of a simple Card class
************************************* */

#include <string>
#include <set>
#include <fstream>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

enum suit_t { OROS, COPAS, ESPADAS, BASTOS };

/*
The values for this type start at 0 and increase by one
afterwards until they get to SIETE.
The rank reported by the function Card::get_rank() below is
the value listed here plus one.
E.g:
The rank of AS is reported as    static_cast<int>(AS) + 1   = 0 + 1 =  1
The rank of SOTA is reported as  static_cast<int>(SOTA) + 1 = 9 + 1 = 10
*/
enum rank_t { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA = 9, CABALLO = 10, REY = 11 };

class Card {
public:
	// Constructor assigns random rank & suit to card.
	Card();

	// Accessors 
	string get_spanish_suit() const;
	string get_spanish_rank() const;
	string get_english_suit() const;
	string get_english_rank() const;

	// returns the rank value for each card
	int get_rank() const;

	// returns the point value for each card (1/2 for 10, 11, 12)
	double get_card_val() const;

	void print_card() const;

	// Compare rank of two cards. E.g: Eight<Jack is true.
	// Assume Ace is always 1. 
	// Useful if you want to sort the cards.
	bool operator < (Card card2) const;

private:
	suit_t suit;
	rank_t rank;
};


class Hand {
public:
	// A vector of Cards
	Hand();
	double hand_val() const;
	bool bust() const;
	void add_card(Card c);
	void print_hand() const;
	void file_print_hand(ostream& fout) const;

private:
	std::multiset <Card> vec_cards;
};


class Player {
public:
	// Constructor. 
	Player(int m);
	int get_money();

private:
	int money;
	// You decide what extra fields (if any) you'll need...
};

#endif