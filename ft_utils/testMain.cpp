/*#include <iostream>
#include "equal.hpp"
#include <vector>

int main()
{
    std::vector<int> v1(1, 10);
    std::vector<int> v2(1, 5);

    bool equal = ft::equal(v1.begin(), v1.end(), v2.begin());

    if (equal)
        std::cout << "V1 and V2 are equal\n";
    else
        std::cout << "V1 and V2 are not equal\n";
}*/


/*
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
    ft::pair<int, int> *p2;

    // Assign values to p2
    p2 = &p1;
    // Print the values of p1 and p2
    std::cout << "p1: " << p1.first << ", " << p1.second << '\n';
    std::cout << "p2: " << p2->first << ", " << p2->second << '\n';

    std::cout << "--------------------------------------------------------" << std::endl;

    //std::cout << "p1 : " << reinterpret_cast<int>(p1) << std::endl;
    //std::cout << "p2 : " << reinterpret_cast<int>(p2) << std::endl;

    return 0;
}*/

#include <iostream>
#include <utility>  // for std::pair
//#include "pair.hpp"

int main()
{
    std::pair(std::string, int) p[] = {
            std::pair<std::string, int>("A", 1);
            std::pair<std::string, int>("B", 2);
            std::pair<std::string, int>("C", 3);
    };
    //std::cout << p[0].first << std::endl;
}