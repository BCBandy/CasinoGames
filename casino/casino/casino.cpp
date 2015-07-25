#include "BlackJack.h"
#include "Person.h"
#include <iostream>
using namespace std;

int main(){
	int game;
	cout << "Choose a game:\n1 for slots\n2 for blackjak\n3 for poker" << endl;
	cin >> game;

	if (game == 2){
		BlackJack game;
		//game.print();  works
		//cout << game;  doesnt

		//game.printDeck();
	}
}