#include "../vector/vector.hpp"
#include "iterator_traits.hpp"
namespace ft
{
	template <typename Iterator> class reverse_iterator {
	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef std::input_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
	private:
		iterator_type _it;
	public:
		reverse_iterator() {};
		reverse_iterator(iterator_type it) {
			_it = it;
		}
		template<class other_it>
		reverse_iterator(const reverse_iterator<other_it>& x)
		: _it(x.base()) {}

		 reference operator*() const {
			iterator_type tmp = _it;
			return *(--tmp);
		}
		iterator_type base() const {
			return _it;
		}
		// increment and decrement operators
		reverse_iterator& operator++() {
			--_it;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			--_it;
			return tmp;
		}

		reverse_iterator& operator--() {
			++_it;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			++_it;
			return tmp;
		}

		reference operator[](difference_type n) const { return *(*this + n); }
		// operator overloads

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_it - n);
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_it + n);
		}

		friend bool operator==(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return (lhs.base() == rhs.base());
		}

		friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return !(lhs == rhs);
		}
		friend bool operator<(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return (rhs.base() < lhs.base());
		}

		friend bool operator>(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return (rhs < lhs);
		}

		friend bool operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return !(rhs < lhs);
		}

		friend bool operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return !(lhs < rhs);
		}

		friend reverse_iterator operator+(difference_type n, const reverse_iterator& it) {
			return (it + n);
		}

		reverse_iterator& operator-=(difference_type n) { _it += n; return *this; }

		friend difference_type operator-(const reverse_iterator& lhs, const reverse_iterator& rhs) {
			return rhs.base() - lhs.base();
		}
		reverse_iterator& operator+=(difference_type n) { _it -= n; return *this; }
	};
}