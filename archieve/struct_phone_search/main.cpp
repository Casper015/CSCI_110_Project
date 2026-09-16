#include <iostream>
#include <string>

struct Contact {
  std::string name;
  std::string phone;
};

Contact contacts[] = {
  { "Warren", "11111" },
  { "Hope", "22222" },
  { "Alyvia", "33333" },
  { "Yasmin", "44444" },
  { "Tyrone", "55555" },
  { "Jayvon", "66666" },
  { "Angelina", "77777" },
  { "Jasper", "88888" },
  { "Catherine", "99999" },
  { "Laura", "AAAAA" },
  { "Keyon", "BBBBB" },
  { "Amiah", "CCCCC" }
};

int contactsLen = sizeof(contacts) / sizeof(contacts[0]);

int main(){
    while(true){
        std::cout << "Enter name: ";
        std::string target;
        std::cin >> target;

        bool found = false;
        for (auto c : contacts) {
            if (c.name == target) {
                std::cout << c.phone << std::endl;
                found = true;   
                break;
            }
        }
        if (!found) {
            std::cout << "Not found" << std::endl;
        }
    }
}