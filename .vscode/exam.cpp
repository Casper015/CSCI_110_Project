#include <iostream>
#include <string>

std::string array_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ  ";

std::string output(int number[], int size) {
    int p = 0;
    std::string result;
    for (int i = 0; i < size; i++) {
        p += number[i];
        result += array_letters[p];
    }
    return result;
}

int main() {
    int secret[] = {19, -12, -3, 23, -23, 9, -10};
    std::string result = output(secret, sizeof(secret) / sizeof(secret[0]));
    std::cout << result << std::endl;
    return 0;
}