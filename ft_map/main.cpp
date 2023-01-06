#include <iostream>
#include "test.hpp"
#include <map>

int main()
{
    ft::map<std::string, int> p;
    p["CPU"] = 10;
    std::cout << p["CPU"] << std::endl;
    /*map["apple"] = 1;
    map["banana"] = 2;
    map["orange"] = 3;

    // Print the elements in the map
    for (const auto& [key, value] : map) {
        std::cout << key << ": " << value << std::endl;
    }*/
}