#ifndef MAP_ITERATOR_UTILS_HPP
# define MAP_ITERATOR_UTILS_HPP

namespace ft{
    template <bool isConst, typename ifFalse, typename isTrue>
    struct chooseConst{};

    template <typename isFalse, typename isTrue>
    struct chooseConst<false, isFalse, isTrue> {typedef isFalse type;};

    template <typename isFalse, typename isTrue>
    struct chooseConst<true, isFalse, isTrue> {typedef isTrue type;};
}

#endif