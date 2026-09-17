#include <iostream>
#include <cstdlib>
#include <string>

int rand_num(int x, int y){
    return rand() % (y-x+1) + x;
}

std::string getRandomValue(){
    std::string s;

    switch (rand_num(1,13)){
        case 1: s = "Ace"; break;
        case 2: s = "2"; break;
        case 3: s = "3"; break;
        case 4: s = "4"; break;
        case 5: s = "5"; break;
        case 6: s = "6"; break;
        case 7: s = "7"; break;
        case 8: s = "8"; break;
        case 9: s = "9"; break;
        case 10: s = "10"; break;
        case 11: s = "Jack"; break;
        case 12: s = "Queen"; break;
        case 13: s = "King"; break;
    }

    return s;
}

std::string getRandomSuit(){
    std::string s;

    switch (rand_num(1,4)){
        case 1: s = "Heart"; break;
        case 2: s = "Diamonds"; break;
        case 3: s = "Clubs"; break;
        case 4: s = "Spades"; break;
    }

    return s;
}


int main(){
    srand(time(0));

    for (int i = 0; i < 10; i++){
        std::cout << getRandomValue() << " of " << getRandomSuit() << std::endl;
    }
    
    return 0;
}