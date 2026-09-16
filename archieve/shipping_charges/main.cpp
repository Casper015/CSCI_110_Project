/*
declare real weight, rate, chage

display "Weight (lb): "
input weight

if (weight <= 2) then
    set rate = 1.1
else 
if (weight <= 6) then
    set rate = 2.2
else 
if (weight <= 10) then
    set rate = 3.7
else
    set rate = 3.8
end if

display "Rate: ", rate
delcare real charge = weight * rate 
dipaly "Total Charge: ", charge
*/

#include <iostream>

int main() {
    double weight, rate;

    // Input
    std::cout << "Weight (lb): ";
    std::cin >> weight;
    
    if (weight <= 2){
        rate = 1.10;
    }
    else if (weight <= 6){
        rate = 2.20;
    }
    else if (weight <= 10){
        rate = 3.70;
    }
    else {
        rate = 3.80;
    }
    
    // Output
    std::cout << "Rate : " << rate << std::endl;
    std::cout << "Total Charge: $" << weight * rate ;

    return 0;
}