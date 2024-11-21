#include <iostream>
#include <iomanip>
#include "bst.h"

void BST::insert(int num, Node *&node) {
    if (node == nullptr) {
        node = new Node({num});
    } else if (num < node->_data) {
        // insert to the left
        insert(num, node->_left);
    } else if (num > node->_data) {
        // insert to the right
        insert(num, node->_right);
    }
}

void BST::print_tree(std::ostream &output, Node *&node, int indent) {
    if (node != nullptr) {
        print_tree(output, node->_right, indent + 8);
        output << std::setw(indent) << node->_data << std::endl;
        print_tree(output, node->_left, indent + 8);
    }
}

void BST::insert(int num) {
    insert(num, _root);
}

void BST::remove(int num) {
    Node *node = _root;
    Node *parent = nullptr;

    // search for node to delete
    while (node != nullptr) {
        if (num < node->_data) {
            parent = node;
            node = node->_left;
        } else if (num > node->_data) {
            parent = node;
            node = node->_right;
        } else {
            // found the node!
            break;
        }
    }

    // did we find the node?
    if (node == nullptr) return; // no, we didn't

    // is this a node that has two children?
    if (node->_left != nullptr && node->_right != nullptr) {
        // we have two children

        // use the right-most node in the left subtree
        // as the "successor" to the node that will removed

        // start on the left subtree
        auto successor = node->_left;

        // go as far right as possible
        parent = node;
        while (successor->_right != nullptr) {
            parent = successor;
            successor = successor->_right;
        }

        // swap data between successor and the node to delete
        node->_data = successor->_data;
        // the successor is now the node to delete
        node = successor;
    }

    // assume there is a child on the left
    Node *subtree = node->_left;

    // if not on left side, must be right side!
    if (subtree == nullptr) {
        subtree = node->_right;
    }

    // are we deleting a node on the left side? or the right side?
    if (parent == nullptr) {
        // a node with no parent must be the root node
        _root = subtree;
    } else if (parent->_left == node) {
        // on the left side!
        parent->_left = subtree;
    } else if (parent->_right == node) {
        // on the right side!
        parent->_right = subtree;
    }

    delete node;
}

void BST::save_array(std::span<int> array, Node *&node) {
    static auto i = 0;

    if (node != nullptr) {
        save_array(array, node->_right);
        array[i++] = node->_data;
        save_array(array, node->_left);
    }
}

void BST::save_array(std::span<int> array) {
    save_array(array, _root);
}

std::ostream &operator<<(std::ostream &output, BST &bst) {
    bst.print_tree(output, bst._root, 0);
    return output;
}
