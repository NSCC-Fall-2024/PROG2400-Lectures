#include <iostream>
#include <iomanip>

struct Node {
  int _data {-1};
  Node *_left {nullptr};
  Node *_right {nullptr};
};

class BST {
  Node *_root {nullptr};

  void insert(int num, Node *&node) {
      if (node == nullptr) {
          node = new Node({num});
      } else if (num < node->_data) {
          // insert to the left
          insert(num, node->_left);
      } else if (num > node->_data) {
          // insert to the right
          insert(num, node->_right);
      } else {
          std::cout << "Node value " << node->_data << " already exists." << std::endl;
      }
  }

  void print_tree(std::ostream &output, Node *&node, int indent) {
      if (node != nullptr) {
          print_tree(output, node->_right, indent + 8);
          output << std::setw(indent) << node->_data << std::endl;
          print_tree(output, node->_left, indent + 8);
      }
  }

public:
  void insert(int num) {
      insert(num, _root);
  }

  void remove(int num) {
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

  friend std::ostream &operator<<(std::ostream &output, BST &bst);
};

std::ostream &operator<<(std::ostream &output, BST &bst) {
    bst.print_tree(output, bst._root, 0);
    return output;
}

int main() {

    BST bst;

    // test 1 - add nodes to search tree

    std::cout << "Test 1 - adding nodes" << std::endl;
    std::cout << "---------------------" << std::endl;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    std::cout << bst << std::endl;

    // test 2 - delete node with no children
    std::cout << "Test 2 - delete node with no children" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    bst.remove(2);

    std::cout << bst << std::endl;

    // test 3 - delete node with one child
    std::cout << "Test 3 - delete node with one child" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    bst.remove(3);

    std::cout << bst << std::endl;

    // test 4 - delete node with two children
    std::cout << "Test 4 - delete node with two children" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    bst.remove(7);

    std::cout << bst << std::endl;

    // test 5 - delete root node
    std::cout << "Test 5 - delete root" << std::endl;
    std::cout << "--------------------" << std::endl;

    std::cout << "(removing 5)" << std::endl;
    bst.remove(5);
    std::cout << bst << std::endl;

    std::cout << "(removing 4)" << std::endl;
    bst.remove(4);
    std::cout << bst << std::endl;

    std::cout << "(removing 6)" << std::endl;
    bst.remove(6);
    std::cout << bst << std::endl;

    std::cout << "(removing 8)" << std::endl;
    bst.remove(8);
    std::cout << bst << std::endl;

    return 0;
}
