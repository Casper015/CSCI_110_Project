/*
* declare real lA, wA, lB, wB
*
* display "Enter length and width of A: "
* input lA, wA
* display "Enter length and width of B :"
* input lA, wA
*
* declare real A, B
* A = lA * wA
* B = lB * wB
*
* if(A > B) then
*   display "A is larger than B"
* else 
* if (B > A) then
*   display "B is larger than A"
* else
*   display "A and B are same"
* end if
*/

#include <iostream>
#include <string>

double rectangle(std::string name){
    double l, w;
    
    std::cout << "Enter length and width of " + name + ": ";
    std::cin >> l >> w;

    double area = l * w;
    return area;
}

int main() {

    double areaA = rectangle("A");
    double areaB = rectangle("B");

    if (areaA > areaB){
        std::cout << "A is larger than B" << std::endl;
    }
    else if (areaA < areaB){
        std::cout << "B is larger than A" << std::endl;
    }
    else{
        std::cout << "A and B are the same" << std::endl;
    }
    
    return 0;
}
