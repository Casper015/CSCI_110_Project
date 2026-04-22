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

bool isReal(std::string s){
    int startPos = (s.length() > 0 && s[0] == '-' ? 1 : 0);
    int decCnt = 0;
    for (int i = startPos; i < s.length(); i++){
        char c = s[i];
        if (c == '.'){
            if (decCnt>0)
                return false;
            decCnt++;
            continue;
        }
        if (c < '0' || c > '9'){
        return false;
    }
    }
}

int main(){
    while (true){
        std::string s;
        std::getline(std::cin, s);
        if (isInteger(s)){
            std::cout << "The string is an integer." << std::endl;
        } else if (isReal(s)) {
            std::cout << "The string is an real." << std::endl;
        }else {
            std::cout << "The string is not an integer or real." << std::endl;
        }
        return 0;
        }
}