#pragma once

#include "base.hpp"

namespace ft{
    template<typename T, typename Container = ft::vector<T> >
        class stack{
            private:
                typedef Container container;
                typedef typename Container::const_reference const &const_reference;
                typedef Container container_type;
                typedef typename Container::size_type size_type;
                typedef typename Container::value_type value_type;
            protected:
                container _c;
            public:
                //explicit			stack(const container_type& ctnr = container_type()): c(ctnr) {}
                explicit stack(const container_type &container = container_type()): _c(container) {}
                //stack(container_type const &_c=container_type()): _c(_c) {}
                //stack(stack const &other): _c(other.container) {}
                //----------FUNCTIONS----------
                // empty | size | top | const &top | push | pop
                bool empty() const { return this->_c.empty();}
                size_type size() const { return this->_c.size();}
                void push(value_type x) {this->_c.push_back(x);}
                void pop() {_c.pop_back();}
                value_type &top() {return _c.back();}
                const value_type &top() const {return _c.back();}
                //---------OPERATOR OVERLOAD----------
                // == | != | < | <= | > | >=
                template <class T1, class Containe>
                friend bool operator==(const stack<T1, Containe>& x, const stack<T1, Containe>& y) {return x._c == y._c;};
                template <class T1, class Containe>
                friend bool operator!=(const stack<T1, Containe>& x, const stack<T1, Containe>& y);
                template <class T1, class Containe>
                friend bool operator<(const stack<T1, Containe>& x, const stack<T1, Containe>& y);
                template <class T1, class Containe>
                friend bool operator<=(const stack<T1, Containe>& x, const stack<T1, Containe>& y);
                template <class T1, class Containe>
                friend bool operator>(const stack<T1, Containe>& x, const stack<T1, Containe>& y);
                template <class T1, class Containe>
                friend bool operator>=(const stack<T1, Containe>& x, const stack<T1, Containe>& y);
        };
        template <class T, class C1>
        bool operator!=(const stack<T, C1> &x, const stack<T, C1> &y)
        {
            return (x._c != y._c);
        }
        template <class T, class C1>
        bool operator<(const stack<T, C1> &x, const stack<T, C1> &y)
        {
            return (x._c < y._c);
        }
        template<class T, class C1>
        bool operator<=(const stack<T, C1> &x, const stack<T, C1> &y)
        {
            return (x._c <= y._c);
        }
        template<class T, class C1>
        bool operator>(const stack<T, C1> &x, const stack<T, C1> &y)
        {
            return (x._c > y._c);
        }
        template<class T, class C1>
        bool operator>=(const stack<T, C1> &x, const stack<T, C1> &y)
        {
            return (x._c >= y._c);
        }
}
