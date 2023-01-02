#include <iostream>
//#include <utility>  // for std::pair
#include "pair.hpp"

int main() {
    // Create a pair of integers, initialized to (10, 20)
    int a = 10;
    int b = 20;
    ft::pair<int, int> p1(a, b);

    ft::pair<int, float>p = ft::make_pair(1, 3.14);
    std::cout << p.first << ' ' << p.second << '\n';

    ft::pair<char, float>g = ft::make_pair('C', 3.14159);
    std::cout << g.first << ' ' << g.second << '\n';

    ft::pair<int, int> p3(a, b);
    std::cout << p3.first << ' ' << p3.second << '\n';

    // Create a pair of integers, initialized to the default values (0, 0)
    ft::pair<int, int> p2;

    // Assign values to p2
    p2.first = 100;
    p2.second = 200;

    // Print the values of p1 and p2
    std::cout << "p1: " << p1.first << ", " << p1.second << '\n';
    std::cout << "p2: " << p2.first << ", " << p2.second << '\n';

    return 0;
}