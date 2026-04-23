#include <array>
#include <iostream>
#include <string>

std::array <std::string,3> pin = {"0000","0000","0000"};
int balance = 0;

bool log_in();

void menu();
void show_balance();
void withdraw(double input);
void deposit_money(double input);
void change_pin(std::string, std::string);
void self_test_1();
void self_test_2();

int edit_balance();
std::string edit_PIN();

class utils {
    public:
        static void clear_the_screen();
        static void clear_input_error(std::string name_function); // clear the cin error, output error
        static bool check_PIN(std::string); // check pin 1. s.length == 4 2. is it all int ？
        static int money_to_balance(double money); // double money > int balance
        static std::string rand_PIN();
        static std::string locale_en_us(int money); // int balance > string money(en_us fomart)
};


int main() {
    std::cout << "\n\nRe_SIMPLE ATM Version 1.1\n\n";
    while (true) {
        if (log_in()){
            menu();
        }
    }
}

bool log_in(){
    std::string inputPin;
    
    do{
        std::cout <<"Enter PIN: ";
        std::cin >> inputPin;

        if(std::cin.fail()){
            utils::clear_input_error("PIN");
            continue;
        }

        if(inputPin != pin[0]){
            std::cout << "Wrong PIN. Please try again." << std::endl;
            continue;
        }
        
    } while (inputPin != pin[0]);

    std::cout << "Login successful!" << std::endl; 
    return true;
}

void menu() {
    
    int choice;
    bool login = true;

    while(login){
        utils::clear_the_screen();
        std::cout << "\n**** SIMPLE ATM ****\n";
        std::cout << "1. Show balance\n";
        std::cout << "2. Withdraw\n";
        std::cout << "3. Deposit\n";
        std::cout << "4. Change PIN\n";
        std::cout << "5. Logout\n";
        std::cout << "6. Self Test\n";

        do {
            std::cout << "Choose option 1-6: ";
            std::cin >> choice;

            if (std::cin.fail()) {
                utils::clear_input_error("choice");
                continue;
            }

            if (choice < 1 || choice > 6) {
            std::cout << "Please choose a number from 1 to 6: \n";
            }

        } while (choice < 1 || choice > 6);

        switch (choice) {
            case 1:
                show_balance();
                break;
            case 2:
                withdraw(0);
                break;
            case 3:
                deposit_money(0);
                break;
            case 4:
                change_pin("", "");
                break;
            case 5:
                std::cout << "\nYou are logged out.\n";
                login = false;
                break;
            case 6:
                std::cout << "Self Test selected.\n";
                self_test_1();
                self_test_2();
                break;
            }
        system("pause");
    }
}

void show_balance(){ 
    std::cout << std::endl << "Your balance is " << utils::locale_en_us(balance) << std::endl;
}

void withdraw(double input){

    while(input <= 0){
        std::cout <<"\nTotal balance: "<< utils::locale_en_us(balance) << ". Withdraw amount: ";
        std::cin >> input;

        if(std::cin.fail()){
            utils::clear_input_error("Withdraw amount");
            continue;

        }else if(input <= 0){
            std::cout << "Invalid withdraw amount. Try again.\n";
        }
    }

    int withdraw = utils::money_to_balance(input);

    if(withdraw > balance){
        std::cout << "Insufficient funds. Withdraw cancelled.\n";
    }
    else{
        balance -= withdraw;
        std::cout << std::endl << utils::locale_en_us(withdraw) << " withdrawn. Your balance is "
        << utils::locale_en_us(balance) << std::endl;
    }
    
}

void deposit_money(double input){
    
    while(input <= 0){
        std::cout << "Deposit amount: ";
        std::cin >> input;

        if (std::cin.fail()){
            utils::clear_input_error("currency amount");
            continue;
        }else if(input <= 0){
            std::cout << "Invalid deposit amount. Try again.\n";
            continue;
        }
    }
    
    int deposit = utils::money_to_balance(input);
    balance += deposit;

    std::cout << std::endl << utils::locale_en_us(deposit) << " deposited. Your balance is "
    << utils::locale_en_us(balance) << std::endl;
}

