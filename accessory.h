#ifndef TASK3_ACCESSORY_H
#define TASK3_ACCESSORY_H

#include <string>
#include <vector>
#include <sstream>

auto string_to_int = [](const std::string& s) {return std::stoi(s);};
auto string_to_double = [](const std::string& s) {return std::stod(s);};
auto int_to_string = [](const int i) {return std::to_string(i);};

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void help(){
    std::cout << "write exit for exit" << std::endl;
    std::cout << "write help for help" << std::endl;
    std::cout << "write area to calculate sum of areas" << std::endl;
    std::cout << "write index delete to remove figure by index" << std::endl;
    std::cout << "write go to show common function 1-3 for all array" << std::endl;
    std::cout << "input format x_1 y_1 x_2 y_2 ... x_n y_n figure" << std::endl;
    std::cout << "" << std::endl;
}

#endif //TASK3_ACCESSORY_H
