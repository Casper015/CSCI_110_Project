/**
Inside main(), complete the following steps
Declare two int variables named itemPrice and shippingCost, and assign them values
Create an int variable named sum
Calculate the total cost by adding itemPrice and shippingCost (store the result in sum)
Print the total cost using cout
**/

#include <iostream>

int main(){
    int itemPrice = 10, shippingCost = 10 , sum;
    
    sum = itemPrice + shippingCost;

    std::cout << sum;

    return 0;
}