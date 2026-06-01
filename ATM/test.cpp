#include <iostream>
#include <string>

int main(){
    std::string name[] = {"Abe", "Bob", "Carl"};
    name[2] = "John";

    int i = -20;
    while (i <= 20){
        std::cout << i << std::endl;
        i+=2;
    }
    for(int i = -20; i<=20;i+=2){
        std::cout << i << std::endl;
    }
    
}

bool esists(std::string s){
    std::string colors[] = {"red", "green", "blue"};
    for (int i; i<= sizeof(colors) / sizeof(colors[0]); i++)
        if (colors[i] == s)
            return true;
    return false;
}
