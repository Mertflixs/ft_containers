#include <iostream>
#include "stack.hpp"

int main()
{
    ft::stack<int> a;
    ft::stack<int> b;

    a.push(1);
    a.push(2);

    //a.pop();
    std::cout << a.top() << std::endl;
    std::cout << a.size() << std::endl;

    if (a.empty())
        std::cout << "stack a boş" << std::endl;
    else
        std::cout << "stack a dolu" << std::endl;

    if (b.empty())
        std::cout << "stack b boş" << std::endl;
    else
        std::cout << "stack b dolu" << std::endl;
}