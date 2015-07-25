#ifndef PERSON_H
#define PERSON_H
#include "Card.h"
#include <vector>
using namespace std;

class Person
{
public:
	Person();
	~Person(){};
	int setBet(int);
	int getBet() const;
	vector<vector<Card>>hand;
	double getBankRoll() const;
	void setBankRoll(double);
//	virtual void setHandTotal(int);
	int getHandTotal() const;
	void setPlayHand(int);
	int getPlayHand() const;
	void setSplitBets(int);
	int getSplitBets(int);
	void setHandTotals(int);
	int getHandTotal(int, int);
	vector<int> handTotal;
protected:
	int howToPlayHand;
	
	vector<int> splitBets;
	int bet;
	double bankRoll;
};
#endif