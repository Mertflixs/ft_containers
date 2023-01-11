#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include "../ft_utils/is_integral.hpp"
#include "../ft_utils/pair.hpp"
#include "../ft_utils/equal.hpp"
#include "ft_avltree.hpp"
#include "../revers_iterator/iterator_traits.hpp"
#include "../revers_iterator/ReverseIterator.hpp"

namespace ft{
    template<class Key, class T, class Cmp = ft::less<Key>, class alloc = std::allocator<ft::pair<const Key, T> > >
    class map{
        private:
            ft::AVLTree<Key, T> *node;

        public:
            map() { node = new ft::AVLTree<Key, T>; }


    };
}

#endif