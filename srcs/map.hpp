#pragma once

#include "base.hpp"

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class A = std::allocator<std::pair<const Key, T> > >
    class Map {
    public:
        typedef Key																		key_type;
        typedef T																		mapped_type;
        typedef ft::pair<const Key, T>													value_type;
        typedef std::size_t																size_type;
        typedef std::ptrdiff_t															difference_type;
        typedef Compare																	key_compare;
        typedef A																		allocator_type;
        typedef value_type&																reference;
        typedef const value_type&														const_reference;
        typedef typename allocator_type::pointer										pointer;
        typedef typename allocator_type::const_pointer									const_pointer;
        typedef ft::node_iterator<Node_<value_type>*, value_type>						iterator;
        typedef ft::node_iterator<const Node_<value_type>*, value_type>					const_iterator;
        typedef ft::reverse_iterator<iterator>											reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
        typedef typename allocator_type::template rebind<Node_<value_type> >::other		allocator_rebind_node;
        typedef typename allocator_type::template rebind<Tree<value_type> >::other		allocator_rebind_tree;

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

    private:
        allocator_type 											_allocator;
        allocator_rebind_tree										_allocator_rebind_tree;
        allocator_rebind_node										_allocator_rebind_node;
        Compare		 										_comp;
        Tree<value_type >*										_tree;

    public:
        Map() {
            _tree = _allocator_rebind_tree.allocate(sizeof(Tree<value_type>));
            _allocator_rebind_tree.construct(_tree);
        }

        explicit Map( const Compare& comp, const A& alloc = A()) : _comp(comp), _allocator(alloc) {
            _tree = _allocator_rebind_tree.allocate(sizeof(Tree<value_type>));
            _allocator_rebind_tree.construct(_tree);
        }

        template <class InputIt>
        Map(InputIt first, InputIt last,
            const Compare& comp = Compare(), const A& alloc = A()) : _allocator(alloc), _comp(comp) {
            _tree = _allocator_rebind_tree.allocate(sizeof(Tree<value_type>));
            _allocator_rebind_tree.construct(_tree);
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        Map(const Map &other) : _allocator(other._allocator), _comp(other._comp) {
            _tree = _allocator_rebind_tree.allocate(sizeof(Tree<value_type>));
            _allocator_rebind_tree.construct(_tree, *(other._tree));
            fillTree(other._tree->root);
        }

        Map& operator=(const Map& other) {
            if (this == &other)
                return *this;
            _comp = other._comp;
            _allocator = other._allocator;
            clearMap();
            _tree = _allocator_rebind_tree.allocate(sizeof(Tree<value_type>));
            _allocator_rebind_tree.construct(_tree, *other._tree);
            fillTree(other._tree->root);
            return *this;
        }


        ~Map() {
            clearMap();
        }

        T& at(const Key& key) {
            iterator tmp = find(key);
            return (tmp == end()) ? throw std::out_of_range("key not found") : tmp->second;
        }

        allocator_type 			get_allocator() const 						{ return _allocator; }
        const T&			at(const Key& key) const					{ return static_cast<const T>(at(key)); }
        T&				operator[](const Key& key) 					{ return insert(ft::make_pair(key, T())).first->second; }
        iterator 			begin()								{ return _tree->getBegin(); }
        const_iterator 			begin() const							{ return _tree->getBegin(); }
        iterator 			end()								{ return _tree->getEnd(); }
        const_iterator 			end() const							{ return _tree->getEnd(); }
        reverse_iterator 		rbegin()							{ return reverse_iterator(iterator(_tree->getLast())); }
        const_reverse_iterator 		rbegin() const							{ return const_reverse_iterator(const_iterator(_tree->getLast())); }
        reverse_iterator 		rend()								{ return reverse_iterator(iterator(_tree->getEnd())); }
        const_reverse_iterator 		rend() const							{ return const_reverse_iterator(const_iterator(_tree->getEnd())); }
        bool 				empty() const							{ return size() == 0; }
        size_type			size() const 							{ return _tree->m_size; }
        size_type			max_size() const 						{ return (std::min((size_type) std::numeric_limits<difference_type>::max(),
                                                                                        std::numeric_limits<size_type>::max() / (sizeof(Node_<value_type>) + sizeof(T*)))); }

        void clear() {
            clearMap();
            _tree = _allocator_rebind_tree.allocate(sizeof(Tree<value_type>));
            _allocator_rebind_tree.construct(_tree);
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
            return insertNode(_tree->root, value);
        }

        iterator insert(iterator hint, const value_type& value) {
            if (hint == end()) {
                return insertNode(_tree->root, value).first;
            }
            else {
                if (hint->first > value.first)
                {
                    iterator prev = hint;
                    --prev;
                    while (prev != end() && prev->first >= value.first){
                        --hint;
                        --prev;
                    }
                } else if (hint->first < value.first) {
                    iterator next = hint;
                    ++next;
                    while (next != end() && next->first <= value.first) {
                        ++hint;
                        ++next;
                    }
                }
            }
            return insertNode(hint.base(), value).first;
        }

        template< class InputIt >
        void insert( InputIt first, InputIt last ) {
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        void erase( iterator pos ) {
            iterator tmp = pos;
            _tree->deleteNode(tmp.base());
        }

        void erase( iterator first, iterator last ) {
            iterator tmp;

            for (; first != last ;) {
                tmp = first++;
                _tree->deleteNode(tmp.base());
            }
        }

        size_type erase( const key_type& key ) {
            return _tree->deleteNode(find(key).base());
        }

        void swap( Map& other ) {
            std::swap(_tree, other._tree);
        }

        size_type count( const Key& key ) const {
            return (find(key) == end()) ? 0 : 1;
        }

        iterator find( const Key& key ) {
            Node_<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->pair->first)
                    return (current);
                else
                    current = _comp(key, current->pair->first) ? current->left : current->right;
            }
            return end();
        }

        const_iterator find( const Key& key ) const {
            Node_<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->pair->first)
                    return (current);
                else
                    current = _comp(key, current->pair->first) ? current->left : current->right;
            }
            return end();
        }

        iterator lower_bound(const Key& key) {
            Node_<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->pair->first)
                    return iterator(current);
                else {
                    if (_comp(key, current->pair->first)) {
                        if (!current->left->NIL)
                            current = current->left;
                        else
                            return iterator(current);
                    }
                    else {
                        if (!current->right->NIL)
                            current = current->right;
                        else
                            return ++iterator(current);
                    }
                }
            }
            return end();
        }

        const_iterator lower_bound( const Key& key ) const {
            Node_<value_type> *current = _tree->root;

            while (!current->NIL) {
                if (key == current->pair.first)
                    return const_iterator(current);
                else {
                    if (_comp(key, current->pair.first)) {
                        if (!current->left->NIL)
                            current = current->left;
                        else
                            return const_iterator(current);
                    }
                    else {
                        if (!current->right->NIL)
                            current = current->right;
                        else
                            return ++const_iterator(current);
                    }
                }
            }
            return end();
        }

        iterator upper_bound(const Key& key) {
            iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (_comp(key, tmp->first)) ? tmp : ++tmp;
        }

        const_iterator upper_bound( const Key& key ) const {
            const_iterator tmp = lower_bound(key);

            return (tmp == end()) ? tmp : (_comp(key, tmp->first)) ? tmp : ++tmp;
        }

        ft::pair<iterator,iterator> equal_range( const Key& key ) {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        key_compare key_comp() const {
            return _comp;
        }

        ft::Map<Key, T, Compare, A>::value_compare value_comp() const {
            return value_compare(key_comp());
        }

        friend bool operator== (const Map &lhs, const Map &rhs) {
            return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        friend bool operator!= (const Map &lhs, const Map &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator< (const Map &lhs, const Map &rhs) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator> (const Map &lhs, const Map &rhs) {
            return rhs < lhs;
        }

        friend bool operator>= (const Map &lhs, const Map &rhs) {
            return !(lhs < rhs);
        }

        friend bool operator<= (const Map &lhs, const Map &rhs) {
            return !(rhs < lhs);
        }

    private:

        void fillTree(Node_<value_type> *t) {
            if (!t->left->NIL)
                fillTree(t->left);
            if (!t->NIL) insert(*t->pair);
            if (!t->right->NIL)
                fillTree(t->right);
        }

        void clearTree(Node_<value_type> *tmp) {
            if (tmp->NIL) return;
            if (!tmp->left->NIL) clearTree(tmp->left);
            if (!tmp->right->NIL) clearTree(tmp->right);
            _allocator_rebind_node.destroy(tmp);
            _allocator_rebind_node.deallocate(tmp, sizeof(Node_<value_type>));
        }

        void clearMap() {
            clearTree(_tree->root);
            _allocator_rebind_tree.destroy(_tree);
            _allocator_rebind_tree.deallocate(_tree, sizeof(Tree<value_type>));
        }

        ft::pair<iterator, bool> insertNode(Node_<value_type> *hint, const value_type& value) {
            Node_<value_type> *current, *parent, *x;

            current = hint;
            parent = 0;
            while (!current->NIL) {
                if (value.first == current->pair->first) return ft::make_pair(current, false);
                parent = current;
                current = _comp(value.first, current->pair->first) ?
                          current->left : current->right;
            }

            x = _allocator_rebind_node.allocate(sizeof(Node_<value_type>));
            _allocator_rebind_node.construct(x, value);
            x->parent = parent;
            x->left = &_tree->sentinel;
            x->right = &_tree->sentinel;
            x->color = 1;

            if (parent) {
                if (_comp(value.first, parent->pair->first))
                    parent->left = x;
                else
                    parent->right = x;
            } else {
                _tree->root = x;
            }

            _tree->insertFixup(x);

            if (x == _tree->getLast()) { _tree->sentinel.parent = x; }
            if (x == _tree->getBegin()) { _tree->sentinel.begin = x; }
            _tree->m_size++;
            return ft::make_pair(x, true);
        }

    };
}