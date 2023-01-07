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

            map_iterator& operator++() {}

            map_iterator operator++() {}

            map_iterator& operator--() {}

            map_iterator operator--(int) {}

            bool operator==(const map_iterator& it) const { return (it._node == _node); }
            bool operator!=(const map_iterator& it) const { return (it._node != _node); }

            /**
             * ------------------ PRİVATE MEMBER FUNCTIONS ------------------
             */
        private:
            Node *searchMixNode(Node *root)
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