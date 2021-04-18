#include <iostream>
#include "Handler.hpp"

const short choices[4] = {1, 2, 3, 4};

Handler handler;

int main() {

    std::cout << "Welcome to DNA storage. Please enter one of the following options:\n\n";
    std::cout << "\t1. Print\n\t2. Insert <pos> <lanac>\n\t3. Remove <pos> <len>\n\t4. Exit\n\n";

    short cmd = 0;
    bool loop = true;
    do {
        std::cout << "Your choice: "; 
        std::cin >> cmd;

        if(cmd == 1) {
            handler.print();
        } else

        if(cmd == 2) {
            handler.insert();
        } else

        if(cmd == 3) {
            handler.remove();
        } else

        if(cmd == 4) {
            std::cout << "Shutting down.\n";
            loop = false;
        } else std::cout << "Unknown command. Try again.\n";

    } while (loop);

    return 0;
};