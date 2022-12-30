#include "is_integral.hpp"
#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    std::cout << "is_integral<char>::value: " << is_integral<char>::value << std::endl;
    std::cout << "is_integral<signed char>::value: " << is_integral<signed char>::value << std::endl;
    std::cout << "is_integral<unsigned char>::value: " << is_integral<unsigned char>::value << std::endl;
    std::cout << "is_integral<short>::value: " << is_integral<short>::value << std::endl;
    std::cout << "is_integral<unsigned short>::value: " << is_integral<unsigned short>::value << std::endl;
    std::cout << "is_integral<int>::value: " << is_integral<int>::value << std::endl;
    std::cout << "is_integral<unsigned int>::value: " << is_integral<unsigned int>::value << std::endl;
    std::cout << "is_integral<long>::value: " << is_integral<long>::value << std::endl;
    std::cout << "is_integral<unsigned long>::value: " << is_integral<unsigned long>::value << std::endl;
    std::cout << "is_integral<long long>::value: " << is_integral<long long>::value << std::endl;
    std::cout << "is_integral<unsigned long long>::value: " << is_integral<unsigned long long>::value << std::endl;
    std::cout << "is_integral<std::string>::value: " << is_integral<std::string>::value << std::endl;
}