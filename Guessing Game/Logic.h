#pragma once

struct Player
{
	string name = "Jamaal";
	int money = 500;
	int bet;
	int vault;
	int guess;

	float gameWin;
	float gameLoss;
	float gamesPlayed;

	void Wins(float multiplier)
	{
		money += (bet * multiplier) - 1;
		gameWin++;
		gamesPlayed++;
	}

	void Loss()
	{
		money -= bet;
		gameLoss++;
		gamesPlayed++;
	}
	
	int netWorth()
	{
		return money + vault;
	}

	float winRate()
	{

		if (gamesPlayed == 0) return 0.0f;

		float winrate = (gameWin / gamesPlayed) * 100.0f;
		
		if (winrate > 50.0f)
		{
			cout << green << winrate << reset;
		}
		
		else if (winrate < 50.0f)
		{
			cout << red << winrate << reset;
		}

	}

	void stats()
	{
		cout << "Money: " << money << endl;
		cout << "Vault: " << vault << endl;
		cout << "NetWorth: " << netWorth() << endl;
		space(); 

		cout << "Wins: " << gameWin << endl;
		cout << "Losses: " << gameLoss << endl;
		cout << "Games Played: " << gamesPlayed << endl;
		cout << "Win Rate: " << winRate() << "%" << endl;
	}
};

enum mainMenu
{
	Play = 1,
	Deposit,
	Vault,
	Loan,
	PNL,
	Quit,
};

enum gameDifficulties
{
	Easy = 1,
	Medium,
	Hard,
	Extreme
};