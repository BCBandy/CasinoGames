#include "BlackJack.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

BlackJack::BlackJack()
{
	getPlayers();
	createPlayers();
	loopGame();
}
void BlackJack::getPlayers()
{
	cout << "How many players? Choose between 1-5" << endl;
	cin >> numPlayers;

	while (numPlayers > 5 || numPlayers < 1){
		cout << "Invalid number of players, choose betwen 1-5" << endl;
		cin >> numPlayers;
	}
	numPlayers += 1;
}
void BlackJack::createPlayers()
{
	players = new Person [numPlayers];                          
}
void BlackJack::printHand(int aPlayer) const
{
	if (aPlayer <= numPlayers - 2){
		cout << "Player " << aPlayer + 1 << ": " << endl;
		for (int p = 0; p < players[aPlayer].hand.size(); p++){
			for (int j = 0; j < players[aPlayer].hand[p].size(); j++){
				if (players[aPlayer].getPlayHand() != 1)
				cout << players[aPlayer].hand[p][j].getMyFace() << " of " << players[aPlayer].hand[p][j].getMySuit() << endl;
			}
			cout << endl;
		}
	}
	else{
		cout << "Dealer" << ": " << endl;
		cout << "face down" << endl;

		for (int j = 1; j < players[aPlayer].hand[0].size(); j++){
			cout << players[aPlayer].hand[0][j].getMyFace() << " of " << players[aPlayer].hand[0][j].getMySuit() << endl;
		}
		cout << endl;
	}

}
/*ostream &operator<<(ostream& os, BlackJack *players)
{
	for (int i = 0; i < getNumPlayers(); i++){
		os << players[i].getBet() << endl;
	}
	return os;
}*/
int BlackJack::getNumPlayers() const
{
	return numPlayers;
}
void BlackJack::deal()
{
	cout << "Dealing cards...\n" << endl;
	
	for (int j = 0; j < 2; j++){
		for (int i = 0; i < numPlayers; i++){				//first card dealt, then second, dealer is last player
			if (players[i].getBankRoll() > 5){
				players[i].hand.push_back(vector<Card>());
				players[i].hand[0].push_back(deck[deckCount]);			
				deckCount++;
//				setHandTotal(i);
			}
		}
	}
	for (int i = 0; i < numPlayers ; i++){				//prints players and dealers hand
		if (players[i].getBankRoll() > 5){
				printHand(i);
		}
	}
//	cout << "Dealer:\n" << "face down\n" << dealerHand[1].getMyFace() << " of " << dealerHand[1].getMySuit() << endl << endl;
}
void BlackJack::placeBets()
{
	int playerBet = 0;
	int bankRollCheck = 0;

	for (int i = 0; i < numPlayers - 1; i++){
		if (players[i].getBankRoll() < 5)
			cout << "Player " << i + 1 << " is out of money!" << endl;
		while ((playerBet < 5 || playerBet > 100) && players[i].getBankRoll() >= 5){
			cout << "Player " << i + 1 << " place your bet (5-100)" << endl;
			cin >> playerBet;
		}
		players[i].setBet(playerBet);
		playerBet = 0;
		cout << "Player " << i + 1 << "'s bank: " << players[i].getBankRoll() << endl << endl;
	}
}
void BlackJack::playHand()
{
	int choice;

	for (int i = 0; i < numPlayers - 1; i++){
		if (checkSplit(i) != -1){
			printHand(i);
			cout << "Player " << i + 1 << " play your hand: \n1 = surrender\n2 = double down\n3 = hit\n4 = stand\n5 = split (if you have doubles)" << endl;
			cin >> choice;
			players[i].setPlayHand(choice);

			if (choice == 1)
				surrender(i);
			if (choice == 2)
				doubleDown(i);
			if (choice == 5)
				split(i);
			if (choice == 3)
				hit(i, 0);
			if (choice == 4)
				stand(i);
		}
		else{
			printHand(i);
			cout << "Player " << i + 1 << " play your hand: \n1 = surrender\n2 = double down\n3 = hit\n4 = stand\n" << endl;
			cin >> choice;
			players[i].setPlayHand(choice);

			if (choice == 1)
				surrender(i);
			if (choice == 2)
				doubleDown(i);
			if (choice == 3)
				hit(i, 0);
			if (choice == 4)
				stand(i);
		}
	}
}
void BlackJack::surrender(int player)
{
	double s, totalBank;

	totalBank = players[player].getBankRoll();
	totalBank += (double)players[player].getBet() / 2;
	players[player].setBankRoll(totalBank);
	cout << "Player " << player + 1 << " folds, credited " << (double)players[player].getBet() / 2
		<< " dollars\nCurrent bank: " << players[player].getBankRoll() << endl << endl;

}
void BlackJack::doubleDown(int player)
{
	int choice;

	players[player].setBankRoll(players[player].getBankRoll() + players[player].getBet());

	cout << "Removed $" << players[player].getBet() << endl;
	cout << "Current bank: $" << players[player].getBankRoll() << endl;

	players[player].setBet((players[player].getBet() * 2));

	cout << "Player " << player + 1 << " hit or stand? (1 = hit, 2 = stand)" << endl;
	cin >> choice;

	if (choice == 1){
		players[player].hand[0].push_back(deck[deckCount]);
		deckCount++;
	}
		players[player].setHandTotals(setHandTotal(player, 0));

		printHand(player);
}
void BlackJack::split(int player)
{
	int split = 0, choice = 1, count = 0;

	while (split != -1 && count < 3 && choice == 1){
		players[player].hand[count + 1].resize(2);
		players[player].hand.push_back(vector<Card>());
		players[player].hand[count + 1][0] = players[player].hand[split][0];
		players[player].hand[split][0] = deck[deckCount];
		deckCount++;
		players[player].hand[count + 1][1] = deck[12];
		deckCount++;

		players[player].setBankRoll(players[player].getBankRoll() - players[player].getBet());		//removing $bet from bankroll
		printHand(player);

		cout << "Bet increased by: " << players[player].getBet() << endl;
		cout << "Current bank: " << players[player].getBankRoll() << endl << endl;
		split = checkSplit(player);
		if (split != -1){
			cout << "Do you want to split again? (1 = yes, 2 = no)" << endl;
			cin >> choice;
		}
		players[player].setSplitBets(players[player].getBet());
		count++;
	}

	for (int p = 0; p < players[player].hand.size() - 1; p++){
		cout << "Play hand " << p + 1 << endl;
		cout << "Do you want to hit? (1 = yes, 2 = no)" << endl;
		cin >> choice;
		if (choice == 1)
			hit(player, p);
		else
			players[player].setHandTotals(setHandTotal(player, p));
	}
}
int BlackJack::checkSplit(int player)
{
	for (int i = 0; i < players[player].hand.size() - 1; i++){
		if (players[player].hand[i][0].getMyFace() == players[player].hand[i][1].getMyFace()){
			return i;
		}
	}
	return -1;
}
void BlackJack::hit(int player, int hand)
{
	int choice, total;
	do{
		choice = 0;
		cout << "Player " << player + 1 << " hit!" << endl << endl;
		players[player].hand[hand].push_back(deck[deckCount]);
		deckCount++;
		printHand(player);
		total = setHandTotal(player, hand);
		if (total < 21){
			cout << "Hit again? (1 = yes, any key = no)" << endl;
			cin >> choice;
		}
	} while (choice == 1 && total < 21);
	players[player].setHandTotals(total);
}
int BlackJack::setHandTotal(int player, int hand)
{
	int total = 0, aceCount = 0;
	vector<int> values;


//	for (int i = 0; i < players[player].hand[hand + 1].size(); i++){
		for (int j = 0; j < players[player].hand[hand].size(); j++){
			values.push_back(determineCardValue(players[player].hand[hand][j].getMyFace()));
		}
//	}
	for (int k = 0; k < values.size(); k++){
		total += values.at(k);
		if (values.at(k) == 11)
			aceCount++;
	}
	while (total > 21 && aceCount > 0){
		total -= 10;
		aceCount--;
	}
	if (total > 21){
		cout << "Bust!" << endl << endl;
	}
	return total;
}
int BlackJack::determineCardValue(string card)
{
	string face[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
	int value[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

	for (int i = 0; i < 13; i++){
		if (face[i] == card)
			return value[i];
	}
}
void BlackJack::stand(int player)
{
	players[player].setHandTotals(setHandTotal(player, 0));
}
void BlackJack::playDealerHand()
{
	int total = setHandTotal(numPlayers - 1, 0);
	printDealerHand();
	while (total < 17){
		players[numPlayers - 1].hand[0].push_back(deck[deckCount]);
		deckCount++;
		printDealerHand();
		total = setHandTotal(numPlayers - 1, 0);
		
	}
	players[numPlayers - 1].setHandTotals(total);
//	cout << players[numPlayers - 1].getHandTotal(numPlayers - 1, 0) << "hereeeeeeeeeeee" << endl;
//	cout << players[0].getHandTotal(numPlayers - 1, 0) << "hereeeeeeeeeeee" << endl;
}
void BlackJack::printDealerHand() const
{
	cout << "Dealer: "  << endl;
	for (int p = 0; p < players[numPlayers - 1].hand.size(); p++){
		for (int j = 0; j < players[numPlayers - 1].hand[p].size(); j++){
			if (players[numPlayers - 1].getPlayHand() != 1)
				cout << players[numPlayers - 1].hand[p][j].getMyFace() << " of " << players[numPlayers - 1].hand[p][j].getMySuit() << endl;
		}
		cout << endl;
	}
}
void BlackJack::payOut()
{
	for (int i = 0; i < numPlayers - 1; i++){
		for (int j = 0; j < players[i].hand.size() - 1; j++){
			if (players[i].getPlayHand() != 1 && players[i].getPlayHand() < 22){
				if (players[i].getHandTotal(i, j) == 21 && players[i].hand[j].size() == 2){
					cout << "Player " << i + 1 << " has a Black Jack!" << endl;
					//if push, credits money
					if (players[numPlayers - 1].hand[0].size() == 2 && players[numPlayers - 1].getHandTotal(i, 0) == 21){
						cout << "Its a push for player " << i + 1 << endl;

						players[i].setBankRoll(players[i].getBankRoll() + players[i].getBet());
						cout << "Credited " << players[i].getBet() << endl;
						cout << "Bank: " << players[i].getBankRoll() << endl << endl;
					}
					else if (players[i].getHandTotal(i, j) > players[numPlayers - 1].getHandTotal(i, 0)){
						cout << "Player " << i + 1 << " wins with Black Jack!" << endl;
						cout << "Credited extra 1.5 x bet: " << endl;
						players[i].setBankRoll(players[i].getBankRoll() + (players[i].getBet() * 1.5) + players[i].getBet());
						cout << "Bank: " << players[i].getBankRoll() << endl << endl;
					}
				}
				//checking tie without blackjack
				else if (players[i].getHandTotal(i, j) == players[numPlayers - 1].getHandTotal(i, 0) && 
					players[i].getHandTotal(i, j) < 22 && players[numPlayers - 1].getHandTotal(i, 0) < 22){
					cout << "Its a push" << endl;

					players[i].setBankRoll(players[i].getBankRoll() + players[i].getBet());
					cout << "Credited " << players[i].getBet() << endl;
					cout << "Bank: " << players[i].getBankRoll() << endl << endl;
				}
				else if (players[i].getHandTotal(i, j) > players[numPlayers - 1].getHandTotal(i, 0) && players[i].getHandTotal(i, j) < 22){
					cout << "Player " << i + 1 << " wins!" << endl << endl;

					players[i].setBankRoll(players[i].getBankRoll() + players[i].getBet() * 2);
					cout << "Credited " << players[i].getBet() * 2 << endl;
					cout << "Bank: " << players[i].getBankRoll() << endl << endl;
				}
				else if ((players[i].getHandTotal(i, j) < 22) && ((players[i].getHandTotal(i, j) < players[numPlayers - 1].getHandTotal(i, 0))) && players[numPlayers - 1].getHandTotal(i, 0 ) < 22){
					cout << "Player " << i + 1 << " loses!" << endl << endl;
				}
				else if (players[i].getHandTotal(i, j) < 22 && players[numPlayers - 1].getHandTotal(i, 0) > 21){
					cout << "Player " << i + 1 << " wins! " << endl << endl;

					players[i].setBankRoll(players[i].getBankRoll() + players[i].getBet() * 2);
					cout << "Credited " << players[i].getBet() * 2 << endl;
					cout << "Bank: " << players[i].getBankRoll() << endl << endl;
				}

			}
		}
	}
}
void BlackJack::loopGame()
{
	int choice = 1;
	while (choice == 1){
		placeBets();
		shuffle();
		deal();
		playHand();
		playDealerHand();
		payOut();
		
		for (int p = 0; p < numPlayers; p++){
//			for (int q = 0; q < players[numPlayers].hand.size(); q++){
				players[p].hand.clear();
				players[p].handTotal.clear();
			}
//		}
		

		deckCount = 0;
		cout << "Play again? (1 = yes, any key for no)" << endl;
		cin >> choice;
		cout << "Deck shuffeled" << endl;
		
	}
}

