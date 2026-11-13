#ifndef STRATPLAYER_H
#define STRATPLAYER_H
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

enum Strategie {ALLD, RANDOM, TITFORTAT, TESTER, JOSS};
enum Choice {C, D, FT};

class StratPlayer
{
	public:
		const int IDStrat;
		const Strategie strat;

		StratPlayer(int chosenIDStrat, Strategie chosenStrat);
		StratPlayer operator=(const StratPlayer& other);

		string getName(vector<string> stratsNames);
		int getPoints();
		void addPoints(int gain);
		void increaseWins();

		Choice playStrat(Choice preAdvMove);
		Choice playAllD();
		Choice playRandom();
		Choice playTitForTat(Choice prevAdvMove);
		Choice playTester(Choice preAdvMove);
		Choice playJoss(Choice preAdvMove);

	private:
		int gamesWon = 0;
		int pointsWon = 0;
		int playedC = 0;
};

#endif