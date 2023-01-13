#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>
#include <list>
#include <alloca.h>
#include <algorithm>
#include <stddef.h>
#include <limits.h>
#include <memory>

#include "../ft_utils/is_integral.hpp"
#include "../revers_iterator/ReverseIterator.hpp"

using std::cout;
using std::endl;
namespace ft
{
    template<class T, class Allocator = std::allocator<T> > class vector{

    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef size_t size_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef ft::iterator<T*> iterator;
        typedef ft::iterator<const T*> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        allocator_type _alloc;
        pointer _data;
        size_type _size;
        size_type _capacity;
        // constructors
    public:
        explicit vector(const Allocator& alloc = Allocator())
        :    _alloc(alloc),
             _data(NULL),
             _size(0),
             _capacity(0) {}

        explicit vector(size_type n, const Allocator& alloc = Allocator())
        :    _alloc(alloc),
             _data(_alloc.allocate(n)),
             _size(n),
             _capacity(n) {}

        vector(size_type n, const T& x, const Allocator& alloc = Allocator()) {
            if (n < 0)
                throw std::out_of_range("Vector");
            _alloc = (alloc);
            _data = (_alloc.allocate(n));
            _size = (n);
            _capacity = (n);
            assign(n, x);
        }
        template<class In>
        vector(In first, In last, const Allocator& alloc = Allocator(),
               typename ft::enable_if<!ft::is_integral<In>::value, void>::type* = 0)
        :    _alloc(alloc),
            _size(0),
            _capacity(0),
            _data(NULL) {
            this->assign(first, last);
        }
        vector(const vector& x)
        :    _alloc(x.get_allocator()),
            _data(_alloc.allocate(x.capacity())),
            _size(x.size()),
            _capacity(x.capacity()) {
            std::uninitialized_copy(x._data, x._data + _size, _data);
        }
        vector(const vector& x, const Allocator& allocator)
        :    _alloc(allocator),
             _data(_alloc.allocate(x.capacity())),
             _size(x.size()),
             _capacity(x.capacity()) {
            std::uninitialized_copy(x._data, x._data + _size, _data);
        }
        // Destructor
        ~vector() {
            clear();
            _alloc.deallocate(_data, _capacity);
        }

        const_reverse_iterator rend() const { return reverse_iterator(begin()); }

        // element access
        reference at(size_type index) {
            if (index >= _size) {
                throw std::out_of_range("vector");
            }
            return (_data[index]);
        }

        const_reference at(size_type index) const {
            if (index >= _size) {
                throw std::out_of_range("vector");
            }
            return (_data[index]);
        }

        // push and pop
        void push_back(const T& value) {
            if (_size == _capacity)
                (!_capacity) ? this->reserve(1) : this->reserve(_capacity * 2);
            _data[_size] = value;
            ++_size;
          }

        void                    pop_back() { erase(end() - 1); }

        reference                front() { return _data[0]; }

        const_reference            front() const { return _data[0]; }

        reference                back() { return _data[_size - 1]; }

        reference                back() const { return _data[_size - 1]; }

        void                    swap(vector &other) { std::swap(*this, other); }

        //iterators
        pointer                 data() { return _data; }

        pointer                 data() const{ return _data; }

        iterator                 begin() { return iterator(_data); }

        const_iterator            begin() const { return iterator(_data); }

        reverse_iterator        rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator    rbegin() const { return reverse_iterator(end()); }

        iterator                end() { return (_data + _size); }

        const_iterator            end() const { return (_data + _size); }

        reverse_iterator        rend() { return reverse_iterator(begin()); }

        bool                    empty() const { return (_size == 0); }

        size_type                size() { return _size; }

        size_type                size() const { return _size; }

        size_type                capacity() { return _capacity; }

        size_type                max_size() const { return _alloc.max_size(); }

        size_type                capacity() const { return _capacity; }

        Allocator                get_allocator() { return _alloc; }

        Allocator                get_allocator() const { return _alloc; }

        // operator overloads

        reference                operator[](size_type index)                            { return _data[index]; }

        reference                operator[](size_type index) const                    { return _data[index]; }

        friend bool                operator!=(const vector& lhs, const vector& rhs)    { return (!(lhs == rhs)); }

        friend bool             operator<=(const vector& lhs, const vector& rhs)    { return (!(rhs < lhs)); }

        friend bool             operator>(const vector& lhs, const vector& rhs)        { return (rhs < lhs); }

        friend bool             operator>=(const vector& lhs, const vector& rhs)    { return (!(lhs < rhs)); }

        friend bool operator< (const vector& lhs, const vector& rhs) { //!!
            return ( std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
        }

        vector &operator=(const vector& x) {
            if (this == &x)
                return *this;
            this->clear();
            this->insert(this->end(), x.begin(), x.end());
            this->_size = x._size;
            this->_capacity = x._capacity;
            return (*this);
        }

        friend bool operator==(const vector& lhs, const vector& rhs) {
            if (lhs.size() != rhs.size())
                return (false);
            typename ft::vector<T>::const_iterator first1 = lhs.begin();
            typename ft::vector<T>::const_iterator first2 = rhs.begin();
            while (first1 != lhs.end()) {
                if (first2 == rhs.end() || *first1 != *first2)
                    return (false);
                ++first1;
                ++first2;
            }
            return (true);
        }


        // important functions to use //
        void clear() {
            for (size_type i = 0; i < _size; ++i) {
                _alloc.destroy(_data + i);
            }
            _size = 0;
        }

        void reserve(size_type count) {
            if (count > _capacity) {
                pointer new_data = _alloc.allocate(count);
                for (size_type i = 0; i < _size; ++i) {
                    new_data[i] = _data[i];
                }
                if (_data != NULL)
                    delete _data;
                _data = new_data;
                _capacity = count;
            }
        }

        void resize(size_type n, T value = T()) {
            if (n > this->max_size())
                throw (std::length_error("vector::resize"));
            else if (n < this->size())
            {
                while (this->size() > n)
                {
                    --_size;
                    _alloc.destroy(_data + _size);
                }
            }
            else
                this->insert(this->end(), n - this->size(), value);
          }
        //! insert functions
        
        iterator insert(const_iterator pos, const T& value) {
              size_type index = pos - begin();
            if (_size == _capacity)
                reserve(_capacity == 0 ? 1 : _capacity * 2);
              for (size_type i = _size; i > index; i--)
                _data[i] = _data[i - 1];
              _data[index] = value;
            ++_size;
            return begin() + index;
          }

          iterator insert(const_iterator pos, size_type count, const T& value) {
                size_type index = pos - begin();
                if (_size + count > _capacity)
                  reserve(std::max(_capacity == 0 ? count : _capacity * 2, _size + count));
                for (size_type i = _size + count - 1; i > index + count - 1; --i) {
                  _data[i] = _data[i - count];
            }
              for (size_type i = 0; i < count; ++i) {
                  _data[index + i] = value;
              }
                _size += count;
                return begin() + index;
          }

        template <typename In>
        typename ft::enable_if<!ft::is_integral<In>::value, void>::type
        insert(const_iterator pos, In first, In last) {
             size_type temp;
            size_type temp1;
            size_type index = pos - begin();
             size_type count = (last - first);
             temp = _capacity;
             temp1 = _size;
             if (_size + count > _capacity) {
                 reserve(std::max(_capacity == 0 ? count : _capacity * 2, _size + count));
             }
             for (size_type i = _size + count - 1; i > index + count - 1; --i) {
               _data[i] = _data[i - count]; // in c++ 11 they are using std::move or static_cast<T&&> but we are not allowed! amk
             }
            _size += count;
             try{
                std::copy(first, last, begin() + index);
             } catch (const char *a) {
                 _capacity = temp;
                 _size = temp1;
                 throw (a);
             }
         }

          iterator erase(const_iterator pos) {
              size_type index = pos - begin();
              for (size_type i = index; i < _size - 1; ++i) {
                _data[i] = _data[i + 1];
              }
              _alloc.destroy(_data + _size - 1);
              --_size;
              return begin() + index;
          }

        iterator erase(const_iterator first, const_iterator last) {

            size_type index = first - begin();
              size_type count = last - first;
              for (size_type i = index; i < _size - count; ++i) {
                _data[i] = _data[i + count];
              }
              for (size_type i = _size - count; i < _size; ++i) {
                _alloc.destroy(_data + i);
              }
              _size -= count;
              return begin() + index;
          }

        void assign(size_type count, const T& value) {
            clear();
            if (count > _capacity) {
                reserve(count);
            }
            for (size_type i = 0; i < count; ++i)
                this->push_back(value);
            _size = count;
        }

        template <class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
        assign(InputIterator first, InputIterator last) {
            clear();
            size_type count = last - first;
            if (count < 0) throw std::length_error("Vector");
            if (count > _capacity)
                reserve(count);
            for (size_type i = 0; i < count; ++i, ++first) {
                _data[i] = (*first);
            }
            _size = count;
        }
    };
};

#endif
