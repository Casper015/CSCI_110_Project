#include <iostream>
#include <string>
std::string getPhone(std::string name, std::string names[], std::string phones[], int size){
    size --;
    while(size >= 0 ){
        if(names[size--] == name){
            return phones[size + 1];
        }
    }
    return "Not Found";
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
    
    std::string phones[] = {
    "364-942-9743",
    "216-412-6159",
    "295-622-4892",
    "151-986-0123",
    "363-554-9619",
    "688-230-2481",
    "583-240-7353",
    "848-524-8279",
    "728-252-3890",
    "937-508-6947",
    "556-807-2996",
    "123-456-7890",
};
    
int nameCount = sizeof(names) / sizeof(names[0]);

    while(true){
        std::string s;
        std::cin >> s;

        std::string phone = getPhone(s, names, phones, nameCount);
        std::cout << phone << std::endl;
    }
}