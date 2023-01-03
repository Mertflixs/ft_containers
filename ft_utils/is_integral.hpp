#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft{
    template <bool Condition, typename T = void> struct enable_if{};
    template <class T> struct enable_if<true, T> {typedef T type;};

    template <bool is_integral, typename T>
    struct is_integral_type{
        typedef T type;
        static const bool value = is_integral;
    };

    template <typename>
    struct is_integral : public is_integral_type<false, bool> {};

    template <>
    struct is_integral<char> : public is_integral_type<true, char> {};

    template <>
    struct is_integral<signed char> : public is_integral_type<true, signed char> {};

    template <>
    struct is_integral<unsigned char> : public is_integral_type<true, unsigned char> {};

    template <>
    struct is_integral<short> : public is_integral_type<true, short> {};

    template <>
    struct is_integral<unsigned short> : public is_integral_type<true, unsigned short> {};

    template <>
    struct is_integral<int> : public is_integral_type<true, int> {};

    template <>
    struct is_integral<unsigned int> : public is_integral_type<true, unsigned int> {};

    template <>
    struct is_integral<long> : public is_integral_type<true, unsigned int> {};

    template <>
    struct is_integral<unsigned long> : public is_integral_type<true, unsigned long> {};

    template <>
    struct is_integral<long long> : public is_integral_type<true, long long> {};

    template <>
    struct is_integral<unsigned long long> : public is_integral_type<true, unsigned long long> {};

    //less
    template <class T>
        struct less{
            bool operator()(const T &lhs, const T &rhs) {return lhs < rhs;}
        };
}

#endif