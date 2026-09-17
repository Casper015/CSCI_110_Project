#include <iostream>
#include <string>
bool isExisist(std::string names[], int size, std::string name){
    size --;
    while(size >= 0 ){
        if(names[size--] == name){
            return true;
        }
    }
    return false;
}
void reverseArray(const std::string arr[], std::string rever_array[], int size) {
    for (int i = 0; i < size; i++) {
        rever_array[i] = arr[size - 1 - i];
    }
}
int main (){
    std::string names[] = {
        "Warren",
        "Hope",
        "Alyvia",
        "Yasmin",
        "Tyrone",
        "Jayvon",
        "Angelina",
        "Jasper",
        "Catherine",
        "Laura",
        "Keyon",
        "Amiah"
    };
    int nameCount = sizeof(names) / sizeof(names[0]);
    std::string rever_array[nameCount];

    reverseArray(names, rever_array, nameCount);

    for (int i = 0; i < nameCount; i++) {
        std::cout << rever_array[i] << std::endl << std::endl;
    }

    for (int i = 0; i < nameCount; i++) {
        std::cout << names[i] << std::endl;
    }
}