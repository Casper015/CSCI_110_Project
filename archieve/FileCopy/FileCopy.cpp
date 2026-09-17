
#include <iostream>
#include <fstream>

int main(){
    std::ifstream f1;
    f1.open("loremipsum.txt");
    if(!f1.is_open()){
        std::cout<<"Failed to open file1.txt"<<std::endl;
        return 1;
    }

    std::ifstream f2;
    f2.open("pg76071.txt");
    if(!f2.is_open()){
        std::cout<<"Failed to open file2.txt"<<std::endl;
        return 1;
    }

    std::ofstream f3;
    f3.open("bigdata2.txt");
    if(!f3.is_open()){
        std::cout<<"Failed to open file3.txt"<<std::endl;
        return 1;
    }
    std::string line;
    while(std::getline(f1, line)){
        f3<<line<<std::endl;
    }
    f1.close();

    while (std::getline(f2, line)){
        f3<<line<<std::endl;
    }
    f2.close();
    f3.close();
}