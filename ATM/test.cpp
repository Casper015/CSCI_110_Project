#include <iostream>
#include <string>

bool isInteger(std::string s){

    for (int i = 0; i < s.length(); i++){
        if (s[i] < '0' || s[i] > '9'){
            return false;
        }
    }
    return true;

}

int main(){
    std::string s = "12345";
    if (isInteger(s)){
        std::cout << "The string is an integer." << std::endl;
    } else {
        std::cout << "The string is not an integer." << std::endl;
    }
    return 0;
}