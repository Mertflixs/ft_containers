#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1(1,10);
    std::vector<int> v2(1,5);

    bool equal = std::equal(v1.begin(), v1.end(), v2.begin());

    if (equal)
        std::cout << "V1 and V2 are equal\n";
    else
        std::cout << "V1 and V2 are not equal\n";
}


/*#include <iostream>
#include <utility>  // for std::pair

int main() {
    // Create a pair of integers, initialized to (10, 20)
    int a = 10;
    int b = 20;
    std::pair<int, int> p1(a, b);

    std::pair<int, float>p = std::make_pair(1, 3.14);
    std::cout << p.first << ' ' << p.second << '\n';

    // Create a pair of integers, initialized to the default values (0, 0)
    std::pair<int, int> p2;

    // Assign values to p2
    p2.first = 100;
    p2.second = 200;

    // Print the values of p1 and p2
    std::cout << "p1: " << p1.first << ", " << p1.second << '\n';
    std::cout << "p2: " << p2.first << ", " << p2.second << '\n';

    return 0;
}*/