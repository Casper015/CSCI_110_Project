#include <iostream>
#include <string>
#include <vector>


const std::string CSI = "\x1b[";
const std::string REVERSE = CSI + "7m";
const std::string NORMAL = CSI + "0m";

std::string cities[] = {
 "Tokyo",
 "Delhi",
 "Shanghai",
 "Dhaka",
 "Cairo",
 "Sao Paulo",
 "Mexico City",
 "Beijing",
 "Mumbai",
 "Osaka",
 "Chongqing",
 "Karachi",
 "Kinshasa",
 "Lagos",
 "Istanbul",
 "Kolkata",
 "Buenos Aires",
 "Manila",
 "Guangzhou",
 "Lahore",
 "Tianjin",
 "Bangalore",
 "Rio de Janeiro",
 "Shenzhen",
 "Moscow",
 "Chennai",
 "Bogota",
 "Jakarta",
 "Lima",
 "Bangkok",
 "Paris",
 "Hyderabad",
 "Nanjing",
 "Luanda",
 "Seoul",
 "Chengdu",
 "London",
 "Ho Chi Minh City",
 "Tehran",
 "Nagoya",
 "Xi-an",
 "Ahmedabad",
 "Kuala Lumpur",
 "Wuhan",
 "Suzhou",
 "Hangzhou",
 "Surat",
 "Dar es Salaam",
 "New York City",
};

std::string toLower(std::string s){
    std::string res;
    for (auto &c : s){
        if (isupper(c)){ // c >= 'A' && c <= 'Z'
            c = tolower(c);  // c + '32'
        }
    }
    return s;
}

std::vector<std::string> searchCities(const std::string& pattern) {
    std::vector<std::string> matches;
    for (auto city : cities){
        auto cityLower = toLower(city);
        auto patternLower = toLower(pattern);
        auto pos = cityLower.find(patternLower);
        if (pos != std::string::npos){
                std::string s1 = city.substr(0, pos);
                std::string s2 = city.substr(pos, pattern.length());
                std::string s3 = city.substr(pos + pattern.length());
                std::string cityHighlight = s1 + REVERSE + s2 + NORMAL + s3;
                matches.push_back(cityHighlight);
            }
        }
    return matches;
    }


int main(){

    while(true){
        std::cout << "City: ";
        std::string pattern;
        getline(std::cin, pattern);

        std::vector <std::string> matches = searchCities(pattern);
        for(auto m : matches){
            std::cout<< m << std::endl;
        }
        
        std::cout << matches.size() << " cities found." << std::endl << std::endl;
    }
}
