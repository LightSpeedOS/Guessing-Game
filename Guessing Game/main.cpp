#include "Includes.h"
#include "Logic.h"

using namespace std;

auto main() -> int
{
	initConsole();
	SetConsoleTitleA("Guess My Number");

	vector<int>numbers;
	Player player{};


	int option;

	while (true)
	{
		clear();

		cout << "Welcome To Guess My Number! | Balance: $";
		if (player.money > 0)
		{
			cout << green << player.money << reset << endl;
		}

		else if (player.money < 0)
		{
			cout << red << player.money << reset << endl;
		}

		else
		{
			cout << player.money << endl;
		}
		space();

		cout << "[1] Play" << endl;
		cout << "[2] Deposit" << endl;
		cout << "[3] Vault" << endl;
		cout << "[4] Loan" << endl;
		cout << "[5] Profit & Loss (PNL)" << endl;
		cout << "[6] " << red << "Quit" << reset << endl;
		cout << "> ";
		cin >> option;

		if (input())
		{
			continue;
		}

		switch (option)
		{
		case Play:
		{
			clear();
			cout << "How much would you like to bet?" << endl;
			cout << "Amount:";
			cin >> player.bet;

			if (player.bet > player.money || player.bet < 0)
			{
				space();
				cout << "[!] Invalid Bet" << endl;
				pause();
				continue;
			}

			if (player.bet > 25000)
			{
				space();
				cout << "[!] Bet exceeded $25000" << endl;
				pause();
				continue;
			}

			if (player.bet == 0)
			{
				space();
				cout << "You cannot bet 0" << endl;
				pause();
				continue;
			}

			if (player.bet < 10)
			{
				cout << "[!] $10 is minimum bet." << endl;
			}

			clear();

			cout << "The Computer Will Have 20 Guesses! | Bet Amount: " << player.bet << endl;
			space();

			cout << "Guess a Number [ 10 - 100 ]" << endl;
			cout << "Number:";
			cin >> player.guess;
			
			if (player.guess < 0 || player.guess > 100)
			{
				space();
				cout << "[!] Invalid Number" << endl;
				pause();
				continue;
			}

			for (size_t i = 0; i < 20; i++)
			{
				int computer = ((rand() % 10000) / 100 + 1);
				cout << "Computer: " << setw(3) << computer << " | " << "Guess # " << i + 1 << endl;
				this_thread::sleep_for(chrono::milliseconds(500));
				numbers.push_back(computer);
			}

			bool computerFound = false;
			int matchedAt = 0;

			for (size_t i = 0; i < numbers.size(); i++)
			{
				if (player.guess == numbers[i])
				{
					computerFound = true;
					matchedAt = i + 1;
					break;
				}

			}

			if (computerFound)
			{ 
				space();
				cout << "You " << red << "Lose! " << reset << " || The computer found you on guess # " << matchedAt << endl;
				int moneySnapshot = player.money;
				player.Loss();
				cout << moneySnapshot << " -> " << player.money << " (" << red << "-" << player.bet << reset << ")" << endl;
				computerFound = false;
				numbers.clear();
				getKey();
				clear();
			}
			
			else
			{
				cout << "You Win!" << endl;
				int moneySnapshot = player.money;
				player.Wins(1.2f);
				cout << moneySnapshot << " -> " << player.money << " (" << green << "+" << player.bet * (1.2 - 1) << reset << ")" << endl;
				numbers.clear();
				getKey(); 
				clear();
			}
			break;
		}

		case Deposit:
		{
			clear();

			cout << "Balance: $" << player.money << endl;
			space();

			cout << "How much would you like to deposit? [ 100 - 5000 ]" << endl;
			cout << "$";
			cin >> player.depo;

			if (player.depo < 100 || player.depo > 5000)
			{
				cout << "[!] Invalid Input" << endl;
				pause();
				break;
			}

			int moneySnap = player.money;
			player.money += player.depo;
			cout << "Successfully Deposited " << moneySnap << " -> " << player.money << " (" << green << "+" << player.depo << reset << ")" << endl;
			player.depo = 0;
			getKey();
			break;
		}

		case Vault:
			clear();

		break;
		
		case Loan:

		break;

		case PNL:
			player.Stats();
		break;

		case Quit:
			shutDown();
		break;
		}
	}
}