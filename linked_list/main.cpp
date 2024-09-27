#include <iostream>

class LinkedList {
  struct LinkedListNode {
    int _data {-1};
    LinkedListNode *_next {nullptr};
  };

  LinkedListNode *_start {nullptr};
public:
  void add(int data) {
      // create a new node on the heap
      auto new_node = new LinkedListNode({._data=data});

      // check if list is empty
      if (_start == nullptr) {
          // attach node to start of chain
          _start = new_node;
      } else {
          LinkedListNode *node = _start;
          LinkedListNode *prev = nullptr;

          // look for the end of the chain
          while (node != nullptr) {
              prev = node;
              node = node->_next;
          }

          // attach new node to the end of the chain
          prev->_next = new_node;
      }
  }

  void insert(int index, int data) {
      // create new node to insert
      auto new_node = new LinkedListNode({data});

      // find index in chain
      LinkedListNode *node = _start;
      LinkedListNode *prev = nullptr;
      auto curr_idx = 0;

      while (node != nullptr) {

          // application specific - use index to find node
          if (curr_idx == index) {
              break;
          }

          curr_idx++;
          prev = node;
          node = node->_next;
      }

      // are we inserting at the start of the chain?
      if (prev == nullptr) {
          // inserting at the start
          new_node->_next = _start;
          _start = new_node;
      } else {
          // insert the node in the middle
          new_node->_next = prev->_next;
          prev->_next = new_node;
      }

  }

  void remove(int data) {

      LinkedListNode *node = _start;
      LinkedListNode *prev = nullptr;

      // find the node to delete
      while (node != nullptr) {
          // stop when the node is found
          if (node->_data == data) {
              break;
          }
          prev = node;
          node = node->_next;
      }

      // did I find the node I was looking for?
      if (node != nullptr) {

          // am I deleting the first node or another node?
          if (prev == nullptr) {
              // deleting the first node
              _start = node->_next;
          } else {
              // deleting another node

              // detach node from chain
              prev->_next = node->_next;
          }

          delete node;
      } else {
          std::cout << "node doesn't exist." << std::endl;
      }
  }

  friend std::ostream &operator<<(std::ostream &output, LinkedList &list);
};

std::ostream &operator<<(std::ostream &output, LinkedList &list) {

    auto node = list._start;

    // display all list data separated by spaces
    while (node != nullptr) {
        output << node->_data << " ";
        node = node->_next;
    }

    return output;
}

int main() {

    LinkedList list;

    // test 1 - add some data
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    std::cout << "Test 1" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list << std::endl;

    // test 2 - delete a node
    list.remove(3); // remove node with the value of 3

    std::cout << "Test 2" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list << std::endl;

    // test 3 - delete the first node
    list.remove(1);

    std::cout << "Test 3" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list << std::endl;

    // test 4 - insert a node in the middle of the chain
    list.insert(1, 9); // at index 1 insert the value 9

    std::cout << "Test 4" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list << std::endl;

    // test 5 - insert a node at the start of the chain
    list.insert(0, 0); // at index 0 insert the value 0

    std::cout << "Test 5" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list << std::endl;

    // test 6 - insert into an empty chain
    LinkedList list2;
    list2.insert(0, 12345); // at index 0 insert the value 12345

    std::cout << "Test 6" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list2 << std::endl;

    // test 7 - insert into an empty chain
    LinkedList list3;
    list3.insert(1, 666); // at index 1 insert the value 666

    std::cout << "Test 7" << std::endl;
    std::cout << "------" << std::endl;

    std::cout << list3 << std::endl;
    return 0;
}
