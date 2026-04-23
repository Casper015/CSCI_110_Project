/*
 * Project #1: ATM
 * Author: Casper Xu
 */

#include <array>
#include <iostream>
#include <string>

std::array <std::string,3> pin = {"0000","0000","0000"};
int balance = 0;

void menu();
void show_balance();
void withdraw();
void deposit_money();
void change_pin();

bool log_in(); // true means the user entered the correct current PIN
bool self_test_1(const std::string& deposit, const std::string& with_draw); // true means the deposit/withdraw precision test passed
bool self_test_2(); // true means the PIN history test passed

void edit_balance(const int& input, const bool& with_draw); // with_draw true means withdraw and false means deposit
void edit_PIN(const std::string& new_PIN); 

class utils {
    public:
        static void clear_the_screen();
        static void clear_input_error(const std::string& name_function);
        static bool is_PIN(const std::string& s); // true means the input is NOT a valid 4-digit PIN
        static bool is_money(std::string s); // true means the input is a valid money string
        static bool check_balance(const int& with_draw); // true means the balance is enough for this withdrawal
        static bool check_PIN(const std::string& new_PIN); // true means the PIN is reused from the last 3 PINs
        static int money_string_to_int(std::string s);
        static std::string rand_PIN();
        static std::string locale_en_us(const int& money); // converts cents to US currency format
};


int main() {
    while (true) {
        if (log_in()){
            menu();
        }
    }
}

// true means login succeeded with the current PIN
bool log_in(){
    std::string inputPin;
    std::cout << "\n\nRe_SIMPLE ATM Version 1.2\n\n";    
    
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
    bool login = true; // true means stay in the menu loop

    while(login){
        utils::clear_the_screen();
        std::cout << "**** SIMPLE ATM ****\n";
        std::cout << "Balance: " << utils::locale_en_us(balance) << std::endl << std::endl << std::endl;
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
                utils::clear_the_screen();
                break;
            case 6:
                
                std::cout << "Self Test selected.\n" << "Test Precision: ";

                if (self_test_1("0.03", "0.01")){
                    std::cout << "PASS. \n";
                }else{
                    std::cout << "NOT PASS. \n";
                }

                std::cout << "Test PIN Change History: ";
                if (self_test_2()){
                    std::cout << "PASS. \n";
                }else{
                    std::cout << "NOT PASS. \n";
                }                
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
    std::cin.ignore(10000, '\n');

    // Read and validate withdrawal input
    while(true){

        std::cout <<"\nTotal balance: "<< utils::locale_en_us(balance) 
        << ". Withdraw amount (blank = cancel) : ";
        std::getline(std::cin,raw);
        
        if(raw.empty()){
            return;
        }else if (!(utils::is_money(raw))){
            std::cout << "Invalid withdraw amount. Try again.\n";
            continue;
        }
        break;
    }

    // Convert input money text to cents
    int withdraw = utils::money_string_to_int(raw);
    
    // Check whether the withdrawal amount is within the current balance
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
    std::cin.ignore(10000, '\n');
    
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
    
    // Convert input money text to cents and add it to balance
    int deposit = utils::money_string_to_int(raw);
    edit_balance(deposit, false);

    std::cout << std::endl << utils::locale_en_us(deposit) << " deposited. Your balance is "
    << utils::locale_en_us(balance) << std::endl;
}

void change_pin(){
    std::string input, re_PIN, new_PIN; 
    std::cin.ignore(10000, '\n');

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
        
        if(utils::is_PIN(new_PIN)){
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
            return;
        }

        break;
    }

    edit_PIN(new_PIN);
    std::cout << "Your PIN has been changed.\n"; 
    return;

}

// true means this test confirms balance math is correct
bool self_test_1(const std::string& deposit, const std::string& with_draw){
    int deposit_test, with_draw_test, temp = balance;
    // Set balance to 0.00 dollars
    balance = 0;
    if (!(utils::is_money(deposit) && utils::is_money(with_draw))){
        balance = temp;
        return false;
    }
    // Convert money strings to cents
    deposit_test = utils::money_string_to_int(deposit);
    with_draw_test = utils::money_string_to_int(with_draw);
    // Simulate deposit
    edit_balance(deposit_test, false);
    
    // Simulate withdrawal
    if (!(utils::check_balance(with_draw_test))){
        balance = temp;
        return false;        
    }else{
        edit_balance(with_draw_test, true);
    }
    
    if (balance == (deposit_test - with_draw_test)){
        balance = temp;
        return true;
    }

    balance = temp;
    return false;  
}

