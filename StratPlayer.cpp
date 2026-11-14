#include "StratPlayer.hpp"

StratPlayer::StratPlayer(int chosenIDStrat, Strategie chosenStrat)
	: IDStrat {chosenIDStrat}
{
	strat = chosenStrat;
}

int StratPlayer::getPoints() const {
	return pointsWon;
}

string StratPlayer::getName(vector<string> stratsNames) {
	return stratsNames[IDStrat];
}

void StratPlayer::addPoints(int gain) {
	pointsWon += gain;
}

void StratPlayer::endOfGame(bool clearPoints, vector<Strategie> availableStrats) {
	pointsWon = (clearPoints ? 0 : pointsWon);
	nAdvResp = -1;
	playedC = 2;
	advresponses = vector(4, 0);
	strat = availableStrats[IDStrat];
}

Choice StratPlayer::playStrat(Choice prevAdvMove) {
	switch(strat) {
		case Strategie::ALLD:
			return playAllD();
		break;
		case Strategie::RANDOM:
			return playRandom();
		break;
		case Strategie::TITFORTAT:
			return playTitForTat(prevAdvMove);
		break;
		case Strategie::TESTER:
			return playTester(prevAdvMove);
		break;
		case Strategie::JOSS:
			return playJoss(prevAdvMove);
		break;
		case Strategie::ALTERNATORC:
			return playAlternatorC();
		break;
		case Strategie::FOURT:
			return playFourT(prevAdvMove);
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
	return prevAdvMove == Choice::D ? Choice::D : Choice::C;
}

Choice StratPlayer::playTester(Choice prevAdvMove) {
	playedC = (prevAdvMove == Choice::D || (prevAdvMove != Choice::FT && playedC == -1) ? -1 : (playedC + 1) % 3);
	return playedC == -1 ? playTitForTat(prevAdvMove) : (playedC == 0 ? Choice::D : Choice::C);
}

Choice StratPlayer::playJoss(Choice prevAdvMove) {
	return (prevAdvMove == Choice::FT && rand() < RAND_MAX/10) || prevAdvMove == Choice::D ? Choice::D : Choice::C;
}

Choice StratPlayer::playAlternatorC() {
	playedC = (playedC + 1) % 2;
	return playedC == 0 ? Choice::D : Choice::C;
}

void StratPlayer::chooseNextStrat() {
	int diffRespC = advresponses[1] - advresponses[0];
	int diffRespD = advresponses[3] - advresponses[2];
	//cout << diffRespC << " " << diffRespD << endl;
	if (diffRespC < 0 && diffRespD < 0) { //overall coop
		cout << "Estimation FOUR-T : cooperation leaning. Switch to TESTER." << endl;
		strat = Strategie::TESTER;
	}
	else if (diffRespC > 0 && diffRespD > 0) { //overall deceit
		cout << "Estimation FOUR-T : deceit leaning. Switch to ALL-D." << endl;
		strat = Strategie::ALLD;
	}
	else if (diffRespC < 0 && diffRespD > 0) { //overall tit-for-tat
		cout << "Estimation FOUR-T : tit-for-tat leaning. Switch to TIT-FOR-TAT." << endl;
		strat = Strategie::TITFORTAT;
	}
	else { //overall opposite
		cout << "Estimation FOUR-T : opposite leaning. Switch to ALTERNATOR-C" << endl;
		strat = Strategie::ALTERNATORC;
	}
}

Choice StratPlayer::playFourT(Choice prevAdvMove) {
	nAdvResp++;
	//cout << nAdvResp << endl;
	if (nAdvResp < 16) {
		if (prevAdvMove != Choice::FT) {
			prevAdvMove == Choice::C ? advresponses[0]++ : advresponses[1]++;
			//cout << advresponses[0] << " " << advresponses[1] << " " << advresponses[2] << " " << advresponses[3] << endl;
		}
	} else {
		prevAdvMove == Choice::C ? advresponses[2]++ : advresponses[3]++;
		//cout << advresponses[0] << " " << advresponses[1] << " " << advresponses[2] << " " << advresponses[3] << endl;
		if (nAdvResp >= 30)
			chooseNextStrat();
	}
	return strat != Strategie::FOURT ? playStrat(prevAdvMove) : (nAdvResp < 15 ? Choice::C : Choice::D);
}