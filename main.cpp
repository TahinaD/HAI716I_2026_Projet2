#include <algorithm>
#include <cstring>
#include "StratPlayer.hpp"
using namespace std;

vector<Strategie> availableStrats = {ALLD, RANDOM, TITFORTAT, TESTER, JOSS, ALTERNATORC, FOURT};
vector<string> stratsNames = {"ALL-D", "RANDOM", "TIT-FOR-TAT", "TESTER", "JOSS", "ALTERNATOR-C", "FOUR-T"};

int turnResults(Choice playerMove, Choice advMove) {
	int points;
	string stringPMove = (playerMove == Choice::C ? "C" : "D");
	string stringAdvMove = (advMove == Choice::C ? "C" : "D");
	//cout << "Player : " << stringPMove << " Adversaire : " << stringAdvMove << endl;
	if (playerMove == Choice::C)
		points = ((advMove == Choice::C) ? 3 : 0);
	else
		points = ((advMove == Choice::C) ? 5 : 2);
	//cout << points << endl;
	return points;
}

void turn(StratPlayer &p1, StratPlayer &p2, Choice &prevP1Move, Choice &prevP2Move, string p1Name, string p2Name, float noise, bool printTurns) {
	Choice p1Move = p1.playStrat(prevP2Move);
	Choice p2Move = p2.playStrat(prevP1Move);
	p1Move = (float)rand() < (float)RAND_MAX*noise ? (p1Move == Choice::C ? Choice::D : Choice::C) : p1Move;
	p2Move = (float)rand() < (float)RAND_MAX*noise ? (p2Move == Choice::C ? Choice::D : Choice::C) : p2Move;
	p1.addPoints(turnResults(p1Move, p2Move));
	p2.addPoints(turnResults(p2Move, p1Move));
	if (printTurns) {
		cout << p1Name << " joue " << (p1Move == Choice::C ? "C." : "D.") << endl;
		cout << p2Name << " joue " << (p2Move == Choice::C ? "C." : "D.") << endl;
		cout << p1Name << " a " << p1.getPoints() << "." << endl;
		cout << p2Name << " a " << p2.getPoints() << ".\n" << endl;
	}
	prevP1Move = p1Move;
	prevP2Move = p2Move;
}

void partie(StratPlayer &p1, StratPlayer &p2, unsigned int ntour, bool clearPoints, bool addNoise, bool printTurns) {
	string p1Name = p1.getName(stratsNames), p2Name = p2.getName(stratsNames);
	cout << "\n********** " << p1Name << " vs " << p2Name << " **********\n" << endl;
	Choice prevP1Move = Choice::FT, prevP2Move = Choice::FT;
	float noise = (addNoise ? 0.05 : 0.0);
	for (unsigned int tour = 1; tour <= ntour || (ntour == 1 && ((float)rand() < (float)RAND_MAX*0.95)); tour++) {
		if (printTurns)
			cout << "Tour " << tour << endl;
		turn(p1, p2, prevP1Move, prevP2Move, p1Name, p2Name, noise, printTurns);
	}
	cout << "Resultats :" << endl;
	cout << p1Name << " a au total " << p1.getPoints() << " points." << endl;
	cout << p2Name << " a au total " << p2.getPoints() << " points.\n" << endl;
	p1.endOfGame(clearPoints, availableStrats);
	p2.endOfGame(clearPoints, availableStrats);
}

void podium(vector<StratPlayer> players, int nStrats) {
	vector<int> podium = vector<int>(nStrats, 0);
	for (int i = 0; i < nStrats; i++)
		podium[i] = i;
	sort(podium.begin(), podium.end(), 
	[&players](int a, int b)
	{
		return players[a].getPoints() > players[b].getPoints();
	});
	cout << "Classement du tournoi : " << endl;
	for (int k = 0; k < nStrats; k++) {
		cout << k+1 << " : " << players[podium[k]].getName(stratsNames);
		cout << " avec " << players[podium[k]].getPoints() << " points." << endl;
	}
}

int main(int argc, char** argv) {
	if ((argc != 2 && argc != 3) || (strcmp(argv[1], "ft") && strcmp(argv[1], "axelrod") && strcmp(argv[1], "axelrod_base")  && strcmp(argv[1], "axelrod_bruit")  && strcmp(argv[1], "axelrod_horizon_inconnu")) || (argc == 3 && strcmp(argv[2], "print_turns"))) {
		cout << "Argument 1 : " << endl;
		cout << "- ft : FOUR-T contre tous, 40 tours" << endl;
		cout << "- axelrod_base : tournoi Axelrod tous contre tous, 200 tours, sans FOUR-T et ALTERNATOR-C" << endl;
		cout << "- axelrod : tournoi Axelrod tous contre tous, 200 tours" << endl;
		cout << "- axelrod_bruit : tournoi Axelrod tous contre tous, 200 tours, probabilite 0.5 d'inverser un coup" << endl;
		cout << "- axelrod_horizon_inconnu : tournoi Axelrod tous contre tous, probabilite 0.95 de continuer la partie." << endl;
		cout << "Argument 2 (optionel) : " << endl;
		cout << "- print_turns : affiche les coups de chaque tours et le total des points apres le tour" << endl;
		return 0;
	}
	bool printTurns = (argc == 3 && !strcmp(argv[2], "print_turns"));
	srand(40);
	
	unsigned int ntour;
	int nStrats = availableStrats.size();
	vector<StratPlayer> players;
	for (int k = 0; k < nStrats; k++) {
		players.push_back(StratPlayer(k, availableStrats[k]));
	}

	if (!strcmp(argv[1], "ft")) {
		ntour = 40;
		for (int k = 0; k < nStrats - 1; k++) {
			partie(players[k], players[nStrats - 1], ntour, true, false, printTurns);
		}
		return 0;
	}

	ntour = (!strcmp(argv[1], "axelrod_horizon_inconnu") ? 1 : 200);
	nStrats -= (!strcmp(argv[1], "axelrod_base") ? 2 : 0);
	for (int i = 0; i < nStrats; i++) {
		for (int j = i+1; j < nStrats; j++)
			partie(players[i], players[j], ntour, false, !strcmp(argv[1], "axelrod_bruit"), printTurns);
	}
	podium(players, nStrats);
	return 0;
}