// true means this test confirms the last-3-PIN reuse rule works
bool self_test_2(){
    
    
    // Clear PIN history
    srand(time(0));
    std::array <std::string,3> temp = pin;
    std::array <std::string,4> test_pin;
    pin = {"0000","0000","0000"};

    // Change PIN 3 times and use a different valid PIN each time
    for(int i = 0; i < 4; i++){
        test_pin[i] = utils::rand_PIN();
        
        // Regenerate until the PIN is valid and different from previous test PINs
        while (utils::is_PIN(test_pin[i]) ||
               (i > 0 && test_pin[i] == test_pin[0]) ||
               (i > 1 && test_pin[i] == test_pin[1]) ||
               (i > 2 && test_pin[i] == test_pin[2])) {
            test_pin[i] = utils::rand_PIN();
        }
        
        //Check is anybody reuse it before?
        if (utils::check_PIN(test_pin[i])){
            pin = temp;
            return false;
        }
        edit_PIN(test_pin[i]);
    }

    // Reusing the oldest test PIN should be detected
    // 1. check the first is not one of the least 3
    // 2. check the second is on  of the least 3
    if (utils::check_PIN(test_pin[0])){
        pin = temp;
        return false;
    } else if (utils::check_PIN(test_pin[1])){
        pin = temp;
        return true;
    } else{
        pin = temp;
        return false;
    }
        
    
}

// with_draw true means subtract from balance and false means add to balance
void edit_balance(const int& input, const bool& with_draw){
    
    
    if (with_draw){
        balance -= input;
    }else {
        balance += input;
    }

}

// Move all the pin foward a digit
void edit_PIN(const std::string& new_PIN){
    pin[2] = pin[1];
    pin[1] = pin[0]; 
    pin[0] = new_PIN;
}

// Adapted from the Slot Machine C++ project
// Clear screen using ANSI terminal codes
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
void utils::clear_the_screen(){
    const std::string CSI = "\x1b[";	// ANSI terminal escape sequence

	std::cout << CSI << "2J";
	std::cout << CSI << "1;1H";

}

// Clear std::cin error state so the next input can proceed
void utils::clear_input_error(const std::string& name_function){ 
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Invalid " << name_function << ". Try again.\n";
}

// true means this string is NOT a valid 4-digit PIN
// s.find_first_not_of("0123456789") != std::string::npos is equivalent to
// checking whether any non-digit character exists
bool utils::is_PIN(const std::string& s){ 
    return s.length() != 4 || 
           s.find_first_not_of("0123456789") != std::string::npos;
}

// true means this is a valid money input.
// Accepts values like: 0.xx 0.x .xx 0. 123
bool utils::is_money(std::string s){
    int dot_count = 0, after_dot = 0;
    char c;

    // Support inputs like .45 or .3
    if (s[0] == '.') s = "0" + s;

    for(int i = 0; i < static_cast<int>(s.size()); i++){
        c = s[i];

        if (c == '.'){
            // Only allow one decimal point
            if (dot_count > 0) return false;
            
            dot_count ++;
            continue;
        }

        if (c < '0' || c > '9') return false;

        if (dot_count == 1) after_dot ++;
    }

    // Only accept at most 2 digits after the decimal point
    if (after_dot > 2) return false;

    return true;

}

// true means the balance is greater than or equal to the withdrawal amount
bool utils::check_balance(const int& with_draw){
    return (with_draw <= balance);
}

// true means the new PIN matches one of the last 3 PINs
bool utils::check_PIN(const std::string& new_PIN){      
    return (new_PIN == pin[0] || new_PIN == pin[1]|| new_PIN == pin[2]);
}

// Convert money string to integer cents
int utils::money_string_to_int(std::string s){
    std::string dollars, cents;
    int dotpos = -1;

    if (s.empty()) return 0;
    if (s[0] == '.') s = "0" + s;

    for (int i = 0; i < static_cast<int>(s.size()); i++){
        if (s[i] == '.'){
            dotpos = i;
            break;
        }
    }

    // No decimal point
    if(dotpos == -1) {
        dollars = std::stoi(s);
        return std::stoi(s) * 100;
    }

    // Dollars part
    dollars = s.substr(0, dotpos);

    // Cents part normalize to two digits
    cents = s.substr(dotpos + 1);
    if (cents.size() == 0) cents = "00";
    else if (cents.size() == 1) cents += "0";

    return std::stoi(dollars + cents);
}

// Generate a random 4-digit PIN
std::string utils::rand_PIN(){
    std::string radom_PIN;
    
    for(int i = 0; i < 4; i++){
        radom_PIN += std::to_string(rand()%10);
    }

    return radom_PIN;

}

// MinGW (GCC on Windows) has limited locale formatting support
// so this manually formats US currency text
// Output example: $1,2123.31
std::string utils::locale_en_us(const int& money){ 
    
    // Start with currency symbol
    std::string result = "$";
    
    // Separate dollars and cents
    int dollor = money/100;
    result += std::to_string(dollor);

    // Insert a comma every three digits in the dollars part
    for(int i = static_cast<int>(result.size()) - 3 ;
    i > 1; i -=3 ){
        result.insert(i, ",");
    }

    result += ".";
    
    // Cents part
    int cents =  money%100;
    if (cents < 10){
        result += "0";
    }
    result += std::to_string(cents);

    return result;
}
