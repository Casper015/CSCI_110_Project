#include <iostream>
#include <vector>

int main() {
    std::vector<int> data;

    int number;
    while (std::cin >> number) {
        data.push_back(number);
    }

    for (int i = static_cast<int>(data.size()) - 1; i >= 0; --i) {
        std::cout << data[i] << std::endl;
    }

    return 0;
}

