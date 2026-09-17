#include <iostream>
#include <string>

int main(){
    const int HEIGHT =3;
    char grid[HEIGHT][3];


    for (int r = 0; r < HEIGHT; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            grid[r][c] = ' ';
        }
    }
    
    int row, col;
    char symbol;

    while (std::cout << "Enter row col symbol: ", std::cin >> row >> col >> symbol)
    {

    
    if (std::cin.fail())
    {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(1000, '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter row and column as integers and symbol as a character." << std::endl;
        continue;
    }

    if (row < 0 || row >= HEIGHT || col < 0 || col >= 3)
    {
        std::cout << "Invalid input" << std::endl;
        continue;
    }

    grid[row][col] = symbol;

    std::cout << "+---+---+---+" << std::endl;
    for (int r = 0; r < HEIGHT; r++)
    {
        std::cout << "| ";
        for (int c = 0; c < 3; c++)
        {
            std::cout << grid[r][c] << " | ";
        }
        std::cout << std::endl;
        std::cout << "+---+---+---+" << std::endl;
    }
    }
}