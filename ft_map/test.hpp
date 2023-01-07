#ifndef TEST_HPP
# define TEST_HPP

# include <functional>
# include <cmath>

# include "../ft_utils/is_integral.hpp"
# include "../ft_utils/pair.hpp"
# include "../ft_utils/equal.hpp"
# include "../revers_iterator/test_map_iterator.hpp"
# include "../revers_iterator/test_reverse_map_iterator.hpp"

namespace ft{
    template<class Key, class T, class cmp = ft::less<Key>, class allo = std::allocator<ft::pair<const Key, T> > >
    class map{

        private:
            struct node{
                ft::pair<const Key, T> content;
                node *parent;
                node *left;
                node *right;
            };

        public:
            typedef Key key_type;
            typedef cmp key_compare;
            typedef allo   allocator_type;
            typedef T   mapped_type;
            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef long int    difference_type;
            typedef size_t  size_type;
            typedef T&  reference;
            typedef const T&    const_reference;
            typedef T*  pointer;
            typedef const T*    const_pointer;
            typedef typename ft::map_iterator<Key, T, cmp, node, false> iterator;
            typedef typename ft::map_iterator<Key, T, cmp, node, true> const_iterator;
            typedef typename ft::rev_map_iterator<Key, T, cmp, node, false> reverse_iterator;
            typedef typename ft::rev_map_iterator<Key, T, cmp, node, true> const_reverse_iterator;

            class value_compare {
                friend class map;
                protected:
                    key_compare comp;

                    value_compare(cmp c) : comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;

                    bool operator()(const value_type &x, const value_type &y) const
                    {
                        return comp(x.first, y.first);
                    }
            };

        private:
            node *_root;
            node *_lastElem;
            size_type _size;
            allocator_type _allocPair;
            key_compare _comp;
            std::allocator<node> _allocNode;

        public:

            //constructor
            explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
                    _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;
            }
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
                    _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;

                for (; first != last; ++first)
                    insert(*first);
            }
            map(const map& x) :
                    _size(0), _allocPair(x._allocPair), _comp(x._comp), _allocNode(x._allocNode)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;

                for (const_iterator it = x.begin(); it != x.end(); ++it)
                    insert(*it);
            }
            ~map()
            {
                clear();
                deallocateNode(_lastElem);
            }
            map& operator=(const map& x)
            {
                map tmp(x);
                this->swap(tmp);

                return *this;
            }
