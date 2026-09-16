/*
declare string color1, color2, result

display "Enter 2 colors: "
input color1, corlor2

if color1 and color2 is not "red" , "blue" or "yellow" then
    display "Invalid color"
    exit
end if

if  (color1 = "red" and color2 = "blue") or
    (color1 = "blue" and color2 = "red") then
    set result = "purple"
else 
if  (color1 = "red" and color2 = "yellow") or
    (color1 = "yellow" and color2 = "red") then
    set result = "orange"
else 
if  (color1 = "yellow" and color2 = "blue") or
    (color1 = "blue" and color2 = "yellow") then
    set result = "green"
else
    set result = color1
end if

display "The color is " + result
*/
#include <iostream>
#include <string>

bool is_compared_color(std::string colorA, std::string colorB, std::string first, std::string second){
    
    return (
        (colorA == first && colorB == second) || 
        (colorA == second && colorB == first));
}

int main(){
    
    std::string color1, color2, result;

    std::cout << "Enter 2 Colors: ";
    std::cin >> color1 >> color2;

    bool is_color1_bad, is_color2_bad;
    is_color1_bad = (color1 != "red" && color1 != "blue" && color1 != "yellow");
    is_color2_bad = (color2 != "red" && color2 != "blue" && color2 != "yellow");

    if ((is_color1_bad)||(is_color2_bad)){
        std::cout << "Invalid color \n";
        return 1;
    }
    
    if (is_compared_color(color1, color2, "red", "blue")){
        result = "purple";
    }else if (is_compared_color(color1, color2, "red", "yellow")){
        result = "orange"; 
    }else if (is_compared_color(color1, color2, "yellow", "blue")){
        result = "green";
    }else {
        result = color1;
    }

    std::cout << "Result: " << result;

    return 0; 
}