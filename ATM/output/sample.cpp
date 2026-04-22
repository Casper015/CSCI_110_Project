#include <array>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

std::array<std::string, 3> pin_history = {"0000", "0000", "0000"};
long long balance_cents = 10012;
bool logged_in = false;

void log_in();
void menu();
void show_balance();
void withdraw_money();
void deposit_money();
void change_pin();
void self_test();

bool c_PIN(const std::string& pin);
long long money_to_balance(double money);
std::string locale_en_us(long long money);
void clear_input_error(const std::string& field_name);

int main() {
    std::cout << "Re_SIMPLE ATM Version 1.0" << std::endl << std::endl;
    while (true) {
        log_in();
    }
}

void log_in() {
    std::string input_pin;

    while (true) {
        std::cout << "Enter PIN: ";
        if (!(std::cin >> input_pin)) {
            if (std::cin.eof()) {
                std::cout << "\nInput ended.\nProgram exited.\n";
                std::exit(0);
            }
            clear_input_error("PIN");
            continue;
        }

        if (input_pin != pin_history[0]) {
            std::cout << "Wrong PIN. Please try again." << std::endl;
            continue;
        }

        std::cout << "Login successful!" << std::endl;
        logged_in = true;
        menu();
        return;
    }
}

void menu() {
    int choice = 0;

    while (logged_in) {
        std::cout << "\n**** SIMPLE ATM ****\n";
        std::cout << "1. Show balance\n";
        std::cout << "2. Withdraw\n";
        std::cout << "3. Deposit\n";
        std::cout << "4. Change PIN\n";
        std::cout << "5. Logout\n";
        std::cout << "6. Self Test\n";

        while (true) {
            std::cout << "Choose option 1-6: ";
            if (!(std::cin >> choice)) {
                if (std::cin.eof()) {
                    std::cout << "\nInput ended.\nProgram exited.\n";
                    std::exit(0);
                }
                clear_input_error("menu option");
                continue;
            }

            if (choice < 1 || choice > 6) {
                std::cout << "Please choose a number from 1 to 6.\n";
                continue;
            }

            break;
        }

        switch (choice) {
            case 1:
                show_balance();
                break;
            case 2:
                withdraw_money();
                break;
            case 3:
                deposit_money();
                break;
            case 4:
                change_pin();
                break;
            case 5:
                std::cout << "\nYou are logged out.\n";
                logged_in = false;
                break;
            case 6:
                self_test();
                break;
            default:
                break;
        }
    }
}

void show_balance() {
    std::cout << "Your balance is " << locale_en_us(balance_cents) << std::endl;
}

void withdraw_money() {
    double input = 0.0;

    while (true) {
        std::cout << "\nTotal balance: " << locale_en_us(balance_cents) << "\n";
        std::cout << "Withdraw amount: ";

        if (!(std::cin >> input)) {
            if (std::cin.eof()) {
                std::cout << "\nInput ended.\nProgram exited.\n";
                std::exit(0);
            }
            clear_input_error("withdraw amount");
            continue;
        }

        if (input <= 0.0) {
            std::cout << "Amount must be greater than 0.\n";
            continue;
        }

        break;
    }

    long long withdraw_amount = money_to_balance(input);
    if (withdraw_amount > balance_cents) {
        std::cout << "Insufficient funds. Withdraw cancelled." << std::endl;
        return;
    }

    balance_cents -= withdraw_amount;
    std::cout << locale_en_us(withdraw_amount) << " withdrawn. Your balance is "
              << locale_en_us(balance_cents) << std::endl;
}

void deposit_money() {
    double input = 0.0;

    while (true) {
        std::cout << "\nDeposit amount: ";

        if (!(std::cin >> input)) {
            if (std::cin.eof()) {
                std::cout << "\nInput ended.\nProgram exited.\n";
                std::exit(0);
            }
            clear_input_error("deposit amount");
            continue;
        }

        if (input <= 0.0) {
            std::cout << "Amount must be greater than 0.\n";
            continue;
        }

        break;
    }

    long long deposit_amount = money_to_balance(input);
    balance_cents += deposit_amount;

    std::cout << locale_en_us(deposit_amount) << " deposited. Your balance is "
              << locale_en_us(balance_cents) << std::endl;
}

void change_pin() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string current_pin;
    std::cout << "\nEnter current PIN (blank = cancel): ";
    if (!std::getline(std::cin, current_pin)) {
        std::cout << "\nInput ended.\nProgram exited.\n";
        std::exit(0);
    }

    if (current_pin.empty()) {
        std::cout << "\nChange PIN cancelled.\n";
        return;
    }

    if (current_pin != pin_history[0]) {
        std::cout << "Invalid PIN. Returning to Main Menu.\n";
        return;
    }

    while (true) {
        std::string new_pin;
        std::string confirm_pin;

        std::cout << "Enter new PIN (exactly 4 digits): ";
        if (!std::getline(std::cin, new_pin)) {
            std::cout << "\nInput ended.\nProgram exited.\n";
            std::exit(0);
        }

        if (c_PIN(new_pin)) {
            std::cout << "Invalid PIN format. Try again.\n";
            continue;
        }

        std::cout << "Confirm new PIN: ";
        if (!std::getline(std::cin, confirm_pin)) {
            std::cout << "\nInput ended.\nProgram exited.\n";
            std::exit(0);
        }

        if (confirm_pin != new_pin) {
            std::cout << "New PINs do not match.\n";
            continue;
        }

        if (new_pin == pin_history[0] || new_pin == pin_history[1] || new_pin == pin_history[2]) {
            std::cout << "Can't re-use the last 3 PINs.\n";
            continue;
        }

        pin_history[2] = pin_history[1];
        pin_history[1] = pin_history[0];
        pin_history[0] = new_pin;

        std::cout << "Your PIN has been changed.\n";
        return;
    }
}

void self_test() {
    bool passed = true;

    std::cout << "\nRunning self test...\n";

    if (locale_en_us(123456789) != "$1,234,567.89") {
        passed = false;
        std::cout << "Currency format test failed.\n";
    }

    if (c_PIN("1234") || !c_PIN("12a4") || !c_PIN("12345")) {
        passed = false;
        std::cout << "PIN validation test failed.\n";
    }

    if (passed) {
        std::cout << "Self test passed.\n";
    } else {
        std::cout << "Self test found issues.\n";
    }
}

bool c_PIN(const std::string& pin) {
    return pin.length() != 4 || pin.find_first_not_of("0123456789") != std::string::npos;
}

long long money_to_balance(double money) {
    return static_cast<long long>(std::llround(money * 100.0));
}

std::string locale_en_us(long long money) {
    bool is_negative = money < 0;
    long long abs_cents = std::llabs(money);
    long long dollars = abs_cents / 100;
    int cents = static_cast<int>(abs_cents % 100);

    std::string dollars_text = std::to_string(dollars);
    for (int i = static_cast<int>(dollars_text.size()) - 3; i > 0; i -= 3) {
        dollars_text.insert(i, ",");
    }

    std::ostringstream formatted;
    if (is_negative) {
        formatted << "-";
    }

    formatted << "$" << dollars_text << "." << std::setw(2) << std::setfill('0') << cents;
    return formatted.str();
}

void clear_input_error(const std::string& field_name) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid " << field_name << ". Try again.\n";
}