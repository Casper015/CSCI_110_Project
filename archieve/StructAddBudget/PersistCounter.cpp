#include <fstream>
#include <iostream>
#include <string>

int loadCounter(const std::string& fileName){
    std::ifstream input(fileName);
    int counter = 0;

    if (input >> counter){
        return counter;
    }

    return 0;
}

void saveCounter(const std::string& fileName, int counter){
    std::ofstream output(fileName);
    output << counter;
}

int main(){
    const std::string fileName = "counter.txt";
    int counter = loadCounter(fileName);

    std::cout << "Current counter: " << counter << std::endl;
    std::cout << "Press ENTER to increment. Press Ctrl+Z then Enter to quit." << std::endl;

    std::string line;
    while (true){
        std::getline(std::cin, line);
        if (!std::cin){
            break;
        }

        counter++;
        std::cout << counter << std::endl;
        saveCounter(fileName, counter);
    }

    return 0;
}
