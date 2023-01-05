#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include "../ft_utils/is_integral.hpp"
#include "../ft_utils/pair.hpp"
#include "../ft_utils/equal.hpp"
#include "../revers_iterator/iterator_traits.hpp"
#include "../revers_iterator/ReverseIterator.hpp"

namespace ft{
    template<class Key, class T, class Cmp = ft::less<Key>, class alloc = std::allocator<ft::pair<const Key, T> > >
    class map{
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const Key, T> value_type;
            typedef Cmp key_compare;
            typedef alloc allocator_type;
            typedef typename alloc::reference reference;
            typedef typename alloc::const_reference const_reference;
            typedef implementation_defined1 iterator;
            typedef implementation_defined2 const_iterator;
            typedef typename alloc::size_type size_type;
            typedef typename alloc::difference_type difference_type;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            //constructor
            explicit map(const Cmp& = Cmp(), const alloc& = alloc());
            template<class In> map(In first, In last, const Cmp& = Cmp(), const alloc& = alloc());
            map(const map&);
            ~map();
            map& operator=(const map&);

            //value_compare !!!!!!!!binary_function yazılacak
            class value_compare : public std::binary_function<value_type, value_type, bool>{
                friend class map;
                protected:
                    Cmp = cmp;
                    value_compare(Cmp c) : cmp(c) {}
                public:
                    bool operator()(const T& x, const T& y) const {return cmp(x.first, y.first);}
            };
            key_compare key_comp() const;
            value_compare value_comp() const;

            //iterator:
            iterator begin();
            const_iterator begin() const;

            iterator end();
            const_iterator end() const;

            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;

            reverse_iterator rend();
            const_reverse_iterator rend() const;

            mapped_type& operator[](const key_type& k); // tanımlanacak

            //map operations:
            iterator find(const key_type& k); //find element with key k
            const_iterator find(const key_type& k) const;

            size_type count(const key_type& k) const; //find number of elements with key k

            iterator lower_bound(const key_type& k); //find first element with key k
            const_iterator lower_bound(const key_type& k) const;

            iterator upper_bound(const key_type& k);
            const_iterator upper_bound(const key_type& k) const;

            ft::pair<iterator, iterator> equal_range(const key_type& k);
            ft_pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

            //list operations:
            ft::pair<iterator, bool> insert(const value_type& val); //insert (key, value) pair
            iterator insert(iterator pos, const value_type& val); //pos is just a hint
            template<class In> void insert(In first, In last); //insert elements from sequence

            void erase(iterator pos); //erase the element pointed to
            size_type erase(const key_type& k); //erase element with key k(if present)
            void erase(iterator first, iterator last); //erase range
            void clear();

            //capacity:
            size_type size() const; //number of elements
            size_type max_size() const // size of largest possible map
            bool empty() const {return size()==0;}
            void swap(map&);
    };
}

#endif