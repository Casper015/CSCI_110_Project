/*
declare integer i, maxN

display "Enter positive interger: "
input maxN

set k = 1

while k <= maxN
begin
    dispaly k
    set k = k + 1
*/

#include <iostream>

int main(){
    int maxN;

    std::cout << "Enter positive integer: ";
    std::cin >> maxN;

    int j = 1;

    while (j < maxN){
        std::cout << j << std::endl;
        j++;
    }

    while (maxN >= 1){
        std::cout<< maxN << std::endl;
        maxN--;
    }
/* for loop
    for(int i = 1; i <= maxN; i++){
        std::cout << i << std::endl;
    }

    for(int i = (maxN - 1); i >= 1; i--){
        std::cout << i << std::endl;
    }
*/
    return 0;
}