#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "map_iterator_utils.hpp"
#include "../ft_utils/pair.hpp"

namespace ft
{
    template<class Key, class T, class Compare, typename Node, bool B>
    class map_iterator
    {
        public:
            typedef Key                                                             key_type;
            typedef Compare                                                         key_compare;
            typedef T                                                               mapped_type;
            typedef ft::pair<const key_type, mapped_type>                           value_type;
            typedef long int                                                        difference_type;
            typedef size_t                                                          size_type;
            typedef std::bidirectional_iterator_tag                                 iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type   reference;
            typedef typename chooseConst<B, value_type&, const value_type&>::type   pointer;
            typedef Node*                                                           nodePtr;

        private:
            nodePtr     _node;
            nodePtr     _lastElem;
            key_compare _comp;

        public:

            /*------------------ CLASS FUNCTİONS ------------------*/
            /**
             * map_iterator default constructor
             */
            map_iterator(nodePtr node = 0, nodePtr lastElem = 0, const key_compare& comp = key_compare()) :
                        _node(node), _lastElem(lastElem), _comp(comp) {}

            /**
             * map_iterator copy constructor
             */

            map_iterator(const map_iterator<Key, T, Compare, Node, B> &copy){
                _node = copy.getNode();
                _lastElem = copy.getLastElem();
                _comp = copy.getCompare();
            }

            /**
             * map_iterator operator= overload
             */

            map_iterator& operator=(const map_iterator &assign)
            {
                if (this != &assign)
                {
                    _node = assign._node;
                    _lastElem = assign._lastElem;
                    _comp = assign._comp;
                }
                return (*this);
            }

            /**
             * map_iterator destructor
             */

            ~map_iterator() {}

            /*------------------ GETTER FUNCTİONS ------------------*/

            nodePtr getNode() const { return _node; }

            nodePtr getLastElem() const { return _lastElem; }

            nodePtr getCompare() const { return _comp; }

            /*------------------ POİNTER OPERATOR OVERLOAD ------------------*/

            reference operator*() const { return (_node->content); }
            poniter operator->() const { return (&_node->content); }

            map_iterator& operator++() {
                nodePtr previousNode = _node;

                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (*this);
                }

                while (_node != _lastElem && !_comp(previousNode->content.first, _node->content.first))
                {
                    if (_node->right && (_node->right == _lastElem ||
                            _comp(previousNode->content.first, _node->right->content.first))) {
                        _node = _node->right;
                        Node *tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node))) {
                            _node = tmp;
                        }
                    }
                    else {
                        _node = _node->parent;
                    }
                }
                return (*this);
            }

            map_iterator operator++() {
                map_iterator res(*this);

                if (_node == _lastElem) {
                    _node = _lastElem->right;
                    return (res);
                }

                while (_node != _lastElem && !_comp(res->first, _node->content.first)) {
                    if (_node->right && (_node->right == _lastElem ||
                            _comp(res->first, _node->right->content.first))) {
                        _node = _node->right;

                        Node *tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node))) {
                            _node = tmp;
                        }
                    }
                    else {
                        _node = _node->parent;
                    }
                }
                return (res);
            }

            map_iterator& operator--() {
                nodePtr previousNode = _node;

                if (_node == _lastElem) {
                    _node = _lastElem->left;
                    return (*this);
                }

                while (_node != _lastElem && !_comp(_node->content.first, previousNode->content.first)) {
                    if (_node->left && (_node->left == _lastElem ||
                            _comp(_node->left->content.first, previousNode->content.first))) {
                        _node = _node->left;

                        Node *tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node))) {
                            _node = tmp;
                        }
                    }
                    else{
                        _node = _node->parent;
                    }
                }
                return (*this);
            }

            map_iterator operator--(int) {
                map_iterator res(*this);

                if (_node == _lastElem) {
                    _node = _lastElem->left;
                    return res;
                }

                while (_node != _lastElem && !_comp(_node->content.first, res->first)) {
                    if (_node->left && (_node->left == _lastElem ||
                            _comp(_node->left->content.first, res->first))) {
                        _node = _node->left;

                        Node *tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node))) {
                            _node = tmp;
                        }
                    }
                    else {
                        _node = _node->parent;
                    }
                }
                return (res);
            }

            bool operator==(const map_iterator& it) const { return (it._node == _node); }
            bool operator!=(const map_iterator& it) const { return (it._node != _node); }

            /**
             * ------------------ PRİVATE MEMBER FUNCTIONS ------------------
             */
        private:
            Node *searchMinNode(Node *root)
            {
                if (root && root != _lastElem && root->left && root->left != _lastElem)
                    return searchMaxNode(root->left);
                return root;
            }

            Node *searchMaxNode(Node *root)
            {
                if (root && root != _lastElem && root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return (root);
            }

    };
}

#endif