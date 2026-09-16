#include <iostream>
#include <iomanip>

int main() {
    double weight;

    std::cout << "Enter package weight (lbs): ";
    std::cin >> weight;

    if (weight <= 0) {
        std::cout << "Invalid weight." << std::endl;
        return 1;
    }

    double rate = 0.0;
    if (weight <= 2) rate = 1.10;
    else if (weight <= 6) rate = 2.20;
    else if (weight <= 10) rate = 3.70;
    else rate = 4.80;

    std::cout << std::fixed << std::setprecision(2)
              << "Shipping charge: $" << rate << std::endl;
    return 0;
}
