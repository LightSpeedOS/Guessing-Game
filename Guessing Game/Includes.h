#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <iomanip>


using namespace std;


void clear()
{
	system("CLS");
}

void pause()
{
	this_thread::sleep_for(chrono::seconds(2));
	clear();
}

void space()
{
	cout << endl;
}

void getKey()
{
	space();
	cout << "Press any key to return." << endl;
	_getch();
}

bool input()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		clear();
		cout << "[!] Invalid Input" << endl;
		pause();
		return true;
	}
	return false;
}


void initConsole()
{

	srand(time(0));

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void shutDown()
{
	int result = MessageBoxA(NULL, "Are you sure?", "Warning!", MB_YESNO | MB_ICONHAND);
	clear();

	if (result == IDYES)
	{
		cout << "[!] Shutting Down";
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << ".";
		exit(0);
	}

	else if (result == IDNO)
	{
		cout << "[+] Aborting";
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << ".";
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << ".";
		return;
	}
}


// -- Text colours --
const char* black = "\033[30m";
const char* red = "\033[31m";
const char* green = "\033[32m";
const char* yellow = "\033[33m";
const char* blue = "\033[34m";
const char* magenta = "\033[35m";
const char* cyan = "\033[36m";
const char* white = "\033[37m";

// -- Bright versions --
const char* brightRed = "\033[91m";
const char* brightGreen = "\033[92m";
const char* brightYellow = "\033[93m";
const char* brightBlue = "\033[94m";
const char* brightMagenta = "\033[95m";
const char* brightCyan = "\033[96m";
const char* brightWhite = "\033[97m";

// -- Styles --
const char* bold = "\033[1m";
const char* underline = "\033[4m";
const char* reset = "\033[0m";
