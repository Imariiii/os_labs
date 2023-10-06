#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        double dividend;
        if(!(iss >> dividend)) {
            dividend = 0;
        }
        double divisor;
        while (iss >> divisor) {
            dividend /= divisor;
            if (divisor == 0) {
                write(STDOUT_FILENO, &dividend, sizeof(double));
                return -1;
            }
        }
        write(STDOUT_FILENO, &dividend, sizeof(double));
    }
    return 0;
}