#include <iostream>
#include <iomanip>

int main(){
    for (int hour = 0; hour < 24; hour++){
        for (int minute = 0; minute < 60; minute++){
            for (int second = 0; second < 60; second++){
                std::cout << std::setw(2) << std::setfill('0') << hour << 
            ":" << std::setw(2) << std::setfill('0') << minute <<
            ":" << std::setw(2) << std::setfill('0') << second << std::endl;
            }
            
        }
    }
}