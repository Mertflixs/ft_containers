#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include "../ft_utils/is_integral.hpp"
#include "../ft_utils/pair.hpp"
#include "../ft_utils/equal.hpp"
#include "ft_avltree.hpp"
#include "../revers_iterator/iterator_traits.hpp"
#include "../revers_iterator/ReverseIterator.hpp"

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class A = std::allocator<std::pair<const Key, T> > >
    class Map {
    public:
        typedef Key											key_type;
        typedef T											mapped_type;
        typedef ft::pair<const Key, T>									value_type;
        typedef std::size_t										size_type;
        typedef std::ptrdiff_t										difference_type;
        typedef Compare											key_compare;
        typedef A											allocator_type;
        typedef value_type&										reference;
        typedef const value_type&									const_reference;
        typedef typename allocator_type::pointer							pointer;
        typedef typename allocator_type::const_pointer							const_pointer;
        typedef ft::node_iterator<Node_<value_type>*, value_type>					iterator;
        typedef ft::node_iterator<const Node_<value_type>*, value_type>					const_iterator;
        typedef ft::reverse_iterator<iterator>								reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
        typedef typename allocator_type::template rebind<Node_<value_type> >::other			allocator_rebind_node;
        typedef typename allocator_type::template rebind<Tree<value_type> >::other			allocator_rebind_tree;

        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class Map;
        protected:
            key_compare comp;
            value_compare(key_compare c) : comp(c) {}
        public:
            bool operator()(const value_type& __x, const value_type& __y) const {
                return comp(__x.first, __y.first);
            }
        };
}

#endif