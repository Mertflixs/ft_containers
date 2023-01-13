#pragma once

#include "../vector/vector.hpp"

namespace ft
{
	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator {
		private:
			T value;
		public:
			typedef T iterator_type;
			typedef typename iterator_traits<iterator_type>::value_type value_type;
			typedef typename iterator_traits<iterator_type>::pointer pointer;
			typedef typename iterator_traits<iterator_type>::const_pointer 	const_pointer;
			typedef typename iterator_traits<iterator_type>::reference reference;
			typedef typename iterator_traits<iterator_type>::const_reference const_reference;
			typedef typename iterator_traits<iterator_type>::difference_type difference_type;
			typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

			iterator(T value = NULL) : value(value)								{}
			~iterator()											{};
			template <class U> 
			iterator(const iterator<U>& other,typename std::enable_if<std::is_convertible<U,
			iterator_type>::value>::type* = 0) : value(other.base()) {};
			
			T base() const 									   { return value; }
			iterator	&operator=(const iterator &obj)        { this->value = obj.value; return *this; }
			iterator	operator++(int)	                       { iterator tmp(*this); value++; return tmp; }
			iterator	operator--(int)                        { iterator tmp(*this); value--; return tmp; }
			iterator	&operator++() 	                       { value++; return *this; }
			iterator	&operator--() 						   { value--; return *this; }
			int			operator-(iterator const &obj) const   { return value - obj.value; }
			int			operator+(iterator const &obj) const   { return (value + obj.value); }
			iterator	operator-(int n) const 				   { return iterator(this->value - n); }
			iterator	operator+(int n) const 			       { return iterator(this->value + n); }
			iterator	&operator-=(int n)                     { this->value -= n; return (*this); }
			iterator	&operator+=(int n)                     { this->value += n; return (*this); }
			reference 	operator*()  const                     { return *value; }
			pointer 	operator->() const                     { return &(*value); }
			reference 	operator[](const unsigned int index)   { return *(value + index); }
			friend bool	operator==(iterator const &x, iterator const &y) { return x.value == y.value; }
			bool		operator!=(iterator const &obj) const  { return value != obj.value; }
			bool 		operator<(iterator const &obj) const   { return value < obj.value; }
			bool 		operator>(iterator const &obj) const   { return value > obj.value; }
			bool 		operator<=(iterator const &obj) const  { return value <= obj.value; }
			bool 		operator>=(iterator const &obj) const  { return value >= obj.value; }
		};
}