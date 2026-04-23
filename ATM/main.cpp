#include <array>
#include <iostream>
#include <string>

std::array <std::string,3> pin = {"0000","0000","0000"};
int balance = 0;

bool log_in();

void menu();
void show_balance();
void withdraw();
void deposit_money();
void change_pin();

bool self_test_1();
bool self_test_2();

void edit_balance(const int& input, const bool& with_draw);
std::string edit_PIN(const std::string& new_PIN);

class utils {
    public:
        static void clear_the_screen();
        static void clear_input_error(const std::string& name_function);
        static bool is_PIN(const std::string& s); // check pin 1. s.length == 4 2. is it all int ？
        static bool utils::is_money(std::string s); 
        static bool utils::check_balance(const int& with_draw);
        static bool utils::check_PIN(const std::string& new_PIN);
        static int utils::money_string_to_int(std::string s);
        static std::string rand_PIN();
        static std::string locale_en_us(const int& money); // int balance > string money(en_us fomart)
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
                withdraw();
                break;
            case 3:
                deposit_money();
                break;
            case 4:
                change_pin();
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

void withdraw(){
    std::string raw;

    //Check cin raw and cout
    while(true){

        std::cout <<"\nTotal balance: "<< utils::locale_en_us(balance) 
        << ". Withdraw amount (blank = cancel) : ";
        std::getline(std::cin,raw);

        if(std::cin.fail()){
            utils::clear_input_error("Withdraw amount");
            continue;
        }else if(raw.empty()){
            return;
        }else if (!utils::is_money(raw)){
            std::cout << "Invalid withdraw amount. Try again.\n";
            continue;
        }
        
        break;
    }

    //edit the balance, true means with_draw
    int withdraw = utils::is_PIN(raw);
    
    // check withdraw < balance ?
    if(utils::check_balance(withdraw)){
        edit_balance(withdraw, true);
        std::cout << std::endl << utils::locale_en_us(withdraw) << " withdrawn. Your balance is "
        << utils::locale_en_us(balance) << std::endl;
    }else{
        std::cout << "Insufficient funds. Withdraw cancelled.\n";
    }

    return;
}

void deposit_money(){
    std::string raw;

    // Input and check raw
    while(true){
        std::cout << "Deposit amount (blank = cancel) : ";
        std::getline(std::cin,raw);

        if (std::cin.fail()){
            utils::clear_input_error("currency amount");
            continue;
        }else if(raw.empty()){
            return;
        }else if(!utils::is_money(raw)){
            std::cout << "Invalid Input. Please try again\n";
            continue;
        }
        break;
    }
    
    //deposit money
    //1. string to int
    //2. deposit in to the 
    int deposit = utils::money_string_to_int(raw);
    edit_balance(deposit, false);

    std::cout << std::endl << utils::locale_en_us(deposit) << " deposited. Your balance is "
    << utils::locale_en_us(balance) << std::endl;
}

void change_pin(){

    std::string input, re_PIN, new_PIN; 
    while (true) {

        std::cout << "Enter current PIN (blank = cancel): ";
        std::getline(std::cin, input);

        if (input.empty()){
            std::cout << "\n Change PIN cancelled.\n";
            return;
        } else if(input != pin[0]){
            std::cout << "Invalid PIN. Please try again.\n";
            continue;
        }
        
        break;
    };
    
    while(true) {

        std::cout << "Enter new PIN (exactly 4 digits): ";
        std::getline(std::cin, new_PIN);
        
        if(!utils::is_PIN(new_PIN)){
            std::cout << "Invalid PIN format. Try again.\n";
            continue;
        } 

        std::cout << "Confirm new PIN: ";
        std::getline(std::cin, re_PIN);
        
        if (re_PIN != new_PIN){
            std::cout << "New PINs do not match.\n";
            continue;
        }

        if (utils::check_PIN(new_PIN)){
            std::cout << "Can't re-use the last 3 PINs.\n";
            continue;
        }

        break;
    }

    std::cout << "Your PIN has been changed.\n"; 

    return;

}

bool self_test_1(){
    int temp = balance;
    balance = 0;
    deposit_money(0.03);
    withdraw(0.01);
    show_balance();
    balance = temp;
}

bool self_test_2(){
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

void edit_balance(const int& input, const bool& with_draw){
    
    // if is withdraw  - balance
    // if it deposit   + balance  
    if (with_draw){
        balance -= input;
    }else {
        balance += input;
    }

}

std::string edit_PIN(const std::string& new_PIN){
    pin[2] = pin[1];
    pin[1] = pin[0]; 
    pin[0] = new_PIN;
    return;
}

// Direct copy form the Slot machine cpp
// Clear screen using ANSI terminal codes
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
void utils::clear_the_screen(){
    const std::string CSI = "\x1b[";	// ANSI terminal escape sequence

	std::cout << CSI << "2J";
	std::cout << CSI << "1;1H";

}

// Clear the error of cin, make it possbile for next use
void utils::clear_input_error(const std::string& name_function){ 
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Invalid " << name_function << ". Try again.\n";
}

//check the PIN is ready to go or not
// s.find_first_not_of("0123456789") != std::string::npos is same us for loop find 1 to 9
bool utils::is_PIN(const std::string& s){ 
    return s.length() == 4 || 
           s.find_first_not_of("0123456789") == std::string::npos;
}

//check user is legal input? Accept input look like (0.xx/0.x/.xx/0./123) 
bool utils::is_money(std::string s){
    int dot_count = 0, after_dot = 0;
    char c;

    // suppot someone type .45 or .3
    if (s[0] == '.') s = "0" + s;

    for(int i = 0; i < static_cast<int>(s.size()); i++){
        c = s[i];

        if (c == '.'){
            //only allow one '.'
            if (dot_count > 0) return false;
            
            dot_count ++;
            continue;
        }

        if (c < '0' || c > '9') return false;

        if (dot_count == 1) after_dot ++;
    }

    // only accpet fomat like 0.XX or 0.X
    if (after_dot > 2) return false;

    return true;
}

// if the balance is larger the  with_draw
bool utils::check_balance(const int& with_draw){
    return (with_draw <= balance);
}

bool utils::check_PIN(const std::string& new_PIN){      
    return (new_PIN == pin[0] || new_PIN == pin[1]|| new_PIN == pin[2]);
}

//convert the string money to int balance
int utils::money_string_to_int(std::string s){
    std::string dollars = 0, cents = 0;
    int dotpos = -1;
    if (s[0] == '.') s = "0" + s;

    for (int i = 0; i < static_cast<int>(s.size()); i++){
        if (s[i] == '.'){
            dotpos = i;
            break;
        }
    }

    // not dot 
    if(dotpos == -1) {
        dollars = std::stoi(s);
        return std::stoi(s) * 100;
    }

    // dollars part
    dollars = s.substr(0, dotpos);

    //cent part, make sure have two 00
    cents = s.substr(dotpos, dotpos+1);
    if (cents.size() == 0) cents = "00";
    else if (cents.size() == 1) cents += "0";

    return std::stoi(dollars + cents);

}

//4 digtals random PIN
std::string utils::rand_PIN(){
    std::string radom_PIN;
    
    for(int i = 0; i < 4; i++){
        radom_PIN += std::to_string(rand()%10);
    }

    return radom_PIN;

}

//Mingw(GCC in win) don't support, rewrite the en_us
//Output: $123.31
std::string utils::locale_en_us(const int& money){ 
    
    // start at $
    std::string result = "$";
    
    //Seperate the dolloras and cents
    int dollor = money/100;
    result += std::to_string(dollor);

    //Add , for after each 3 digtals
    for(int i = static_cast<int>(result.size()) - 3 ;
    i > 1; i -=3 ){
        result.insert(i, ",");
    }

    result += ".";
    
    // cents part
    int cents =  money%100;
    if (cents < 10){
        result += "0";
    }
    result += std::to_string(cents);

    return result;
}
