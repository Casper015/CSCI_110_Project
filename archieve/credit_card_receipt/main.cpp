#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "locale.h"

int main() {
    double amt, tip_amt, total_amt;
    int tip_rate;
    std::string cc_num;

    // Input
    std::cout << "Amount: $";
    std::cin >> amt;

    std::cout << "Tip Rate (%): ";
    std::cin >> tip_rate;

    if (tip_rate > 100 || tip_rate < 0) {
        std::cerr << "Error: Tip rate must be between 0 and 100!";
        return 1;
    }

    std::cout << "Credit Card Number (16 digits): ";
    std::cin >> cc_num;

    if (cc_num.length() != 16) {
        std::cerr << "Error: Credit card number must be 16 digits!";
        return 1;
    }

    // Output
    std::cout << "******** RECEIPT ******** \n";

    print_line("CC Number:", cc_num.substr(cc_num.length() - 4));
    print_line("Amount:", locale_en_us(amt));

    tip_amt = (tip_rate / 100.0) * amt;
    std::stringstream tip_label;
    tip_label << "Tip (" << tip_rate << "%):";
    print_line(tip_label.str(), locale_en_us(tip_amt));

    total_amt = tip_amt + amt;
    print_line("Total:", locale_en_us(total_amt));

    return 0;
}
