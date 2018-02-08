
#include "card.h"
#include "holecards.h"
#include "deck.h"
#include "RandNumMT.h"
#include <iostream>

int main(void) {
	CHoleCards holecards;
	RandNumMT rng(0);
	CDeck deck(&rng);

	deck.shuffle();

	holecards.deal(deck);

	holecards.catASCII(std::cout);
	std::cout << std::endl;

}