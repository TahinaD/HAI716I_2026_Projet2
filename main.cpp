#include <iostream>
#include "StratPlayer.hpp"
using namespace std;

vector<Strategie> availableStrats = {ALLD, RANDOM, TITFORTAT, TESTER, JOSS};
vector<string> stratsNames = {"ALL-D", "RANDOM", "TIT-FOR-TAT", "TESTER", "JOSS"};

int turnResults(Choice playerMove, Choice advMove) {
	int points;
	string stringPMove = (playerMove == Choice::C ? "C" : "D");
	string stringAdvMove = (advMove == Choice::C ? "C" : "D");
	//cout << "Player : " << stringPMove << " Adversaire : " << stringAdvMove << endl;
	if (playerMove == Choice::C)
		points = ((advMove == Choice::C) ? 3 : 0);
	else
		points = ((advMove == Choice::C) ? 5 : 2);
	cout << points << endl;
	return points;
}

void partie(StratPlayer &p1, StratPlayer &p2, unsigned int ntour) {
	string p1Name = p1.getName(stratsNames), p2Name = p2.getName(stratsNames);
	cout << p1Name << " vs " << p2Name << ".\n" << endl;
	Choice p1Move, p2Move;
	Choice prevP1Move = Choice::FT, prevP2Move = Choice::FT;
	for (unsigned int tour = 0; tour < ntour; tour++) {
		cout << "Tour " << tour << endl;
		p1Move = p1.playStrat(prevP2Move);
		p2Move = p2.playStrat(prevP1Move);
		cout << p1Name << " joue " << (p1Move == Choice::C ? "C." : "D.") << endl;
		cout << p2Name << " joue " << (p2Move == Choice::C ? "C." : "D.") << endl;
		p1.addPoints(turnResults(p1Move, p2Move));
		p2.addPoints(turnResults(p2Move, p1Move));
		cout << p1Name << " a " << p1.getPoints() << "." << endl;
		cout << p2Name << " a " << p2.getPoints() << ".\n" << endl;
		prevP1Move = p1Move;
		prevP2Move = p2Move;
	}
	cout << "Fin de la partie. Resultats :" << endl;
	cout << p1Name << " a " << p1.getPoints() << "." << endl;
	cout << p2Name << " a " << p2.getPoints() << "." << endl;
	if (p1.getPoints() == p2.getPoints())
		cout << "Egalite.\n" << endl;
	else
		cout << "Le vainqueur est " << (p1.getPoints() > p2.getPoints() ? p1Name : p2Name) << ".\n" << endl;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Entrez une graine." << endl;
		return 0;
	}

	srand(atoi(argv[1]));
	
	unsigned int ntour = 20;
	//nStrats = availableStrats.size();
	vector<StratPlayer> players;
	for (int i = 0; i < 2; i++) {
		players.push_back(StratPlayer(i, availableStrats[i]));
	}
	partie(players[0], players[1], ntour);
	return 0;
}
