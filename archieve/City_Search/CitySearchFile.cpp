#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct City
{
    std::string name;
    std::string state;
    int pop;
};
std::vector<City> cities;

void readCities()
{
    std::string name, state;
    int pop;

    std::ifstream f;
    f.open("uscities.csv");
    if(!f.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }
    
    while (true)
    {
        std::string city, state;
        int pop;

        std::getline(f, city, ',');
        std::getline(f, state, ',');
        f >> pop;
        f.ignore(100, '\n'); // Ignore the newline character
        City c = {city, state, pop};
        cities.push_back(c);
        if (f.eof()) break;
    }
}

int main()
{
    readCities();
    std::cout << cities.size() << " cities read." << std::endl;
}