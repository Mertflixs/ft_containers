#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft{
    template <class T1, class T2>
    struct pair{
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;
        pair() : first(), second() {}

        template<class x, class y>
            pair(const pair<x, y> &pr) : first(pr.first), second(pr.second) {}

        pair (const first_type &x, second_type &y) : first(x), second(y) {}

        pair &operator=(const pair &pr)
        {
            if (*this == pr)
                return *this;
            this->first = pr.first;
            this->second = pr.second;
            return (*this);
        }
    };

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {return pair<T1, T2>(x, y);}
}

#endif