#include <iostream>

//function definition
int add(int a, int b);
/*
int add(int, int)
function prototype, can without parameter names, but must have parameter types and return type
*/ 


int main(){
    int x = 10, y = 20;
    //calling the function
    add(2, 3); // 5
    add_x(x, y); // 30
    std::cout << x; // this will print 5, not 10, because x is passed by reference and modified in the function

    int x = 7 % 4; // this will assign the value of 7 mod 4, which is 3, to x


}

void add_x(int& x, int y) {
    x = 5;
    std::cout << x + y; // this will print 5 + y, not the original value of x
}

// need to defin the function before calling it,
int add(int a, int b) {
    // int x, y;
    // std cin >> x >> y; // this will not work because the function is defined to take parameters, not to read input
    return a + b;
    // cout << a + b; // this will not work because the function is defined to return an int, not to print it

    //return a，b; // this will not work because the function is defined to return a single int, not two ints
}

void f(std::string s[], int size){

}

void copy(std::string s[], std::string copy[], int alan){

}

