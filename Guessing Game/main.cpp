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
		cout << "[6] Settings" << endl;
		cout << "[7] " << red << "Quit" << reset << endl;
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
			numbers.clear();

			if (player.money == 0)
			{
				clear();
				cout << "[!] You Need To Deposit" << endl;
				pause();
				break;
			}

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
				clear();
				cout << "[!] $10 is minimum bet." << endl;
				pause();
				break;
			}

			clear();

			cout << "The Computer Will Have 20 Guesses! | Bet Amount: " << player.bet << endl;
			space();

			cout << "Guess a Number [ 10 - 100 ]" << endl;
			cout << "Number:";
			cin >> player.guess;
			
			if (player.guess < 1 || player.guess > 100)
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

				if (!player.fastMode) this_thread::sleep_for(chrono::milliseconds(500));
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
				float moneySnapshot = player.money;
				player.Loss();
				cout << moneySnapshot << " -> " << player.money << " (" << red << "-" << player.bet << reset << ")" << endl;
				computerFound = false;
				getKey();
				clear();
			}
			
			else
			{
				cout << "You Win!" << endl;
				float moneySnapshot = player.money;
				player.Wins(1.2f);
				cout << moneySnapshot << " -> " << player.money << " (" << green << "+" << player.money - moneySnapshot << reset << ")" << endl;
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

			float moneySnap = player.money;
			player.money += player.depo;
			cout << "Successfully Deposited " << moneySnap << " -> " << player.money << " (" << green << "+" << player.depo << reset << ")" << endl;
			player.depo = 0;
			getKey();
			break;
		}

		case Vault:
		{
			clear();
			
			string passCode;
			int pinNumber;
			int vaultOption;
			bool failed = false;
			bool hasZero = false;;

			cout << "Money Balance: " << player.money << " | Vault Balance : " << player.vault << endl;
			space();

			cout << "[1] Deposit" << endl;
			cout << "[2] Withdrawal" << endl;
			cout << "> ";
			cin >> vaultOption;

			if (input())
			{
				continue;
			}
			switch (vaultOption)
			{


			case Depo:
			{
				clear();

				if (player.hasPasscode == false)
				{
					cout << "Create a Six Digit Pin" << endl;
					cout << "Pin:";
					cin >> passCode;

					if (input())
					{
						continue;
					}

					for (size_t j = 0; j < passCode.size(); j++)
					{
						if (passCode[j] == '0')
						{
							hasZero = true;
						}
					}

					if (hasZero)
					{
						space();
						cout << "Passcode cannot contain any zero's" << endl;
						hasZero = false;
						pause();
						continue;
					}

					if (passCode.size() != 6)
					{
						space();
						cout << "[!] Passcode Must Contain Six Digits." << endl;
						pause();
						break;
					}


					try
					{
						pinNumber = stoi(passCode);
						cout << "[+] " << green << "Successfully " << reset << "Created Passcode | Passcode: " << passCode << endl;
						player.hasPasscode = true;
						getKey();
					}
					catch (invalid_argument&)
					{
						clear();
						cout << "[!] Error Numbers Only" << endl;
						pause();
						failed = true;
					}
					catch (out_of_range&)
					{
						clear();
						cout << "[!] Six Digits Only." << endl;
						pause();
						failed = true;
					}

					if (failed)
					{
						failed = false;
						continue;
					}
					break;

				}
				clear();

				int toVault = 0;
				int vaultSnap = 0;
				cout << "How much money would you like to vault | Vault Balance: $" << player.vault << endl;
				space();

				cout << "$";
				cin >> toVault;

				if (toVault > player.money)
				{
					clear();
					cout << "[!] Error, Insufficient Balance" << endl;
					pause();
					break;
				}

				if (toVault < 0)
				{
					clear();
					cout << "[!] Error, You cannot vault a negative number" << endl;
					pause();
					break;
				}

				cout << "[+] " << green << "Successfully " << reset << "Vaulted " << toVault << endl;
				player.vault += toVault;
				player.money -= toVault;
				cout << "Vault Balance: $" << player.vault << endl;
				getKey();
				break;
			}

			case Withdrawal:
			{
				clear();

				if (!player.vaultOpen)
				{
					if (player.hasPasscode = true)
					{
						int passcodeCheck;
						cout << "Passcode:";
						cin >> passcodeCheck;

						int invalid = 0;

						if (passcodeCheck != pinNumber)
						{
							cout << "[!] Invalid Passcode! | " << invalid - 3 << " Attempts Remaining." << endl;
							invalid++;
							continue;

							if (invalid == 3)
							{
								clear();
								cout << "[!] Try again Later." << endl;
								pause();
								break;
							}
						}
					}
				}

				if (player.vault == 0)
				{
					clear();
					cout << "[!] Error, Cannot withdrawal." << endl;
					cout << "Vault Balance:" << player.vault << endl;
					pause();
					break;
				}

				float fromVault;
				cout << "How much would you like to withdrawal?" << endl;
				cout << "Amount: $";
				cin >> fromVault;

				if (input())
				{
					continue;
				}

				if (fromVault == 0 || fromVault < 0 || fromVault > player.vault)
				{
					clear();
					cout << "[!] Error, Invalid Optoion" << endl;
					pause();
					break;
				}

				space();
				float vaultSnap = player.vault;
				player.money += fromVault;
				player.vault -= fromVault;
				cout << "[+] " << green << "Successfully" << reset << " Withdrawed " << fromVault << endl;
				
				cout << vaultSnap << " -> " << player.vault << " (" << red << "-" << fromVault << reset << ")" << endl;
			}

			}
		}
		break;
		
		case Loan:
			clear();

		break;

		case PNL:
			player.Stats();
		break;

		case Settings:
		{
			clear();
			bool inSettings = true;

			while (inSettings)
			{
				clear();
				if (player.vaultOpen) cout << "[1] Keep Vault Open -> " << green << "On" << reset << endl;
				else cout << "[1] Keep Vault Open -> " << red << "Off" << reset << endl;

				if (player.fastMode) cout << "[2] Instant Bot Gusses -> " << green << "On" << reset << endl;
				else cout << "[2] Instant Bot Gusses -> " << red << "Off" << reset << endl;
				cout << "[Q] " << red << "Quit" << reset << endl;
				char key = _getch();

				switch (tolower(key))
				{
				case '1':
					if (!player.vaultOpen) player.vaultOpen = true;
					else player.vaultOpen = false;
					break;

				case '2':
					if (!player.fastMode) player.fastMode = true;
					else player.fastMode = false;
					break;

				case 'q':
					inSettings = false;
					break;
				}
			}
			break;
		}

		case Quit:
			shutDown();
		break;

		default:
			invalid();
			break;
		}
	}
}