/*
            //value_compare !!!!!!!!binary_function yazılacak
            class value_compare : public std::binary_function<value_type, value_type, bool>{
                friend class map;
            protected:
                cmp = key_cmp;
                value_compare(cmp c) : key_cmp(c) {}
            public:
                bool operator()(const T& x, const T& y) const {return key_cmp(x.first, y.first);}
            };*/
            key_compare key_comp() const;
            value_compare value_comp() const;

            //iterator:
            iterator begin()                        { return iterator(_lastElem->right, _lastElem, _comp); }

            /**
            *   @return     A const_iterator pointing to the first node of the map (minimum value).
            */
            const_iterator begin() const            { return const_iterator(_lastElem->right, _lastElem, _comp); }

            /**
            *   @return     An iterator pointing after the last map's element, on a dummy node.
            *               Access this iterator will result in undefined behavior.
            */
            iterator end()                          { return iterator(_lastElem, _lastElem, _comp); }

            /**
            *   @return     A const_iterator pointing after the last map's element, on a dummy node.
            *               Access this iterator will result in undefined behavior.
            */
            const_iterator end() const              { return const_iterator(_lastElem, _lastElem, _comp); }

            /**
            *   @return     A reverse_iterator pointing to the last element of the map (maximum value).
            */
            reverse_iterator rbegin()               { return reverse_iterator(_lastElem->left, _lastElem, _comp); }

            /**
            *   @return     A const_reverse_iterator pointing to the last element of the map (maximum value).
            */
            const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastElem->left, _lastElem, _comp); }

            /**
            *   @return     A reverse_iterator pointing before the first map's element, on a dummy node.
            *               Access this iterator will result in undefined behavior.
            */
            reverse_iterator rend()                 { return reverse_iterator(_lastElem, _lastElem, _comp); }

            /**
            *   @return     A const_reverse_iterator pointing before the first map's element, on a dummy node.
            *               Access this iterator will result in undefined behavior.
            */
            const_reverse_iterator rend() const     { return const_reverse_iterator(_lastElem, _lastElem, _comp); }

            mapped_type& operator[](const key_type& k)
            {
                node* tmp = searchNode(_root, k);

                if (tmp)
                    return tmp->content.second;

                value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
                return insertNode(_root, val)->content.second;
            }

            //map operations:
            iterator find(const key_type& k); //find element with key k
            const_iterator find(const key_type& k) const;

            size_type count(const key_type& k) const; //find number of elements with key k

            iterator lower_bound(const key_type& k); //find first element with key k
            const_iterator lower_bound(const key_type& k) const;

            iterator upper_bound(const key_type& k);
            const_iterator upper_bound(const key_type& k) const;

            ft::pair<iterator, iterator> equal_range(const key_type& k);
            ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

            //list operations:
            /**
            *   Inserts one element if the key didn't already exist in map, starting from
            *   a certain position in the tree in order to optimize the insert process.
            *   Increases the size by one if the element was inserted.
            *
            *   @param position Hint for the position where the element can be inserted.
            *                   The function optimizes its insertion time if position points to
            *                   the element that will precede the inserted element.
            *   @param val      The pair<key, mapped value> to insert.
            *   @return         An iterator pointing to the newly element inserted if the key
            *                   wasn't existing in map, otherwise an iterator to the key already present.
            */
            iterator insert (iterator position, const value_type& val)
            {
                // If position key is higher than val, we need to decrease position
                // until we find the closest highest key from val in the tree
                if (position->first > val.first)
                {
                    iterator prev(position);
                    --prev;
                    while (prev != end() && prev->first >= val.first)
                    {
                        --position;
                        --prev;
                    }
                }

                    // Opposite case
                else if (position->first < val.first)
                {
                    iterator next(position);
                    ++next;
                    while (next != end() && next->first <= val.first)
                    {
                        ++position;
                        ++next;
                    }
                }

                // If the value already exist, and the tree isn't empty
                if (position != end() && val.first == position->first)
                    return position;

                ++_size;
                return iterator(insertNode(position.getNode(), val), _lastElem, _comp);
            }

            /**
            *   Inserts all elements between first and last (if they're not already existing),
            *   and increases the map' size.
            *
            *   @param first    An iterator pointing to the range's beginning (will be include).
            *   @param last     An iterator pointing to the range's end (will not be include).
            */
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
                         typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
            {
                while (first != last)
                    insert(*first++);
            }

            void erase (iterator position)
            {
                deleteNode(position.getNode(), position->first);
                --_size;
            }

            /**
            *   Removes from the map one element that matches a specific key. This reduces the size
            *   of the container by the number of elements removed (which can be only one).
            *
            *   @param k    The key to find in map and to remove.
            *   @return     Number of elements erased. Since you can't have twice the same key in
            *               map, this is either 0 or 1.
            */
            size_type erase (const key_type& k)
            {
                size_type ret = deleteNode(_root, k);
                _size -= ret;
                return ret;
            }

            /**
            *   Removes from the map a range of elements. Size is decreased by the number of
            *   elements removed.
            *
            *   @param first    An iterator pointing to the range's beginning (will be included).
            *   @param last     An iterator pointing to the range's end (will not be included).
            */
            void erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    iterator tmp(first);
                    ++first;
                    erase(tmp);
                }
            }

            void clear()        { erase(begin(), end()); }

            //capacity:
            size_type size() const; //number of elements
            size_type max_size() const; // size of largest possible map
            bool empty() const ;
            void swap(map &x) {
                swap(_root, x._root);
                swap(_lastElem, x._lastElem);
                swap(_size, x._size);
                swap(_comp, x._comp);
                swap(_allocPair, x._allocPair);
                swap(_allocNode, x._allocNode);
            }

            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */
        private:
            template<typename X>
            void swap(X &a, X &b){
                X tmp = a;
                a = b;
                b = tmp;
            }

            template<class T1, class T2>
            ft::pair<T1, T2> make_pair(T1 x, T2 y) const{
                return (ft::pair<T1, T2>(x,y));
            }

        /* ------------------ RB Tree Utils Function ------------------- */
        /* ------------------------------------------------------------- */

            node *createNode(const value_type &pair)
            {
                node *newNode = _allocNode.allocate(1);

                _allocPair.construct(&newNode->content, pair);
                newNode->parent = 0;
                newNode->left = 0;
                newNode->right = 0;

                return newNode;
            }

            void deallocateNode(node *del)
            {
                _allocPair.destroy(&del->content);
                _allocNode.deallocate(del, 1);
            }

            int heightTree(node *root, int height)
            {
                if (!root || root == _lastElem)
                    return height - 1;
                int leftHeight = heightTree(root->left, height + 1);
                int rightHeight = heightTree(root->right, height + 1);

                return leftHeight > rightHeight ? leftHeight : rightHeight;
            }

            node *searchNode(node *root, key_type key) const
            {
                // We reached a leaf or tree is empty
                if (!root || root == _lastElem)
                    return 0;

                // Case we find a match
                if (!_comp(root->content.first, key) && !_comp(key, root->content.first))
                    return root;

                // Recursive loop until we find key
                if (root->content.first > key && root->left && root->left != _lastElem)
                    return searchNode(root->left, key);
                else if (root->content.first < key && root->right && root->right != _lastElem)
                    return searchNode(root->right, key);

                // If we reach this step in the first searchNode func that was called
                // with root (first node of the tree), then element is missing.
                return 0;
            }

            node *searchMaxNode(node *root) const
            {
                if (root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            node *searchMinNode(node *root) const
            {
                if (root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }

            ft::pair<iterator,bool> insert (const value_type& val)
            {
                // Searches in the tree if val's key is already present and returns
                // an iterator to the key inside the tree if it's the case
                node* elemIsPresent = searchNode(_root, val.first);
                if (elemIsPresent)
                    return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastElem, _comp), false);

                // Inserts the pair in the tree and returns an iterator to its position
                ++_size;
                return ft::pair<iterator, bool>(iterator(insertNode(_root, val), _lastElem, _comp), true);
            }

            node *insertNode(node *insertPos, const value_type &pair)
            {
                if (_root == _lastElem)
                {
                    _root = createNode(pair);

                    _root->left = _lastElem;
                    _root->right = _lastElem;
                    _lastElem->left = _root;
                    _lastElem->right = _root;

                    return _root;
                }

                if (insertPos->content.first == pair.first)
                    return 0;

                // Recursive loop until we reach a leaf or fake last node (_lastElem)
                if (insertPos->content.first > pair.first &&
                    insertPos->left && insertPos->left != _lastElem)
                    return insertNode(insertPos->left, pair);
                else if (insertPos->content.first < pair.first &&
                         insertPos->right && insertPos->right != _lastElem)
                    return insertNode(insertPos->right, pair);

                // If we reach this step, we arrived to a leaf or to the max node / min node
                // of the tree (they're both linked to _lastElem): inserting new node to his correct position
                node *newNode = createNode(pair);

                // Case we reached a left or right leaf
                if (insertPos->content.first > newNode->content.first && !insertPos->left)
                    insertPos->left = newNode;
                else if (insertPos->content.first < newNode->content.first && !insertPos->right)
                    insertPos->right = newNode;

                    // Case we reach min node or max node, inserting the node between min / max
                    // and lastElem
                else if (insertPos->left && insertPos->content.first > newNode->content.first)
                {
                    newNode->left = _lastElem;
                    _lastElem->right = newNode;
                    insertPos->left = newNode;
                }
                else if (insertPos->right && insertPos->content.first < newNode->content.first)
                {
                    newNode->right = _lastElem;
                    _lastElem->left = newNode;
                    insertPos->right = newNode;
                }

                newNode->parent = insertPos;

                // Equilibrating the tree from newNode to root node
                balanceTheTree(&_root, newNode);

                return newNode;
            }

        bool deleteNode(node* deletePos, key_type key)
        {
            // Balance node will point to the first node impacted by the deletion (if we delete a node,
            // it will be the parent node; if we delete root, it will be one of his son).
            // We will then call balanceTheTree function to equilibrate the AVL tree
            node* balanceNode = 0;

            // The node to delete, looking from deletePos node until we match key
            node* del = searchNode(deletePos, key);

            // If element isn't present, nothing to delete
            if (!del)
                return false;

            /* --------------- CASE DELETING ROOT --------------- */
            // Case the node to delete is the root
            if (!del->parent)
            {
                // Root is the only node in the tree, it will be empty
                if (del->left == _lastElem && del->right == _lastElem)
                {
                    _root = _lastElem;
                    _lastElem->left = _lastElem;
                    _lastElem->right = _lastElem;
                }

                    // Case only one son (left or right, need to equilibrate the tree
                    // for only root)
                else if (del->left && del->right == _lastElem)
                {
                    balanceNode = del->parent;
                    _root = del->left;
                    del->left->parent = 0;

                    // Since the tree is AVL, if _root has only one son, this son is
                    // a leaf and has no left and right son. So the new root has to be
                    // llastElem from left and right side, but he's already
                    // linked to inked to _it from one side (in this case, left)
                    _lastElem->left = del->left;
                    del->left->right = _lastElem;
                }
                else if (del->left == _lastElem && del->right)
                {
                    balanceNode = del->parent;
                    _root = del->right;
                    del->right->parent = 0;

                    // Same explanation but with opposite side than just above
                    _lastElem->right = del->right;
                    del->right->left = _lastElem;
                }

                    // Case two sons, need to switch the key of the node to delete with the highest key
                    // in the left subtree, and to delete the node with this highest key in the left subtree
                else
                {
                    node* maxNode = searchMaxNode(del->left);

                    // Need to destroy then construct for copying const variable)
                    _allocPair.destroy(&del->content);
                    _allocPair.construct(&del->content, maxNode->content);

                    return deleteNode(del->left, maxNode->content.first);
                }
            }


                /* --------------- CASE DELETING NODE --------------- */
                // Case the node to delete is a leaf
            else if ((!del->left || del->left == _lastElem) && (!del->right || del->right == _lastElem))
            {
                balanceNode = del->parent;

                // Case min node / max node, linking differs for _lastElem
                node* linkToParent = 0;
                if (del->left == _lastElem || del->right == _lastElem)
                {
                    linkToParent = _lastElem;
                    del->content.first <= del->parent->content.first ?
                            _lastElem->right = del->parent : _lastElem->left = del->parent;
                }

                del->content.first <= del->parent->content.first ?
                        del->parent->left = linkToParent : del->parent->right = linkToParent;
            }

                // Case only one son (only left son or only right son)
            else if ((del->left && del->left != _lastElem) && (!del->right || del->right == _lastElem))
            {
                balanceNode = del->parent;

                del->content.first <= del->parent->content.first ?
                        del->parent->left = del->left : del->parent->right = del->left;
                del->left->parent = del->parent;

                // Case the node to delete is max node, need to relink _lastElem
                if (del->right == _lastElem)
                {
                    _lastElem->left = del->left;
                    del->left->right = _lastElem;
                }
            }
            else if ((!del->left || del->left == _lastElem) && del->right && del->right != _lastElem)
            {
                balanceNode = del->parent;

                del->content.first <= del->parent->content.first ?
                        del->parent->left = del->right : del->parent->right = del->right;
                del->right->parent = del->parent;

                // Case the node to delete is max node, need to relink _lastElem
                if (del->left == _lastElem)
                {
                    _lastElem->right = del->right;
                    del->right->left = _lastElem;
                }
            }

                // Case two sons, need to switch the key of the node to delete with the highest key
                // in the left subtree, and to delete the node with this highest key in the left subtree
            else
            {
                node* maxNode = searchMaxNode(del->left);

                // Need to destroy then construct for copying const variable)
                _allocPair.destroy(&del->content);
                _allocPair.construct(&del->content, maxNode->content);

                return deleteNode(del->left, maxNode->content.first);
            }

            // Equilibrating the tree from balanceNode to root node
            balanceTheTree(&_root, balanceNode);

            deallocateNode(del);
            return true;
        }

        int balanceOfSubtrees(node *node)
        {
            if (!node)
                return 0;
            return heightTree(node->left, 1) - heightTree(node->right, 1);
        }

        void rotateRight(node** root, node* nodeGoingDown)
        {
            //   P (nodeGoingUp) is going up and will replace Q (nodeGoingDown)
            //
            //
            //               Q                                 P              |
            //              / \     RIGHT ROTATION            / \             |
            //             P   C  ------------------->>>     A   Q            |
            //            / \                                   / \           |
            //           A   B                                 B   C          |

            node* nodeGoingUp = nodeGoingDown->left;

            // Left Q' son become right P' son
            nodeGoingDown->left = nodeGoingUp->right;

            // Case right son is NULL to prevent segfault
            if (nodeGoingUp->right)
                nodeGoingUp->right->parent = nodeGoingDown;

            // rigth P' son is Q
            nodeGoingUp->right = nodeGoingDown;

            // Parent P = Parent Q
            nodeGoingUp->parent = nodeGoingDown->parent;

            // Determinating if Q has a parent (if not, Q is root) and if it's the case,
            // determinating if it's left son or right son. Then updating Q's parent with
            // his new son, P node
            if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                nodeGoingDown->parent->left = nodeGoingUp;
            else if (nodeGoingDown->parent)
                nodeGoingDown->parent->right = nodeGoingUp;

            // Parent of Q is now P
            nodeGoingDown->parent = nodeGoingUp;

            // Updating root node if the rotation occured on root
            if (!nodeGoingUp->parent)
                *root = nodeGoingUp;
        }

        void rotateLeft(node** root, node* nodeGoingDown)
        {
            //   Q (nodeGoingUp) is going up and will replace P (nodeGoingDown)
            //
            //
            //               Q                                 P              |
            //              / \          LEFT ROTATION        / \             |
            //             P   C    <<<-------------------   A   Q            |
            //            / \                                   / \           |
            //           A   B                                 B   C          |

            node* nodeGoingUp = nodeGoingDown->right;

            // Right P' son become left Q' son
            nodeGoingDown->right = nodeGoingUp->left;

            // Case Q left son is NULL to prevent segfault
            if (nodeGoingUp->left)
                nodeGoingUp->left->parent = nodeGoingDown;

            // Left Q' son is now P
            nodeGoingUp->left = nodeGoingDown;

            // Parent Q = Parent P
            nodeGoingUp->parent = nodeGoingDown->parent;

            // Determinating if P has a parent (if not, P is root) and if it's the case,
            // determinating if it's left son or right son. Then updating P's parent with
            // his new son, Q node
            if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                nodeGoingDown->parent->left = nodeGoingUp;
            else if (nodeGoingDown->parent)
                nodeGoingDown->parent->right = nodeGoingUp;

            // Parent of P is now Q
            nodeGoingDown->parent = nodeGoingUp;

            // Updating root node if the rotation occured on root
            if (!nodeGoingUp->parent)
                *root = nodeGoingUp;
        }

        void balanceTheTree(node** root, node* node)
        {
            // Checking balance of subtrees every parents of this node until we
            // reach root node
            while (node)
            {
                int balance;

                // Right right case (right subtree is deeper, and right right subtree aswell)
                if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
                    rotateLeft(root, node);

                    // Right left case (if balance of right node == 0, no difference between right
                    // right case and and right left case)
                else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
                {
                    rotateRight(root, node->right);
                    rotateLeft(root, node);
                }

                    // Left left case (opposite of right right case)
                else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
                    rotateRight(root, node);

                    // Left right case (opposite of right left case)
                else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
                {
                    rotateLeft(root, node->left);
                    rotateRight(root, node);
                }
                node = node->parent;
            }
        }
    };
}

#endif