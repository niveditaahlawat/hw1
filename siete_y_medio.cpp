#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"

// Global constants (if any)
// Non member functions declarations (if any)
// Non member functions implementations (if any)

/*
std::ostream& operator << (std::ostream& fout, const Hand& user_hand) {
	user_hand.print_hand();
	return fout;
}
*/

int main() {
	srand((int)time(0));			// seed random #
	ofstream fout;					// file output for game log
	fout.open("gamelog.txt");
	int game_number = 0;

	bool dealer_out = false;
	bool play_again = true;			// user wants to play again or draw another card

	int player_money = 100;
	int bet = 0;
	char answer;

	while (player_money > 0 && player_money < 900) {
		play_again = true;
		dealer_out = false;
		Hand player_hand;
		Hand dealer_hand;

		std::cout << "You have $" << player_money << ". Enter bet: ";
		std::cin >> bet;
		while (bet > player_money) {
			std::cout << "You cannot bet more than $" << player_money << ". Please input a valid bet: " << std::endl;
			std::cin >> bet;
		}

		fout << "-----------------------------------------------" << std::endl;
		fout << "Game number: " << game_number << "\t\t" << "Money left: $" << player_money << "\nBet: $" << bet << "\n";

		Card player_card;
		player_hand.add_card(player_card);

		std::cout << "Your cards: " << std::endl;
		player_hand.print_hand();
		
		std::cout << "Your total is " << player_hand.hand_val() << ". Do you want another card (y/n)? ";
		std::cin >> answer;
		if (answer == 'y') {
			play_again = true;
		}
		else if (answer == 'n') {
			play_again = false;
		}
		while (play_again) {
			Card player_card;
			player_hand.add_card(player_card);

			player_card.print_card();
			std::cout << std::endl;

			std::cout << "Your cards: " << std::endl;
			player_hand.print_hand();

			if (player_hand.hand_val() > 7.5) {
				std::cout << "Your total is " << player_hand.hand_val() << std::endl;
				play_again = false;
			}
			else {
				std::cout << "Your total is " << player_hand.hand_val() << ". Do you want another card (y/n)? ";
				std::cin >> answer;
				if (answer == 'y') {
					play_again = true;
				}
				else if (answer == 'n') {
					play_again = false;
				}
			}

		}

		// print to gamelog.txt
		fout << std::endl;
		fout << "Your cards: " << "\n";
		player_hand.file_print_hand(fout);
		fout << std::endl;
		fout << "Your total: " << player_hand.hand_val() << ". \n";
		fout << std::endl;

		while (!dealer_out) {
			while (dealer_hand.hand_val() < 5.5) {
				Card dealer_card;
				dealer_hand.add_card(dealer_card);
			}
			std::cout << "Dealer's cards: " << std::endl;
			dealer_hand.print_hand();
			std::cout << "The dealer's total is " << dealer_hand.hand_val() << "." << std::endl;
			std::cout << std::endl;
			
			// print to gamelog.txt
			fout << "Dealer's cards: " << "\n";
			dealer_hand.file_print_hand(fout);
			fout << std::endl;
			fout << "Dealer's total: " << dealer_hand.hand_val() << ". \n";
			fout << std::endl;
			
			// if player busts
			if (player_hand.bust()) {
				player_money -= bet;
				std::cout << "You busted! You lose $" << bet << "." << std::endl << std::endl;
			}
			// if dealer busts
			else if (dealer_hand.bust()) {
				std::cout << "You win $" << bet << "." << std::endl << std::endl;
				player_money += bet;
			}
			// if dealer is closer to 7.5 than player
			else if (dealer_hand.hand_val() > player_hand.hand_val()) {
				std::cout << "Too bad. You lose $" << bet << "." << std::endl << std::endl;
				player_money -= bet;
			}
			// if player is closer to 7.5 than dealer
			else if (player_hand.hand_val() > dealer_hand.hand_val()) {
				std::cout << "You win $" << bet << "." << std::endl << std::endl;
				player_money += bet;
			}
			// draw
			else if (player_hand.hand_val() == dealer_hand.hand_val()) {
				std::cout << "A draw! You get back your $" << bet << "." << std::endl << std::endl;
			}
			dealer_out = true;
		}
	}
	if (player_money >= 900) {
		std::cout << std::endl << "You win $" << player_money << "." << std::endl;
		std::cout << "Congratulations. You beat the casino!" << std::endl;
		std::cout << std::endl;
		std::cout << "Bye!";
	}
	if (player_money <= 0) {
		std::cout << std::endl << "You have $" << player_money << ". GAME OVER!" << std::endl;
		std::cout << "Come back when you have more money." << std::endl;
		std::cout << std::endl;
		std::cout << "Bye!";
		std::cout << std::endl;
	}

	fout.close();
	return 0;
}