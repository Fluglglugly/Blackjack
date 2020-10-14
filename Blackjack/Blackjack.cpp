

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>


int deck[] = { 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,
	7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
bool Player_turn = true;
bool Ace = false;
int PlayerValue = 0;
int DealerValue = 0;
int number = 0;
int PlayerCash = 100;
int DealerCash = 100;
int Pool = 0;
int y = 0;
int z = 0;


//not sure if I entirely understand how srand works, so I'll say what my understanding of it is, and if it's wrong you can say so
//srand is the seed that rand uses, and so every time you use rand, it is saved as a sequence in srand. if you don't reset the seed, 
//you will continue to get the same result. If you set srand to 1, it will make rand start the sequence from the start, while srand(time(0)) resets it
void func_shuffle() 
{
	srand(time(0));
	for (int x = 0; x < 5; x++) {

		for (int i = 0; i < 52; i++) {
			int random = rand() % 52;
			//std::cout << random;
			std::swap(deck[i], deck[random]);
		}
		//std::cout << "\n";

	}

};

void func_wincon() 
{

	if (PlayerValue > 21) {
		std::cout << "You lost the bet :(\n";
		PlayerValue = 0;
		DealerValue = 0;
		DealerCash += Pool;
		Pool = 0;
		y = 1;

	}
	else if (DealerValue > 21) {
		std::cout << "You won the bet :)\n";
		PlayerValue = 0;
		DealerValue = 0;
		PlayerCash += Pool;
		Pool = 0;
		y = 1;
	}
	else if (DealerValue > PlayerValue) {
		std::cout << "You lost the bet :(\n";
		PlayerValue = 0;
		DealerValue = 0;
		DealerCash += Pool;
		Pool = 0;
		y = 1;
	};
};

void func_true_win() {
	if (PlayerCash == 0) {
		std::cout << "You're broke! Game over :(";
		y = 2;
	}
	else if (DealerCash == 0) {
		std::cout << "The Dealer's broke! You Won :)";
		y = 2;
	}

};

void func_draw() 
{

	
	if (Player_turn == true) {
		if (number > 52) {
			func_shuffle();
			number = 0;
		};
		std::cout << "The card is a " << deck[number] << "\n";
		PlayerValue += deck[number];
		if (deck[number] == 11) {
			Ace = true;
		};
		if (Ace == true && PlayerValue > 21) {
			PlayerValue -= 10;
			Ace = false;
		};
		std::cout << "Your cards now give you a score of: " << PlayerValue << "\n";
	}
	else {
		if (number > 52) {
			func_shuffle();
			number = 0;
		};
		std::cout << "The card is a " << deck[number] << "\n";
		DealerValue += deck[number];
		if (deck[number] == 11) {
			Ace = true;
		};
		if (Ace == true && PlayerValue > 21) {
			PlayerValue -= 10;
			Ace = false;
		};
		std::cout << "The Dealers cards now give a score of: " << DealerValue << "\n";
	};
	number++;
};

void func_play()
{
	
	int bet = 0;
	for (y = 0; y < 2;) {
		y = 0;
		z = 0;
		Ace = false;
		Player_turn = true;
		std::cout << "You have: "<< PlayerCash<<"$\nDealer has: "<<DealerCash<<"$\nWhat do you bet? The minimum is 10$. ";
		std::cin >> bet;
		for (int x = 0; x < 1;)
		{

				if (bet < 10)
				{
					std::cout << "Your bet is too low, enter another.\n";
					bet = 0;
					std::cin >> bet;
				}
				else
				{
					x = 1;
					std::cout << "Your bet of " << bet << "$ is accepted.\n";
					Pool = bet * 2;
					PlayerCash -= bet;
					DealerCash -= bet;
					func_draw();
					func_draw();

				};
		};
		for (y = 0; y < 1;)
		{
			std::cout << "Do you want to draw another card? ";
			std::string answer = "default";
			std::cin >> answer;
			if (answer == "yes" | answer == "Yes") {
				func_draw();
			}
			else if (answer == "No" | answer == "no" | answer == "stand" | answer == "Stand") {
				for (y = 0; y < 1;) {
					//std::cout << "test";
					Player_turn = false;
					Ace = false;
					func_draw();
					func_wincon();
				}
			}
			else {
				std::cout << "Your answer was not accepted, try: Yes or No";
			};
			func_wincon();
		};
		func_true_win();
	};

};

int main()
{

	func_shuffle();
	func_play();
//	std::cout << "\n";
//	for (int i = 0; i < 51; i++) {
//		std::cout << deck[i]<<"\n";
//	}
}