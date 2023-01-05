#ifndef BSTT_HPP
# define BSTT_HPP

#include "../vector/vector.hpp"
#include "../ft_utils/pair.hpp"
#include <iostream>

template<typename k, typename v>
class TreeNode{
    private:
        ft::pair<k, v>val;
    public:
        k value;

        TreeNode<k, v> *left;
        TreeNode<k, v> *right;

        TreeNode()
        {
            value = NULL;
            left = NULL;
            right = NULL;
        }
        TreeNode(ft::pair<k, v> &x)
        {
            value = x.first;
            val = x;
            left = NULL;
            right = NULL;
        }
};

template<typename T1, typename T2>
class AVLTree {
    public:
        TreeNode<T1, T2> *root;
        AVLTree() {root = NULL;}

        bool isTreeEmpty() {
            if (root == NULL)
                return true;
            else
                return false;
        }

        int height(TreeNode<T1, T2> *r) {
            if (r == NULL)
                return -1;
            else {
                int lheight = height(r->left);
                int rheight = height(r->right);
                if (lheight > rheight)
                    return (lheight + 1);
                else
                    return (rheight + 1);
            }
        }

        int getBalanceFactor(TreeNode<T1, T2> *n) {
            if (n == NULL)
                return -1;
            return height(n->left) - height(n->right);
        }

        TreeNode<T1, T2> *rightRotate(TreeNode<T1, T2> *y) {
            TreeNode<T1, T2> *x = y->left;
            TreeNode<T1, T2> *z = x->right;
            x->right = y;
            y->left = z;
            return x;
        }

        TreeNode<T1, T2> *leftRotate(TreeNode<T1, T2> *x) {
            TreeNode<T1, T2> *y = x->right;
            TreeNode<T1, T2> *z = y->left;

            y->left = x;
            x->right = z;
            return y;
        }

        TreeNode<T1, T2> *insert(TreeNode<T1, T2> *r, TreeNode<T1, T2> *new_node) {
            if (r == NULL)
            {
                r = new_node;
                std::cout << "Value inserted successfully" << std::endl;
                return r;
            }
            if (new_node->value < r->value) {
                r->left = insert(r->left, new_node);
            } else if (new_node->value > r->value) {
                r->right = insert(r->right, new_node);
            } else {
                std::cout << "No duplicate values allowed!" << std::endl;
                return r;
            }

            int bf = getBalanceFactor(r);
            if (bf > 1 && new_node->value < r->left->value)
                return rightRotate(r);

            if (bf < -1 && new_node->value > r->right->value)
                return leftRotate(r);

            if (bf > 1 && new_node->value > r->left->value) {
                r->left = leftRotate(r->left);
                return rightRotate(r);
            }

            if (bf < -1 && new_node->value < r->right->value) {
                r->right = rightRotate(r->right);
                return leftRotate(r);
            }
            return r;
        }

        TreeNode<T1, T2> *minValueNode(TreeNode<T1, T2> *node) {
            TreeNode<T1, T2> *current = node;
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        TreeNode<T1, T2> *deleteNode(TreeNode<T1, T2> *r, int v) {
            if (r == NULL)
                return NULL;
            else if (v < r->value)
                r->left = deleteNode(r->left, v);
            else if (v > r->value)
                r->right = deleteNode(r->right, v);
            else {
                if (r->left == NULL) {
                    TreeNode<T1, T2>* temp = r->right;
                    delete r;
                    return temp;
                } else if (r->right == NULL) {
                    TreeNode<T1, T2>* temp = r->left;
                    delete r;
                    return temp;
                } else {

                    TreeNode<T1, T2>* temp = minValueNode(r->right);
                    r->value = temp->value;
                    r->right = deleteNode(r->right, temp->value);
                }
            }

            int bf = getBalanceFactor(r);

            if (bf == 2 && getBalanceFactor(r->left) >= 0)
                return rightRotate(r);

            else if (bf == 2 && getBalanceFactor(r->left) == -1) {
                r->left = leftRotate(r->left);
                return rightRotate(r);
            }

            else if (bf == -2 && getBalanceFactor(r->right) <= -0)
                return leftRotate(r);

            else if (bf == -2 && getBalanceFactor(r->right) == 1) {
                r->right = rightRotate(r->right);
                return leftRotate(r);
            }
            return r;
        }

        TreeNode<T1, T2>* iterativeSearch(int v) {
            if (root == NULL)
                return root;
            else {
                TreeNode<T1, T2>* temp = root;
                while (temp != NULL) {
                    if (v == temp->value) {
                        return temp;
                    } else if (v < temp->value) {
                        temp = temp->left;
                    } else {
                        temp = temp->right;
                    }
                }
                return NULL;
            }
        }

        TreeNode<T1, T2>* recursiveSearch(TreeNode<T1, T2>* r, int val) {
            if (r == NULL || r->value == val)
                return r;
            else if (val < r->value)
                return recursiveSearch(r->left, val);
            else
                return recursiveSearch(r->right, val);
        }
};

#endif