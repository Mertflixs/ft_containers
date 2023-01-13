#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft{
    /**
     ********************ENABLE_İF**********************
     */
    template <bool Condition, typename T = void> struct enable_if{};
    template <class T> struct enable_if<true, T> {typedef T type;};

    template<class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

    /**
     ********************IS_INTEGRAL**********************
     */

    template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
    template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};

    /**
     ********************LESS**********************
     */

    template <class T>
    struct less
    {
        typedef T       first_argument_type;
        typedef T       second_argument_type;
        typedef bool    result_type;

        bool operator() (const T& x, const T& y) const {return x<y;}

    };

    /**
     ********************EQUAL**********************
     */

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

    /**
     ********************PAİR_AND_MAKE_PAİR**********************
     */

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

    /**
     ********************LEXICOGRAPHICAL**********************
     */

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

}

#endif