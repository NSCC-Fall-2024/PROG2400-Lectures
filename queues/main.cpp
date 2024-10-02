#include <iostream>

struct Data {
  int _age {0};
  std::string _name {"no student name"};
  std::string _id {"no student id"};
};

std::ostream &operator<<(std::ostream &output, const Data &data) {
    output << "Name: " << data._name << ", ";
    output << "ID: " << data._id << ", ";
    output << "Age: " << data._age << std::endl;
    return output;
}

class Queue final {

  struct Node;

  class SmartNodePtr {
    Queue::Node *_node {nullptr};
  public:
    explicit SmartNodePtr(Queue::Node *node) : _node(node) {}
    ~SmartNodePtr() {
        delete _node;
    }

    static SmartNodePtr make_smartnodeptr(Data data) {
        return SmartNodePtr(new Queue::Node({data}));
    }

    bool operator==(Queue::Node *n) const { return _node == n; }
    bool operator!=(Queue::Node *n) const { return _node != n; }
    Queue::Node *operator->() const noexcept { return _node; }
  };

  struct Node {
    Data _data;
    SmartNodePtr _next {nullptr};

    friend class SmartNodePtr;
  };

  SmartNodePtr _front {nullptr};
  SmartNodePtr _back {nullptr};
  size_t _size {0};
public:
  void push_back(Data data) {
      //auto node = new Node {data};
      auto node = SmartNodePtr::make_smartnodeptr(data);

      // are we adding to an empty queue?
      if (_front == nullptr) {
          // yes! it is empty
          _front = node;
      } else {
          // no! there is a node already.
          _back->_next = node;
      }
      _back = node;

      _size++;
  }

  void pop_front() {

      // can't remove from an empty queue
      if (_front == nullptr) return;

      auto node = _front;

      _front = _front->_next;

      // update the back if we are deleting the last node
      if (_front == nullptr) _back = nullptr;

      //delete node;

      _size--;
  }

  [[nodiscard]] inline Data peek() const {
      return _front != nullptr ? _front->_data : Data();
  }

  [[nodiscard]] inline size_t size() const {
      return _size;
  }

  [[nodiscard]] inline bool empty() const {
      return _size == 0;
  }

  friend std::ostream &operator<<(std::ostream &output, const Queue &queue);
};

std::ostream &operator<<(std::ostream &output, const Queue &queue) {

    auto node = queue._front;
    while (node != nullptr) {
        output << node->_data << " ";
        node = node->_next;
    }
    return output;
}

int main() {

    Queue queue;

    // test 1: add nodes to the queue
    std::cout << "Test 1: adding nodes" << std::endl;
    std::cout << "--------------------" << std::endl;

    queue.push_back({20, "John", "W1111111"});
    queue.push_back({25, "Jane", "W2222222"});
    queue.push_back({27, "Jill", "W3333333"});
    queue.push_back({18, "Jack", "W4444444"});
    queue.push_back({19, "Mark", "W5555555"});

    std::cout << queue << std::endl;

    // test 2: look at the front of the queue
    std::cout << "Test 2: Peeking at the front node" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::cout << queue.peek() << std::endl;

    // test 3: remove a node from the front of the queue
    std::cout << "Test 3: Pop off node at front of queue" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    queue.pop_front();
    std::cout << queue << std::endl;

    // test 4: remove all nodes from the queue
    std::cout << "Test 4: Pop all nodes in queue" << std::endl;
    std::cout << "------------------------------" << std::endl;

    while (!queue.empty()) {
        std::cout << queue << std::endl;
        queue.pop_front();
    }

    return 0;
}
