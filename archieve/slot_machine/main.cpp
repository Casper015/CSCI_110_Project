/*
* SlotMachine.cpp - Console app modeled after https://www.freeslots.com/Slot7.htm for educational purposes.
* 
* Created by: Chun Wong
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXBET = 3;
const int INITCREDIT = 10;

// Global variables to skip parameter passing
int Credit = INITCREDIT;			// Coins available to play
int NextBet = 0;					// Next bet
int LastBet = MAXBET;				// Last bet
int LastPayout = 0;					// Last payout
string Symbol1, Symbol2, Symbol3;	// Reel symbols

// Function prototypes
int displayScreen();
void displayReels();
void displayPayoutTable();
void showStatistics();
void betOne();
void betMax();
void spinReel();
void getRandomSymbol(string&, string&, string&);
string getRandomSymbol();
int getPayoutRatio();
bool isThreeOfAKind(string, string, string, string);
bool isTwoOfAKind(string, string, string, string);
bool isAny(string, string, string, string);
void clearScreen();

int main()
{
	// Seed random number generator
	srand(static_cast<int>(time(nullptr)));

	bool inPlay = true;	// Keep playing as long as inPlay=true
	while (inPlay)
	{
		switch (displayScreen())
		{
			case 1: betOne(); break;
			case 2: betMax(); break;
			case 3: spinReel(); break;
			case 4: displayPayoutTable(); break;
			case 5: showStatistics(); break;
			case 6: inPlay = false; break;	// Quit
		}

		// Exit game if there's no more credit and there's no next bet
		if (Credit == 0 && NextBet == 0)
		{
			cout << endl << "YOU HAVE NO MORE CREDIT. GAME OVER!" << endl;
			inPlay = false;
		}
	}
}

// Display entire screen including menu choices. Prompt user for choice and returns choice
int displayScreen()
{
	// Keep prompting if user enters invalid entry
	int option;
	while (true)
	{
		clearScreen();
		cout << "***** SIMPLE SLOTS *****" << endl;
		displayReels();
		
		cout << "Credits: " << Credit << ", Next Bet: " << NextBet << endl << endl;

		// Display menu choices
		cout << "1. Add 1 Bet" << endl;
		cout << "2. Bet Max and Spin" << endl;
		cout << "3. Spin Reel" << endl;
		cout << "4. Show Pay Table" << endl;
		cout << "5. Statistics" << endl;
		cout << "6. Quit" << endl;
		cout << "Choose 1-5: ";
		cin >> option;
		cin.ignore(100, '\n');
		if (cin.good())
			break;

		cout << "Invalid choice. Try again." << endl;
		cin.clear();
	}

	return option;
}

// Format the reel symbols in ASCII boxes
void displayReels()
{
	// Display blank character if no symbols
	string s1 = Symbol1.empty() ? "  " : Symbol1;
	string s2 = Symbol2.empty() ? "  " : Symbol2;
	string s3 = Symbol3.empty() ? "  " : Symbol3;

	cout << "+" << string(s1.length(), '-') << "+ ";
	cout << "+" << string(s2.length(), '-') << "+ ";
	cout << "+" << string(s3.length(), '-') << "+" << endl;

	cout << "|" << s1 << "| |" << s2 << "| |" << s3 << "|" << endl;

	cout << "+" << string(s1.length(), '-') << "+ ";
	cout << "+" << string(s2.length(), '-') << "+ ";
	cout << "+" << string(s3.length(), '-') << "+" << endl;

	cout << "Winner Paid: " << LastPayout << ", Coins Played: " << LastBet << endl << endl;
}

// Display payout multiple
void displayPayoutTable()
{
	const int wLabel = 12, wValue = 10;
	clearScreen();
	cout << "PAYOUT TABLE" << endl;
	cout << setfill('.');
	cout << setw(wLabel) << left << "3 4's" << setw(wValue) << right << "4000" << endl;
	cout << setw(wLabel) << left << "3 hats" << setw(wValue) << right << "800" << endl;
	cout << setw(wLabel) << left << "3 7's" << setw(wValue) << right << "100" << endl;
	cout << setw(wLabel) << left << "3 bars" << setw(wValue) << right << "30" << endl;
	cout << setw(wLabel) << left << "3 cherries" << setw(wValue) << right << "10" << endl;
	cout << setw(wLabel) << left << "2 cherries" << setw(wValue) << right << "5" << endl;
	cout << setw(wLabel) << left << "1 cherry" << setw(wValue) << right << "2" << endl;
	cout << endl;
	cout << "Press ENTER to continue...";
	string s;
	getline(cin, s);
}

// betOne bets one credit. Can't bet if bet is already at MAXBET or no credit.
void betOne()
{
	if (NextBet < MAXBET && Credit > 0)
	{
		Credit--;
		NextBet++;
	}
}

// betMax bets up to MAXBET and automatically spins the reel. Can't add more bet if bet is already at MAXBET or no credit.
void betMax()
{
	if (NextBet < MAXBET)
	{
		int addlBet = MAXBET - NextBet;
		if (addlBet > Credit)
			addlBet = Credit;

		Credit -= addlBet;
		NextBet += addlBet;
	}

	spinReel();
}

// Randomizes reel symbols. Updates Credit based on payout. Remembers LastBet and LastPayout. Reset Bet to 0.
void spinReel()
{
	if (NextBet == 0)
	{
		NextBet = LastBet;
		if (NextBet > Credit)
			NextBet = Credit;
		Credit -= NextBet;
	}

	getRandomSymbol(Symbol1, Symbol2, Symbol3);

	int payout = NextBet * getPayoutRatio();

	Credit += payout;

	LastPayout = payout;
	LastBet = NextBet;
	NextBet = 0;
}

void getRandomSymbol(string& s1, string& s2, string& s3)
{
	s1 = getRandomSymbol();
	s2 = getRandomSymbol();
	s3 = getRandomSymbol();
}

// Decide on a reel symbol based on some probability calculation
string getRandomSymbol()
{
	string symbol;

	int n = rand() % 100;
	if (n > 90) symbol = "4";
	else if (n > 75) symbol = "hat";
	else if (n > 55) symbol = "7";
	else if (n > 30) symbol = "bar";
	else if (n > 15) symbol = "cherry";
	else symbol = "";

	return symbol;
}

// Calculate payout based on Symbols and Bet
int getPayoutRatio()
{
	int payoutRatio = 0;

	// Triple 4
	if (isThreeOfAKind("4", Symbol1, Symbol2, Symbol3))
		payoutRatio = 4000;
	// Triple hat
	else if (isThreeOfAKind("hat", Symbol1, Symbol2, Symbol3))
		payoutRatio = 800;
	// Triple 7
	else if (isThreeOfAKind("7", Symbol1, Symbol2, Symbol3))
		payoutRatio = 100;
	// Triple bar
	else if (isThreeOfAKind("bar", Symbol1, Symbol2, Symbol3))
		payoutRatio = 30;
	// Triple cherry
	else if (isThreeOfAKind("cherry", Symbol1, Symbol2, Symbol3))
		payoutRatio = 10;
	// Double cherry
	else if (isTwoOfAKind("cherry", Symbol1, Symbol2, Symbol3))
		payoutRatio = 5;
	// Single cherry
	else if (isAny("cherry", Symbol1, Symbol2, Symbol3))
		payoutRatio = 2;

	return payoutRatio;
}

void showStatistics()
{
	const int iterations = 100000;
	string s1, s2, s3;
	int triple4 = 0, tripleHat = 0, triple7 = 0, tripleBar = 0, tripleCherry = 0, doubleCherry = 0, singleCherry = 0;
	for (int i = 0; i < iterations; i++)
	{
		getRandomSymbol(s1, s2, s3);
		if (isThreeOfAKind("4", s1, s2, s3))
			triple4++;
		else if (isThreeOfAKind("hat", s1, s2, s3))
			tripleHat++;
		else if (isThreeOfAKind("7", s1, s2, s3))
			triple7++;
		else if (isThreeOfAKind("bar", s1, s2, s3))
			tripleBar++;
		else if (isThreeOfAKind("cherry", s1, s2, s3))
			tripleCherry++;
		else if (isTwoOfAKind("cherry", s1, s2, s3))
			doubleCherry++;
		else if (isAny("cherry", s1, s2, s3))
			singleCherry++;
	}
	cout << "STATISTICS" << endl;
	cout << "3 4's: " << (100.0 * triple4 / iterations) << "%" << endl;
	cout << "3 hats: " << (100.0 * tripleHat / iterations) << "%" << endl;
	cout << "3 7's: " << (100.0 * triple7 / iterations) << "%" << endl;
	cout << "3 bars: " << (100.0 * tripleBar / iterations) << "%" << endl;
	cout << "3 cherries: " << (100.0 * tripleCherry / iterations) << "%" << endl;
	cout << "2 cherries: " << (100.0 * doubleCherry / iterations) << "%" << endl;
	cout << "1 cherry: " << (100.0 * singleCherry / iterations) << "%" << endl;
	cout << endl;
	cout << "Press ENTER to continue...";
	string s;
	getline(cin, s);
}

bool isThreeOfAKind(string target, string s1, string s2, string s3)
{
	return (s1 == target && s2 == target && s3 == target);
}

bool isTwoOfAKind(string target, string s1, string s2, string s3)
{
	return ((s1 == target && s2 == target) || (s2 == target && s3 == target) || (s1 == target && s3 == target));
}

bool isAny(string target, string s1, string s2, string s3)
{
	return (s1 == target || s2 == target || s3 == target);
}

// Clear screen using ANSI terminal codes
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
void clearScreen()
{
	const string CSI = "\x1b[";	// ANSI terminal escape sequence

	cout << CSI << "2J";
	cout << CSI << "1;1H";
}