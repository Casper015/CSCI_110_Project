#include <iostream>

int main() {
    std::cout << "Count up:" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }

    std::cout << "\nCount down:" << std::endl;
    for (int i = 5; i >= 1; --i) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    return 0;
}
