#include <iostream>
#include <string>


struct Expense
{
  std::string name;
  double amount;
};

const int MAX_EXPENSES = 5;
Expense expenses[MAX_EXPENSES];
int expenseLength = 0;

int main(){
    while (true){
        std::cout << "Expense and amount: ";
        std::string name;  
        double amount;

        if (!(std::cin >> name >> amount)){
            break;
        }

        expenses[expenseLength].name = name;
        expenses[expenseLength].amount = amount;
        expenseLength++;

        if (expenseLength >= MAX_EXPENSES){
            std::cout << "Expense limit reached. Cannot add more expenses." << std::endl;
            break;
        }
    }

    double total = 0;
    for(auto i = 0; i < expenseLength; i++){
        auto rec = expenses[i];
        std::cout << rec.name << ": " << rec.amount << std::endl;
        total += rec.amount;
    }
    std::cout << "TOTAL: " << total << std::endl;
}