void change_pin(std::string input, std::string new_PIN){

    do {

        std::cout << "Enter current PIN (blank = cancel): ";
        if(input != pin[0]){
            std::cin.ignore(10000, '\n'); // Clear the input
            std::getline(std::cin, input);
        } else if (input.empty()){
            std::cout << "\nChange PIN cancelled.\n";
            return;
        } else if(input != pin[0]){
            std::cout << "Invalid PIN. Please try again.\n";
            continue;
        }else{
            std::cout << input  << std::endl;
        }
        break;

    } while (true);
    
    std::string re_PIN = new_PIN;
    
    do {
        std::cout << "Enter new PIN (exactly 4 digits): ";
        if (new_PIN.empty()) {
            std::getline(std::cin, new_PIN);
            std::cout << "\nChange PIN cancelled.\n";
            return;
        } else if (new_PIN.empty()){
            std::cout << "\nChange PIN cancelled.\n";
            return;
        } else if(utils::check_PIN(new_PIN)){
            std::cout << "Invalid PIN format. Try again.\n";
            continue;
        } else{
            std::cout << new_PIN  << std::endl;
        }

        std::cout << "Confirm new PIN: ";
        if (re_PIN.empty()) {
            std::getline(std::cin, re_PIN);
        } else if (re_PIN.empty()) {
            std::cout << "\nChange PIN cancelled.\n";
            return;
        } else if (re_PIN != new_PIN){
            std::cout << "New PINs do not match.\n";
            continue;
        }else{
            std::cout << re_PIN  << std::endl;
            
        }

        break;

    } while(new_PIN.empty()||re_PIN.empty());

    if(new_PIN == pin[0] || new_PIN == pin[1]|| new_PIN == pin[2]){
        std::cout << "Can't re-use the last 3 PINs.\n";
        return;
    }

    pin[2] = pin[1];
    pin[1] = pin[0]; 
    pin[0] = new_PIN; 

    std::cout << "Your PIN has been changed.\n"; 

}

void self_test_1(){
    int temp = balance;
    balance = 0;
    deposit_money(0.03);
    withdraw(0.01);
    show_balance();
    balance = temp;
}

void self_test_2(){
    srand(time(0));
    std::array <std::string,3> temp = pin;
    std::array <std::string,4> test_pin = {"0000","0000","0000","0000"};
    pin = {"0000","0000","0000"};
    
    for(int i = 1; i < 4; i++){

        test_pin[i] = utils::rand_PIN();
        change_pin(test_pin[i-1],test_pin[i]);
        std::cout << std::endl;

    }

    change_pin(test_pin[3],test_pin[1]);

    pin = temp;
    system("pause");
    
}


// Clear screen using ANSI terminal codes
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
void utils::clear_the_screen(){
    const std::string CSI = "\x1b[";	// ANSI terminal escape sequence

	std::cout << CSI << "2J";
	std::cout << CSI << "1;1H";

}

void utils::clear_input_error(std::string name_function){ 
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Invalid " << name_function << ". Try again.\n";
}

bool utils::check_PIN(std::string s){ 
    return s.length() != 4 || 
           s.find_first_not_of("0123456789") != std::string::npos;
}

int utils::money_to_balance(double money){ 
    int dollars = static_cast<int>(money * 100);
    return dollars;
}

std::string utils::rand_PIN(){
    std::string radom_PIN;
    
    for(int i = 0; i < 4; i++){
        radom_PIN += std::to_string(rand()%10);
    }

    return radom_PIN;

}

std::string utils::locale_en_us(int money){ 
    
    std::string result = "$";
    
    int dollor = money/100;
    result += std::to_string(dollor);

    for(int i = static_cast<int>(result.size()) - 3 ;
    i > 1; i -=3 ){
        result.insert(i, ",");
    }

    result += ".";
    
    int cents =  money%100;
    if (cents < 10){
        result += "0";
    }
    result += std::to_string(cents);

    return result;
}
