#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &output, const std::vector<int> &v) {
    for (auto &n : v) {
        output << n << " ";
    }
    return output;
}

void operator<<(std::vector<int> &v, const std::vector<int> &in) {
    for (auto &n : in) {
        v.push_back(n);
    }
}

class VectorDemo {
public:
  const int ROWS = 51;
  const int COLS = 51;
  std::vector<int> _nums;
  VectorDemo() : _nums(ROWS * COLS) {}
};

int main() {

    VectorDemo vd;

    std::cout << "basic vector...." << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;

    v.push_back(6);

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;

    std::cout << "---" << std::endl;

    std::cout << "vector with capacity..." << std::endl;
    std::vector<int> v2;
    v2.reserve(10);
    std::cout << "capacity: " << v2.capacity() << std::endl;
    std::cout << "size: " << v2.size() << std::endl;
    for (auto i = 0; i < 5; i++) {
        v2.push_back(i + 1);
    }

    std::cout << v2 << std::endl;
    std::cout << "capacity: " << v2.capacity() << std::endl;

    v2.push_back(6);

    std::cout << v2 << std::endl;
    std::cout << "capacity: " << v2.capacity() << std::endl;

    std::cout << "vector with increased elements..." << std::endl;

    v2 << std::vector({7, 8, 9, 10, 11});

    std::cout << v2 << std::endl;
    std::cout << "capacity: " << v2.capacity() << std::endl;
    std::cout << "size: " << v2.size() << std::endl;

    std::cout << "vector shrunk..." << std::endl;
    std::vector<int> v3; // initial allocation
    v3.reserve(100);  // second allocation of estimated size

    // fill in vector with unknown data amount
    for (auto i = 0; i < 56; i++) {
        v3.push_back(i + 1);
    }

    // will reallocate a new block of memory
    v3.shrink_to_fit();

    std::cout << "capacity: " << v3.capacity() << std::endl;
    std::cout << "size: " << v3.size() << std::endl;

    return 0;
}
