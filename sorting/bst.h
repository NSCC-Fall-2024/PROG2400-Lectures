#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <span>

struct Node {
  int _data {-1};
  Node *_left {nullptr};
  Node *_right {nullptr};
};

class BST {
  Node *_root {nullptr};

  void insert(int num, Node *&node);
  void print_tree(std::ostream &output, Node *&node, int indent);
  void save_array(std::span<int> array, Node *&node);

public:
  void insert(int num);
  void remove(int num);
  void save_array(std::span<int> array);

  friend std::ostream &operator<<(std::ostream &output, BST &bst);
};

std::ostream &operator<<(std::ostream &output, BST &bst);

#endif