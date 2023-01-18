#pragma once

#include "../base.hpp"

namespace ft {

    template <class T>
    class reverse_iterator {
        T iterator;
    public:
        typedef T                                                					iterator_type;
        typedef typename iterator_traits<T>::difference_type     					difference_type;
        typedef typename iterator_traits<T>::value_type         					value_type;
        typedef typename iterator_traits<T>::reference           					reference;
        typedef typename iterator_traits<T>::const_reference     					const_reference;
        typedef typename iterator_traits<T>::pointer             					pointer;
        typedef typename iterator_traits<T>::const_pointer       					const_pointer;
        typedef typename iterator_traits<T>::iterator_category  					iterator_category;

        reverse_iterator(iterator_type value = nullptr) : iterator(value) 				{};
        ~reverse_iterator()										{};
        template <class U> reverse_iterator(const reverse_iterator<U>& other,
                                            typename ft::enable_if<std::is_convertible<U, T>::value>::type* = 0)
                : iterator(other.base()) 					{};
        reverse_iterator	&operator=(const reverse_iterator &obj)					{ iterator = obj.iterator; return *this; }
        iterator_type 		base() const								{ return iterator; }
        reference 		operator*()		                         			{ return *iterator; }
        pointer 		operator->()		                          			{ return &(operator*()); }
        reverse_iterator&	operator++()                     					{ --iterator; return *this; }
        reverse_iterator 	operator++(int)                    					{ reverse_iterator tmp(*this); iterator--; return tmp; }
        reverse_iterator& 	operator--()                      					{ ++iterator; return *this; }
        reverse_iterator 	operator--(int)                    					{ reverse_iterator tmp(*this); iterator++; return tmp; }
        reverse_iterator 	operator+(difference_type n) const 					{ return reverse_iterator(iterator - n); }
        reverse_iterator& 	operator+=(difference_type n)     					{ iterator -= n; return *this; }
        reverse_iterator 	operator-(difference_type n) const 					{ return reverse_iterator(iterator + n); }
        reverse_iterator& 	operator-=(difference_type n)     					{ iterator += n; return *this; }
        reference 		operator[](difference_type n) const       				{ return *(*this + n); }
        bool			operator==(reverse_iterator const &obj) const 				{ return iterator == obj.iterator; };
        bool			operator!=(reverse_iterator const &obj) const 				{ return iterator != obj.iterator; };
        bool 			operator<(reverse_iterator const &obj) const 				{ return iterator < obj.iterator; };
        bool 			operator>(reverse_iterator const &obj) const 				{ return iterator > obj.iterator; };
        bool 			operator<=(reverse_iterator const &obj) const 				{ return iterator <= obj.iterator; };
        bool 			operator>=(reverse_iterator const &obj) const 				{ return iterator >= obj.iterator; };
    };

}