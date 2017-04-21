#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"

int main() {
	srand((int)time(0));			// seed random #
	ofstream fout;					// file output for game log
	fout.open("gamelog.txt");		// open the gamelog.txt file
	int game_number = 0;

	bool dealer_out = false;
	bool player_alive = true;		// user wants to play again or draw another card

	int player_money = 100;
	int bet = 0;
	char answer;

	while (player_money > 0 && player_money < 1000) {
		player_alive = true;
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
		fout << "Game number: " << game_number;
		fout.width(15);
		fout << "Money left: $" << player_money << "\nBet: $" << bet << "\n";

		Card player_card;
		player_hand.add_card(player_card);

		std::cout << "Your cards: " << std::endl;
		player_hand.print_hand();
		
		std::cout << "Your total is " << player_hand.hand_val() << ". Do you want another card (y/n)? ";
		std::cin >> answer;
		if (answer == 'y') {
			player_alive = true;
		}
		else if (answer == 'n') {
			player_alive = false;
		}
		while (player_alive) {
			Card player_card;
			player_hand.add_card(player_card);

			std::cout << "New card:" << std::endl;
			player_card.print_card();
			std::cout << std::endl;

			std::cout << "Your cards: " << std::endl;
			player_hand.print_hand();

			if (player_hand.hand_val() > 7.5) {
				std::cout << "Your total is " << player_hand.hand_val() << std::endl;
				player_alive = false;
			}
			else {
				std::cout << "Your total is " << player_hand.hand_val() << ". Do you want another card (y/n)? ";
				std::cin >> answer;
				if (answer == 'y') {
					player_alive = true;
				}
				else if (answer == 'n') {
					player_alive = false;
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
			Card dealer_card;
			dealer_hand.add_card(dealer_card);

			std::cout << "Dealer's cards: ";
			std::cout << std::endl;
			dealer_card.print_card();
			std::cout << "The dealer's total is " << dealer_hand.hand_val() << "." << std::endl;
			std::cout << std::endl;

			while (dealer_hand.hand_val() < 5.5) {
				Card dealer_card;
				dealer_hand.add_card(dealer_card);
				std::cout << "New card: " << std::endl;
				dealer_card.print_card();
				std::cout << std::endl;
				std::cout << "Dealer's cards: " << std::endl;
				dealer_hand.print_hand();
				std::cout << "The dealer's total is " << dealer_hand.hand_val() << "." << std::endl;
				std::cout << std::endl;
			}
			
			// print to gamelog.txt
			fout << "Dealer's cards: " << "\n";
			dealer_hand.file_print_hand(fout);
			fout << std::endl;
			fout << "Dealer's total: " << dealer_hand.hand_val() << ". \n";
			fout << std::endl;
			
			// if player busts
			if (player_hand.bust()) {
				std::cout << "You busted! You lose $" << bet << "." << std::endl << std::endl;
				player_money -= bet;
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

	// console output if player wins
	if (player_money >= 900) {
		std::cout << std::endl << "You win $" << player_money << "." << std::endl;
		std::cout << "Congratulations. You beat the casino!" << std::endl;
		std::cout << std::endl;
		std::cout << "Bye!";
	}

	// console output if player loses
	if (player_money <= 0) {
		std::cout << std::endl << "You have $" << player_money << ". GAME OVER!" << std::endl;
		std::cout << "Come back when you have more money." << std::endl;
		std::cout << std::endl;
		std::cout << "Bye!";
		std::cout << std::endl;
	}

	fout.close();		// close the gamelog.txt file
	return 0;
}