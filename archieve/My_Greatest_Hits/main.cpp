#include <iostream>
#include <string>
#include <cstdlib>

void runCppModule(const std::string& fileName) {
    std::string outputExe = "output\\selected_module.exe";
    std::string command = "g++ \"" + fileName + "\" -o \"" + outputExe + "\" && \"" + outputExe + "\"";

    int result = std::system(command.c_str());
    if (result != 0) {
        std::cout << "Could not compile or run: " << fileName << std::endl;
    }
}
/*
declare choice

display 
“**** MY GREATEST HITS ****
1. Hello World
2. Shipping Charges
3. Count Up and Down
4. Quit

do
switch 
    choice = 1 : display Hello World!
    choice = 2 : display Shipping Charges
    choice = 3 : Count Up and Down
    choice = 4 : display Quit 
    others = Invalid choice. Try again.
while (choice not equal to 4)
*/


int main() {
    int choice;

    std::string fileA = "Hello World!.cpp";
    std::string fileB = "Shipping Charges.cpp";
    std::string fileC = "Count Up and Down.cpp";

    do {
        std::cout << "\n**** MY GREATEST HITS ****\n"
                  << "1. " << fileA << "\n"
                  << "2. " << fileB << "\n"
                  << "3. " << fileC << "\n"
                  << "4. Quit\n"
                  << "Enter choice (1-4): ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                runCppModule(fileA);
                break;
            case 2:
                runCppModule(fileB);
                break;
            case 3:
                runCppModule(fileC);
                break;
            case 4:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }

    } while (choice != 4);

    return 0;
}
