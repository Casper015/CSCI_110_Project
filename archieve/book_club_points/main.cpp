/*
declare interger books, points

display "Enter books: "
input books

if books < 0 then
    display "Bad quantity!"
    exit
end if

case:books
0: set points = 0
1: set points = 5
2: set points = 15
3: set points = 30
others: set points = 60
end case 

display "Points "，points
*/
#include <iostream>

int main(){

    int books, points;

    std::cout << "Enter Books: ";
    std::cin >> books;

    if (books < 0){
        std::cerr << "Bad Quantity" << std::endl;
        exit(1);
    }

    switch(books){
        case 0: points = 0;
            break;
        case 1: points = 5;
            break;
        case 2: points = 15;
            break;
        case 3: points = 30;
            break;
        default: points = 60;
            break;
    }

    std::cout << "Points: " << points << std::endl;

    return 0;
}