#include <iostream>#include "stack.hpp"int main(){    //Normal test    ft::stack<int> a;    ft::stack<int> b;    a.push(1);    a.push(2);    //a.pop();    std::cout << a.top() << std::endl;    std::cout << a.size() << std::endl;    if (a.empty())        std::cout << "stack a boş" << std::endl;    else        std::cout << "stack a dolu" << std::endl;    if (b.empty())        std::cout << "stack b boş" << std::endl;    else        std::cout << "stack b dolu" << std::endl;    //---------OPERATOR OVERLOAD----------    // == | != | < | <= | > | >=    ft::stack<int> s1;    s1.push(1);    s1.push(2);    s1.push(3);    ft::stack<int> s2;    s2.push(1);    s2.push(2);    s2.push(3);    if (s1 == s2)        std::cout << "s1 and s2 are equal" << std::endl;    else        std::cout << "s1 and s2 are not equal" << std::endl;    if (s1 != s2)        std::cout << "s1 and s2 are equal" << std::endl;    else        std::cout << "s1 and s2 are not equal" << std::endl;    if (s1 < s2)        std::cout << "s1 and s2 are equal" << std::endl;    else        std::cout << "s1 and s2 are not equal" << std::endl;    if (s1 <= s2)        std::cout << "s1 and s2 are equal" << std::endl;    else        std::cout << "s1 and s2 are not equal" << std::endl;    if (s1 > s2)        std::cout << "s1 and s2 are equal" << std::endl;    else        std::cout << "s1 and s2 are not equal" << std::endl;    if (s1 >= s2)        std::cout << "s1 and s2 are equal" << std::endl;    else        std::cout << "s1 and s2 are not equal" << std::endl;}