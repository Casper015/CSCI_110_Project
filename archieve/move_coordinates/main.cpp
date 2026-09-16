#include <iostream>
#include <string>

void north(int& y) { ++y; }
void south(int& y) { --y; }
void west(int& x) { --x; }
void east(int& x) { ++x; }

void showCoords(int x, int y)
{
    std::cout << "(" << x << "," << y << ")" << std::endl;
}

int main()
{
    std::string cmd;
    int x = 0, y = 0;
    
    do {
        showCoords(x,y);
        std::cin >> cmd;
        if (cmd == "north") north(y);
        else if (cmd == "south") south(y);
        else if (cmd == "west") west(x);
        else if (cmd == "east") east(x);
        else if (cmd == "northeast"){
            north(y);
            east(x);
        }
        else if (cmd == "northwest"){
            north(y);
            west(x);
        }
        else if (cmd == "southeast"){
            south(y);
            east(x);
        }
        else if (cmd == "southwest"){
            south(y);
            west(x);
        }
        else std::cout << "Huh?" << std::endl;
    } while (cmd != "Bye!");
}