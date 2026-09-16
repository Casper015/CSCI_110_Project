/*
display "Enter a series of number (0=end): "
input n
set max = n

if n == 0 then
    display "no data"
    exit
end if 

declare integer sum = 0, count == 0, max

declare interger sum

while n != 0
begin
    set sum = sum + n
    set count = count + 1
    if n > max then 
        set max = n
    end if 
    input n
end

display "Sum: ", sum
declare real avg = sum / count
display "Avg: ", avg
*/
#include <iostream>

int main(){
    int n, sum = 0, count = 0, max , min;
    std::cout << "Enter a series of number (0=end): ";
    std::cin >> n;
    max = min = n;

    if (n == 0){
        std::cout << "Invaid number";
        return(1);
    }

    while (n !=0 ){
        sum += n;
        count++;
        if (n > max) max = n;
        if (n < min) min = n;
        std::cin >> n; 
    }

    std::cout << "Sum: " << sum << std::endl;
    double avg = 1.0 * sum / count;
    std::cout << "Avg: " << avg << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;

    return(0);
}