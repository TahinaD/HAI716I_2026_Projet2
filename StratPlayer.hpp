#ifndef STRATPLAYER_H
#define STRATPLAYER_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

enum Strategie {ALLD, RANDOM, TITFORTAT, TESTER, JOSS, ALTERNATORC, FOURT};
enum Choice {C, D, FT};

class StratPlayer
{
	public:
		const int IDStrat;

		StratPlayer(int chosenIDStrat, Strategie chosenStrat);

		string getName(vector<string> stratsNames);
		int getPoints() const;
		void addPoints(int gain);

		Choice playStrat(Choice prevAdvMove);
		Choice playAllD();
		Choice playRandom();
		Choice playTitForTat(Choice prevAdvMove);
		Choice playTester(Choice prevAdvMove);
		Choice playJoss(Choice prevAdvMove);
		Choice playAlternatorC();
		Choice playFourT(Choice prevAdvMove);
		void chooseNextStrat();

	private:
		Strategie strat;
		int pointsWon = 0;
		int playedC = 2;
		int nAdvResp = -1;

		vector<int> advresponses = vector(4, 0);
};

#endif