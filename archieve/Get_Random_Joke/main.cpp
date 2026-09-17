#include <iostream>
#include <string>

#include "csci110-wong.h"

int main(){

    while (true){

    std::string setup, punchline;
    getRandomJoke(setup, punchline);

    std::cout << "Q: " << setup << std::endl;
    
    string s;
    std::getline(cin, s);

    std::cout << "A: " << punchline << std::endl;
    
}
}