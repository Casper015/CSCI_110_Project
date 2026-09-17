#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "locale.h" // The function of locale

std::string locale_en_us(double amount) {
    // Implementation for US English locale
    std::stringstream ss;
    ss << "$" << std::fixed << std::setprecision(2) << amount;
    return ss.str();
}

void print_line(const std::string& label, const std::string& value){
    std::cout << std::left << std::setw(10) << label 
              << std::right << std::setw(15) << value << std::endl;
}