/*
// Declare the necessary variables.
Declare Integer hits
Declare Integer atBat
Declare Real battingAverage

// Get the number of hits.
Display "Enter the player's number of hits."
Input hits

// Get the number of times at bat.
Display "Enter the player's number of times at bat."
Input atBat

// Calculate the batting average.
Set battingAverage = hits / atBat  

// Display the batting average.
Display "The player's batting average is ", battingAverage
*/

#include <iostream>

//using namespace std;

int main() {

    int hits;
    std::cout << "Player's number of hits: \n" ; // or << std::endl
    std::cin >> hits;

    int at_bat;
    std::cout << "Player's number of times at bat：" << std::endl ;
    std::cin >> at_bat;

    /* batting_average = hits / at_bat;

    Don't change the variables from int to double at the top of the program; instead, 
    just temporarily change them to doubles right here in the math formula.

    Temporarily treat the integer as a double for this calculation to prevent integer division.*/

    double batting_average;
    batting_average = 1.0 * hits / at_bat; 
    // or double battingAverage = double(hits) / at_bat;

    std::cout << "The player's batting average is " << batting_average;
    // or std::cout << "The player's batting average is " << 1.0 * hits / at_bat);
}