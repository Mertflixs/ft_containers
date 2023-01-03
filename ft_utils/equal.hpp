#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft{
    template<class Input1, class Input2>
    bool equal(Input1 first1, Input1 last1, Input2 first2)
    {
        for(; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
                return false;
        }
        return true;
    }
}

#endif