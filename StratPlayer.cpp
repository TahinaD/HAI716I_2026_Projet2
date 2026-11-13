#include "StratPlayer.hpp"

StratPlayer::StratPlayer(int chosenIDStrat, Strategie chosenStrat)
	: IDStrat {chosenIDStrat}
	, strat {chosenStrat}
{

}

StratPlayer StratPlayer::operator=(const StratPlayer& other)
{
	return StratPlayer(other.IDStrat, other.strat);
}

int StratPlayer::getPoints() {
	return pointsWon;
}

string StratPlayer::getName(vector<string> stratsNames) {
	return stratsNames[IDStrat];
}

void StratPlayer::addPoints(int gain) {
	pointsWon += gain;
}

void StratPlayer::increaseWins()
{
	gamesWon++;
}

Choice StratPlayer::playStrat(Choice preAdvMove) {
	switch(strat) {
		case Strategie::ALLD:
			return playAllD();
		break;
		case Strategie::RANDOM:
			return playRandom();
		break;
		case Strategie::TITFORTAT:
			return playTitForTat(preAdvMove);
		break;
		case Strategie::TESTER:
			return playTester(preAdvMove);
		break;
		case Strategie::JOSS:
			return playJoss(preAdvMove);
		break;
		default:
			return Choice::FT;
		break;
	}
}

Choice StratPlayer::playAllD() {
	return Choice::D;
}

Choice StratPlayer::playRandom() {
	return rand() < RAND_MAX/2 ? Choice::C : Choice::D;
}

Choice StratPlayer::playTitForTat(Choice prevAdvMove) {
	return prevAdvMove = Choice::FT || prevAdvMove == Choice::D ? Choice::D : Choice::C;
}

Choice StratPlayer::playTester(Choice preAdvMove) {
	playedC = (playedC == 2 ? 0 : playedC++);
	return preAdvMove == Choice::D ? playTitForTat(preAdvMove) : (playedC == 0 ? Choice::D : Choice::C);
}

Choice StratPlayer::playJoss(Choice preAdvMove) {
	return (preAdvMove == Choice::FT && rand() < RAND_MAX/10) || preAdvMove == Choice::D ? Choice::D : Choice::C;
}