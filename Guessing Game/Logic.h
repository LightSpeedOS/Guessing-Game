#pragma once

struct Player
{
	string name = "Jamaal";
	float money = 500;
	int bet;
	int vault;
	int guess;
	int depo;

	bool hasPasscode = false;

	string vaultCode;

	float gameWin;
	float gameLoss;
	float gamesPlayed;

	void Wins(float multiplier)
	{
		money += bet * (multiplier - 1);
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

			float winrate = (gameWin / gamesPlayed) * 100.0f;

			if (gamesPlayed == 0) return 0.0f;
			return winrate;

	}

	void Stats()
	{
		clear();
		cout << brightYellow << name << reset << "'s PNL" << endl;
		space();

		cout << "Money: " << money << endl;
		cout << "Vault: " << vault << endl;
		cout << "NetWorth: " << netWorth() << endl;
		space(); 

		cout << "Wins: " << gameWin << endl;
		cout << "Losses: " << gameLoss << endl;
		cout << "Games Played: " << gamesPlayed << endl;
		
		float rate = winRate();
		cout << "Win Rate: ";
		if (rate >= 50.0f) cout << green << rate << "%" << reset << endl;
		else if (rate < 50) cout << red << rate << "%" << reset << endl;
		else cout << rate << endl;

		getKey();
		clear();
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